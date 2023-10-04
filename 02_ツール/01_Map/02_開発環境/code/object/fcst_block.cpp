//========================================
// 
// 仮ブロック処理
// 
//========================================
// *** fast_block.h ***
//========================================
#include "fcst_block.h"
#include "../manager.h"
#include "model.h"
#include "../imgui_block.h"

//========================================
// コンストラクタ
//========================================
CFcstBlock::CFcstBlock(int nPriority) : CObjectX(nPriority)
{
	m_SetInfo.pos = INIT_D3DXVECTOR3;
	m_SetInfo.move = INIT_D3DXVECTOR3;
	m_SetInfo.rot = INIT_D3DXVECTOR3;
	m_SetInfo.col = INIT_D3DXCOLOR;
	m_SetInfo.nType = 0;
}

//========================================
// デストラクタ
//========================================
CFcstBlock::~CFcstBlock()
{

}

//========================================
// 生成
//========================================
CFcstBlock *CFcstBlock::Create(int nType, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CFcstBlock *pObj = new CFcstBlock;

	if (pObj != NULL)
	{
		pObj->SetModel(nType);

		pObj->Init();

		pObj->m_SetInfo.pos = pos;
		pObj->m_SetInfo.rot = rot;
		pObj->m_SetInfo.nType = nType;

		pObj->SetPos(pObj->m_SetInfo.pos);
		pObj->SetRot(pObj->m_SetInfo.rot);
		pObj->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));
	}

	return pObj;
}

//========================================
// 初期化
//========================================
HRESULT CFcstBlock::Init(void)
{

	// 種類の設定
	SetType(TYPE_FCST_BLOCK);

	m_SetInfo.pos = INIT_D3DXVECTOR3;
	m_SetInfo.rot = INIT_D3DXVECTOR3;
	m_SetInfo.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
	m_SetInfo.nType = 0;

	CObjectX::Init();
	return S_OK;
}

//========================================
// 終了
//========================================
void CFcstBlock::Uninit(void)
{
	CObjectX::Uninit();
}

//========================================
// 更新
//========================================
void CFcstBlock::Update(void)
{
	CImgui *pInfo = CManager::GetImgui();		// Imgui

	m_SetInfo.move = pInfo->GetMove();

	m_SetInfo.pos += m_SetInfo.move;
	m_SetInfo.rot = pInfo->GetRot();

	SetModel(m_SetInfo.nType);
	SetPos(m_SetInfo.pos);
	SetRot(m_SetInfo.rot);
	SetColor(m_SetInfo.col);

	CObjectX::Update();
}

//========================================
// 描画
//========================================
void CFcstBlock::Draw(void)
{
	CObjectX::Draw();
}