#include "CSceneManager.h"
#include "Sound/CSoundManager.h"

CSceneManager::CSceneManager()
	: m_pScene	( nullptr )
	, m_hWnd	()
	, m_pDx11	()
	, m_pDx9	()
{

}

CSceneManager::~CSceneManager()
{
}

HRESULT CSceneManager::Create(HWND hWnd)
{
	m_hWnd = hWnd;
	LoadScene(List::Title);
	return S_OK;
}

void CSceneManager::Update()
{
	m_pScene->Update();
}

void CSceneManager::Drae()
{
	m_pScene->Draw();
}

void CSceneManager::LoadScene(List Scene)
{
	m_pScene.reset();

	//�V�[���쐬.
	MakeScene(Scene);
	m_pScene->Create();
}

HWND CSceneManager::GetHWND() const
{
	return m_hWnd;
}

//�V�[���쐬.
void CSceneManager::MakeScene(List Scene)
{
	switch (Scene)
	{
	case CSceneManager::Title:
		m_pScene = std::make_unique<CTitle>(m_pDx11);
		break;
	case CSceneManager::GameMain:
		m_pScene = std::make_unique<CGameMain>(m_pDx9, m_pDx11);
		break;
	case CSceneManager::GameOver:
		m_pScene = std::make_unique<CGameOver>(m_pDx11);
		break;
	case CSceneManager::Ending:
		m_pScene = std::make_unique<CEnding>(m_pDx11);
		break;
	default:
		break;
	}
}
