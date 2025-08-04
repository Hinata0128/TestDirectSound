#include "CEnemyA.h"
#include "StaticMash\CStaticMeshManager.h"

CEnemyA::CEnemyA()
	: m_shotInterval	(2.f)
	, m_shotTime		(0.f)
	, m_pPlayer			(nullptr)
{
	AttachMesh(*CStaticMeshManager::GetInstance()->GetMeshInstance(CStaticMeshManager::CMeshList::EnemyA));
}

CEnemyA::~CEnemyA()
{
}

void CEnemyA::Update()
{
	m_vPosition.z -= 0.1f;
	if ( m_vPosition.z <= 0.f )
	{
		m_bIsDead = true;
	}

	//-----------------------------------------------------
	// �z�[�~���O�e�̔��˃��W�b�N��ǉ�.
	//-----------------------------------------------------
	float deltaTime = 1.f / 100.f; //���� deltaTime

	//���S���Ă��Ȃ��ꍇ�̂ݒe�𔭎�
	if (!m_bIsDead)
	{
		m_shotTime += deltaTime;	//�^�C�}�[�X�V.

		const float FIRE_Z_THRESHOLD = 30.f; // ��: Z���W��30.0f�ȉ��ɂȂ����甭�ˊJ�n



		//�^�C�}�[�����ˊԊu�𒴂�����e�𔭎�.
		if (m_shotTime >= m_shotInterval && m_vPosition.z <= FIRE_Z_THRESHOLD )
		{
			if (m_pPlayer)
			{
				D3DXVECTOR3 enemyPosition = GetPosition();
				// �G����v���C���[�ւ̏��������x�N�g�����v�Z
				// �v���C���[�̈ʒu����G�̈ʒu���������ƂŁA�G����v���C���[�֌������x�N�g���������.
				D3DXVECTOR3 initialShotDirection = m_pPlayer->GetPosition() - enemyPosition;
				D3DXVec3Normalize(&initialShotDirection, &initialShotDirection);
				// �G�̒e�}�l�[�W���[��ʂ��ăz�[�~���O�e�𔭎˂���
				// ����: ���ˈʒu�A���������A�ǔ��Ώۂ̃v���C���[
				m_shotTime = 0.f;
			}
		}
	}
	//�����蔻����X�V.
	UpdateBSpherePos();

	CCharacter::Update();
}

void CEnemyA::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
	CCharacter::Draw(View, Proj, Light, Camera);

}
