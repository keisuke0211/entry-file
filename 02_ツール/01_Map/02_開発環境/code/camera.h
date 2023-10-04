//========================================
// 
// カメラ処理
// 
//========================================
// *** camera.h ***
//========================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"
#include "physics.h"

//****************************************
// マクロ定義
//****************************************
#define CAMERA_SPEED			(50)					// 移動速度（X・Z座標）
#define CAMERA_SPEED1			(2)						// 移動速度（Y座標）
#define ROT_SPEED				(0.015f)				// 回転スピード
#define SPIN_DAMP				(0.9f)					// 回転の減衰量
#define ROT_CURSOR	(D3DXVECTOR3(0.0005f,0.00075f,0.0f))// カメラのカーソルの回転力

//****************************************
// クラス
//****************************************
class CCamera : public CPhysics
{
public:

	// ***** 列挙型 *****

	// カメラの投影種類
	typedef enum
	{
		SCREEN_NONE = 0,	// 無し
		SCREEN_2D,			// 平行投影
		SCREEN_3D,			// 透視投影
		SCREEN_MAX
	}SCREEN;

	// ***** 構造体 *****

	// カメラ情報
	typedef struct
	{
		D3DXMATRIX mtxProjection;	// プロジェクションマトリックス
		D3DXMATRIX mtxView;			// ビューマトリックス

		D3DXVECTOR3 posV;			// 現在の視点
		D3DXVECTOR3 posR;			// 現在の注視点
		D3DXVECTOR3 posOldV;		// 前回の視点
		D3DXVECTOR3 posOldR;		// 前回の注視点
		D3DXVECTOR3 vecU;			// 上方向ベクトル
		D3DXVECTOR3 rot;			// 向き
		D3DXVECTOR3 spin;			// 回転量

		int nScreen;				// 投影モード

		float fDistance;			// 距離
		float fHeight;				// 高さ
		float fVerticalMove;		// 縦の移動量
	} Info;

	// ***** 関数 *****
	CCamera();	// コンストラクタ
	~CCamera();	// デストラクタ

	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新

	/* 設定 */
	void SetCamera(void);							// カメラ
	void SetScreen(void);							// 画面設定
	void SetPosV(D3DXVECTOR3 pos, int nIdx = 0);	// 視点
	void SetPosR(D3DXVECTOR3 pos, int nIdx = 0);	// 注視点

	/* 取得 */
	Info GetInfo() { return m_Info; }			// プレイヤー情報
	int GetScreen() { return m_Info.nScreen; }	// スクリーンモード

private:

	// ***** 構造体 *****

	// カメラの保存情報
	typedef struct
	{
		D3DXVECTOR3 posV;			// 視点
		D3DXVECTOR3 posR;			// 注視点
		D3DXVECTOR3 rot;			// 向き
		D3DXVECTOR3 spin;			// 回転量

		float fDistance;			// 距離
		float fHeight;				// 高さ
		float fVerticalMove;		// 縦の移動量
	} Save;

	// ***** 関数 *****
	void AxisRotationCamera(DIRECTION drct, float fRot, int nIdx = 0); //回転処理

	// ***** 変数 *****
	Info m_Info;		// カメラ
	Save m_Save;		// 保存 

	D3DXVECTOR3 m_FixPosR;	// 注視点の固定
	bool m_bRot;			// 視点移動フラグ

};

#endif