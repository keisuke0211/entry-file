//========================================
// 
// imgui�u���b�N����
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
// �R���X�g���N�^
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
// �f�X�g���N�^
//========================================
CImgui::~CImgui()
{

}

//========================================
// ������
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
// �I��
//========================================
void CImgui::Uninit(void)
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

//========================================
// �X�V
//========================================
void CImgui::Update(void)
{
	m_move = INIT_D3DXVECTOR3;

	// --- �擾---------------------------------
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// �L�[�{�[�h
	CInputMouse *pInputMouse = CManager::GetInputMouse();			// �}�E�X

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

	// ImGui�֐��̌Ăяo��
	{
		/* �E�C���h�E */
		ImGui::SetNextWindowPos(ImVec2(20.0f, 30.0f), ImGuiCond_Once);	// �ʒu
		ImGui::SetNextWindowSize(ImVec2(335, 580), ImGuiCond_Once);		// �T�C�Y
		ImGui::Begin(u8"�u���b�N�z�u", NULL, window_flags);				// ���O

		// ���j���[�o�[
		if (ImGui::BeginMenuBar())
		{
			MenuFile();

			ImGui::EndMenuBar();
		}

		/* �p�[�e�B�N�� */
		ImGui::InputInt(u8"���", &m_nType);

		// �z�u���[�h�̎�
		if (m_nMode == MODE_SET)
		{
			// ���Z�ƌ��Z
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

			// �ړ�����
			if (pInputKeyboard->GetPress(DIK_A))
			{
				if (pInputKeyboard->GetPress(DIK_W)) { MoveKeyboard(DIRECTION_LEFT_BACK); }			// �����ړ�
				else if (pInputKeyboard->GetPress(DIK_S)) { MoveKeyboard(DIRECTION_LEFT_FRONT); }	// ����O�ړ�
				else { MoveKeyboard(DIRECTION_LEFT); }		// ���ړ�
			}
			else if (pInputKeyboard->GetPress(DIK_D))
			{
				if (pInputKeyboard->GetPress(DIK_W)) { MoveKeyboard(DIRECTION_RIGHT_BACK); }		// �E���ړ�
				else if (pInputKeyboard->GetPress(DIK_S)) { MoveKeyboard(DIRECTION_RIGHT_FRONT); }	// �E��O�ړ�
				else { MoveKeyboard(DIRECTION_RIGHT); }		// �E�ړ�
			}
			else if (pInputKeyboard->GetPress(DIK_W)) { MoveKeyboard(DIRECTION_BACK); }				// ���ړ�
			else if (pInputKeyboard->GetPress(DIK_S)) { MoveKeyboard(DIRECTION_FRONT); }			// ��O�ړ�
		}
		// �ʒu�̐ݒ�
		if (ImGui::TreeNode(u8"�ʒu"))
		{
			ImGui::DragFloat3(" ", m_pos);

			if (ImGui::Button(u8"������"))
				m_pos = INIT_D3DXVECTOR3;

			ImGui::TreePop();
		}

		m_move = m_pos - m_posOld;

		// �����̐ݒ�
		if (ImGui::TreeNode(u8"����"))
		{
			ImGui::DragFloat3(" ", m_rot, 0.01f);
			if (ImGui::Button(u8"������"))
				m_rot = INIT_D3DXVECTOR3;

			ImGui::TreePop();
		}

		// �u���b�N��
		ImGui::SeparatorText(u8"�u���b�N��");
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

		/* �I�� */
		ImGui::End();
	}

	{
		ImGui::SetNextWindowPos(ImVec2(980.0f, 50.0f), ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(275, 200), ImGuiCond_Once);	
		ImGui::Begin(u8"������@", &m_bMode);
		ImGui::Text(u8"�u���b�N�ړ� �@�@�FW A S D");
		ImGui::Text(u8"�u���b�N��� ���Z�FE");
		ImGui::Text(u8"�@�@�@�@�@�@ ���Z�FQ");
		ImGui::Text(u8"�J�����̎��_�ړ� �F�}�E�X�@���C�g�{�^��");

		/* �I�� */
		ImGui::End();
	}

	{
		ImGui::SetNextWindowPos(ImVec2(1000.0f, 450.0f), ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(250, 200), ImGuiCond_Once);
		ImGui::Begin(u8"���[�h", &m_bMode);


		// �폜���[�h�̎�
		if (m_nMode == MODE_DELETE)
		{
			// ���Z�ƌ��Z
			if (pInputKeyboard->GetTrigger(DIK_Q))
			{
				m_Index--;
			}
			else if (pInputKeyboard->GetTrigger(DIK_E))
			{
				m_Index++;
			}
		}

		ImGui::InputInt(u8"�ԍ�", &m_Index);

		if (m_Index > (CBlock::GetNumAll() - 1))
		{
			m_Index = 0;
		}
		if (m_Index < 0)
		{
			m_Index = (CBlock::GetNumAll() - 1);
		}

		// ���[�h�ؑ�
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

		const char* sType[] = { u8"�z�u", u8"�폜" };
		ImGui::Combo(u8"���[�h", &m_nMode, sType, IM_ARRAYSIZE(sType));

		ImGui::Text(u8"FPS		 �F(%d)", GetFps());
		ImGui::Text(u8"�u���b�N���F(%d)", CBlock::GetNumAll());

		/* �I�� */
		ImGui::End();
	}

	ImGui::EndFrame();
}

//========================================
// �`��
//========================================
void CImgui::Draw(void)
{
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

//========================================
// �ړ�����
//========================================
void CImgui::MoveKeyboard(DIRECTION drct)
{
	CCamera *pCamera = CManager::GetCamera();						// �J����

	// --- ��� ---------------------------------
	moveRot = rot;	// �ړ�����

	// --- �ړ� ---------------------------------

	// �ړ������ɉ~��������
	moveRot.y = D3DX_PI;

	switch (drct)
	{
	case DIRECTION_LEFT:moveRot.y *= -0.5f; break;	// ��
	case DIRECTION_RIGHT:moveRot.y *= 0.5f;	break;	// �E
	case DIRECTION_BACK:moveRot.y *= 0.0f;	break;	// ��
	case DIRECTION_FRONT:moveRot.y *= 1.0f;	break;	// ��O
	case DIRECTION_LEFT_BACK:moveRot.y *= -0.25f; break;	// ����
	case DIRECTION_LEFT_FRONT:moveRot.y *= -0.75f; break;	// ����O
	case DIRECTION_RIGHT_BACK:moveRot.y *= 0.25f; break;	// �E��
	case DIRECTION_RIGHT_FRONT:moveRot.y *= 0.75f; break;	// �E��O
	}

	D3DXVECTOR3 posV = pCamera->GetInfo().posV;	// ���_
	D3DXVECTOR3 posR = pCamera->GetInfo().posR;	// �����_

	// ���_���璍���_�܂ł̊p�x
	float fAngle
		= FindAngle(D3DXVECTOR3(posV.x, posV.z, 0.0f), D3DXVECTOR3(posR.x, posR.z, 0.0f));

	moveRot.y += fAngle;

	m_pos.x += sinf(moveRot.y) * 5;
	m_pos.z += cosf(moveRot.y) * 5;
}

//========================================
// ���j���[����
//========================================
void CImgui::MenuFile(void)
{
	if (ImGui::BeginMenu(u8"�t�@�C��"))
	{
		if (ImGui::MenuItem(u8"�ǂݍ���"))
		{
			// ���[�h�ݒ�
			m_nFileMode = FILE_MODE_LODE;

			// �t�@�C���I���̃_�C�A���O�\��
			FileSelect();

			// �J��(O)�n�{�^���������ꂽ��
			if (m_bOpen)
			{
				//�ǂݍ���
				CBlock::Load(m_szFile);
				m_bOpen = false;
			}
		}
		if (ImGui::MenuItem(u8"��������"))
		{
			// ���[�h�ݒ�
			m_nFileMode = FILE_MODE_SAVE;

			// �t�@�C���I���̃_�C�A���O�\��
			FileSelect();

			// �m�ۑ�(S)�n�{�^���������ꂽ��
			if (m_bSave)
			{
				// �����o��
				CBlock::Save(m_szFile);
				m_bSave = false;
			}
		}
		ImGui::EndMenu();
	}
}

//========================================
// �t�@�C���I��
//========================================
TCHAR CImgui::FileSelect(void)
{
	HWND *pHwnd = GetWindowHandle();

	static OPENFILENAME     ofn;
	static TCHAR            szPath[MAX_PATH];	// �����t�H���_�ʒu�̊i�[�ϐ�
	static TCHAR            szFile[MAX_PATH];	// �I���t�@�C���̊i�[�ϐ�

	// �t�@�C���I���̃_�C�A���O�\��
	if (szPath[0] == TEXT('\0'))
	{
		GetCurrentDirectory(MAX_PATH, szPath);
	}
	if (ofn.lStructSize == 0) {
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = *pHwnd;
		ofn.lpstrInitialDir = szPath;	// �����t�H���_�ʒu
		ofn.lpstrFile = m_szFile;		// �I���t�@�C��
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrFilter =
			//TEXT("�e�L�X�g����(*.txt)\0*.txt\0")
			TEXT("CSV(�R���}��؂�)(*.csv)\0*.csv\0")
			//TEXT("���ׂẴt�@�C��(*.*)\0*.*\0")
			;

		if (m_nFileMode == FILE_MODE_LODE)
		{
			ofn.lpstrTitle = TEXT("�t�@�C�����J��");
		}
		else if (m_nFileMode == FILE_MODE_SAVE)
		{
			ofn.lpstrTitle = TEXT("���O��t���ĕۑ�");
		}
		ofn.Flags = OFN_FILEMUSTEXIST;
	}

	if (m_nFileMode == FILE_MODE_LODE)
	{
		// �J��(O)�n�{�^���������ꂽ��
		if (GetOpenFileName(&ofn))
		{
			m_bOpen = true;
		}
	}
	else if (m_nFileMode == FILE_MODE_SAVE)
	{
		// �m�ۑ�(S)�n�{�^���������ꂽ��
		if (GetSaveFileName(&ofn))
		{
			m_bSave = true;
		}
	}
	return szFile[0];
}

//========================================
// �u���b�N�z�u
//========================================
void CImgui::SetBlock(void)
{
	CSVFILE *pFile = new CSVFILE;

	// �ǂݍ���
	pFile->FileLood("data\\GAMEDATA\\BLOCK\\STAGE_DATA1.csv", true, true, ',');

	// �s���̎擾
	int nRowMax = pFile->GetRowSize();

	// �e�f�[�^�ɑ��
	for (int nRow = 0; nRow < nRowMax; nRow++)
	{
		// �z�u���̐���
		int nType;				// ���
		D3DXVECTOR3 pos;		// �ʒu

								// �񐔂̎擾
		int nLineMax = pFile->GetLineSize(nRow);

		for (int nLine = 0; nLine < nLineMax; nLine++)
		{
			string sData = pFile->GetData(nRow, nLine);

			switch (nLine)
			{
			case 0:	pFile->ToValue(nType, sData); break;	// ���
			case 1:	pFile->ToValue(pos.x, sData); break;	// �ʒu X
			case 2:	pFile->ToValue(pos.y, sData); break;	// �ʒu Y
			case 3:	pFile->ToValue(pos.z, sData); break;	// �ʒu Z
			}
		}

		// �ő吔�ɒB������Ԃ�
		if (nRow == nRowMax - 1)	// (�� - ��̍ő吔 - �w�b�_�[�̗�)
		{
			return;
		}

		// �z�u
		CBlock *pObj = CBlock::Create(nType, pos);
	}

	// �������J��
	delete pFile;
	pFile = NULL;
}