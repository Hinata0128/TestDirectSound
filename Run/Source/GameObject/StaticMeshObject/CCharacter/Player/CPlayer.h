#pragma once
#include "GameObject\StaticMeshObject\CCharacter\CCharacter.h"


/**************************************************
*	�v���C���[�N���X.
**/

//�e�̃N�[���^�C���������ɒǉ�.
const int ShotCoolTime = 15;
//�v���C���[�̐i�߂�ǂ̐���.
const float WallUP = 5.5f;
const float WallDOWN = 0.5f;
const float WallRIGHT = 7.5f;
const float WallLEFT = -7.5f;

class CPlayer
	: public CCharacter	//�L�����N�^�[�N���X���p��.
{
public:
	CPlayer();
	virtual ~CPlayer() override;

	virtual void Update() override;
	virtual void Draw( 
		D3DXMATRIX& View, D3DXMATRIX& Proj,
		LIGHT& Light, CAMERA& Camera) override;

	const D3DXVECTOR3& GetPosition() const { return m_vPosition; }

	// �v���C���[�̏���������
	void Init();
protected:
	int		m_ShotCoolDown; // �V���b�g�̃N�[���_�E���J�E���^
};