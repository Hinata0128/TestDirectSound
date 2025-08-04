#include "CGameMain.h"
#include "Sound/CSoundManager.h"

CGameMain::CGameMain(CDirectX9* pDx9, CDirectX11* pDx11)
	: CSceneBase			( pDx11 ) 
	, m_pDbgText			( nullptr )
	, m_pSpriteGround		( nullptr )
	, m_pSpriteExplosion	( nullptr )

	, m_pStaticMeshFighter	( nullptr )
	, m_pStaticMeshGround	( nullptr )
	, m_pStaticMeshEnemyA	( nullptr )
	, m_pStaticMeshEnemyB	( nullptr )
	, m_pStaticMeshBullet	( nullptr )
	, m_pStaticMeshBSohere	( nullptr )

	, m_pStcMeshObj			( nullptr )
	, m_pPlayer				( nullptr )

	, m_pGround				( nullptr )

	, m_pGameMain			( nullptr )
	, m_pSpriteTitle		( nullptr )
{
	m_pDx11 = pDx11;
	m_pDx9	= pDx9;

	//カメラの位置を変更できるところ.
	m_Camera.vPosition = D3DXVECTOR3(0.0f, 5.0f, -5.0f); 
	//カメラを見ているところを変更できるところ.
	m_Camera.vLook = D3DXVECTOR3(0.0f, 2.0f, 5.0f);

	//ライト情報
	m_Light.vDirection = D3DXVECTOR3(1.5f, 1.f, -1.f);		//ライト方向.

	Initialize();
}

CGameMain::~CGameMain()
{
	//地面の破棄.
	SAFE_DELETE(m_pGround);

	//プレイヤーの破棄.
	SAFE_DELETE(m_pPlayer);
	//スタティックメッシュオブジェクトクラスの破棄.
	SAFE_DELETE(m_pStcMeshObj);

	SAFE_DELETE(m_pStaticMeshBSohere);
	SAFE_DELETE(m_pStaticMeshBullet);
	SAFE_DELETE(m_pStaticMeshEnemyB);
	SAFE_DELETE(m_pStaticMeshEnemyA);
	SAFE_DELETE(m_pStaticMeshGround);
	SAFE_DELETE(m_pStaticMeshFighter);


	//爆発スプライト解放 (これはCGameで生成したものなので残す)
	SAFE_DELETE(m_pSpriteExplosion);
	//地面スプライトの解放.
	SAFE_DELETE(m_pSpriteGround);

	//デバックテキストの破棄.
	SAFE_DELETE(m_pDbgText);

	// 外部で作成しているので、ここでは破棄しない
	m_hWnd = nullptr;
	m_pDx11 = nullptr;
	m_pDx9 = nullptr;
}

void CGameMain::Initialize()
{

	// カメラの位置を初期化
	m_Camera.vPosition = D3DXVECTOR3(0.0f, 5.0f, -5.0f);
	m_Camera.vLook = D3DXVECTOR3(0.0f, 2.0f, 5.0f);

	m_Score = 0;
	m_Count = 0;

	m_isGameOverTransitioning = false;
	m_gameOverDelayTimer	= 0;
	m_isEndingTransitioning = false;
	m_endingDelayTimer		= 0;
}

void CGameMain::Create()
{
	//デバックテキストのインスタンス生成.
	m_pDbgText = new CDebugText();



	//スタティックメッシュのインスタンス生成.
	m_pStaticMeshFighter	= new CStaticMesh();
	m_pStaticMeshGround		= new CStaticMesh();
	m_pStaticMeshEnemyA		= new CStaticMesh();
	m_pStaticMeshEnemyB		= new CStaticMesh();
	m_pStaticMeshBullet		= new CStaticMesh();
	m_pStaticMeshBSohere	= new CStaticMesh(); // BSphere用のメッシュインスタンスをここで生成

	//スタティックメッシュオブジェクトクラスのインスタンス生成.
	m_pStcMeshObj = new CStaticMeshObject();

	//スプライトのインスタンス作成.
	m_pSpriteGround		= new CSprite3D();
	m_pSpriteExplosion	= new CSprite3D(); // 爆発マネージャーに渡すためのスプライト

	//地面スプライトの構造体
	CSprite3D::SPRITE_STATE SSGround;
	SSGround.Disp.w = 1.f;
	SSGround.Disp.h = 1.f;
	SSGround.Base.w = 256.f;
	SSGround.Base.h = 256.f;
	SSGround.Stride.w = 256.f;
	SSGround.Stride.h = 256.f;

	//地面スプライトの読み込み.
	m_pSpriteGround->Init(*m_pDx11,
		_T("Data\\Texture\\Ground.png"), SSGround);


	// 爆発スプライトの構造体
	CSprite3D::SPRITE_STATE SSExplosion =
	{ 1.f, 1.f,			// Disp(w.h)
		256.f, 256.f ,	// Base(w.h)
		32.f , 32.f		// Stride(w.h)
	};
	//爆発スプライトの読み込み.
	m_pSpriteExplosion->Init(*m_pDx11,
		_T("Data\\Texture\\explosion.png"), SSExplosion);


	//キャラクタークラスのインスタンス生成.
	m_pPlayer = new CPlayer();
	CEnemyManager::GetInstance()->SetPlayer(dynamic_cast<CPlayer*>(m_pPlayer));

	//地面クラスのインスタンス生成.
	m_pGround = new CGround();

	//デバックテキストの読み込み.
	if (FAILED(m_pDbgText->Init(*m_pDx11)))
	{
		return ;
	}

	//スタティックメッシュの読み込み.
	m_pStaticMeshFighter->Init(*m_pDx9, *m_pDx11,
		_T("Data\\Mesh\\Static\\Fighter\\Fighter.x"));
	//地面の読み込み.
	m_pStaticMeshGround->Init(*m_pDx9, *m_pDx11,
		_T("Data\\Mesh\\Static\\Ground\\ground.x"));
	//バウンディングスフィア(当たり判定用).
	m_pStaticMeshBSohere->Init(*m_pDx9, *m_pDx11,
		_T("Data\\Collision\\Sphere.x"));

	//スタティックメッシュを設定.
	m_pStcMeshObj->AttachMesh(*m_pStaticMeshFighter);
	//プレイヤーを設定.
	m_pPlayer->AttachMesh(*m_pStaticMeshFighter);
	//地面スプライトを設定.
	m_pGround->AttachMesh(*m_pStaticMeshGround);

	//バウンディングスフィアの作成.
	m_pPlayer->CreateBSphereForMesh(*m_pStaticMeshBSohere);

	// CSVから敵をロード
	CEnemyManager::GetInstance()->LoadData();


	// ロードされた全ての敵に対してBSphereを生成し、半径を設定します
	for (size_t i = 0; i < CEnemyManager::GetInstance()->GetEnemyCount(); ++i)
	{
		CCharacter* enemy = CEnemyManager::GetInstance()->GetEnemy(i);
		if (enemy) // 敵インスタンスが存在するか確認
		{
			// 各敵のバウンディングスフィアを実際に生成する
			enemy->CreateBSphereForMesh(*m_pStaticMeshBSohere);
			// その後、半径を設定
			enemy->GetBSphere()->SetRadius(0.5f); // 必要に応じて適切な半径を設定.

			enemy->GetBSphere()->SetPosition(D3DXVECTOR3(0.0f, 5.f, 0.0f));
		}
	}
	//キャラクターの初期座標を決定.
	m_pPlayer->SetPosition(0.f, 1.f, 6.f);
}

void CGameMain::Update()
{

	constexpr int POINT = 100;
	constexpr int GameClreaPoint = 1500;

	m_Count++;

	// ゲームオーバー遷移中の処理
	if (m_isGameOverTransitioning)
	{
		m_gameOverDelayTimer--;
		if (m_gameOverDelayTimer <= 0)
		{
			CSceneManager::GetInstance()->LoadScene(CSceneManager::GameOver);
			m_isGameOverTransitioning = false;
			return; // シーン遷移後はこのフレームの残りのUpdate処理はスキップ
		}
		return; // 他のUpdate処理をスキップ
	}

	if (m_isEndingTransitioning)
	{
		m_endingDelayTimer--; // タイマーを減らす
		if (m_endingDelayTimer <= 0)
		{
			CSceneManager::GetInstance()->LoadScene(CSceneManager::Ending);
			m_isEndingTransitioning = false; // フラグをリセット
			return; // シーン遷移後はこのフレームの残りのUpdate処理はスキップ
		}
		return;
	}
	//強制的にゲームオーバーへ遷移.
	if (m_Count > 2700)
	{
		CSceneManager::GetInstance()->LoadScene(CSceneManager::GameOver);
		return;
	}

	//地面.
	m_pGround->Update();
	//プレイヤー.
	m_pPlayer->Update();

	//敵.
	CEnemyManager::GetInstance()->Update();
	//敵の弾.
}

void CGameMain::Draw()
{
	Camera();
	Projection();

		//地面表示.
	m_pGround->Draw(m_mView, m_mProj, m_Light, m_Camera);
	//プレイヤー表示.
	m_pPlayer->Draw(m_mView, m_mProj, m_Light, m_Camera);
	
	CEnemyManager::GetInstance()->Draw(m_mView, m_mProj, m_Light, m_Camera);
	//ここのSetDepth(false)の下のtrueをつけないと透明になる.
	//深度テスト無効にすることで、処理順番で描画させることができる.
	m_pDx11->SetDepth(false);
	//やりたいことが終わったらので、深度テストを有効にしておく.
	m_pDx11->SetDepth(true);
	if (m_pDbgText)

	{

		m_pDbgText->SetColor(1.0f, 1.0f, 1.0f);

		TCHAR dbgText[64];

		_stprintf_s(dbgText, _T("Score: %d"), m_Score);

		m_pDbgText->Render(dbgText, 600, 10);

	}
}

HRESULT CGameMain::LoadData()
{
	return S_OK;
}

void CGameMain::Camera()
{
	D3DXVECTOR3 cam_pos = m_Camera.vPosition;
	D3DXVECTOR3 cam_look = m_Camera.vLook;
	D3DXVECTOR3	vUpVec(0.0f, 1.0f, 0.0f);	//上方（ベクトル）.

	//ビュー（カメラ）変換.
	D3DXMatrixLookAtLH(
		&m_mView,	//(out)ビュー計算結果.
		&cam_pos, &cam_look, &vUpVec);
}

//プロジェクション関数.
void CGameMain::Projection()
{
	//y方向の視野角。数値を大きくしたら視野が狭くなる.
	float fov_y = static_cast<FLOAT>(D3DXToRadian(45.0));	//ラジアン値.
	//アスペクト（幅÷高さ）.
	float aspect = static_cast<FLOAT>(WND_W) / static_cast<FLOAT>(WND_H);
	float near_z = 0.1f;
	float far_z = 100.0f;

	//プロジェクション（射影）変換.
	D3DXMatrixPerspectiveFovLH(
		&m_mProj,	//(out)プロジェクション計算結果.
		fov_y,		//視野角（FOV：Field of View）.
		aspect,		//アスペクト.
		near_z,		//近いビュー平面のz値.
		far_z);	//遠いビュー平面のz値.
}

