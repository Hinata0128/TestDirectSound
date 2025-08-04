#pragma once
#include "GameObject\StaticMeshObject\CCharacter\CCharacter.h"

/*****************************************************************************************************
*	エネミークラス.
**/

/*
* ロボAに関しては、bmp表示にしているので、違うフォルダーに移動するときは一緒に持っていく.
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

	//ゲッター
	virtual bool GetIsDead() const override { return m_bIsDead; }
protected:
	bool m_bIsDead = false;
};