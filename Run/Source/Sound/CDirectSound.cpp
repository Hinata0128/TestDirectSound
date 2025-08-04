#include "CDirectSound.h"

CDirectSound::CDirectSound()
	: m_lpSoundInterface	()
	, m_lpSoundBuffer		()
{
}

CDirectSound::~CDirectSound()
{
	Relese();
}

bool CDirectSound::Init(const LPDIRECTSOUND8& DirectSound, std::wstring filePath)
{
	m_lpSoundInterface = DirectSound;

	m_lpSoundBuffer = NULL;

	//音声データの読み込み.
	LoadSound(filePath);
	return true;
}

void CDirectSound::Relese()
{
	//セカンダリーバッファの解放.
	if (m_lpSoundBuffer != NULL)
	{
		m_lpSoundBuffer->Stop();
		m_lpSoundBuffer->Release();
		m_lpSoundBuffer = NULL;
	}

	//DirectSoundは外部で作成しているためここでは解放はしない.
	if (m_lpSoundInterface != NULL)
	{
		m_lpSoundInterface = NULL;
	}
}

bool CDirectSound::LoadSound(std::wstring filename)
{
	MusicWaveStructureData MWavData;

	if (LoadWaveFile(filename, &MWavData) == false)
	{
		return false;
	}

	//バッファ情報の設定.
	DSBUFFERDESC dsbd;

	//構造体のメンバをゼロにする(メモリを空にする?).
	//sizeofはバイト管理をしている.
	ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));
	dsbd.dwSize = sizeof(DSBUFFERDESC);
	dsbd.dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_GLOBALFOCUS;
	dsbd.dwBufferBytes = MWavData.Size;
	dsbd.guid3DAlgorithm = DS3DALG_DEFAULT;
	dsbd.lpwfxFormat = &MWavData.WaveFormat;

	//セカンダリーバッファー作成.
	if (FAILED(m_lpSoundInterface->CreateSoundBuffer(
		&dsbd,
		&m_lpSoundBuffer,
		NULL)))
	{
		//作成失敗.
		delete[] MWavData.SoundBuffer;
		return false;
	}

	//波型データを書き込むためにセカンダリバッファーをロックする.
	//void型のポインタを宣言している.
	void* buffer;
	DWORD buffer_size;
	if (FAILED(m_lpSoundBuffer->Lock(
		0,					//オフセット: ロックを開始するバッファの先頭からのバイト数.
		MWavData.Size,		//ロックするバッファサイズ: ロックしたいバイト数。WAVデータのサイズを指定しています.
		&buffer,			//ロックされたバッファパート1の保存先: ロックしたメモリ領地へのポインタがここに返される.
		&buffer_size,		//ロックされたバッファパート1のサイズ
		NULL,				// ロックされたバッファパート２の保存先: 循環バッファではないためNULLを指定する。
		NULL,				// ロックされたバッファパート２のサイズ: 循環バッファではないためNULLを指定する。
		0)))				// ロックオプション: 特別なフラグがないため0を指定する。
	{
		//ロック失敗.
		delete[] MWavData.SoundBuffer;
		return false;
	}

	//メモリ内容を別の場所にコピーする.
	//bufferはコピー先.
	//MWavData.SoundBufferはコピー元.
	//MWavData.Sizeはコピーするバイト数(サイズ).
	memcpy(buffer, MWavData.SoundBuffer, MWavData.Size);

	//バッファをアンロック.
	m_lpSoundBuffer->Unlock(
		&buffer,		//アンロックするバッファパート1.
		buffer_size,	//パート1のバッファサイズ.
		NULL,			//アンロックするバッファパート2
		NULL);			//
	

	return false;
}

void CDirectSound::Play(bool LoopSound)
{
}

void CDirectSound::Stop()
{
}

void CDirectSound::FirstSound()
{
}

void CDirectSound::SetVolume(int volume)
{
}

bool CDirectSound::Playing()
{
	return false;
}

bool CDirectSound::LoadWaveFile(std::wstring FileName, MusicWaveStructureData* OutWaveData)
{
	return false;
}
