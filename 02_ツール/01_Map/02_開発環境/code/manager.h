//========================================
// 
// マネージャー処理
// 
//========================================
// *** manager.h ***
//========================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"

//****************************************
// 前方宣言
//****************************************
class CRenderer;		// レンダラー
class CCamera;			// カメラ
class CLight;			// ライト
class CTexture;			// テクスチャ
class CInputKeyboard;	// キーボード
class CInputMouse;		// マウス
class CInputJoypad;		// ジョイパット
class CBlock;			// ブロック
class CImgui;			// imGui
class CSetBlock;		// セットブロック

//****************************************
// クラス
//****************************************
class CManager
{
public:

	// ***** 関数 *****
	CManager();
	virtual~CManager();

	/* 初期化	*/HRESULT Init(HINSTANCE hinstance, HWND hWnd, BOOL bWindow);
	/* 終了		*/void Uninit(void);
	/* 更新		*/void Update(void);
	/* 描画		*/void Draw(void);

	// -- 取得 --------------------------------------
	/* レンダラー		*/static CRenderer *GetRenderer() { return m_pRenderer; }
	/* カメラ			*/static CCamera *GetCamera() { return m_pCamera; }
	/* ライト			*/static CLight *GetLight() { return m_pLight; }
	/* テクスチャ		*/static CTexture* GetTexture(){ return m_pTexture; }
	/* キーボード		*/static CInputKeyboard* GetInputKeyboard() { return m_InputKeyboard; }
	/* マウス			*/static CInputMouse* GetInputMouse() { return m_InputMouse; }
	/* ジョイパット		*/static CInputJoypad* GetInputJoypad() { return m_InputJoypad; }
	/* ブロック			*/static CBlock* GetBlock() { return m_pBlock; }
	/* セットブロック	*/static CSetBlock* GetSetBlock() { return m_pSetBlock; }
	/* imGui			*/static CImgui* GetImgui() { return m_pImgui; }

private:
	/* レンダラー		*/static CRenderer *m_pRenderer;
	/* カメラ			*/static CCamera *m_pCamera;
	/* ライト			*/static CLight *m_pLight;
	/* テクスチャ		*/static CTexture *m_pTexture;
	/* キーボード		*/static CInputKeyboard *m_InputKeyboard;
	/* マウス			*/static CInputMouse* m_InputMouse;
	/* ジョイパット		*/static CInputJoypad* m_InputJoypad;
	/* ブロック			*/static CBlock *m_pBlock;
	/* セットブロック	*/static CSetBlock *m_pSetBlock;
	/* imGui			*/static CImgui	*m_pImgui;
};
#endif