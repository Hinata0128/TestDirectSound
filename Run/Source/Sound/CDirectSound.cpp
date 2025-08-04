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
	if (m_lpSoundBuffer == NULL)
	{
		return;
	}

	int LoopBit = LoopSound == true ? 1 : 0;

	//再生位置を最初に戻して再生.
	FirstSound();
	m_lpSoundBuffer->Play(0, 0, DSBPLAY_LOOPING & LoopBit);

}

void CDirectSound::Stop()
{
	if (m_lpSoundBuffer == NULL)
	{
		return;
	}

	// 停止.
	m_lpSoundBuffer->Stop();

}

void CDirectSound::FirstSound()
{
	if (m_lpSoundBuffer == NULL)
	{
		return;
	}
	// 再生位置を最初に戻す.
	m_lpSoundBuffer->SetCurrentPosition(0);

}

void CDirectSound::SetVolume(int volume)
{
	if (m_lpSoundBuffer == NULL)
	{
		return;
	}

	// DirectSoundのVolumeが-10000～0なので
	// 0～10000にする.
	int Tmp_Volume = volume - 10000;

	// 音量を調整する.
	m_lpSoundBuffer->SetVolume(Tmp_Volume);

}

bool CDirectSound::Playing()
{
	DWORD status = 0;

	// バッファの状態をビットで取得.
	m_lpSoundBuffer->GetStatus(&status);

	// & = ビット論理積　取得した status に DSBSTATUS_PLAYING のビットが立っているかチェック.
	if (status & DSBSTATUS_PLAYING) {
		return true;
	}

	return false;
}

bool CDirectSound::LoadWaveFile(std::wstring FileName, MusicWaveStructureData* OutWaveData)
{
	// WindowsマルチメディアAPIのハンドル.
	HMMIO mmioHandle = NULL;

	// チャンク情報.
	MMCKINFO ck_info;
	// RIFFチャンク用.
	MMCKINFO riffck_info;

	// WAVファイル内音サンプルサイズ.
	DWORD dwWavSize = 0;

	// WAVファイルを開く.
	mmioHandle = mmioOpen(
		(LPWSTR)FileName.c_str(),   // ファイル名.
		NULL,                       // MMIO情報.
		MMIO_READ);                // オープンモード.

	if (mmioHandle == NULL)
	{
		// オープン失敗.
		return false;
	}

	// RIFFチャンクに侵入するためにffcTypeにWAVEを設定する.
	riffck_info.fccType = mmioFOURCC('W', 'A', 'V', 'E');


	// RIFFチャンクに侵入する.
	if (MMSYSERR_NOERROR != mmioDescend(
		mmioHandle,     // MMIOハンドル.
		&riffck_info,   // 取得したチャンクの情報.
		NULL,           // 親チャンク.
		MMIO_FINDRIFF))// 取得情報の種類.
	{
		// 失敗.
		mmioClose(mmioHandle, MMIO_FHOPEN);
		return false;
	}

	// 侵入先のチャンクを"fmt"として設定する.
	ck_info.ckid = mmioFOURCC('f', 'm', 't', ' ');
	if (MMSYSERR_NOERROR != mmioDescend(mmioHandle, &ck_info, &riffck_info, MMIO_FINDCHUNK))
	{
		// fmtチャンクがない.
		mmioClose(mmioHandle, MMIO_FHOPEN);
		return false;
	}

	// fmtチャンクの読み込み.
	LONG ReadSize = mmioRead(
		mmioHandle,
		(HPSTR)&OutWaveData->WaveFormat,
		sizeof(OutWaveData->WaveFormat));

	if (ReadSize != sizeof(OutWaveData->WaveFormat))
	{
		// 読み込みサイズが一致してないのでエラー.
		mmioClose(mmioHandle, MMIO_FHOPEN);
		return false;
	}

	// フォーマットチェック.
	if (OutWaveData->WaveFormat.wFormatTag != WAVE_FORMAT_PCM)
	{
		// フォーマットエラー.
		mmioClose(mmioHandle, MMIO_FHOPEN);
		return false;
	}

	//fmtチャンクを退出する.
	if (mmioAscend(mmioHandle, &ck_info, 0) != MMSYSERR_NOERROR)
	{
		mmioClose(mmioHandle, MMIO_FHOPEN);
		return false;
	}

	// dataチャンクに進入する.
	ck_info.ckid = mmioFOURCC('d', 'a', 't', 'a');
	if (mmioDescend(mmioHandle, &ck_info, &riffck_info, MMIO_FINDCHUNK) != MMSYSERR_NOERROR)
	{
		// 進入失敗.
		mmioClose(mmioHandle, MMIO_FHOPEN);
		return false;
	}

	// サイズを保存.
	OutWaveData->Size = ck_info.cksize;

	// dataチャンク読み込み.
	OutWaveData->SoundBuffer = new char[ck_info.cksize];
	ReadSize = mmioRead(mmioHandle, (HPSTR)OutWaveData->SoundBuffer, ck_info.cksize);
	if (ReadSize != ck_info.cksize)
	{
		mmioClose(mmioHandle, MMIO_FHOPEN);
		delete[] OutWaveData->SoundBuffer;
		return false;
	}

	// ファイルを閉じる.
	mmioClose(mmioHandle, MMIO_FHOPEN);

	return true;
}
