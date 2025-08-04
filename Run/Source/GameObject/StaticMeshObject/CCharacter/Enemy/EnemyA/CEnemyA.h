#pragma once
#include "GameObject\StaticMeshObject\CCharacter\Enemy\CEnemy.h"
#include "GameObject/StaticMeshObject/CCharacter/Player/CPlayer.h"
#include "Collision/CBoundingSphere.h"

/*********************************************************
*	�GA�N���X.
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
	//�z�[�~���O�e�̔��ˊԊu���Ǘ����邽�߂̕ϐ�.
	float m_shotInterval;	//�e�𔭎˂���܂ł̃N�[���_�E������.
	float m_shotTime;		//���݂̃^�C�}�[.

	CPlayer* m_pPlayer;
};
