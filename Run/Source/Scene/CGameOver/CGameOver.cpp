#include "CGameOver.h"
#include "Sound/CSoundManager.h"

CGameOver::CGameOver(CDirectX11* pDx11)
	: CSceneBase		( pDx11 )
	, m_pGameOver		( nullptr )
	, m_pSpriteGameOver	( nullptr )
	, m_pGameOverObj	( nullptr )
{

}

CGameOver::~CGameOver()
{
}

void CGameOver::Initialize()
{
}

void CGameOver::Create()
{
	m_pSpriteGameOver = new CSprite2D();

	//�^�C�g���\����.
	CSprite2D::SPRITE_STATE SSGameOver =
	{ 1280.f, 720.f, 896.f, 560.f, 896.f , 560.f };

	//�^�C�g���X�v���C�g�ǂݍ���.
	m_pSpriteGameOver->Init(*m_pDx11,
		_T("Data\\Texture\\GameOver.png"), SSGameOver);

	//UIObj���C���X�^���X����.
	m_pGameOverObj = new CUIObject();

	m_pGameOverObj->AttachSprite(*m_pSpriteGameOver);
}

void CGameOver::Update()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x0001)
	{
		CSceneManager::GetInstance()->LoadScene(CSceneManager::Title);
	}
}

void CGameOver::Draw()
{
	m_pGameOverObj->Draw();
}
