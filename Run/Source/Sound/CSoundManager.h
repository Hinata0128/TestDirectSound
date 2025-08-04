#pragma once
#include "Sound/CDirectSound.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <dsound.h>

#pragma once(lib, "dsound.lib")	//音楽の再生で必要になる.
#pragma comment(lib, "dxguid.lib") 

/**************************************************
*	サウンドマネージャークラス.
**/
class CSoundManager
{
public:

	static CSoundManager* GetInstance()
	{
		static CSoundManager s_Instance;
		return &s_Instance;
	}

	//音声データの読み込み.
	static bool LoadSound(HWND hWnd);

	//サウンドリストを取得.
	static std::vector<std::string> GetSoundList();

	//音の再生.
	static void Play(std::string list, bool LoopSound = false);
	//音の停止.
	static void Stop(std::string list);
	//全ての音を停止.
	static void StopAll();
	//音量調整.
	static void SetVolume(std::string list, int volume);
	//再生中か.
	static bool Playing(std::string list);

private:
	//コンストラクタ・デストラクタはprivateに入れておく(シングルトン)にしているから.
	CSoundManager();
	~CSoundManager();
	CSoundManager(const CSoundManager& rhs)					= delete;
	CSoundManager& operator = (const CSoundManager& rhs)	= delete;

private:
	LPDIRECTSOUND8 m_lpSoundInterface;
	//DirectSound.
	std::unordered_map<std::string, CDirectSound*> m_pDxSound;
	//サウンドリスト.
	std::vector<std::string> m_SoundList;
};