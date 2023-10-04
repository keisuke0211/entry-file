//========================================
// 
// ブロック処理
// 
//========================================
// *** block.cpp ***
//========================================
#include "block.h"
#include "model.h"
#include "../csv_file.h"

//========================================
// マクロ定義
//========================================
#define RADIUS_TIME	(20)	// 半径・推移時間
#define BULLET_ID	(2)		// 弾ID
#define NUM_DATA	(4)		// データ数

// 静的変数
CBlock::SetInfo *CBlock::pSetInfo = NULL;
int CBlock::m_nNumAll = 0;					// オブジェクト総数
CBlock *CBlock::m_apBlock[MAX_BLOCK] = {};	// ブロックのポインタ

const string CBlock::m_aBlockName[MODEL_BULLET] = {
	"草 00",
	"草 01",
	"草 02",
	"草 03",
	"草 04",
	"土 00",
	"土 01",
	"土 02",
	"土 03",
	"土 04",
};

//========================================
// コンストラクタ
//========================================
CBlock::CBlock(int nPriority) : CObjectX(nPriority)
{
	for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
	{
		if (m_apBlock[nCnt] == NULL)
		{
			m_apBlock[nCnt] = this;	// 自分自身を代入
			break;
		}
	}

	// 値をクリア
	m_Info.pos = INIT_D3DXVECTOR3;
	m_Info.posOld = INIT_D3DXVECTOR3;
	m_Info.rot = INIT_D3DXVECTOR3;
	m_Info.rotOld = INIT_D3DXVECTOR3;
	m_Info.size = INIT_D3DXVECTOR3;
	m_Info.col = INIT_D3DXCOLOR;
	m_Info.nType = 0;
	m_Info.nLife = 0;
	m_Info.nLifeMax = 0;
	m_Info.fRadius = 0.0f;
	m_Info.nCntRadius = 0;
	m_Info.fRadiusRate = 0.0f;
	m_Info.Width = 0.0f;
	m_Info.Height = 0.0f;
	m_Info.Depth = 0.0f;
	m_Info.bSet = false;

	m_nNumAll++;
	m_Info.nID = m_nNumAll - 1;

}

//========================================
// デストラクタ
//========================================
CBlock::~CBlock()
{
	m_nNumAll--;
}

//========================================
// 生成
//========================================
CBlock *CBlock::Create(int nType,D3DXVECTOR3 pos/*, D3DXVECTOR3 rot*/)
{
	CBlock *pBlock = NULL;

	if (pBlock != NULL)
	{
		return pBlock;
	}

	// ブロックの生成
	pBlock = new CBlock;

	if (nType == MODEL_BULLET)
	{
		pBlock->m_Info.nCntRadius = RADIUS_TIME;
		pBlock->m_Info.fRadiusRate = 0.0f;
		pBlock->m_Info.bSet = false;
	}
	else
	{
		pBlock->m_Info.bSet = false;
	}

	pBlock->SetModel(nType);

	// 初期化処理
	pBlock->Init();

	//pBlock->m_Info.rot = rot;
	pBlock->m_Info.nType = nType;
	pBlock->m_Info.nLife = 300;
	pBlock->m_Info.nLifeMax = 300;
	pBlock->BlockSetPos(pos);

	m_apBlock[m_nNumAll - 1]->m_Info.nType = pBlock->m_Info.nType;
	m_apBlock[m_nNumAll - 1]->m_Info.pos = pBlock->m_Info.pos;
	m_apBlock[m_nNumAll - 1]->m_Info.rot = pBlock->m_Info.rot;

	return pBlock;
}

//========================================
// 初期化
//========================================
HRESULT CBlock::Init(void)
{
	CObjectX::Init();

	// 種類の設定
	SetType(TYPE_BLOCK);

	m_Info.pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.size = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Info.col = INIT_D3DXCOLOR;
	m_Info.nType = 0;
	m_Info.fRadius = 1.0f;

	// 生成
	SetPos(m_Info.pos);
	//SetRot(m_Info.rot);
	SetScale(m_Info.size);
	SetColor(m_Info.col);

	return S_OK;
}

//========================================
// 終了
//========================================
void CBlock::Uninit(void)
{

	int nID = m_Info.nID;
	
	CObjectX::Uninit();

	if (m_apBlock[nID] != NULL)
	{
		/*delete m_apBlock[nID];*/
		m_apBlock[nID] = NULL;
	}
}

//========================================
// 更新
//========================================
void CBlock::Update(void)
{
	// 過去の位置・向きの更新
	m_Info.posOld = m_Info.pos;
	m_Info.rotOld = m_Info.rot;

	// 半径推移
	if (m_Info.bSet == false && m_Info.nType == MODEL_BULLET)
	{
		m_Info.fRadiusRate = (float)m_Info.nCntRadius / (float)RADIUS_TIME;
		m_Info.fRadius = 1 * (1.0f - m_Info.fRadiusRate);

		if (--m_Info.nCntRadius <= 0)
		{
			m_Info.bSet = true;
		}
	}

	// 寿命
	if (--m_Info.nLife <= 0 && m_Info.bSet == true)
	{
		Uninit();
		return;
	}
	else if (m_Info.nLife <= RADIUS_TIME && m_Info.bSet == true)
	{
		m_Info.fRadius -= m_Info.fRadius / m_Info.nLife;
		m_Info.col.a *= ((float)m_Info.nLife / RADIUS_TIME);

		SetColor(m_Info.col);
	}

	// サイズの更新
	m_Info.size = D3DXVECTOR3(m_Info.fRadius, m_Info.fRadius, m_Info.fRadius);

	SetPos(m_Info.pos);
	//SetRot(m_Info.rot);
	SetScale(m_Info.size);

	CObjectX::Update();
}

//========================================
// 描画
//========================================
void CBlock::Draw(void)
{
	CObjectX::Draw();
}

//========================================
// 読み込み
//========================================
void CBlock::Load(string filepath)
{
	CSVFILE *pFile = new CSVFILE;

	// 読み込み
	pFile->FileLood(filepath, true, true, ',');

	// 行数の取得
	int nRowMax = pFile->GetRowSize();

	// 確保
	pSetInfo = new SetInfo;

	SetInfo* keep = pSetInfo;

	for (int nRow = 0; nRow < nRowMax; nRow++)
	{
		// 列数の取得
		int nLineMax = pFile->GetLineSize(nRow);

		for (int nLine = 0; nLine < nLineMax; nLine++)
		{
			string sData = pFile->GetData(nRow, nLine);

			switch (nLine)
			{
			case 0:	pFile->ToValue(pSetInfo->nType, sData); break;	// 種類
			case 1:	pFile->ToValue(pSetInfo->pos.x, sData); break;	// 位置 X
			case 2:	pFile->ToValue(pSetInfo->pos.y, sData); break;	// 位置 Y
			case 3:	pFile->ToValue(pSetInfo->pos.z, sData); break;	// 位置 Z
			}
		}
		pSetInfo++;
	}

	// 先頭位置に戻す
	pSetInfo = keep;

	// 配置
	SetBlock(nRowMax - 1);

	delete pFile;
	pFile = NULL;
}

//========================================
//	書き出し
//========================================
void CBlock::Save(string filepath)
{
	CSVFILE *pFile = new CSVFILE;

	// ヘッダーの設定
	pFile->SetHeader("種類,位置 X,Y,Z", ',');

	// データの設定
	for (int nRow = 0; nRow < m_nNumAll; nRow++)
	{
		// インデックスの設定
		pFile->SetIndex(m_aBlockName[m_apBlock[nRow]->m_Info.nType], ',');

		for (int nLine = 0; nLine < NUM_DATA; nLine++)
		{
			string sData;	// 文字列の格納する変数
			
			// 文字列に変換
			switch (nLine)
			{
			case 0:	sData = pFile->CastCell(m_apBlock[nRow]->m_Info.nType); break;	// 種類
			case 1:	sData = pFile->CastCell(m_apBlock[nRow]->m_Info.pos.x); break;	// 位置 X
			case 2:	sData = pFile->CastCell(m_apBlock[nRow]->m_Info.pos.y); break;	// 位置 Y
			case 3:	sData = pFile->CastCell(m_apBlock[nRow]->m_Info.pos.z); break;	// 位置 Z
			}

			// データの追加
			pFile->SetCell(sData, nRow, nLine);
		}
	}

	// 書き出し
	pFile->FileSave(filepath, ',');
}

//========================================
// 配置
//========================================
void CBlock::SetBlock(int nNumSet)
{
	for (int nCntSet = 0; nCntSet < nNumSet; nCntSet++, pSetInfo++)
	{
		CBlock::Create(pSetInfo->nType,
			D3DXVECTOR3(
				pSetInfo->pos.x,
				pSetInfo->pos.y,
				pSetInfo->pos.z)/*,
			pSetInfo->rot*/);
	}
}

//========================================
// 破棄
//========================================
void CBlock::UnLoad(void)
{
	if (pSetInfo != NULL)
	{
		delete pSetInfo;
		pSetInfo = NULL;
	}

	for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
	{
		if (m_apBlock[nCnt] != NULL)
		{
			delete m_apBlock[nCnt];
			m_apBlock[nCnt] = NULL;
		}
	}
}