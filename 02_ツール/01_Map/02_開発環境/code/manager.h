//========================================
// 
// �}�l�[�W���[����
// 
//========================================
// *** manager.h ***
//========================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"

//****************************************
// �O���錾
//****************************************
class CRenderer;		// �����_���[
class CCamera;			// �J����
class CLight;			// ���C�g
class CTexture;			// �e�N�X�`��
class CInputKeyboard;	// �L�[�{�[�h
class CInputMouse;		// �}�E�X
class CInputJoypad;		// �W���C�p�b�g
class CBlock;			// �u���b�N
class CImgui;			// imGui
class CSetBlock;		// �Z�b�g�u���b�N

//****************************************
// �N���X
//****************************************
class CManager
{
public:

	// ***** �֐� *****
	CManager();
	virtual~CManager();

	/* ������	*/HRESULT Init(HINSTANCE hinstance, HWND hWnd, BOOL bWindow);
	/* �I��		*/void Uninit(void);
	/* �X�V		*/void Update(void);
	/* �`��		*/void Draw(void);

	// -- �擾 --------------------------------------
	/* �����_���[		*/static CRenderer *GetRenderer() { return m_pRenderer; }
	/* �J����			*/static CCamera *GetCamera() { return m_pCamera; }
	/* ���C�g			*/static CLight *GetLight() { return m_pLight; }
	/* �e�N�X�`��		*/static CTexture* GetTexture(){ return m_pTexture; }
	/* �L�[�{�[�h		*/static CInputKeyboard* GetInputKeyboard() { return m_InputKeyboard; }
	/* �}�E�X			*/static CInputMouse* GetInputMouse() { return m_InputMouse; }
	/* �W���C�p�b�g		*/static CInputJoypad* GetInputJoypad() { return m_InputJoypad; }
	/* �u���b�N			*/static CBlock* GetBlock() { return m_pBlock; }
	/* �Z�b�g�u���b�N	*/static CSetBlock* GetSetBlock() { return m_pSetBlock; }
	/* imGui			*/static CImgui* GetImgui() { return m_pImgui; }

private:
	/* �����_���[		*/static CRenderer *m_pRenderer;
	/* �J����			*/static CCamera *m_pCamera;
	/* ���C�g			*/static CLight *m_pLight;
	/* �e�N�X�`��		*/static CTexture *m_pTexture;
	/* �L�[�{�[�h		*/static CInputKeyboard *m_InputKeyboard;
	/* �}�E�X			*/static CInputMouse* m_InputMouse;
	/* �W���C�p�b�g		*/static CInputJoypad* m_InputJoypad;
	/* �u���b�N			*/static CBlock *m_pBlock;
	/* �Z�b�g�u���b�N	*/static CSetBlock *m_pSetBlock;
	/* imGui			*/static CImgui	*m_pImgui;
};
#endif