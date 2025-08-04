#include "CStaticMeshManager.h"
//�x���ɂ��ẴR�[�h���͂𖳌��ɂ���.4005:�Ē�`.
#pragma warning(disable:4005)

CStaticMeshManager::CStaticMeshManager()
	: m_pMesh		()
{

}

CStaticMeshManager::~CStaticMeshManager()
{
}

void CStaticMeshManager::Create(CDirectX9& pDx9, CDirectX11& pDx11)
{
	for (int i = 0; i < CMeshList::max; ++i)
	{
		m_pMesh[i] = new CStaticMesh();
	}
	struct MeshList
	{
		int listNo;				//CMeshList�񋓌^��ݒ�.
		const TCHAR path[256];	//�t�@�C���̖��O(�p�X�t��).
	};
	MeshList MList[] =
	{
		{CMeshList::EnemyA,		_T("Data\\Mesh\\Static\\Enemy\\EnemyA.x")},
		{CMeshList::Shot, 		_T("Data\\Mesh\\Static\\Bullet\\bullet.x")},
		{CMeshList::Collision, 	_T("Data\\Collision\\Sphere.x")},
	};
	int list_max = sizeof(MList) / sizeof(MList[0]);
	for (int i = 0; i < list_max; ++i)
	{
		if (FAILED(m_pMesh[i]->Init(
			pDx9,
			pDx11,
			MList[i].path))) {

			return;
		};
	}
}

void CStaticMeshManager::Init()
{
}