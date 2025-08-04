#include "CGame.h"
#include "Sound\\CSoundManager.h" // CSoundManager.h���C���N���[�h

//�R���X�g���N�^.
//���������X�g�̓����o�[�ϐ��̏��Ԃł���.
CGame::CGame(CDirectX9& pDx9, CDirectX11& pDx11, HWND hWnd)
	: m_pDx9				(&pDx9)
	, m_pDx11				(&pDx11)
	, m_hWnd				(hWnd)

	, m_pSpriteGround		(nullptr)
	, m_pSpriteExplosion	(nullptr) 

{
}


//�f�X�g���N�^.
CGame::~CGame()
{

}

//�\�z.
void CGame::Create()
{

	CSceneManager::GetInstance()->SetDx11(m_pDx11);
	CSceneManager::GetInstance()->SetDx9(m_pDx9);
}

//���[�h�f�[�^�֐�.
HRESULT CGame::LoadData()
{
	//�T�E���h�f�[�^�̓ǂݍ���
	if (CSoundManager::GetInstance()->LoadSound(m_hWnd) == false) {
		return E_FAIL;
	}

	CSceneManager::GetInstance()->Create(m_hWnd);
	return S_OK;
}

//����֐�.
void CGame::Release()
{
}

//�X�V����.
void CGame::Update()
{
	CSceneManager::GetInstance()->Update();
}

//�`�揈��.
void CGame::Draw()
{
	CSceneManager::GetInstance()->Drae();
}

//�Q�[��������/���Z�b�g�p�֐�
void CGame::Init()
{
}