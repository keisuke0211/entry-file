//========================================
// 
// ブロック処理
// 
//========================================
// *** block.h ***
//========================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "../main.h"
#include "objectX.h"

//========================================
// マクロ定義
//========================================
#define MAX_BLOCK (4096)	// 最大ブロック

//****************************************
// クラス
//****************************************
class CBlock : public CObjectX
{
public:

	// ***** 構造体 *****

	// プレイヤー情報
	typedef struct
	{
		D3DXVECTOR3 pos;		// 位置
		D3DXVECTOR3 posOld;		// 位置(過去)
		D3DXVECTOR3 rot;		// 向き
		D3DXVECTOR3 rotOld;		// 向き(過去)
		D3DXVECTOR3	size;		// サイズ
		D3DXCOLOR col;			// 頂点カラー
		int nType;				// 種類
		int nLife;				// 寿命
		int nLifeMax;			// 寿命の最大値
		float fRadius;			// 半径
		int nCntRadius;			// 半径・推移時間
		float fRadiusRate;		// 半径の割合
		bool bSet;				// 配置フラグ
		float Width;			// 幅
		float Height;			// 高さ
		float Depth;			// 奥行き
		int nID;				// 自身のID
	} Info;

	// ***** 関数 *****
	CBlock(int nPriority = PRIO_OBJX);
	~CBlock();

	/* メイン */

	// 生成
	static CBlock *Create(int nType,D3DXVECTOR3 pos/*, D3DXVECTOR3 rot*/);

	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画
	
	static void Load(string filepath);	// 読み込み
	static void Save(string filepath);	// 書き出し
	static void SetBlock(int nNumSet);	// 配置
	static void UnLoad(void);			// 破棄

	/* 設定 */
	virtual void BlockSetPos(const D3DXVECTOR3 pos) { m_Info.pos = pos; }	// 位置
	void BlockSetRot(const D3DXVECTOR3 rot) { m_Info.rot = rot; }			// 向き
	void BlockSetColor(const D3DXCOLOR col) { m_Info.col = col; }			// 色
	void BlockSetSize(const D3DXVECTOR3 size) { m_Info.size = size; }		// 大きさ

	/* 所得 */
	D3DXVECTOR3 BlockGetPos(void) { return m_Info.pos; }					// 位置
	D3DXVECTOR3 GetRot(void) { return m_Info.rot; }							// 向き
	D3DXCOLOR BlockGetColor(void) { return m_Info.col; }					// 色
	D3DXVECTOR3 BlockGetSize(void) { return m_Info.size; }					// 大きさ
	static int GetNumAll() { return m_nNumAll; };							// ブロックの総数

private:

	// ***** 列挙型 *****

	// 設定項目
	typedef enum
	{
		SET_TYPE,	// 種類
		SET_POS,	// 位置
		SET_POS_Y,	// 位置 Y
		SET_POS_Z,	// 位置 Z
		SET_NUM,	// ブロック数
		SET_NUM_Y,	// ブロック数 Y
		SET_NUM_Z,	// ブロック数 Z
		SET_MAX,
	}SET;

	// ***** 構造体 *****

	// 配置情報
	typedef struct
	{
		D3DXVECTOR3 pos;	// 位置
		D3DXVECTOR3 rot;	// 向き
		int nType;			// 種類
		int nNumX;			// X ブロック数
		int nNumY;			// Y ブロック数
		int nNumZ;			// Z ブロック数
		float Width;		// 幅
		float Height;		// 高さ
		float Depth;		// 奥行き
	} SetInfo;

	// ***** 変数 *****
	Info m_Info;				// プレイヤー情報
	static SetInfo *pSetInfo;	// セット情報

	static CBlock *m_apBlock[MAX_BLOCK];	// ブロックのポインタ配列
	static int m_nNumAll;					// ブロックの総数

	static const string m_aBlockName[MODEL_BULLET];

};
#endif