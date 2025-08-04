#pragma once
#include "Scene/CSceneBase.h"
#include "GameObject/CSpriteObject/CSpriteObject.h"
#include "SceneManager/CSceneManager.h"

/*********************************************
*	エンディング画像クラス.
**/

class CEnding
	: public CSceneBase
{
public:
	CEnding(CDirectX11* pDx11);
	~CEnding() override;

	void Initialize() override;
	void Create() override;
	void Update() override;
	void Draw() override;

private:
	CStaticMesh* m_pEnding;
	CSprite2D* m_pSpriteEnding;
	CUIObject* m_pEndingObj;

};