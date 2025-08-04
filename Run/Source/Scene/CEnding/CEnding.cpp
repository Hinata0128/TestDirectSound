#include "CEnding.h"
#include "Sound/CSoundManager.h"

CEnding::CEnding(CDirectX11* pDx11)
	: CSceneBase		( pDx11 )
	, m_pEnding			( nullptr )
	, m_pSpriteEnding	( nullptr )
	, m_pEndingObj		( nullptr )
{

}

CEnding::~CEnding()
{
}

void CEnding::Initialize()
{
}

void CEnding::Create()
{
	m_pSpriteEnding = new CSprite2D();

	//�^�C�g���\����.
	CSprite2D::SPRITE_STATE SSTitle =
	{ 1280.f, 720.f, 896.f, 560.f, 896.f , 560.f };

	//�^�C�g���X�v���C�g�ǂݍ���.
	m_pSpriteEnding->Init(*m_pDx11,
		_T("Data\\Texture\\Ending.png"), SSTitle);

	//UIObj���C���X�^���X����.
	m_pEndingObj = new CUIObject();

	m_pEndingObj->AttachSprite(*m_pSpriteEnding);
}

void CEnding::Update()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x0001)
	{
		CSceneManager::GetInstance()->LoadScene(CSceneManager::Title);
	}
}

void CEnding::Draw()
{
	m_pEndingObj->Draw();
}
