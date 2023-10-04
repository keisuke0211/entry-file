//========================================
// 
// �Z�b�g�u���b�N����
// 
//========================================
// *** set_block.h ***
//========================================
#ifndef _SET_BLOCK_H_
#define _SET_BLOCK_H_

#include "../main.h"
#include "objectX.h"

//****************************************
// �N���X
//****************************************

// �Z�b�g�u���b�N�̃N���X
class CSetBlock : public CObjectX
{
public:

	// ***** �֐� *****
	CSetBlock(int nPriority = PRIO_OBJX);
	~CSetBlock();

	/* ���C�� */
	static CSetBlock *Create(void);

	HRESULT Init(void);		// ������
	void Uninit(void);		// �I��
	void Update(void);		// �X�V
	void Draw(void);		// �`��
	void Delete(int nId);	// �폜

private:

	// ***** �\���� *****

	// �z�u���
	typedef struct
	{
		D3DXVECTOR3 pos;	// �ʒu
		D3DXVECTOR3 rot;	// ����
		D3DXCOLOR col;		// ���_�J���[
		int nType;			// ���
		int nNumX;			// X �u���b�N��
		int nNumY;			// Y �u���b�N��
		int nNumZ;			// Z �u���b�N��
		float fWidth;		// ��
		float fHeight;		// ����
		float fDepth;		// ���s��
	} Set;

	// ***** �֐� *****
	void SetFcstBlock(void);

	// ***** �ϐ� *****
	Set m_Set;								// �z�u���
	bool m_bDelete;		// �폜�t���O
};

#endif