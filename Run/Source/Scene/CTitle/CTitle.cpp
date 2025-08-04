#include "CTitle.h"
#include "Sound/CSoundManager.h"

CTitle::CTitle(CDirectX11* pDx11)
	: CSceneBase				( pDx11 )
	, m_pTitle					( nullptr )
	, m_pSpriteTitle			( nullptr )
	, m_pTitleObj				( nullptr )
	
	, m_isTransitioning			()
	, m_transitionDelayTimer	()
{
	CSoundManager::Play("Title", true);

}

CTitle::~CTitle()
{
	//これで音楽の停止になる.
	CSoundManager::StopAll();
}

void CTitle::Initialize()
{
	//遷移関連のフラグとタイマーをリセット
	m_isTransitioning = false;
	m_transitionDelayTimer = 0;
}

void CTitle::Create()
{
	m_pSpriteTitle = new CSprite2D();

	//タイトル構造体.
	CSprite2D::SPRITE_STATE SSTitle =
	{ 1280.f, 720.f, 896.f, 560.f, 896.f , 560.f};

	//タイトルスプライト読み込み.
	m_pSpriteTitle->Init(*m_pDx11,
		_T("Data\\Texture\\Title.png"), SSTitle);

	//UIObjをインスタンス生成.
	m_pTitleObj = new CUIObject();

	m_pTitleObj->AttachSprite(*m_pSpriteTitle);
}

void CTitle::Update()
{
	if (m_isTransitioning)
	{
		m_transitionDelayTimer--; // タイマーを減らす
		if (m_transitionDelayTimer <= 0)
		{
			CSceneManager::GetInstance()->LoadScene(CSceneManager::GameMain); // GameMainシーンへ遷移
			m_isTransitioning = false; // フラグをリセット
			return; // シーン遷移後はこのフレームの残りのUpdate処理はスキップ
		}
		// 遷移演出中も描画は続けるので、Draw() は Update() 外で呼ばれる前提
		// ここで他の入力や更新処理を停止したいので return;
		return;
	}
	if (GetAsyncKeyState(VK_RETURN) & 0x0001)
	{
		m_isTransitioning = true; // 遷移フラグを立てる
		m_transitionDelayTimer = TRANSITION_DELAY_FRAMES; // タイマーを開始
	}
}

void CTitle::Draw()
{
	m_pTitleObj->Draw();
}
