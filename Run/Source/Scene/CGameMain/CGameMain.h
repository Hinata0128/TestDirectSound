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
*	�Q�[�����C���摜�N���X.
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

	//�J�����֐�.
	void Camera();
	//�v���W�F�N�V�����֐�.
	void Projection();

private:
	//�Q�[���ň����X�v���C�g�f�[�^(�g���܂킷����).
	CSprite3D*			m_pSp3D;

	CSprite3D*			m_pSpriteGround;
	CSprite3D*			m_pSpriteExplosion;

	//�X�^�e�B�b�N���b�V��(�g���܂킷����)
	CStaticMesh*		m_pStaticMeshFighter;	//���@.
	CStaticMesh*		m_pStaticMeshGround;	//�n��.
	CStaticMesh*		m_pStaticMeshEnemyA;	//�GA.
	CStaticMesh*		m_pStaticMeshEnemyB;	//�GB.
	CStaticMesh*		m_pStaticMeshBullet;	//�e.
	CStaticMesh*		m_pStaticMeshBSohere;	//�o�E���f�B���O�X�t�B�A(�����蔻��p).


	CStaticMesh*		m_pGameMain;
	CSprite2D*			m_pSpriteTitle;

	//�X�^�e�B�b�N���b�V���I�u�W�F�N�g�N���X.
	CStaticMeshObject* m_pStcMeshObj;


	//�L�����N�^�[�N���X
	CCharacter*			m_pPlayer;

	//�n�ʃN���X.
	CGround*			m_pGround;
	CDebugText*			m_pDbgText;	//�f�o�b�N�e�L�X�g.

	bool				m_isGameOverTransitioning; // �Q�[���I�[�o�[�J�ڒ��t���O
	int					m_gameOverDelayTimer;       // �J�ڂ܂ł̃J�E���g�_�E���^�C�}�[
	const int			GAME_OVER_DELAY_FRAMES = 60; // ��: 60�t���[���҂� (��1.0�b)

	bool				m_isEndingTransitioning;   //�G���f�B���O�J�ڒ��t���O
	int					m_endingDelayTimer;         //�G���f�B���O�J�ڂ܂ł̃J�E���g�_�E���^�C�}�[
	const int			ENDING_DELAY_FRAMES = 30; // ��: 30�t���[���҂� (��0.5�b)
};