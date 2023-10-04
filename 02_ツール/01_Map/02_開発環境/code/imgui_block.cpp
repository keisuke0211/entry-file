//========================================
// 
// imguiブロック処理
// 
//========================================
// *** imgui_block.cpp ***
//========================================
#include "imgui_block.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "camera.h"
#include "object\block.h"
#include "object\model.h"
#include "physics.h"
#include "csv_file.h"
#include "object\set_block.h"

TCHAR CImgui::m_szFile[MAX_PATH] = { NULL };

//========================================
// コンストラクタ
//========================================
CImgui::CImgui()
{
	m_pos = INIT_D3DXVECTOR3;
	m_rot = INIT_D3DXVECTOR3;
	m_move = INIT_D3DXVECTOR3;
	m_size = INIT_D3DXVECTOR3;
	m_col = INIT_D3DXCOLOR;
	m_nType = 0;
	m_nNumX = 0;
	m_nNumY = 0;
	m_nNumZ = 0;
	m_fWidth = INIT_FLOAT;
	m_fHeight = INIT_FLOAT;
	m_fDepth = INIT_FLOAT;
	m_Index = 0;
	m_nMode = 0;
	m_bMode = true;
	m_bOp = true;
	m_bOpen = false;
	m_bSave = false;

	moveRot = INIT_D3DXVECTOR3;
	rot = INIT_D3DXVECTOR3;
	move = INIT_D3DXVECTOR3;
}

//========================================
// デストラクタ
//========================================
CImgui::~CImgui()
{

}

//========================================
// 初期化
//========================================
HRESULT CImgui::Init(HWND hWnd)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// Show the window
	::ShowWindow(hWnd, SW_SHOWDEFAULT);
	::UpdateWindow(hWnd);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.Fonts->AddFontFromFileTTF("data//GAMEDATA//FONTS//meiryo.ttc", 20.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());

	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(pDevice);// GetGlyphRangesJapanese

	m_nNumX = 1;
	m_nNumY = 1;
	m_nNumZ = 1;

	return S_OK;
}

//========================================
// 終了
//========================================
void CImgui::Uninit(void)
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

//========================================
// 更新
//========================================
void CImgui::Update(void)
{
	m_move = INIT_D3DXVECTOR3;

	// --- 取得---------------------------------
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// キーボード
	CInputMouse *pInputMouse = CManager::GetInputMouse();			// マウス

	// Demonstrate the various window flags.Typically you would just use the default!
	static bool no_titlebar = false;
	static bool no_scrollbar = false;
	static bool no_menu = false;
	static bool no_move = false;
	static bool no_resize = false;
	static bool no_collapse = false;
	static bool no_close = false;
	static bool no_nav = false;
	static bool no_background = false;
	static bool no_bring_to_front = false;
	static bool unsaved_document = false;
	ImGuiWindowFlags window_flags = 0;

	if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
	if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
	if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
	if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
	if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
	if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
	if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
	if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
	if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
	if (unsaved_document)   window_flags |= ImGuiWindowFlags_UnsavedDocument;

	// Start the Dear ImGui frame
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	bool show_demo_window = true;
	bool existsChange = false;

	// ImGui関数の呼び出し
	{
		/* ウインドウ */
		ImGui::SetNextWindowPos(ImVec2(20.0f, 30.0f), ImGuiCond_Once);	// 位置
		ImGui::SetNextWindowSize(ImVec2(335, 580), ImGuiCond_Once);		// サイズ
		ImGui::Begin(u8"ブロック配置", NULL, window_flags);				// 名前

		// メニューバー
		if (ImGui::BeginMenuBar())
		{
			MenuFile();

			ImGui::EndMenuBar();
		}

		/* パーティクル */
		ImGui::InputInt(u8"種類", &m_nType);

		// 配置モードの時
		if (m_nMode == MODE_SET)
		{
			// 加算と減算
			if (pInputKeyboard->GetTrigger(DIK_Q))
			{
				m_nType--;
			}
			else if (pInputKeyboard->GetTrigger(DIK_E))
			{
				m_nType++;
			}
		}

		if (m_nType > (CPhysics::MODEL_BULLET - 1))
		{
			m_nType = 0;
		}
		if (m_nType < 0)
		{
			m_nType = (CPhysics::MODEL_BULLET - 1);
		}


		{
			m_posOld = m_pos;

			// 移動処理
			if (pInputKeyboard->GetPress(DIK_A))
			{
				if (pInputKeyboard->GetPress(DIK_W)) { MoveKeyboard(DIRECTION_LEFT_BACK); }			// 左奥移動
				else if (pInputKeyboard->GetPress(DIK_S)) { MoveKeyboard(DIRECTION_LEFT_FRONT); }	// 左手前移動
				else { MoveKeyboard(DIRECTION_LEFT); }		// 左移動
			}
			else if (pInputKeyboard->GetPress(DIK_D))
			{
				if (pInputKeyboard->GetPress(DIK_W)) { MoveKeyboard(DIRECTION_RIGHT_BACK); }		// 右奥移動
				else if (pInputKeyboard->GetPress(DIK_S)) { MoveKeyboard(DIRECTION_RIGHT_FRONT); }	// 右手前移動
				else { MoveKeyboard(DIRECTION_RIGHT); }		// 右移動
			}
			else if (pInputKeyboard->GetPress(DIK_W)) { MoveKeyboard(DIRECTION_BACK); }				// 奥移動
			else if (pInputKeyboard->GetPress(DIK_S)) { MoveKeyboard(DIRECTION_FRONT); }			// 手前移動
		}
		// 位置の設定
		if (ImGui::TreeNode(u8"位置"))
		{
			ImGui::DragFloat3(" ", m_pos);

			if (ImGui::Button(u8"初期化"))
				m_pos = INIT_D3DXVECTOR3;

			ImGui::TreePop();
		}

		m_move = m_pos - m_posOld;

		// 向きの設定
		if (ImGui::TreeNode(u8"向き"))
		{
			ImGui::DragFloat3(" ", m_rot, 0.01f);
			if (ImGui::Button(u8"初期化"))
				m_rot = INIT_D3DXVECTOR3;

			ImGui::TreePop();
		}

		// ブロック数
		ImGui::SeparatorText(u8"ブロック数");
		ImGui::InputInt(u8"X", &m_nNumX);
		ImGui::InputInt(u8"Y", &m_nNumY);
		ImGui::InputInt(u8"Z", &m_nNumZ);

		if (m_nNumX <= 1)
		{
			m_nNumX = 1;
		}
		if (m_nNumY <= 1)
		{
			m_nNumY = 1;
		}
		if (m_nNumZ <= 1)
		{
			m_nNumZ = 1;
		}

		/* 終了 */
		ImGui::End();
	}

	{
		ImGui::SetNextWindowPos(ImVec2(980.0f, 50.0f), ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(275, 200), ImGuiCond_Once);	
		ImGui::Begin(u8"操作方法", &m_bMode);
		ImGui::Text(u8"ブロック移動 　　：W A S D");
		ImGui::Text(u8"ブロック種類 加算：E");
		ImGui::Text(u8"　　　　　　 減算：Q");
		ImGui::Text(u8"カメラの視点移動 ：マウス　ライトボタン");

		/* 終了 */
		ImGui::End();
	}

	{
		ImGui::SetNextWindowPos(ImVec2(1000.0f, 450.0f), ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(250, 200), ImGuiCond_Once);
		ImGui::Begin(u8"モード", &m_bMode);


		// 削除モードの時
		if (m_nMode == MODE_DELETE)
		{
			// 加算と減算
			if (pInputKeyboard->GetTrigger(DIK_Q))
			{
				m_Index--;
			}
			else if (pInputKeyboard->GetTrigger(DIK_E))
			{
				m_Index++;
			}
		}

		ImGui::InputInt(u8"番号", &m_Index);

		if (m_Index > (CBlock::GetNumAll() - 1))
		{
			m_Index = 0;
		}
		if (m_Index < 0)
		{
			m_Index = (CBlock::GetNumAll() - 1);
		}

		// モード切替
		if (pInputMouse->GetTrigger(CInputMouse::MOUSE_4))
		{
			switch (m_nMode)
			{
			case MODE_SET:
				m_nMode = MODE_DELETE;
				break;
			case MODE_DELETE:
				m_nMode = MODE_SET;
				break;
			}
		}

		const char* sType[] = { u8"配置", u8"削除" };
		ImGui::Combo(u8"モード", &m_nMode, sType, IM_ARRAYSIZE(sType));

		ImGui::Text(u8"FPS		 ：(%d)", GetFps());
		ImGui::Text(u8"ブロック数：(%d)", CBlock::GetNumAll());

		/* 終了 */
		ImGui::End();
	}

	ImGui::EndFrame();
}

//========================================
// 描画
//========================================
void CImgui::Draw(void)
{
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

//========================================
// 移動処理
//========================================
void CImgui::MoveKeyboard(DIRECTION drct)
{
	CCamera *pCamera = CManager::GetCamera();						// カメラ

	// --- 代入 ---------------------------------
	moveRot = rot;	// 移動向き

	// --- 移動 ---------------------------------

	// 移動向きに円周率を代入
	moveRot.y = D3DX_PI;

	switch (drct)
	{
	case DIRECTION_LEFT:moveRot.y *= -0.5f; break;	// 左
	case DIRECTION_RIGHT:moveRot.y *= 0.5f;	break;	// 右
	case DIRECTION_BACK:moveRot.y *= 0.0f;	break;	// 奥
	case DIRECTION_FRONT:moveRot.y *= 1.0f;	break;	// 手前
	case DIRECTION_LEFT_BACK:moveRot.y *= -0.25f; break;	// 左奥
	case DIRECTION_LEFT_FRONT:moveRot.y *= -0.75f; break;	// 左手前
	case DIRECTION_RIGHT_BACK:moveRot.y *= 0.25f; break;	// 右奥
	case DIRECTION_RIGHT_FRONT:moveRot.y *= 0.75f; break;	// 右手前
	}

	D3DXVECTOR3 posV = pCamera->GetInfo().posV;	// 視点
	D3DXVECTOR3 posR = pCamera->GetInfo().posR;	// 注視点

	// 視点から注視点までの角度
	float fAngle
		= FindAngle(D3DXVECTOR3(posV.x, posV.z, 0.0f), D3DXVECTOR3(posR.x, posR.z, 0.0f));

	moveRot.y += fAngle;

	m_pos.x += sinf(moveRot.y) * 5;
	m_pos.z += cosf(moveRot.y) * 5;
}

//========================================
// メニュー処理
//========================================
void CImgui::MenuFile(void)
{
	if (ImGui::BeginMenu(u8"ファイル"))
	{
		if (ImGui::MenuItem(u8"読み込み"))
		{
			// モード設定
			m_nFileMode = FILE_MODE_LODE;

			// ファイル選択のダイアログ表示
			FileSelect();

			// 開く(O)］ボタンが押されたら
			if (m_bOpen)
			{
				//読み込み
				CBlock::Load(m_szFile);
				m_bOpen = false;
			}
		}
		if (ImGui::MenuItem(u8"書き込み"))
		{
			// モード設定
			m_nFileMode = FILE_MODE_SAVE;

			// ファイル選択のダイアログ表示
			FileSelect();

			// ［保存(S)］ボタンが押されたら
			if (m_bSave)
			{
				// 書き出し
				CBlock::Save(m_szFile);
				m_bSave = false;
			}
		}
		ImGui::EndMenu();
	}
}

//========================================
// ファイル選択
//========================================
TCHAR CImgui::FileSelect(void)
{
	HWND *pHwnd = GetWindowHandle();

	static OPENFILENAME     ofn;
	static TCHAR            szPath[MAX_PATH];	// 初期フォルダ位置の格納変数
	static TCHAR            szFile[MAX_PATH];	// 選択ファイルの格納変数

	// ファイル選択のダイアログ表示
	if (szPath[0] == TEXT('\0'))
	{
		GetCurrentDirectory(MAX_PATH, szPath);
	}
	if (ofn.lStructSize == 0) {
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = *pHwnd;
		ofn.lpstrInitialDir = szPath;	// 初期フォルダ位置
		ofn.lpstrFile = m_szFile;		// 選択ファイル
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrFilter =
			//TEXT("テキスト文書(*.txt)\0*.txt\0")
			TEXT("CSV(コンマ区切り)(*.csv)\0*.csv\0")
			//TEXT("すべてのファイル(*.*)\0*.*\0")
			;

		if (m_nFileMode == FILE_MODE_LODE)
		{
			ofn.lpstrTitle = TEXT("ファイルを開く");
		}
		else if (m_nFileMode == FILE_MODE_SAVE)
		{
			ofn.lpstrTitle = TEXT("名前を付けて保存");
		}
		ofn.Flags = OFN_FILEMUSTEXIST;
	}

	if (m_nFileMode == FILE_MODE_LODE)
	{
		// 開く(O)］ボタンが押されたら
		if (GetOpenFileName(&ofn))
		{
			m_bOpen = true;
		}
	}
	else if (m_nFileMode == FILE_MODE_SAVE)
	{
		// ［保存(S)］ボタンが押されたら
		if (GetSaveFileName(&ofn))
		{
			m_bSave = true;
		}
	}
	return szFile[0];
}

//========================================
// ブロック配置
//========================================
void CImgui::SetBlock(void)
{
	CSVFILE *pFile = new CSVFILE;

	// 読み込み
	pFile->FileLood("data\\GAMEDATA\\BLOCK\\STAGE_DATA1.csv", true, true, ',');

	// 行数の取得
	int nRowMax = pFile->GetRowSize();

	// 各データに代入
	for (int nRow = 0; nRow < nRowMax; nRow++)
	{
		// 配置情報の生成
		int nType;				// 種類
		D3DXVECTOR3 pos;		// 位置

								// 列数の取得
		int nLineMax = pFile->GetLineSize(nRow);

		for (int nLine = 0; nLine < nLineMax; nLine++)
		{
			string sData = pFile->GetData(nRow, nLine);

			switch (nLine)
			{
			case 0:	pFile->ToValue(nType, sData); break;	// 種類
			case 1:	pFile->ToValue(pos.x, sData); break;	// 位置 X
			case 2:	pFile->ToValue(pos.y, sData); break;	// 位置 Y
			case 3:	pFile->ToValue(pos.z, sData); break;	// 位置 Z
			}
		}

		// 最大数に達したら返す
		if (nRow == nRowMax - 1)	// (列数 - 列の最大数 - ヘッダーの列数)
		{
			return;
		}

		// 配置
		CBlock *pObj = CBlock::Create(nType, pos);
	}

	// メモリ開放
	delete pFile;
	pFile = NULL;
}