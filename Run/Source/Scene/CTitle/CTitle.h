#pragma once
#include "Scene/CSceneBase.h"
#include "GameObject/CSpriteObject/CSpriteObject.h"
#include "SceneManager/CSceneManager.h"

/*********************************************
*	タイトル画像クラス.
**/

class CTitle
	: public CSceneBase
{
public:
	CTitle(CDirectX11* pDx11);
	~CTitle() override;

	void Initialize() override;
	void Create() override;
	void Update() override;
	void Draw() override;

private: 	
	CStaticMesh*	m_pTitle;
	CSprite2D*		m_pSpriteTitle;
	CUIObject*		m_pTitleObj;

	bool			m_isTransitioning;       // シーン遷移中フラグ
	int				m_transitionDelayTimer;   // 遷移までのカウントダウンタイマー
	const int		TRANSITION_DELAY_FRAMES = 30; // 例: 30フレーム待つ (約0.5秒)
};