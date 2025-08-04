#include "CGame.h"
#include "Sound\\CSoundManager.h" // CSoundManager.hをインクルード

//コンストラクタ.
//初期化リストはメンバー変数の順番でする.
CGame::CGame(CDirectX9& pDx9, CDirectX11& pDx11, HWND hWnd)
	: m_pDx9				(&pDx9)
	, m_pDx11				(&pDx11)
	, m_hWnd				(hWnd)

	, m_pSpriteGround		(nullptr)
	, m_pSpriteExplosion	(nullptr) 

{
}


//デストラクタ.
CGame::~CGame()
{

}

//構築.
void CGame::Create()
{

	CSceneManager::GetInstance()->SetDx11(m_pDx11);
	CSceneManager::GetInstance()->SetDx9(m_pDx9);
}

//ロードデータ関数.
HRESULT CGame::LoadData()
{
	//サウンドデータの読み込み
	if (CSoundManager::GetInstance()->LoadSound(m_hWnd) == false) {
		return E_FAIL;
	}

	CSceneManager::GetInstance()->Create(m_hWnd);
	return S_OK;
}

//解放関数.
void CGame::Release()
{
}

//更新処理.
void CGame::Update()
{
	CSceneManager::GetInstance()->Update();
}

//描画処理.
void CGame::Draw()
{
	CSceneManager::GetInstance()->Drae();
}

//ゲーム初期化/リセット用関数
void CGame::Init()
{
}