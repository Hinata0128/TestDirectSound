#include "CSoundManager.h"
#include "MyMacro.h"

CSoundManager::CSoundManager()
{
}

CSoundManager::~CSoundManager()
{
	Release();

}

//�T�E���h�f�[�^�Ǎ��֐�.
bool CSoundManager::Load( HWND hWnd )
{
	return true;
}

//�T�E���h�f�[�^����֐�.
void CSoundManager::Release()
{
}
