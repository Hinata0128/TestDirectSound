#include "CPlayer.h"
#include "Sound\\CSoundManager.h" // �K�v�ł���Ό��ʉ��}�l�[�W���[

// CPlayer�N���X�̃R���X�g���N�^
CPlayer::CPlayer()
	: m_ShotCoolDown(0) // �N�[���_�E���J�E���^�[��������
	// �R���X�g���N�^���������X�g�ł� m_pShot(0) �͔z��ɂ͕s�v�Ȃ̂ō폜���܂���
{
}

// CPlayer�N���X�̃f�X�g���N�^
CPlayer::~CPlayer()
{
}

// �v���C���[�̏�Ԃ��X�V���郁�\�b�h�i���t���[���Ăяo�����z��j
void CPlayer::Update()
{
	float add_value = 0.1f;

	if (GetAsyncKeyState(VK_UP) & 0x8000) {

		if (m_vPosition.y <= WallUP)
		{
			m_vPosition.y += add_value;
		}
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		if (m_vPosition.y >= WallDOWN)
		{
			m_vPosition.y -= add_value;
		}
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		if (m_vPosition.x <= WallRIGHT)
		{
			m_vPosition.x += add_value;
		}
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		if (m_vPosition.x >= WallLEFT)
		{
			m_vPosition.x -= add_value;
		}
	}

	// ���̏������Ȃ��ƁA��x�e�𔭎˂�����N�[���_�E�����i���ɏI��炸�A��x�ƒe�����˂ł��Ȃ��Ȃ�B
	if (m_ShotCoolDown > 0)
	{
		m_ShotCoolDown--;
	}

	//�v���C���[��BSphere�ʒu���X�V.
	UpdateBSpherePos();

	// �e�N���XCCharacter��Update���\�b�h���Ăяo���i�p�����̍X�V�����j
	CCharacter::Update();
}

// �v���C���[����ђe��`�悷�郁�\�b�h�i���t���[���Ăяo�����z��j
void CPlayer::Draw(
	D3DXMATRIX& View, D3DXMATRIX& Proj,
	LIGHT& Light, CAMERA& Camera)
{
	// �e�N���XCCharacter��Draw���\�b�h���Ăяo���i�v���C���[�{�̂̕`��j
	CCharacter::Draw(View, Proj, Light, Camera);
}

// �v���C���[�ƒe��������Ԃɖ߂����\�b�h�i�Q�[���J�n���⃊�g���C���ȂǂɌĂяo���j
void CPlayer::Init()
{
}

