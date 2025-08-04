#include "CSoundManager.h"
#include "MyMacro.h"

CSoundManager::CSoundManager()
{
}

CSoundManager::~CSoundManager()
{
	Release();

}

//サウンドデータ読込関数.
bool CSoundManager::Load( HWND hWnd )
{
	return true;
}

//サウンドデータ解放関数.
void CSoundManager::Release()
{
}
