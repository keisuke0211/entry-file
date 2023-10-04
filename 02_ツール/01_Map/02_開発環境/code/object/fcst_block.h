//========================================
// 
// ���u���b�N����
// 
//========================================
// *** fast_block.h ***
//========================================
#ifndef _fcst_BLOCK_H_
#define _fcst_BLOCK_H_

#include "../main.h"
#include "objectX.h"

//****************************************
// �N���X
//****************************************

// �Z�b�g�u���b�N�̃N���X
class CFcstBlock : public CObjectX
{
public:

	// ***** �֐� *****
	CFcstBlock(int nPriority = PRIO_OBJ3D);
	~CFcstBlock();

	/* ���C�� */
	static CFcstBlock *Create(int nType, D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	HRESULT Init(void);		// ������
	void Uninit(void);		// �I��
	void Update(void);		// �X�V
	void Draw(void);		// �`��

	/* �ʒu			*/void FcstSetPos(const D3DXVECTOR3 pos) { m_SetInfo.pos = pos; }
	/* ����			*/void FcstSetRot(const D3DXVECTOR3 rot) { m_SetInfo.rot = rot; }
	/* �F			*/void FcstSetColor(const D3DXCOLOR col) { m_SetInfo.col = col; }
	/* ���			*/void FcstSetType(const int nType) { m_SetInfo.nType = nType; }

private:

	// ***** �\���� *****

	// �z�u���
	typedef struct
	{
		D3DXVECTOR3 pos;	// �ʒu
		D3DXVECTOR3 rot;	// ����
		D3DXVECTOR3 move;	// �ړ���
		D3DXCOLOR col;		// ���_�J���[
		int nType;			// ���
	} SetInfo;

	// ***** �ϐ� *****
	SetInfo m_SetInfo;	// �Z�b�g���
};

#endif