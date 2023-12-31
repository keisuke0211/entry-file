//========================================
// 
// 物理関連 & 共通情報
// 
//========================================
//  *** physics.h ***
//========================================
#ifndef _PHYSICS_H_
#define _PHYSICS_H_
#include "main.h"

//****************************************
// クラス
//****************************************
class CPhysics
{
public:

	// ***** 列挙型 *****

	// モデル種類
	typedef enum
	{
		MODEL_GRASS_00 = 0,	// 草ブロック 1×1×1
		MODEL_GRASS_01,		// 草ブロック 3×1×1
		MODEL_GRASS_02,		// 草ブロック 5×1×1
		MODEL_GRASS_03,		// 草ブロック 3×3×1
		MODEL_GRASS_04,		// 草ブロック 5×5×1
		MODEL_SOIL_00,		// 土ブロック 1×1×1
		MODEL_SOIL_01,		// 土ブロック 3×1×1
		MODEL_SOIL_02,		// 土ブロック 5×1×1
		MODEL_SOIL_03,		// 土ブロック 1×3×1
		MODEL_SOIL_04,		// 土ブロック 1×5×1
		MODEL_BULLET,		// 弾
		MODEL_MAX
	}MODEL;

	// ベクトルの種類
	typedef enum
	{
		VECTOR_X,		// X方向
		VECTOR_Y,		// Y方向
		VECTOR_Z,		// Z方向
		VECTOR_NONE,	// 無し
		VECTOR_MAX
	}VECTOR;

	// 4方向
	typedef enum
	{
		DIRECTION_UP,			// 上
		DIRECTION_DOWN,			// 下
		DIRECTION_LEFT,			// 左
		DIRECTION_RIGHT,		// 右
		DIRECTION_BACK,			// 奥
		DIRECTION_FRONT,		// 手前

		DIRECTION_LEFT_BACK,	// 左奥
		DIRECTION_LEFT_FRONT,	// 左手前
		DIRECTION_RIGHT_BACK,	// 右奥
		DIRECTION_RIGHT_FRONT,	// 右手前
		DIRECTION_MAX,
	}DIRECTION;

	// ***** 関数 *****
	CPhysics();		// コンストラクタ
	~CPhysics();	// デストラクタ

	void IntControl(int *pData, int nMax, int nMin);				// int型の値の制御処理
	void IntLoopControl(int *pData, int nMax, int nMin);			// int型の値のループ制御処理
	void FloatControl(float *pData, float fMax, float fMin);		// float型の値の制御処理
	void FloatLoopControl(float *pData, float fMax, float fMin);	// float型の値のループ制御処理

	float FindAngle(D3DXVECTOR3 pos, D3DXVECTOR3 targetPos);		// 2点の角度を求める
	void RotControl(D3DXVECTOR3 *pRot);								// 向きを制御

	float AngleDifference(float fAngle, float fTargetAngle);		// 角度の差を求める
	void ControlAngle(float *pAngle);								// 角度の制御

private:

};
#endif