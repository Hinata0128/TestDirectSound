#pragma once
#include "GameObject\StaticMeshObject\CStaticMeshObject.h"	//���N���X

/******************************************
*	�n�ʃN���X.
**/

class CGround
	: public CStaticMeshObject	//�X�^�e�B�b�N���b�V���I�u�W�F�N�g�N���X
{
public:
	CGround();
	virtual ~CGround();

	virtual void Update() override;

private:
};