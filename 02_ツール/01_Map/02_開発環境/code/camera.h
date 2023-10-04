//========================================
// 
// �J��������
// 
//========================================
// *** camera.h ***
//========================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"
#include "physics.h"

//****************************************
// �}�N����`
//****************************************
#define CAMERA_SPEED			(50)					// �ړ����x�iX�EZ���W�j
#define CAMERA_SPEED1			(2)						// �ړ����x�iY���W�j
#define ROT_SPEED				(0.015f)				// ��]�X�s�[�h
#define SPIN_DAMP				(0.9f)					// ��]�̌�����
#define ROT_CURSOR	(D3DXVECTOR3(0.0005f,0.00075f,0.0f))// �J�����̃J�[�\���̉�]��

//****************************************
// �N���X
//****************************************
class CCamera : public CPhysics
{
public:

	// ***** �񋓌^ *****

	// �J�����̓��e���
	typedef enum
	{
		SCREEN_NONE = 0,	// ����
		SCREEN_2D,			// ���s���e
		SCREEN_3D,			// �������e
		SCREEN_MAX
	}SCREEN;

	// ***** �\���� *****

	// �J�������
	typedef struct
	{
		D3DXMATRIX mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
		D3DXMATRIX mtxView;			// �r���[�}�g���b�N�X

		D3DXVECTOR3 posV;			// ���݂̎��_
		D3DXVECTOR3 posR;			// ���݂̒����_
		D3DXVECTOR3 posOldV;		// �O��̎��_
		D3DXVECTOR3 posOldR;		// �O��̒����_
		D3DXVECTOR3 vecU;			// ������x�N�g��
		D3DXVECTOR3 rot;			// ����
		D3DXVECTOR3 spin;			// ��]��

		int nScreen;				// ���e���[�h

		float fDistance;			// ����
		float fHeight;				// ����
		float fVerticalMove;		// �c�̈ړ���
	} Info;

	// ***** �֐� *****
	CCamera();	// �R���X�g���N�^
	~CCamera();	// �f�X�g���N�^

	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V

	/* �ݒ� */
	void SetCamera(void);							// �J����
	void SetScreen(void);							// ��ʐݒ�
	void SetPosV(D3DXVECTOR3 pos, int nIdx = 0);	// ���_
	void SetPosR(D3DXVECTOR3 pos, int nIdx = 0);	// �����_

	/* �擾 */
	Info GetInfo() { return m_Info; }			// �v���C���[���
	int GetScreen() { return m_Info.nScreen; }	// �X�N���[�����[�h

private:

	// ***** �\���� *****

	// �J�����̕ۑ����
	typedef struct
	{
		D3DXVECTOR3 posV;			// ���_
		D3DXVECTOR3 posR;			// �����_
		D3DXVECTOR3 rot;			// ����
		D3DXVECTOR3 spin;			// ��]��

		float fDistance;			// ����
		float fHeight;				// ����
		float fVerticalMove;		// �c�̈ړ���
	} Save;

	// ***** �֐� *****
	void AxisRotationCamera(DIRECTION drct, float fRot, int nIdx = 0); //��]����

	// ***** �ϐ� *****
	Info m_Info;		// �J����
	Save m_Save;		// �ۑ� 

	D3DXVECTOR3 m_FixPosR;	// �����_�̌Œ�
	bool m_bRot;			// ���_�ړ��t���O

};

#endif