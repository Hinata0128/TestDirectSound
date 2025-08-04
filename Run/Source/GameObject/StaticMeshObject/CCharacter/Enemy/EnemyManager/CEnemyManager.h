#pragma once
#include "GameObject\StaticMeshObject\CCharacter\Enemy\CEnemy.h"
#include "GameObject\StaticMeshObject\CCharacter\Enemy\EnemyA\CEnemyA.h"
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <memory>

/********************************************************
*	�G�}�l�[�W���[�N���X.
**/

class CEnemyManager
{
public:
	
	~CEnemyManager();

	void Create();
	void Update();

	void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj,
		LIGHT& Light, CAMERA& Camera);

	void LoadData();

	void RemoveEnemy(size_t index);


public:
	//�C���X�^���X�擾(�B��̃A�N�Z�X�o�H).
//���֐��̑O��static��t���邱�ƂŃC���X�^���X�������Ȃ��Ă��g�p�ł���.
	static CEnemyManager* GetInstance()
	{
		//�B��̃C���X�^���X���쐬����.
		//��static�ō쐬���ꂽ�̂�2��ڈȍ~�́A����1�s�͖��������.
		static CEnemyManager s_Instance;	//s_:static�̈Ӗ�.
		return &s_Instance;
	}

	CCharacter* GetEnemy(size_t No)
	{
		if (No < m_pEnemy.size())
		{
			return m_pEnemy[No];
		}
		return nullptr; // �͈͊O�̏ꍇ��nullptr��Ԃ�
	}

	//�G�̐����擾����֐�
	size_t GetEnemyCount() const { return m_pEnemy.size(); }
	
	//�G�̐����擾����֐�
	void SetPlayer(CPlayer* pPlayer) { m_Player = pPlayer; }

private:
	//�O������R���X�g���N�^�ւ̃A�N�Z�X���֎~����.
	CEnemyManager();
	//�R�s�[�R���X�g���N�^�ɂ��R�s�[���֎~����.
	//�u=delete�v�Ŋ֐��̒�`���폜�ł���.
	CEnemyManager(const CEnemyManager& rhs) = delete;
	//������Z�q�ɂ��R�s�[���֎~����.
	//operator(�I�y���[�^):���Z�q�̃I�[�o�[���[�h�ŁA���Z�̒��g���g���ł���.
	CEnemyManager& operator = (const CEnemyManager& rhs) = delete;

private:
	CPlayer* m_Player;
	std::vector<CCharacter*> m_pEnemy;
};