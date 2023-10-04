//========================================
// 
// セットブロック処理
// 
//========================================
// *** block.cpp ***
//========================================
#include "set_block.h"
#include "block.h"
#include "../manager.h"
#include "../renderer.h"
#include "../camera.h"
#include "model.h"
#include "fcst_block.h"
#include "../input.h"
#include "../imgui_block.h"
//#include "../csv_file.h"

//========================================
// コンストラクタ
//========================================
CSetBlock::CSetBlock(int nPriority) : CObjectX(nPriority)
{
	m_Set.pos = INIT_D3DXVECTOR3;
	m_Set.rot = INIT_D3DXVECTOR3;
	m_Set.col = INIT_D3DXCOLOR;
	m_Set.nType = 0;
	m_Set.nNumX = 0;
	m_Set.nNumY = 0;
	m_Set.nNumZ = 0;
	m_Set.fWidth = INIT_FLOAT;
	m_Set.fHeight = INIT_FLOAT;
	m_Set.fDepth = INIT_FLOAT;
}

//========================================
// デストラクタ
//========================================
CSetBlock::~CSetBlock()
{

}

//========================================
// 生成
//========================================
CSetBlock *CSetBlock::Create(void)
{
	CSetBlock *pBlock = NULL;

	if (pBlock != NULL)
	{
		return pBlock;
	}

	// ブロックの生成
	pBlock = new CSetBlock;

	// 初期化処理
	pBlock->Init();

	return pBlock;
}
//========================================
// 初期化
//========================================
HRESULT CSetBlock::Init(void)
{
	CObjectX::Init();

	// 種類の設定
	SetType(TYPE_SETBLOCK);

	m_Set.pos = INIT_D3DXVECTOR3;
	m_Set.rot = INIT_D3DXVECTOR3;
	m_Set.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	m_Set.nType = 0;
	m_Set.nNumX = 1;
	m_Set.nNumY = 1;
	m_Set.nNumZ = 1;

	// 設定
	SetModel(m_Set.nType);
	SetPos(m_Set.pos);
	SetRot(m_Set.rot);
	SetColor(m_Set.col);

	// 仮ブロックの配置
	CFcstBlock::Create(m_Set.nType, m_Set.pos, m_Set.rot);

	CCamera *pCamera = CManager::GetCamera();						// カメラ

	pCamera->SetPosR(D3DXVECTOR3(0.0f, 300.0f, 0.0f));

	return S_OK;
}

//========================================
// 終了
//========================================
void CSetBlock::Uninit(void)
{
	CObjectX::Uninit();
}

//========================================
// 更新
//========================================
void CSetBlock::Update(void)
{
	// --- 取得---------------------------------
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// キーボード
	CInputMouse *pInputMouse = CManager::GetInputMouse();			// マウス
	CInputJoypad *pInputJoypad = CManager::GetInputJoypad();		// ジョイパット
	CCamera *pCamera = CManager::GetCamera();						// カメラ
	CImgui *pInfo = CManager::GetImgui();							// Imgui


	m_Set.pos = pInfo->GetPos();	// 位置
	m_Set.rot = pInfo->GetRot();	// 向き
	int Type = pInfo->GetType();	// 種類
	int X = pInfo->GetNumX();		// ブロック数 X
	int Y = pInfo->GetNumY();		// ブロック数 Y
	int Z = pInfo->GetNumZ();		// ブロック数 Z

	// 設定
	SetModel(m_Set.nType);
	SetPos(m_Set.pos);
	SetRot(m_Set.rot);
	SetColor(m_Set.col);

	// 配置モードの時
	if (pInfo->GetMode() == CImgui::MODE_SET)
	{
		// 配置情報が変わったら
		if (m_Set.nType != Type ||
			m_Set.nNumX != X ||
			m_Set.nNumY != Y ||
			m_Set.nNumZ != Z)
		{
			m_Set.nType = pInfo->GetType();		// 種類
			m_Set.nNumX = X;		// ブロック数 X
			m_Set.nNumY = Y;		// ブロック数 Y
			m_Set.nNumZ = Z;		// ブロック数 Z

			// 仮ブロックの配置
			SetFcstBlock();
		}

		// 配置
		if (pInputKeyboard->GetTrigger(DIK_SPACE) || pInputMouse->GetTrigger(CInputMouse::MOUSE_5))
		{
			m_Set.fWidth = CModel::GetWidth(m_Set.nType);		// 幅
			m_Set.fHeight = CModel::GetHeight(m_Set.nType);		// 高さ
			m_Set.fDepth = CModel::GetDepth(m_Set.nType);		// 奥行き

			// ブロックの生成
			for (int nCntX = 0; nCntX < m_Set.nNumX; nCntX++)
			{
				for (int nCntY = 0; nCntY < m_Set.nNumY; nCntY++)
				{
					for (int nCntZ = 0; nCntZ < m_Set.nNumZ; nCntZ++)
					{
						CBlock::Create(m_Set.nType,
							D3DXVECTOR3((
								m_Set.pos.x + (nCntX * (m_Set.fWidth * 2))),
								m_Set.pos.y + (nCntY * (m_Set.fHeight * 2)),
								m_Set.pos.z + (nCntZ * (m_Set.fDepth * -2)))/*,
							m_Set.rot*/);
					}
				}
			}
		}
	}

	// 削除
	if (pInfo->GetMode() == CImgui::MODE_DELETE)
	{
		if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputMouse->GetTrigger(CInputMouse::MOUSE_5))
		{
			m_bDelete = true;
		}
		Delete(pInfo->GetID());
		m_bDelete = false;
	}
	// カメラの注視点を設定

	int nScreen = pCamera->GetScreen();

	if (pInfo->GetMode() == CImgui::MODE_SET)
	{
		// カメラの注視点を設定
		if (nScreen == pCamera->SCREEN_2D)
		{
			pCamera->SetPosR(D3DXVECTOR3(m_Set.pos.x, m_Set.pos.y, m_Set.pos.z));
		}
		/*else if (nScreen == pCamera->SCREEN_3D)
		{
			pCamera->SetPosR(D3DXVECTOR3(0.0f, 300.0f, 0.0f));
		}*/
	}

	CObjectX::Update();
}

//========================================
// 描画
//========================================
void CSetBlock::Draw(void)
{
	CObjectX::Draw();
}

//========================================
// 削除
//========================================
void CSetBlock::Delete(int nID)
{
	CCamera *pCamera = CManager::GetCamera();	// カメラ

	int nCntBlock = 0;
	for (int nCntObj = 0; nCntObj < MAX_OBJECT*2; nCntObj++)
	{
		// オブジェクトを取得
		CObject *pObj = GetObjectPointer(PRIO_OBJX, nCntObj);

		if (pObj != NULL)
		{// 使用されている時、

			// 種類を取得
			TYPE type = pObj->GetType();

			if (type == TYPE_BLOCK)
			{// 種類がブロックの時、

				if (nCntBlock == nID)
				{
					D3DXVECTOR3 pos = pObj->GetPos();

					int nScreen = pCamera->GetScreen();
					// カメラの注視点を設定

					if (nScreen == pCamera->SCREEN_2D)
					{
						pCamera->SetPosR(D3DXVECTOR3(pos.x, pos.y + 95, pos.z));
					}
					/*else if (nScreen == pCamera->SCREEN_3D)
					{
						pCamera->SetPosR(D3DXVECTOR3(pos.x, pos.y + 95, pos.z));
					}*/

					if (m_bDelete)
					{
						pObj->Uninit();

						m_bDelete = false;
						return;
					}
				}
				nCntBlock++;
			}
		}
	}
}

//========================================
// 仮ブロックの配置
//========================================
void CSetBlock::SetFcstBlock(void)
{
	// 敵を全て破棄
	CObject::ReleaseAll(CObject::TYPE_FCST_BLOCK);

	m_Set.fWidth = CModel::GetWidth(m_Set.nType);				// 幅
			m_Set.fHeight = CModel::GetHeight(m_Set.nType);		// 高さ
			m_Set.fDepth = CModel::GetDepth(m_Set.nType);		// 奥行き

			for (int nCntX = 0; nCntX < m_Set.nNumX; nCntX++)
			{
				for (int nCntY = 0; nCntY < m_Set.nNumY; nCntY++)
				{
					for (int nCntZ = 0; nCntZ < m_Set.nNumZ; nCntZ++)
					{
						CFcstBlock::Create(m_Set.nType,
							D3DXVECTOR3((
								m_Set.pos.x + (nCntX * (m_Set.fWidth * 2))),
								m_Set.pos.y + (nCntY * (m_Set.fHeight * 2)),
								m_Set.pos.z + (nCntZ * (m_Set.fDepth * -2))),
							m_Set.rot);
					}
				}
			}
}