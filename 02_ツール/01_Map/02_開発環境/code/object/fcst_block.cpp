//========================================
// 
// ���u���b�N����
// 
//========================================
// *** fast_block.h ***
//========================================
#include "fcst_block.h"
#include "../manager.h"
#include "model.h"
#include "../imgui_block.h"

//========================================
// �R���X�g���N�^
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
// �f�X�g���N�^
//========================================
CFcstBlock::~CFcstBlock()
{

}

//========================================
// ����
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
// ������
//========================================
HRESULT CFcstBlock::Init(void)
{

	// ��ނ̐ݒ�
	SetType(TYPE_FCST_BLOCK);

	m_SetInfo.pos = INIT_D3DXVECTOR3;
	m_SetInfo.rot = INIT_D3DXVECTOR3;
	m_SetInfo.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
	m_SetInfo.nType = 0;

	CObjectX::Init();
	return S_OK;
}

//========================================
// �I��
//========================================
void CFcstBlock::Uninit(void)
{
	CObjectX::Uninit();
}

//========================================
// �X�V
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
// �`��
//========================================
void CFcstBlock::Draw(void)
{
	CObjectX::Draw();
}