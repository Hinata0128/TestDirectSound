#pragma once
#include "GameObject\StaticMeshObject\CStaticMeshObject.h"	//基底クラス

/******************************************
*	地面クラス.
**/

class CGround
	: public CStaticMeshObject	//スタティックメッシュオブジェクトクラス
{
public:
	CGround();
	virtual ~CGround();

	virtual void Update() override;

private:
};