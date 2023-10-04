//========================================
// 
// 仮ブロック処理
// 
//========================================
// *** fast_block.h ***
//========================================
#ifndef _fcst_BLOCK_H_
#define _fcst_BLOCK_H_

#include "../main.h"
#include "objectX.h"

//****************************************
// クラス
//****************************************

// セットブロックのクラス
class CFcstBlock : public CObjectX
{
public:

	// ***** 関数 *****
	CFcstBlock(int nPriority = PRIO_OBJ3D);
	~CFcstBlock();

	/* メイン */
	static CFcstBlock *Create(int nType, D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	HRESULT Init(void);		// 初期化
	void Uninit(void);		// 終了
	void Update(void);		// 更新
	void Draw(void);		// 描画

	/* 位置			*/void FcstSetPos(const D3DXVECTOR3 pos) { m_SetInfo.pos = pos; }
	/* 向き			*/void FcstSetRot(const D3DXVECTOR3 rot) { m_SetInfo.rot = rot; }
	/* 色			*/void FcstSetColor(const D3DXCOLOR col) { m_SetInfo.col = col; }
	/* 種類			*/void FcstSetType(const int nType) { m_SetInfo.nType = nType; }

private:

	// ***** 構造体 *****

	// 配置情報
	typedef struct
	{
		D3DXVECTOR3 pos;	// 位置
		D3DXVECTOR3 rot;	// 向き
		D3DXVECTOR3 move;	// 移動量
		D3DXCOLOR col;		// 頂点カラー
		int nType;			// 種類
	} SetInfo;

	// ***** 変数 *****
	SetInfo m_SetInfo;	// セット情報
};

#endif