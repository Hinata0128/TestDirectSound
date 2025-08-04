#pragma once
#include "Scene/CSceneBase.h"
#include "GameObject/CSpriteObject/CSpriteObject.h"
#include "SceneManager/CSceneManager.h"

/*********************************************
*	�Q�[���I�[�o�[�摜�N���X.
**/

class CGameOver
	: public CSceneBase
{
public:
	CGameOver(CDirectX11* pDx11);
	~CGameOver() override;

	void Initialize() override;
	void Create() override;
	void Update() override;
	void Draw() override;

private:
	CStaticMesh* m_pGameOver;
	CSprite2D* m_pSpriteGameOver;
	CUIObject* m_pGameOverObj;
};