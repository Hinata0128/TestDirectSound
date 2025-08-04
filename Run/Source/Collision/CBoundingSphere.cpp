#include "CBoundingSphere.h"
#include "StaticMash/CStaticMeshManager.h"

CBoundingSphere::CBoundingSphere()
	: m_Position	()
	, m_Radius		()
{
	m_pMesh = CStaticMeshManager::GetInstance()->GetMeshInstance(CStaticMeshManager::CMeshList::Collision);
}

CBoundingSphere::~CBoundingSphere()
{
}

//���f���ɍ��킹���o�E���f�B���O�X�t�B�A���쐬.
HRESULT CBoundingSphere::CreateSphereForMesh(const CStaticMesh& pMesh)
{
	LPDIRECT3DVERTEXBUFFER9 pVB = nullptr;	//���_�o�b�t�@.
	void* pVertices = nullptr;				//���_.
	D3DXVECTOR3 Center(0.f, 0.f, 0.f);		//���S���W.
	float Radius = 0.f;						//���a.

	//���_�o�b�t�@���擾.
	if (FAILED(
		pMesh.GetMesh()->GetVertexBuffer(&pVB)))
	{
		return E_FAIL;
	}

	//���b�V���̒��_�o�b�t�@�����b�N����.
	if (FAILED(
		pVB->Lock(0, 0, &pVertices, 0)))
	{
		SAFE_RELEASE(pVB);
		return E_FAIL;
	}

	//���b�V���̊O�ډ~�̒��S�Ɣ��a���v�Z����.
	D3DXComputeBoundingSphere(
		static_cast<D3DXVECTOR3*>(pVertices),				
		pMesh.GetMesh()->GetNumVertices(),					//���_�̐�.
		D3DXGetFVFVertexSize(pMesh.GetMesh()->GetFVF()),	//���_�̏��.
		&Center,											//(out)���S���W.
		&Radius);											//(out)���a.

	//���b�V���̒��_�o�b�t�@���A�����b�N����.
	if (pVB != nullptr)
	{
		pVB->Unlock();
		SAFE_RELEASE(pVB);
	}

	//���S���W�Ɣ��a�̐ݒ�.
	m_Position	= Center;
	m_Radius	= Radius;

	return S_OK;
}

//���̋��̂Ƃ̓����蔻��.
bool CBoundingSphere::IsHit(const CBoundingSphere& pBSphere)
{
	//2�̋��̂̒��S�̋��������߂�.
	//�Q�Ƃ��Ă���ƃh�b�g���Z�q�ɂȂ�.
	D3DXVECTOR3 vLength = m_Position - pBSphere.GetPostion();
	//��L�̃x�N�g�����璷���ɕϊ�.
	float Length = D3DXVec3Length( &vLength );

	//�u2�̋��̂̋����v���u2�̋��̂̂��ꂼ��̔��a�𑫂������́v���A
	//�������Ƃ������Ƃ́A���̓��m���d�Ȃ��Ă���(�Փ˂��Ă���)�Ƃ�������.
	if (Length <= m_Radius + pBSphere.GetRadius())
	{
		return true;	//�Փ˂��Ă���.
	}
	return false;		//�Փ˂��Ă��Ȃ�.
}

void CBoundingSphere::Update()
{
}

void CBoundingSphere::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
	//�`�撼�O�ō��W���]���Ȃǂ��X�V.
	m_pMesh->SetPosition(m_Position);
	m_pMesh->SetScale(m_Radius);

	//�����_�����O.
	m_pMesh->Render(View, Proj, Light, Camera.vPosition);
}

