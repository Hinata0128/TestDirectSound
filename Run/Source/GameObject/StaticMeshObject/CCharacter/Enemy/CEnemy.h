#pragma once
#include "GameObject\StaticMeshObject\CCharacter\CCharacter.h"

/*****************************************************************************************************
*	�G�l�~�[�N���X.
**/

/*
* ���{A�Ɋւ��ẮAbmp�\���ɂ��Ă���̂ŁA�Ⴄ�t�H���_�[�Ɉړ�����Ƃ��͈ꏏ�Ɏ����Ă���.
*/


class CEnemy
	: public CCharacter
{
public:
	CEnemy();
	virtual ~CEnemy() override;

	virtual void Update() override;
	virtual void Draw(
		D3DXMATRIX& View, D3DXMATRIX& Proj,
		LIGHT& Light, CAMERA& Camera) override;

	//�Q�b�^�[
	virtual bool GetIsDead() const override { return m_bIsDead; }
protected:
	bool m_bIsDead = false;
};