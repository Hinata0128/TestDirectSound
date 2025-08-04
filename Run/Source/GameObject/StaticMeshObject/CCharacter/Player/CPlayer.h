#pragma once
#include "GameObject\StaticMeshObject\CCharacter\CCharacter.h"


/**************************************************
*	プレイヤークラス.
**/

//弾のクールタイムをここに追加.
const int ShotCoolTime = 15;
//プレイヤーの進める壁の生成.
const float WallUP = 5.5f;
const float WallDOWN = 0.5f;
const float WallRIGHT = 7.5f;
const float WallLEFT = -7.5f;

class CPlayer
	: public CCharacter	//キャラクタークラスを継承.
{
public:
	CPlayer();
	virtual ~CPlayer() override;

	virtual void Update() override;
	virtual void Draw( 
		D3DXMATRIX& View, D3DXMATRIX& Proj,
		LIGHT& Light, CAMERA& Camera) override;

	const D3DXVECTOR3& GetPosition() const { return m_vPosition; }

	// プレイヤーの初期化処理
	void Init();
protected:
	int		m_ShotCoolDown; // ショットのクールダウンカウンタ
};