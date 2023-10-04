//========================================
// 
// マネージャー処理
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

// 静的メンバ変数
CRenderer *CManager::m_pRenderer = NULL;
CCamera *CManager::m_pCamera = NULL;	// カメラ
CLight *CManager::m_pLight = NULL;		// ライト
CTexture *CManager::m_pTexture = NULL;
CInputKeyboard *CManager::m_InputKeyboard = NULL;
CInputMouse *CManager::m_InputMouse = NULL;
CInputJoypad *CManager::m_InputJoypad = NULL;
CBlock *CManager::m_pBlock = NULL;
CSetBlock *CManager::m_pSetBlock = NULL;
CImgui *CManager::m_pImgui = NULL;


//========================================
// コンストラクタ
//========================================
CManager::CManager()
{
	
}

//========================================
// デストラクタ
//========================================
CManager::~CManager()
{

}

//========================================
// 初期化
//========================================
HRESULT CManager::Init(HINSTANCE hinstance, HWND hWnd, BOOL bWindow)
{
// レンダラーの生成
	m_pRenderer = new CRenderer;

	// レンダラーの初期化処理
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{// 初期化処理が失敗した場合
		return E_FAIL;
	}

	// キーボードの生成
	m_InputKeyboard = new CInputKeyboard;

	// キーボードの初期化
	if (FAILED(m_InputKeyboard->Init(hinstance, hWnd)))
	{
		return E_FAIL;
	}

	// マウスの生成
	m_InputMouse = new CInputMouse;

	// マウスの初期化
	if (FAILED(m_InputMouse->Init(hinstance, hWnd)))
	{
		return E_FAIL;
	}

	// ジョイパットの生成
	m_InputJoypad = new CInputJoypad;

	// ジョイパットの初期化
	if (FAILED(m_InputJoypad->Init()))
	{
		return E_FAIL;
	}

	// カメラの生成
	m_pCamera = new CCamera;

	// カメラの初期化
	if (FAILED(m_pCamera->Init()))
	{
		return E_FAIL;
	}

	// ライトの生成
	m_pLight = new CLight;

	// ライトの初期化
	if (FAILED(m_pLight->Init()))
	{
		return E_FAIL;
	}

	if (m_pTexture == NULL)
	{
		// テクスチャの生成
		m_pTexture = new CTexture;

		// テクスチャ
		m_pTexture->Load();
	}

	// モデルの初期化
	CModel::InitModel();

	// セットブロックの生成
	CSetBlock::Create();

	// imGuiの初期化
	if (m_pImgui == NULL)
	{
		m_pImgui = new CImgui;
		m_pImgui->Init(hWnd);
	}

	// ブロックの生成
	//　CBlock::Load();

	return S_OK;
}

//========================================
// 終了
//========================================
void CManager::Uninit(void)
{
	// キーボードの破棄
	if (m_InputKeyboard != NULL)
	{
		m_InputKeyboard->Uninit();

		delete m_InputKeyboard;
		m_InputKeyboard = NULL;
	}

	// マウスの破棄
	if (m_InputMouse != NULL)
	{
		m_InputMouse->Uninit();

		delete m_InputMouse;
		m_InputMouse = NULL;
	}

	// ジョイパットの破棄
	if (m_InputJoypad != NULL)
	{
		m_InputJoypad->Uninit();

		delete m_InputJoypad;
		m_InputJoypad = NULL;
	}

	// モデルの終了
	CModel::UninitModel();

	// imGuiの初期化
	if (m_pImgui != NULL)
	{
		m_pImgui->Uninit();
		
		delete m_pImgui;
		m_pImgui = NULL;
	}

	// レンダラーの破棄
	if (m_pRenderer != NULL)
	{
		// レンダラー
		m_pRenderer->Uninit();

		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	// ライトの破棄
	if (m_pLight != NULL)
	{
		// ライト
		m_pLight->Uninit();

		delete m_pLight;
		m_pLight = NULL;
	}

	// カメラの破棄
	if (m_pCamera != NULL)
	{
		// カメラ
		m_pCamera->Uninit();

		delete m_pCamera;
		m_pCamera = NULL;
	}

	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Unload();

		delete m_pTexture;
		m_pTexture = NULL;
	}	
}

//========================================
// 更新
//========================================
void CManager::Update(void)
{
	m_InputKeyboard->Update();	// キーボード
	m_InputMouse->Update();		// マウス
	m_InputJoypad->Update();	// ジョイパット
	m_pCamera->Update();		// カメラ
	m_pLight->Update();			// ライト
	m_pRenderer->Update();		// レンダラー
	m_pImgui->Update();			// imGui

}

//========================================
// 描画
//========================================
void CManager::Draw(void)
{
	m_pRenderer->Draw();	// レンダラー
}