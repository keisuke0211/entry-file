//========================================
// 
// imguiブロック処理
// 
//========================================
// *** imgui_block.h ***
//========================================
#ifndef _IMGUI_BLOCK_H_
#define _IMGUI_BLOCK_H_

#include "main.h"
#include "physics.h"

//****************************************
// クラス
//****************************************
class CImgui: public CPhysics
{
public:

	// ***** 列挙型 *****

	// ツールモード
	typedef enum
	{
		MODE_SET = 0,	// 配置
		MODE_DELETE,	// 削除
		MODE_MAX
	}MODE;

	// ファイルモード
	typedef enum
	{
		FILE_MODE_LODE = 0,	// 読み込み
		FILE_MODE_SAVE,		// 書き出し
		FILE_MODE_MAX
	}FILE_MODE;

	// ***** 関数 *****
	CImgui();
	~CImgui();

	/* メイン */

	HRESULT Init(HWND hWnd);	// 初期化
	void Uninit(void);			// 終了
	void Update(void);			// 更新
	static void Draw(void);		// 描画

	// -- 取得 ---------------------------------------------
	/* 位置			*/D3DXVECTOR3 GetPos(void) { return m_pos; }
	/* 移動量		*/D3DXVECTOR3 GetMove(void) { return m_move; }
	/* 向き			*/D3DXVECTOR3 GetRot(void) { return m_rot; }
	/* サイズ		*/D3DXVECTOR3 GetSize(void) { return m_size; }
	/* 色			*/D3DXCOLOR GetColor(void) { return m_col; }
	/* 種類			*/int GetType(void) { return m_nType; }
	/* ブロック数 X	*/int GetNumX(void) { return m_nNumX; }
	/* ブロック数 Y	*/int GetNumY(void) { return m_nNumY; }
	/* ブロック数 Z	*/int GetNumZ(void) { return m_nNumZ; }
	/* ブロックID	*/int GetID(void) { return m_Index; }
	/* モード取得	*/int GetMode(void) { return m_nMode; }

private:

	// ***** 関数 *****
	/* 移動処理		*/void MoveKeyboard(DIRECTION drct);
	/* メニュー処理	*/void MenuFile(void);
	/* ファイル選択	*/TCHAR FileSelect(void);
	/* ブロック		*/void SetBlock(void);

	// ***** 変数 *****
	D3DXVECTOR3 m_pos;		// 位置
	D3DXVECTOR3 m_posOld;	// 位置(過去)
	D3DXVECTOR3 m_move;		// 移動量
	D3DXVECTOR3 m_rot;		// 向き
	D3DXVECTOR3	m_size;		// サイズ
	D3DXCOLOR m_col;		// 頂点カラー
	int m_nType;			// 種類
	int m_nNumX;			// X ブロック数
	int m_nNumY;			// Y ブロック数
	int m_nNumZ;			// Z ブロック数
	float m_fWidth;			// 幅
	float m_fHeight;		// 高さ
	float m_fDepth;			// 奥行き
	int m_Index;			// ブロックID
	int m_nMode;			// ツールモード
	int m_nFileMode;		// ファイルモード
	bool m_bMode;			// モード表示
	bool m_bOp;				// 操作方法の表示フラグ
	bool m_bOpen;			// ファイルを開くか
	bool m_bSave;			// ファイルを保存するか

	static TCHAR m_szFile[MAX_PATH];	// 選択ファイルの格納変数

	D3DXVECTOR3 rot;		// 向き
	D3DXVECTOR3 moveRot;	// 移動向き
	D3DXVECTOR3 move;		// 移動量
};
#endif