#pragma once
#include "StaticMash/CStaticMesh.h"
#include "DirectX/CDirectX11.h"
#include "Sprite2D/CSprite2D.h"
#include "GameObject/UIObject/CUIObject.h"


/**********************************************************
*	���N���X.
**/

class CSceneBase	
{
public:
	CSceneBase(CDirectX11* pDx11);
	virtual ~CSceneBase() {}

	virtual void Initialize() = 0;
	virtual void Create() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	//���b�V����ڑ�����.
	void AttachMesh(CStaticMesh& pMesh) {
		m_pMesh = &pMesh;
	}

protected:
	CStaticMesh* m_pMesh;
	CDirectX9* m_pDx9;
	CDirectX11* m_pDx11;

	//�E�B���h�E�n���h��.
	HWND				m_hWnd;

	//�J�������.
	CAMERA				m_Camera;
	//���C�g���
	LIGHT				m_Light;

	//�s��.
	D3DXMATRIX			m_mView;	//�r���[(�J����)�s��.
	D3DXMATRIX			m_mProj;	//�ˉe�i�v���W�F�N�V�����j�s��.

	int m_Score;

	int m_Count;


};