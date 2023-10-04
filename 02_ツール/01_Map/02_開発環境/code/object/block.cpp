//========================================
// 
// �u���b�N����
// 
//========================================
// *** block.cpp ***
//========================================
#include "block.h"
#include "model.h"
#include "../csv_file.h"

//========================================
// �}�N����`
//========================================
#define RADIUS_TIME	(20)	// ���a�E���ڎ���
#define BULLET_ID	(2)		// �eID
#define NUM_DATA	(4)		// �f�[�^��

// �ÓI�ϐ�
CBlock::SetInfo *CBlock::pSetInfo = NULL;
int CBlock::m_nNumAll = 0;					// �I�u�W�F�N�g����
CBlock *CBlock::m_apBlock[MAX_BLOCK] = {};	// �u���b�N�̃|�C���^

const string CBlock::m_aBlockName[MODEL_BULLET] = {
	"�� 00",
	"�� 01",
	"�� 02",
	"�� 03",
	"�� 04",
	"�y 00",
	"�y 01",
	"�y 02",
	"�y 03",
	"�y 04",
};

//========================================
// �R���X�g���N�^
//========================================
CBlock::CBlock(int nPriority) : CObjectX(nPriority)
{
	for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
	{
		if (m_apBlock[nCnt] == NULL)
		{
			m_apBlock[nCnt] = this;	// �������g����
			break;
		}
	}

	// �l���N���A
	m_Info.pos = INIT_D3DXVECTOR3;
	m_Info.posOld = INIT_D3DXVECTOR3;
	m_Info.rot = INIT_D3DXVECTOR3;
	m_Info.rotOld = INIT_D3DXVECTOR3;
	m_Info.size = INIT_D3DXVECTOR3;
	m_Info.col = INIT_D3DXCOLOR;
	m_Info.nType = 0;
	m_Info.nLife = 0;
	m_Info.nLifeMax = 0;
	m_Info.fRadius = 0.0f;
	m_Info.nCntRadius = 0;
	m_Info.fRadiusRate = 0.0f;
	m_Info.Width = 0.0f;
	m_Info.Height = 0.0f;
	m_Info.Depth = 0.0f;
	m_Info.bSet = false;

	m_nNumAll++;
	m_Info.nID = m_nNumAll - 1;

}

//========================================
// �f�X�g���N�^
//========================================
CBlock::~CBlock()
{
	m_nNumAll--;
}

//========================================
// ����
//========================================
CBlock *CBlock::Create(int nType,D3DXVECTOR3 pos/*, D3DXVECTOR3 rot*/)
{
	CBlock *pBlock = NULL;

	if (pBlock != NULL)
	{
		return pBlock;
	}

	// �u���b�N�̐���
	pBlock = new CBlock;

	if (nType == MODEL_BULLET)
	{
		pBlock->m_Info.nCntRadius = RADIUS_TIME;
		pBlock->m_Info.fRadiusRate = 0.0f;
		pBlock->m_Info.bSet = false;
	}
	else
	{
		pBlock->m_Info.bSet = false;
	}

	pBlock->SetModel(nType);

	// ����������
	pBlock->Init();

	//pBlock->m_Info.rot = rot;
	pBlock->m_Info.nType = nType;
	pBlock->m_Info.nLife = 300;
	pBlock->m_Info.nLifeMax = 300;
	pBlock->BlockSetPos(pos);

	m_apBlock[m_nNumAll - 1]->m_Info.nType = pBlock->m_Info.nType;
	m_apBlock[m_nNumAll - 1]->m_Info.pos = pBlock->m_Info.pos;
	m_apBlock[m_nNumAll - 1]->m_Info.rot = pBlock->m_Info.rot;

	return pBlock;
}

//========================================
// ������
//========================================
HRESULT CBlock::Init(void)
{
	CObjectX::Init();

	// ��ނ̐ݒ�
	SetType(TYPE_BLOCK);

	m_Info.pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.size = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Info.col = INIT_D3DXCOLOR;
	m_Info.nType = 0;
	m_Info.fRadius = 1.0f;

	// ����
	SetPos(m_Info.pos);
	//SetRot(m_Info.rot);
	SetScale(m_Info.size);
	SetColor(m_Info.col);

	return S_OK;
}

//========================================
// �I��
//========================================
void CBlock::Uninit(void)
{

	int nID = m_Info.nID;
	
	CObjectX::Uninit();

	if (m_apBlock[nID] != NULL)
	{
		/*delete m_apBlock[nID];*/
		m_apBlock[nID] = NULL;
	}
}

//========================================
// �X�V
//========================================
void CBlock::Update(void)
{
	// �ߋ��̈ʒu�E�����̍X�V
	m_Info.posOld = m_Info.pos;
	m_Info.rotOld = m_Info.rot;

	// ���a����
	if (m_Info.bSet == false && m_Info.nType == MODEL_BULLET)
	{
		m_Info.fRadiusRate = (float)m_Info.nCntRadius / (float)RADIUS_TIME;
		m_Info.fRadius = 1 * (1.0f - m_Info.fRadiusRate);

		if (--m_Info.nCntRadius <= 0)
		{
			m_Info.bSet = true;
		}
	}

	// ����
	if (--m_Info.nLife <= 0 && m_Info.bSet == true)
	{
		Uninit();
		return;
	}
	else if (m_Info.nLife <= RADIUS_TIME && m_Info.bSet == true)
	{
		m_Info.fRadius -= m_Info.fRadius / m_Info.nLife;
		m_Info.col.a *= ((float)m_Info.nLife / RADIUS_TIME);

		SetColor(m_Info.col);
	}

	// �T�C�Y�̍X�V
	m_Info.size = D3DXVECTOR3(m_Info.fRadius, m_Info.fRadius, m_Info.fRadius);

	SetPos(m_Info.pos);
	//SetRot(m_Info.rot);
	SetScale(m_Info.size);

	CObjectX::Update();
}

//========================================
// �`��
//========================================
void CBlock::Draw(void)
{
	CObjectX::Draw();
}

//========================================
// �ǂݍ���
//========================================
void CBlock::Load(string filepath)
{
	CSVFILE *pFile = new CSVFILE;

	// �ǂݍ���
	pFile->FileLood(filepath, true, true, ',');

	// �s���̎擾
	int nRowMax = pFile->GetRowSize();

	// �m��
	pSetInfo = new SetInfo;

	SetInfo* keep = pSetInfo;

	for (int nRow = 0; nRow < nRowMax; nRow++)
	{
		// �񐔂̎擾
		int nLineMax = pFile->GetLineSize(nRow);

		for (int nLine = 0; nLine < nLineMax; nLine++)
		{
			string sData = pFile->GetData(nRow, nLine);

			switch (nLine)
			{
			case 0:	pFile->ToValue(pSetInfo->nType, sData); break;	// ���
			case 1:	pFile->ToValue(pSetInfo->pos.x, sData); break;	// �ʒu X
			case 2:	pFile->ToValue(pSetInfo->pos.y, sData); break;	// �ʒu Y
			case 3:	pFile->ToValue(pSetInfo->pos.z, sData); break;	// �ʒu Z
			}
		}
		pSetInfo++;
	}

	// �擪�ʒu�ɖ߂�
	pSetInfo = keep;

	// �z�u
	SetBlock(nRowMax - 1);

	delete pFile;
	pFile = NULL;
}

//========================================
//	�����o��
//========================================
void CBlock::Save(string filepath)
{
	CSVFILE *pFile = new CSVFILE;

	// �w�b�_�[�̐ݒ�
	pFile->SetHeader("���,�ʒu X,Y,Z", ',');

	// �f�[�^�̐ݒ�
	for (int nRow = 0; nRow < m_nNumAll; nRow++)
	{
		// �C���f�b�N�X�̐ݒ�
		pFile->SetIndex(m_aBlockName[m_apBlock[nRow]->m_Info.nType], ',');

		for (int nLine = 0; nLine < NUM_DATA; nLine++)
		{
			string sData;	// ������̊i�[����ϐ�
			
			// ������ɕϊ�
			switch (nLine)
			{
			case 0:	sData = pFile->CastCell(m_apBlock[nRow]->m_Info.nType); break;	// ���
			case 1:	sData = pFile->CastCell(m_apBlock[nRow]->m_Info.pos.x); break;	// �ʒu X
			case 2:	sData = pFile->CastCell(m_apBlock[nRow]->m_Info.pos.y); break;	// �ʒu Y
			case 3:	sData = pFile->CastCell(m_apBlock[nRow]->m_Info.pos.z); break;	// �ʒu Z
			}

			// �f�[�^�̒ǉ�
			pFile->SetCell(sData, nRow, nLine);
		}
	}

	// �����o��
	pFile->FileSave(filepath, ',');
}

//========================================
// �z�u
//========================================
void CBlock::SetBlock(int nNumSet)
{
	for (int nCntSet = 0; nCntSet < nNumSet; nCntSet++, pSetInfo++)
	{
		CBlock::Create(pSetInfo->nType,
			D3DXVECTOR3(
				pSetInfo->pos.x,
				pSetInfo->pos.y,
				pSetInfo->pos.z)/*,
			pSetInfo->rot*/);
	}
}

//========================================
// �j��
//========================================
void CBlock::UnLoad(void)
{
	if (pSetInfo != NULL)
	{
		delete pSetInfo;
		pSetInfo = NULL;
	}

	for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
	{
		if (m_apBlock[nCnt] != NULL)
		{
			delete m_apBlock[nCnt];
			m_apBlock[nCnt] = NULL;
		}
	}
}