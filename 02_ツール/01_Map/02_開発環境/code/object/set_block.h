//========================================
// 
// セットブロック処理
// 
//========================================
// *** set_block.h ***
//========================================
#ifndef _SET_BLOCK_H_
#define _SET_BLOCK_H_

#include "../main.h"
#include "objectX.h"

//****************************************
// クラス
//****************************************

// セットブロックのクラス
class CSetBlock : public CObjectX
{
public:

	// ***** 関数 *****
	CSetBlock(int nPriority = PRIO_OBJX);
	~CSetBlock();

	/* メイン */
	static CSetBlock *Create(void);

	HRESULT Init(void);		// 初期化
	void Uninit(void);		// 終了
	void Update(void);		// 更新
	void Draw(void);		// 描画
	void Delete(int nId);	// 削除

private:

	// ***** 構造体 *****

	// 配置情報
	typedef struct
	{
		D3DXVECTOR3 pos;	// 位置
		D3DXVECTOR3 rot;	// 向き
		D3DXCOLOR col;		// 頂点カラー
		int nType;			// 種類
		int nNumX;			// X ブロック数
		int nNumY;			// Y ブロック数
		int nNumZ;			// Z ブロック数
		float fWidth;		// 幅
		float fHeight;		// 高さ
		float fDepth;		// 奥行き
	} Set;

	// ***** 関数 *****
	void SetFcstBlock(void);

	// ***** 変数 *****
	Set m_Set;								// 配置情報
	bool m_bDelete;		// 削除フラグ
};

#endif