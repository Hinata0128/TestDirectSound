#pragma once
#include "GameObject\StaticMeshObject\CCharacter\Enemy\CEnemy.h"
#include "GameObject/StaticMeshObject/CCharacter/Player/CPlayer.h"
#include "Collision/CBoundingSphere.h"

/*********************************************************
*	敵Aクラス.
**/

class CEnemyA
	: public CEnemy
{
public:
	CEnemyA();
	~CEnemyA() override;

	void Update() override;

	void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj,
		LIGHT& Light, CAMERA& Camera) override;

	void SetPlayerTarget(CPlayer* pPlayer) { m_pPlayer = pPlayer; }
private:
	//ホーミング弾の発射間隔を管理するための変数.
	float m_shotInterval;	//弾を発射するまでのクールダウン時間.
	float m_shotTime;		//現在のタイマー.

	CPlayer* m_pPlayer;
};
