//========================================
// 
// �Z�b�g�u���b�N����
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
// �R���X�g���N�^
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
// �f�X�g���N�^
//========================================
CSetBlock::~CSetBlock()
{

}

//========================================
// ����
//========================================
CSetBlock *CSetBlock::Create(void)
{
	CSetBlock *pBlock = NULL;

	if (pBlock != NULL)
	{
		return pBlock;
	}

	// �u���b�N�̐���
	pBlock = new CSetBlock;

	// ����������
	pBlock->Init();

	return pBlock;
}
//========================================
// ������
//========================================
HRESULT CSetBlock::Init(void)
{
	CObjectX::Init();

	// ��ނ̐ݒ�
	SetType(TYPE_SETBLOCK);

	m_Set.pos = INIT_D3DXVECTOR3;
	m_Set.rot = INIT_D3DXVECTOR3;
	m_Set.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	m_Set.nType = 0;
	m_Set.nNumX = 1;
	m_Set.nNumY = 1;
	m_Set.nNumZ = 1;

	// �ݒ�
	SetModel(m_Set.nType);
	SetPos(m_Set.pos);
	SetRot(m_Set.rot);
	SetColor(m_Set.col);

	// ���u���b�N�̔z�u
	CFcstBlock::Create(m_Set.nType, m_Set.pos, m_Set.rot);

	CCamera *pCamera = CManager::GetCamera();						// �J����

	pCamera->SetPosR(D3DXVECTOR3(0.0f, 300.0f, 0.0f));

	return S_OK;
}

//========================================
// �I��
//========================================
void CSetBlock::Uninit(void)
{
	CObjectX::Uninit();
}

//========================================
// �X�V
//========================================
void CSetBlock::Update(void)
{
	// --- �擾---------------------------------
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// �L�[�{�[�h
	CInputMouse *pInputMouse = CManager::GetInputMouse();			// �}�E�X
	CInputJoypad *pInputJoypad = CManager::GetInputJoypad();		// �W���C�p�b�g
	CCamera *pCamera = CManager::GetCamera();						// �J����
	CImgui *pInfo = CManager::GetImgui();							// Imgui


	m_Set.pos = pInfo->GetPos();	// �ʒu
	m_Set.rot = pInfo->GetRot();	// ����
	int Type = pInfo->GetType();	// ���
	int X = pInfo->GetNumX();		// �u���b�N�� X
	int Y = pInfo->GetNumY();		// �u���b�N�� Y
	int Z = pInfo->GetNumZ();		// �u���b�N�� Z

	// �ݒ�
	SetModel(m_Set.nType);
	SetPos(m_Set.pos);
	SetRot(m_Set.rot);
	SetColor(m_Set.col);

	// �z�u���[�h�̎�
	if (pInfo->GetMode() == CImgui::MODE_SET)
	{
		// �z�u��񂪕ς������
		if (m_Set.nType != Type ||
			m_Set.nNumX != X ||
			m_Set.nNumY != Y ||
			m_Set.nNumZ != Z)
		{
			m_Set.nType = pInfo->GetType();		// ���
			m_Set.nNumX = X;		// �u���b�N�� X
			m_Set.nNumY = Y;		// �u���b�N�� Y
			m_Set.nNumZ = Z;		// �u���b�N�� Z

			// ���u���b�N�̔z�u
			SetFcstBlock();
		}

		// �z�u
		if (pInputKeyboard->GetTrigger(DIK_SPACE) || pInputMouse->GetTrigger(CInputMouse::MOUSE_5))
		{
			m_Set.fWidth = CModel::GetWidth(m_Set.nType);		// ��
			m_Set.fHeight = CModel::GetHeight(m_Set.nType);		// ����
			m_Set.fDepth = CModel::GetDepth(m_Set.nType);		// ���s��

			// �u���b�N�̐���
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

	// �폜
	if (pInfo->GetMode() == CImgui::MODE_DELETE)
	{
		if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputMouse->GetTrigger(CInputMouse::MOUSE_5))
		{
			m_bDelete = true;
		}
		Delete(pInfo->GetID());
		m_bDelete = false;
	}
	// �J�����̒����_��ݒ�

	int nScreen = pCamera->GetScreen();

	if (pInfo->GetMode() == CImgui::MODE_SET)
	{
		// �J�����̒����_��ݒ�
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
// �`��
//========================================
void CSetBlock::Draw(void)
{
	CObjectX::Draw();
}

//========================================
// �폜
//========================================
void CSetBlock::Delete(int nID)
{
	CCamera *pCamera = CManager::GetCamera();	// �J����

	int nCntBlock = 0;
	for (int nCntObj = 0; nCntObj < MAX_OBJECT*2; nCntObj++)
	{
		// �I�u�W�F�N�g���擾
		CObject *pObj = GetObjectPointer(PRIO_OBJX, nCntObj);

		if (pObj != NULL)
		{// �g�p����Ă��鎞�A

			// ��ނ��擾
			TYPE type = pObj->GetType();

			if (type == TYPE_BLOCK)
			{// ��ނ��u���b�N�̎��A

				if (nCntBlock == nID)
				{
					D3DXVECTOR3 pos = pObj->GetPos();

					int nScreen = pCamera->GetScreen();
					// �J�����̒����_��ݒ�

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
// ���u���b�N�̔z�u
//========================================
void CSetBlock::SetFcstBlock(void)
{
	// �G��S�Ĕj��
	CObject::ReleaseAll(CObject::TYPE_FCST_BLOCK);

	m_Set.fWidth = CModel::GetWidth(m_Set.nType);				// ��
			m_Set.fHeight = CModel::GetHeight(m_Set.nType);		// ����
			m_Set.fDepth = CModel::GetDepth(m_Set.nType);		// ���s��

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