#pragma once

#include "GameObject\\CGameObject.h"
#include "StaticMash\CStaticMesh.h"
#include "Collision\CBoundingSphere.h"

/************************************************************
*	スタティックメッシュオブジェクトクラス.
*	3DSTGではメインの分類.
**/
class CStaticMeshObject
	: public CGameObject
{
public:
	CStaticMeshObject();
	virtual ~CStaticMeshObject() override;

	//CGameObjectで純粋仮想関数の宣言がされてるのでこちらで定義を書く.
	virtual void Update() override;
	virtual void Draw( D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera) override;

	//メッシュを接続する.
	void AttachMesh( CStaticMesh& pMesh ){
		m_pMesh = &pMesh;
	}
	//スプライトを切り離す.
	void DetachMesh(){
		m_pMesh = nullptr;
	}

	//バウンディングスフィア取得.
	CBoundingSphere* GetBSphere() const
	{
		return m_pBSphere;
	}
	//短くかける関数.
	//モデルに合わせたバウンディングスフィア作成のラッパー関数.
	HRESULT CreateBSphereForMesh(const CStaticMesh& pMesh)
	{
		return m_pBSphere->CreateSphereForMesh(pMesh);
	}
	//バウンディングスフィアをオブジェクト位置に合わせる.
	//※モデルの原点が中心の場合を提示.
	void UpdateBSpherePos()
	{
		m_pBSphere->SetPosition(m_vPosition);
	}

protected:
	CStaticMesh*		m_pMesh;
	CBoundingSphere*	m_pBSphere;
};
