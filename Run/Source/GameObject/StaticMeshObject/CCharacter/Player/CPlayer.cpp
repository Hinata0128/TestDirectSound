#include "CPlayer.h"
#include "Sound\\CSoundManager.h" // 必要であれば効果音マネージャー

// CPlayerクラスのコンストラクタ
CPlayer::CPlayer()
	: m_ShotCoolDown(0) // クールダウンカウンターを初期化
	// コンストラクタ初期化リストでの m_pShot(0) は配列には不要なので削除しました
{
}

// CPlayerクラスのデストラクタ
CPlayer::~CPlayer()
{
}

// プレイヤーの状態を更新するメソッド（毎フレーム呼び出される想定）
void CPlayer::Update()
{
	float add_value = 0.1f;

	if (GetAsyncKeyState(VK_UP) & 0x8000) {

		if (m_vPosition.y <= WallUP)
		{
			m_vPosition.y += add_value;
		}
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		if (m_vPosition.y >= WallDOWN)
		{
			m_vPosition.y -= add_value;
		}
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		if (m_vPosition.x <= WallRIGHT)
		{
			m_vPosition.x += add_value;
		}
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		if (m_vPosition.x >= WallLEFT)
		{
			m_vPosition.x -= add_value;
		}
	}

	// この処理がないと、一度弾を発射したらクールダウンが永遠に終わらず、二度と弾が発射できなくなる。
	if (m_ShotCoolDown > 0)
	{
		m_ShotCoolDown--;
	}

	//プレイヤーのBSphere位置を更新.
	UpdateBSpherePos();

	// 親クラスCCharacterのUpdateメソッドを呼び出し（継承元の更新処理）
	CCharacter::Update();
}

// プレイヤーおよび弾を描画するメソッド（毎フレーム呼び出される想定）
void CPlayer::Draw(
	D3DXMATRIX& View, D3DXMATRIX& Proj,
	LIGHT& Light, CAMERA& Camera)
{
	// 親クラスCCharacterのDrawメソッドを呼び出し（プレイヤー本体の描画）
	CCharacter::Draw(View, Proj, Light, Camera);
}

// プレイヤーと弾を初期状態に戻すメソッド（ゲーム開始時やリトライ時などに呼び出す）
void CPlayer::Init()
{
}

