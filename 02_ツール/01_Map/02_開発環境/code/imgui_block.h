//========================================
// 
// imgui�u���b�N����
// 
//========================================
// *** imgui_block.h ***
//========================================
#ifndef _IMGUI_BLOCK_H_
#define _IMGUI_BLOCK_H_

#include "main.h"
#include "physics.h"

//****************************************
// �N���X
//****************************************
class CImgui: public CPhysics
{
public:

	// ***** �񋓌^ *****

	// �c�[�����[�h
	typedef enum
	{
		MODE_SET = 0,	// �z�u
		MODE_DELETE,	// �폜
		MODE_MAX
	}MODE;

	// �t�@�C�����[�h
	typedef enum
	{
		FILE_MODE_LODE = 0,	// �ǂݍ���
		FILE_MODE_SAVE,		// �����o��
		FILE_MODE_MAX
	}FILE_MODE;

	// ***** �֐� *****
	CImgui();
	~CImgui();

	/* ���C�� */

	HRESULT Init(HWND hWnd);	// ������
	void Uninit(void);			// �I��
	void Update(void);			// �X�V
	static void Draw(void);		// �`��

	// -- �擾 ---------------------------------------------
	/* �ʒu			*/D3DXVECTOR3 GetPos(void) { return m_pos; }
	/* �ړ���		*/D3DXVECTOR3 GetMove(void) { return m_move; }
	/* ����			*/D3DXVECTOR3 GetRot(void) { return m_rot; }
	/* �T�C�Y		*/D3DXVECTOR3 GetSize(void) { return m_size; }
	/* �F			*/D3DXCOLOR GetColor(void) { return m_col; }
	/* ���			*/int GetType(void) { return m_nType; }
	/* �u���b�N�� X	*/int GetNumX(void) { return m_nNumX; }
	/* �u���b�N�� Y	*/int GetNumY(void) { return m_nNumY; }
	/* �u���b�N�� Z	*/int GetNumZ(void) { return m_nNumZ; }
	/* �u���b�NID	*/int GetID(void) { return m_Index; }
	/* ���[�h�擾	*/int GetMode(void) { return m_nMode; }

private:

	// ***** �֐� *****
	/* �ړ�����		*/void MoveKeyboard(DIRECTION drct);
	/* ���j���[����	*/void MenuFile(void);
	/* �t�@�C���I��	*/TCHAR FileSelect(void);
	/* �u���b�N		*/void SetBlock(void);

	// ***** �ϐ� *****
	D3DXVECTOR3 m_pos;		// �ʒu
	D3DXVECTOR3 m_posOld;	// �ʒu(�ߋ�)
	D3DXVECTOR3 m_move;		// �ړ���
	D3DXVECTOR3 m_rot;		// ����
	D3DXVECTOR3	m_size;		// �T�C�Y
	D3DXCOLOR m_col;		// ���_�J���[
	int m_nType;			// ���
	int m_nNumX;			// X �u���b�N��
	int m_nNumY;			// Y �u���b�N��
	int m_nNumZ;			// Z �u���b�N��
	float m_fWidth;			// ��
	float m_fHeight;		// ����
	float m_fDepth;			// ���s��
	int m_Index;			// �u���b�NID
	int m_nMode;			// �c�[�����[�h
	int m_nFileMode;		// �t�@�C�����[�h
	bool m_bMode;			// ���[�h�\��
	bool m_bOp;				// ������@�̕\���t���O
	bool m_bOpen;			// �t�@�C�����J����
	bool m_bSave;			// �t�@�C����ۑ����邩

	static TCHAR m_szFile[MAX_PATH];	// �I���t�@�C���̊i�[�ϐ�

	D3DXVECTOR3 rot;		// ����
	D3DXVECTOR3 moveRot;	// �ړ�����
	D3DXVECTOR3 move;		// �ړ���
};
#endif