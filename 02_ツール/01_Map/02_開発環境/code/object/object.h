//========================================
// 
// �I�u�W�F�N�g����
// 
//========================================
// *** objext.h ***
//========================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "../main.h"
#include "../physics.h"

//****************************************
// �O���錾
//****************************************
class CScore;	// �X�R�A
class CTime;	// �^�C��

//****************************************
// �N���X
//****************************************
class CObject : public CPhysics
{
public:
	/* ��` */
	static const int MAX_OBJECT = 2048;	// �I�u�W�F�N�g�̍ő吔

	// ***** �񋓌^ *****

	// �D�揇�ʎ��
	typedef enum
	{
		PRIO_NONE = 0,	// ����
		PRIO_OBJ2D,		// �I�u�W�F�N�g2D
		PRIO_OBJ3D,		// �I�u�W�F�N�g3D
		PRIO_OBJX,		// �I�u�W�F�N�gX
		PRIO_EFFECT,	// �G�t�F�N�g
		PRIO_TEXT,		// �e�L�X�g
		PRIO_MAX
	}PRIO;

	// �I�u�W�F�N�g���
	typedef enum
	{
		TYPE_NONE = 0,	// ����
		TYPE_SETBLOCK,	// �Z�b�g�u���b�N
		TYPE_BLOCK,		// �u���b�N
		TYPE_FCST_BLOCK,// ���u���b�N
		TYPE_MAX
	}TYPE;

	// ***** �ÓI�֐� *****
	/* �S�Ă̔j��			*/static void ReleaseAll(void);
	/* �S�Ă̔j��(��ޖ�)	*/static void ReleaseAll(TYPE type);	// [�I�[�o�[���[�h]
	/* �S�Ă̍X�V			*/static void UpdateAll(void);
	/* �S�Ă̕`��			*/static void DrawAll(void);

	// ***** �֐� *****
	CObject(int nPriority = 0);
	virtual~CObject();

	/* ������	*/virtual HRESULT Init(void) = 0;
	/* �I��		*/virtual void Uninit(void) = 0;
	/* �X�V		*/virtual void Update(void) = 0;
	/* �`��		*/virtual void Draw(void) = 0;

	// -- �ݒ� ------------------------------------------
	/* ��ސݒ�*/void SetType(TYPE type);

	// -- �擾 ------------------------------------------
	/* ��				*/virtual float GetWidth(void) { return 0.0f; }
	/* ����				*/virtual float GetHeight(void) { return 0.0f; }
	/* ���s��			*/virtual float GetDepth(void) { return 0.0f; }
	/* �T�C�Y			*/virtual D3DXVECTOR3 GetSize(void) { return INIT_D3DXVECTOR3; }
	/* �ʒu				*/virtual D3DXVECTOR3 GetPos(void) { return INIT_D3DXVECTOR3; }
	/* �ʒu(�ߋ�)		*/virtual D3DXVECTOR3 GetPosOld(void) { return INIT_D3DXVECTOR3; }
	/* ����				*/virtual D3DXVECTOR3 GetRot(void) { return INIT_D3DXVECTOR3; }
	/* ����(�ߋ�)		*/virtual D3DXVECTOR3 GetRotOld(void) { return INIT_D3DXVECTOR3; }
	/* ���				*/TYPE GetType() { return m_type; }
	/* �I�u�W�F�N�g����	*/static int GetNumAll() { return m_nNumAll; };
	/* �I�u�W�F�N�g���	*/static CObject *GetObjectPointer(int nPriority,int nIdx) { return m_apObject[nPriority][nIdx]; }

protected:
	/* ������� */void Release(void);

private:
	static CObject *m_apObject[PRIO_MAX][MAX_OBJECT];	// �I�u�W�F�N�g�̃|�C���^�z��
	static int m_nNumAll;								// �I�u�W�F�N�g����
	int m_nPriority;									// �D�揇�ʂ̈ʒu
	int m_nID;											// �������g��ID
	TYPE m_type;										// �������g�̎��

};
#endif