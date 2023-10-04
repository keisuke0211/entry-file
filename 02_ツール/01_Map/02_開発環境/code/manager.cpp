//========================================
// 
// �}�l�[�W���[����
// 
//========================================
// *** manager.cpp ***
//========================================
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "light.h"
#include "texture.h"
#include "input.h"
#include "object\model.h"
#include "object\object.h"
#include "object\block.h"
#include "object\set_block.h"
#include "imgui_block.h"

// �ÓI�����o�ϐ�
CRenderer *CManager::m_pRenderer = NULL;
CCamera *CManager::m_pCamera = NULL;	// �J����
CLight *CManager::m_pLight = NULL;		// ���C�g
CTexture *CManager::m_pTexture = NULL;
CInputKeyboard *CManager::m_InputKeyboard = NULL;
CInputMouse *CManager::m_InputMouse = NULL;
CInputJoypad *CManager::m_InputJoypad = NULL;
CBlock *CManager::m_pBlock = NULL;
CSetBlock *CManager::m_pSetBlock = NULL;
CImgui *CManager::m_pImgui = NULL;


//========================================
// �R���X�g���N�^
//========================================
CManager::CManager()
{
	
}

//========================================
// �f�X�g���N�^
//========================================
CManager::~CManager()
{

}

//========================================
// ������
//========================================
HRESULT CManager::Init(HINSTANCE hinstance, HWND hWnd, BOOL bWindow)
{
// �����_���[�̐���
	m_pRenderer = new CRenderer;

	// �����_���[�̏���������
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{// ���������������s�����ꍇ
		return E_FAIL;
	}

	// �L�[�{�[�h�̐���
	m_InputKeyboard = new CInputKeyboard;

	// �L�[�{�[�h�̏�����
	if (FAILED(m_InputKeyboard->Init(hinstance, hWnd)))
	{
		return E_FAIL;
	}

	// �}�E�X�̐���
	m_InputMouse = new CInputMouse;

	// �}�E�X�̏�����
	if (FAILED(m_InputMouse->Init(hinstance, hWnd)))
	{
		return E_FAIL;
	}

	// �W���C�p�b�g�̐���
	m_InputJoypad = new CInputJoypad;

	// �W���C�p�b�g�̏�����
	if (FAILED(m_InputJoypad->Init()))
	{
		return E_FAIL;
	}

	// �J�����̐���
	m_pCamera = new CCamera;

	// �J�����̏�����
	if (FAILED(m_pCamera->Init()))
	{
		return E_FAIL;
	}

	// ���C�g�̐���
	m_pLight = new CLight;

	// ���C�g�̏�����
	if (FAILED(m_pLight->Init()))
	{
		return E_FAIL;
	}

	if (m_pTexture == NULL)
	{
		// �e�N�X�`���̐���
		m_pTexture = new CTexture;

		// �e�N�X�`��
		m_pTexture->Load();
	}

	// ���f���̏�����
	CModel::InitModel();

	// �Z�b�g�u���b�N�̐���
	CSetBlock::Create();

	// imGui�̏�����
	if (m_pImgui == NULL)
	{
		m_pImgui = new CImgui;
		m_pImgui->Init(hWnd);
	}

	// �u���b�N�̐���
	//�@CBlock::Load();

	return S_OK;
}

//========================================
// �I��
//========================================
void CManager::Uninit(void)
{
	// �L�[�{�[�h�̔j��
	if (m_InputKeyboard != NULL)
	{
		m_InputKeyboard->Uninit();

		delete m_InputKeyboard;
		m_InputKeyboard = NULL;
	}

	// �}�E�X�̔j��
	if (m_InputMouse != NULL)
	{
		m_InputMouse->Uninit();

		delete m_InputMouse;
		m_InputMouse = NULL;
	}

	// �W���C�p�b�g�̔j��
	if (m_InputJoypad != NULL)
	{
		m_InputJoypad->Uninit();

		delete m_InputJoypad;
		m_InputJoypad = NULL;
	}

	// ���f���̏I��
	CModel::UninitModel();

	// imGui�̏�����
	if (m_pImgui != NULL)
	{
		m_pImgui->Uninit();
		
		delete m_pImgui;
		m_pImgui = NULL;
	}

	// �����_���[�̔j��
	if (m_pRenderer != NULL)
	{
		// �����_���[
		m_pRenderer->Uninit();

		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	// ���C�g�̔j��
	if (m_pLight != NULL)
	{
		// ���C�g
		m_pLight->Uninit();

		delete m_pLight;
		m_pLight = NULL;
	}

	// �J�����̔j��
	if (m_pCamera != NULL)
	{
		// �J����
		m_pCamera->Uninit();

		delete m_pCamera;
		m_pCamera = NULL;
	}

	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Unload();

		delete m_pTexture;
		m_pTexture = NULL;
	}	
}

//========================================
// �X�V
//========================================
void CManager::Update(void)
{
	m_InputKeyboard->Update();	// �L�[�{�[�h
	m_InputMouse->Update();		// �}�E�X
	m_InputJoypad->Update();	// �W���C�p�b�g
	m_pCamera->Update();		// �J����
	m_pLight->Update();			// ���C�g
	m_pRenderer->Update();		// �����_���[
	m_pImgui->Update();			// imGui

}

//========================================
// �`��
//========================================
void CManager::Draw(void)
{
	m_pRenderer->Draw();	// �����_���[
}