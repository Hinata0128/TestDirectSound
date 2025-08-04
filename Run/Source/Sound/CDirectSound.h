#pragma once
#include <string>
#include <dsound.h>	//DirectSound実装用ヘッダーファイル.
#pragma once(lib, "dsound.lib")	//音楽の再生で必要になる.

/*******************************************
* DirectSoundクラス.
**/

class CDirectSound final
{
public:
	//---------------------
	//音楽実装に必要な構造体.
	//---------------------

	//waveでの音楽取得構造体.
	struct MusicWaveStructureData
	{
		//waveでの音楽実装のために必要な変数.llll
		//DirectSoundを使用するのに必要.
		WAVEFORMATEX	WaveFormat;		//フォーマット
		char*			SoundBuffer;	//書き込みバッファ
		DWORD			Size;			//バッファサイズ
	};

public:
	CDirectSound();
	~CDirectSound();

	//初期化.
	bool Init(const LPDIRECTSOUND8& DirectSound, std::wstring filePath);

	//解放関数.
	void Relese();

	//音声データの読み込み.
	bool LoadSound(std::wstring filename);

	//再生.
	void Play(bool LoopSound);

	//停止.
	void Stop();

	//音を最初に設定する関数.
	void FirstSound();

	//音の音量変更用関数.
	void SetVolume(int volume);

	//再生中.
	bool Playing();

private:
	//読み込むWaveファイル.
	bool LoadWaveFile(std::wstring FileName, MusicWaveStructureData* OutWaveData);
private:
	LPDIRECTSOUND8		m_lpSoundInterface;
	LPDIRECTSOUNDBUFFER m_lpSoundBuffer;
};