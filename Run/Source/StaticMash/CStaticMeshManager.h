#pragma once
#include "CStaticMesh.h"

/**********************************************
*	�X�^�e�B�b�N���b�V���}�l�[�W���[�N���X.
**/

class CStaticMeshManager
{
public:
	//���f���̎�ނ̗񋓌^.
	enum CMeshList
	{
		EnemyA,
		Shot,
		Collision,

		max,
	};
public:
		~CStaticMeshManager();

		void Create(CDirectX9& pDx9, CDirectX11& pDx11);
		void Init();

		//�X�^�e�B�b�N�N���X�̃Q�b�g�C���X�^���X������
		CStaticMesh* GetMeshInstance(CMeshList MeshNo)
		{
			return m_pMesh[MeshNo];
		};

		//�C���X�^���X�擾(�B��̃A�N�Z�X�o�H).
		//���֐��̑O��static��t���邱�ƂŃC���X�^���X�������Ȃ��Ă��g�p�ł���.
		static CStaticMeshManager* GetInstance()
		{
			//�B��̃C���X�^���X���쐬����.
			//��static�ō쐬���ꂽ�̂�2��ڈȍ~�́A����1�s�͖��������.
			static CStaticMeshManager s_Instance;	//s_:static�̈Ӗ�.
			return &s_Instance;
		}


private:
	//�O������R���X�g���N�^�ւ̃A�N�Z�X���֎~����.
	CStaticMeshManager();
	//�R�s�[�R���X�g���N�^�ɂ��R�s�[���֎~����.
	//�u=delete�v�Ŋ֐��̒�`���폜�ł���.
	CStaticMeshManager(const CStaticMeshManager& rhs) = delete;
	//������Z�q�ɂ��R�s�[���֎~����.
	//operator(�I�y���[�^):���Z�q�̃I�[�o�[���[�h�ŁA���Z�̒��g���g���ł���.
	CStaticMeshManager& operator = (const CStaticMeshManager& rhs) = delete;

	CStaticMesh* m_pMesh[CMeshList::max];

};