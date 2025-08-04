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
	// ホーミング弾の発射ロジックを追加.
	//-----------------------------------------------------
	float deltaTime = 1.f / 100.f; //仮の deltaTime

	//死亡していない場合のみ弾を発射
	if (!m_bIsDead)
	{
		m_shotTime += deltaTime;	//タイマー更新.

		const float FIRE_Z_THRESHOLD = 30.f; // 例: Z座標が30.0f以下になったら発射開始



		//タイマーが発射間隔を超えたら弾を発射.
		if (m_shotTime >= m_shotInterval && m_vPosition.z <= FIRE_Z_THRESHOLD )
		{
			if (m_pPlayer)
			{
				D3DXVECTOR3 enemyPosition = GetPosition();
				// 敵からプレイヤーへの初期方向ベクトルを計算
				// プレイヤーの位置から敵の位置を引くことで、敵からプレイヤーへ向かうベクトルが得らる.
				D3DXVECTOR3 initialShotDirection = m_pPlayer->GetPosition() - enemyPosition;
				D3DXVec3Normalize(&initialShotDirection, &initialShotDirection);
				// 敵の弾マネージャーを通じてホーミング弾を発射する
				// 引数: 発射位置、初期方向、追尾対象のプレイヤー
				m_shotTime = 0.f;
			}
		}
	}
	//当たり判定を更新.
	UpdateBSpherePos();

	CCharacter::Update();
}

void CEnemyA::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
	CCharacter::Draw(View, Proj, Light, Camera);

}
