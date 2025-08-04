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
	//����ŉ��y�̒�~�ɂȂ�.
	CSoundManager::StopAll();
}

void CTitle::Initialize()
{
	//�J�ڊ֘A�̃t���O�ƃ^�C�}�[�����Z�b�g
	m_isTransitioning = false;
	m_transitionDelayTimer = 0;
}

void CTitle::Create()
{
	m_pSpriteTitle = new CSprite2D();

	//�^�C�g���\����.
	CSprite2D::SPRITE_STATE SSTitle =
	{ 1280.f, 720.f, 896.f, 560.f, 896.f , 560.f};

	//�^�C�g���X�v���C�g�ǂݍ���.
	m_pSpriteTitle->Init(*m_pDx11,
		_T("Data\\Texture\\Title.png"), SSTitle);

	//UIObj���C���X�^���X����.
	m_pTitleObj = new CUIObject();

	m_pTitleObj->AttachSprite(*m_pSpriteTitle);
}

void CTitle::Update()
{
	if (m_isTransitioning)
	{
		m_transitionDelayTimer--; // �^�C�}�[�����炷
		if (m_transitionDelayTimer <= 0)
		{
			CSceneManager::GetInstance()->LoadScene(CSceneManager::GameMain); // GameMain�V�[���֑J��
			m_isTransitioning = false; // �t���O�����Z�b�g
			return; // �V�[���J�ڌ�͂��̃t���[���̎c���Update�����̓X�L�b�v
		}
		// �J�ډ��o�����`��͑�����̂ŁADraw() �� Update() �O�ŌĂ΂��O��
		// �����ő��̓��͂�X�V�������~�������̂� return;
		return;
	}
	if (GetAsyncKeyState(VK_RETURN) & 0x0001)
	{
		m_isTransitioning = true; // �J�ڃt���O�𗧂Ă�
		m_transitionDelayTimer = TRANSITION_DELAY_FRAMES; // �^�C�}�[���J�n
	}
}

void CTitle::Draw()
{
	m_pTitleObj->Draw();
}
