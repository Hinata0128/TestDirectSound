#pragma once
#include "Scene/CSceneBase.h"
#include "GameObject/CSpriteObject/CSpriteObject.h"
#include "SceneManager/CSceneManager.h"

#include "GameObject/StaticMeshObject/CGround/CGround.h"
#include "GameObject/StaticMeshObject/CCharacter/Player/CPlayer.h"
#include "GameObject/StaticMeshObject/CCharacter/Enemy/EnemyManager/CEnemyManager.h"
#include "DebugText/CDebugText.h"
#include "GameObject/StaticMeshObject/CCharacter/CCharacter.h"


/*********************************************
*	ゲームメイン画像クラス.
**/

class CGameMain
	: public CSceneBase
{
public:
	CGameMain(CDirectX9* pDx9, CDirectX11* pDx11);
	~CGameMain() override;

	void Initialize() override;
	void Create() override;
	void Update() override;
	void Draw() override;

	HRESULT LoadData();

	//カメラ関数.
	void Camera();
	//プロジェクション関数.
	void Projection();

private:
	//ゲームで扱うスプライトデータ(使いまわす資源).
	CSprite3D*			m_pSp3D;

	CSprite3D*			m_pSpriteGround;
	CSprite3D*			m_pSpriteExplosion;

	//スタティックメッシュ(使いまわす資源)
	CStaticMesh*		m_pStaticMeshFighter;	//自機.
	CStaticMesh*		m_pStaticMeshGround;	//地面.
	CStaticMesh*		m_pStaticMeshEnemyA;	//敵A.
	CStaticMesh*		m_pStaticMeshEnemyB;	//敵B.
	CStaticMesh*		m_pStaticMeshBullet;	//弾.
	CStaticMesh*		m_pStaticMeshBSohere;	//バウンディングスフィア(当たり判定用).


	CStaticMesh*		m_pGameMain;
	CSprite2D*			m_pSpriteTitle;

	//スタティックメッシュオブジェクトクラス.
	CStaticMeshObject* m_pStcMeshObj;


	//キャラクタークラス
	CCharacter*			m_pPlayer;

	//地面クラス.
	CGround*			m_pGround;
	CDebugText*			m_pDbgText;	//デバックテキスト.

	bool				m_isGameOverTransitioning; // ゲームオーバー遷移中フラグ
	int					m_gameOverDelayTimer;       // 遷移までのカウントダウンタイマー
	const int			GAME_OVER_DELAY_FRAMES = 60; // 例: 60フレーム待つ (約1.0秒)

	bool				m_isEndingTransitioning;   //エンディング遷移中フラグ
	int					m_endingDelayTimer;         //エンディング遷移までのカウントダウンタイマー
	const int			ENDING_DELAY_FRAMES = 30; // 例: 30フレーム待つ (約0.5秒)
};