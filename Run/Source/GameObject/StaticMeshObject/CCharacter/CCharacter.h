#pragma once
#include "StaticMash\CStaticMesh.h"							//���N���X
#include "GameObject/StaticMeshObject/CStaticMeshObject.h"	//���N���X

/*******************************************
*	�L�����N�^�[�N���X
**/

class CCharacter
	: public CStaticMeshObject		//�X�^�e�B�b�N���b�V���I�u�W�F�N�g�N���X���p��.
{
public:
	CCharacter();
	virtual ~CCharacter() override;


	//�p������Ƃ��͏����Ȃ��Ă����������H(���͏���)
	virtual void Update() override;
	virtual void Draw(
		D3DXMATRIX& View, D3DXMATRIX& Proj,
		LIGHT& Light, CAMERA& Camera ) override;
	
	//�e���΂��������m�F.
	bool IsShot(int No) const;

	virtual bool GetIsDead() const { return false; }

protected:
	bool m_Shot[ShotMax];	//�e���΂��t���O.
};