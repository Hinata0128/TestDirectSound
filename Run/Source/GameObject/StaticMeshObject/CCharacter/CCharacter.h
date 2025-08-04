#pragma once
#include "StaticMash\CStaticMesh.h"							//基底クラス
#include "GameObject/StaticMeshObject/CStaticMeshObject.h"	//基底クラス

/*******************************************
*	キャラクタークラス
**/

class CCharacter
	: public CStaticMeshObject		//スタティックメッシュオブジェクトクラスを継承.
{
public:
	CCharacter();
	virtual ~CCharacter() override;


	//継承するときは書かなくてもいいかも？(俺は書く)
	virtual void Update() override;
	virtual void Draw(
		D3DXMATRIX& View, D3DXMATRIX& Proj,
		LIGHT& Light, CAMERA& Camera ) override;
	
	//弾を飛ばしたいか確認.
	bool IsShot(int No) const;

	virtual bool GetIsDead() const { return false; }

protected:
	bool m_Shot[ShotMax];	//弾を飛ばすフラグ.
};