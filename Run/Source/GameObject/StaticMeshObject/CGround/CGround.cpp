#include "CGround.h"

CGround::CGround()
{
}

CGround::~CGround()
{
}

void CGround::Update()
{
	//�n�ʃX�N���[���������ɏ���
	//m_vPosition�e�N���X�ɏ����Ă��邩��|�W�V���������ł���.
	//�n�ʂ̔w�i�X�N���[������p�̏���
	m_vPosition.z -= 0.2f;
	//-100.0f�����n��s�����Ȃ�Ə��������Ă܂��n�߂�.
	if (m_vPosition.z < -100.f)
	{
		m_vPosition.z = 0.f;
	}
}
