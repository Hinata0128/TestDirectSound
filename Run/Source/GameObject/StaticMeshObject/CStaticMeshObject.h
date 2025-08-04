#pragma once

#include "GameObject\\CGameObject.h"
#include "StaticMash\CStaticMesh.h"
#include "Collision\CBoundingSphere.h"

/************************************************************
*	�X�^�e�B�b�N���b�V���I�u�W�F�N�g�N���X.
*	3DSTG�ł̓��C���̕���.
**/
class CStaticMeshObject
	: public CGameObject
{
public:
	CStaticMeshObject();
	virtual ~CStaticMeshObject() override;

	//CGameObject�ŏ������z�֐��̐錾������Ă�̂ł�����Œ�`������.
	virtual void Update() override;
	virtual void Draw( D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera) override;

	//���b�V����ڑ�����.
	void AttachMesh( CStaticMesh& pMesh ){
		m_pMesh = &pMesh;
	}
	//�X�v���C�g��؂藣��.
	void DetachMesh(){
		m_pMesh = nullptr;
	}

	//�o�E���f�B���O�X�t�B�A�擾.
	CBoundingSphere* GetBSphere() const
	{
		return m_pBSphere;
	}
	//�Z��������֐�.
	//���f���ɍ��킹���o�E���f�B���O�X�t�B�A�쐬�̃��b�p�[�֐�.
	HRESULT CreateBSphereForMesh(const CStaticMesh& pMesh)
	{
		return m_pBSphere->CreateSphereForMesh(pMesh);
	}
	//�o�E���f�B���O�X�t�B�A���I�u�W�F�N�g�ʒu�ɍ��킹��.
	//�����f���̌��_�����S�̏ꍇ���.
	void UpdateBSpherePos()
	{
		m_pBSphere->SetPosition(m_vPosition);
	}

protected:
	CStaticMesh*		m_pMesh;
	CBoundingSphere*	m_pBSphere;
};
