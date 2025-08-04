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

	//�����f�[�^�̓ǂݍ���.
	LoadSound(filePath);
	return true;
}

void CDirectSound::Relese()
{
	//�Z�J���_���[�o�b�t�@�̉��.
	if (m_lpSoundBuffer != NULL)
	{
		m_lpSoundBuffer->Stop();
		m_lpSoundBuffer->Release();
		m_lpSoundBuffer = NULL;
	}

	//DirectSound�͊O���ō쐬���Ă��邽�߂����ł͉���͂��Ȃ�.
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

	//�o�b�t�@���̐ݒ�.
	DSBUFFERDESC dsbd;

	//�\���̂̃����o���[���ɂ���(����������ɂ���?).
	//sizeof�̓o�C�g�Ǘ������Ă���.
	ZeroMemory(&dsbd, sizeof(DSBUFFERDESC));
	dsbd.dwSize = sizeof(DSBUFFERDESC);
	dsbd.dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_GLOBALFOCUS;
	dsbd.dwBufferBytes = MWavData.Size;
	dsbd.guid3DAlgorithm = DS3DALG_DEFAULT;
	dsbd.lpwfxFormat = &MWavData.WaveFormat;

	//�Z�J���_���[�o�b�t�@�[�쐬.
	if (FAILED(m_lpSoundInterface->CreateSoundBuffer(
		&dsbd,
		&m_lpSoundBuffer,
		NULL)))
	{
		//�쐬���s.
		delete[] MWavData.SoundBuffer;
		return false;
	}

	//�g�^�f�[�^���������ނ��߂ɃZ�J���_���o�b�t�@�[�����b�N����.
	//void�^�̃|�C���^��錾���Ă���.
	void* buffer;
	DWORD buffer_size;
	if (FAILED(m_lpSoundBuffer->Lock(
		0,					//�I�t�Z�b�g: ���b�N���J�n����o�b�t�@�̐擪����̃o�C�g��.
		MWavData.Size,		//���b�N����o�b�t�@�T�C�Y: ���b�N�������o�C�g���BWAV�f�[�^�̃T�C�Y���w�肵�Ă��܂�.
		&buffer,			//���b�N���ꂽ�o�b�t�@�p�[�g1�̕ۑ���: ���b�N�����������̒n�ւ̃|�C���^�������ɕԂ����.
		&buffer_size,		//���b�N���ꂽ�o�b�t�@�p�[�g1�̃T�C�Y
		NULL,				// ���b�N���ꂽ�o�b�t�@�p�[�g�Q�̕ۑ���: �z�o�b�t�@�ł͂Ȃ�����NULL���w�肷��B
		NULL,				// ���b�N���ꂽ�o�b�t�@�p�[�g�Q�̃T�C�Y: �z�o�b�t�@�ł͂Ȃ�����NULL���w�肷��B
		0)))				// ���b�N�I�v�V����: ���ʂȃt���O���Ȃ�����0���w�肷��B
	{
		//���b�N���s.
		delete[] MWavData.SoundBuffer;
		return false;
	}

	//���������e��ʂ̏ꏊ�ɃR�s�[����.
	//buffer�̓R�s�[��.
	//MWavData.SoundBuffer�̓R�s�[��.
	//MWavData.Size�̓R�s�[����o�C�g��(�T�C�Y).
	memcpy(buffer, MWavData.SoundBuffer, MWavData.Size);

	//�o�b�t�@���A�����b�N.
	m_lpSoundBuffer->Unlock(
		&buffer,		//�A�����b�N����o�b�t�@�p�[�g1.
		buffer_size,	//�p�[�g1�̃o�b�t�@�T�C�Y.
		NULL,			//�A�����b�N����o�b�t�@�p�[�g2
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

	//�Đ��ʒu���ŏ��ɖ߂��čĐ�.
	FirstSound();
	m_lpSoundBuffer->Play(0, 0, DSBPLAY_LOOPING & LoopBit);

}

void CDirectSound::Stop()
{
	if (m_lpSoundBuffer == NULL)
	{
		return;
	}

	// ��~.
	m_lpSoundBuffer->Stop();

}

void CDirectSound::FirstSound()
{
	if (m_lpSoundBuffer == NULL)
	{
		return;
	}
	// �Đ��ʒu���ŏ��ɖ߂�.
	m_lpSoundBuffer->SetCurrentPosition(0);

}

void CDirectSound::SetVolume(int volume)
{
	if (m_lpSoundBuffer == NULL)
	{
		return;
	}

	// DirectSound��Volume��-10000�`0�Ȃ̂�
	// 0�`10000�ɂ���.
	int Tmp_Volume = volume - 10000;

	// ���ʂ𒲐�����.
	m_lpSoundBuffer->SetVolume(Tmp_Volume);

}

bool CDirectSound::Playing()
{
	DWORD status = 0;

	// �o�b�t�@�̏�Ԃ��r�b�g�Ŏ擾.
	m_lpSoundBuffer->GetStatus(&status);

	// & = �r�b�g�_���ρ@�擾���� status �� DSBSTATUS_PLAYING �̃r�b�g�������Ă��邩�`�F�b�N.
	if (status & DSBSTATUS_PLAYING) {
		return true;
	}

	return false;
}

bool CDirectSound::LoadWaveFile(std::wstring FileName, MusicWaveStructureData* OutWaveData)
{
	// Windows�}���`���f�B�AAPI�̃n���h��.
	HMMIO mmioHandle = NULL;

	// �`�����N���.
	MMCKINFO ck_info;
	// RIFF�`�����N�p.
	MMCKINFO riffck_info;

	// WAV�t�@�C�������T���v���T�C�Y.
	DWORD dwWavSize = 0;

	// WAV�t�@�C�����J��.
	mmioHandle = mmioOpen(
		(LPWSTR)FileName.c_str(),   // �t�@�C����.
		NULL,                       // MMIO���.
		MMIO_READ);                // �I�[�v�����[�h.

	if (mmioHandle == NULL)
	{
		// �I�[�v�����s.
		return false;
	}

	// RIFF�`�����N�ɐN�����邽�߂�ffcType��WAVE��ݒ肷��.
	riffck_info.fccType = mmioFOURCC('W', 'A', 'V', 'E');


	// RIFF�`�����N�ɐN������.
	if (MMSYSERR_NOERROR != mmioDescend(
		mmioHandle,     // MMIO�n���h��.
		&riffck_info,   // �擾�����`�����N�̏��.
		NULL,           // �e�`�����N.
		MMIO_FINDRIFF))// �擾���̎��.
	{
		// ���s.
		mmioClose(mmioHandle, MMIO_FHOPEN);
		return false;
	}

	// �N����̃`�����N��"fmt"�Ƃ��Đݒ肷��.
	ck_info.ckid = mmioFOURCC('f', 'm', 't', ' ');
	if (MMSYSERR_NOERROR != mmioDescend(mmioHandle, &ck_info, &riffck_info, MMIO_FINDCHUNK))
	{
		// fmt�`�����N���Ȃ�.
		mmioClose(mmioHandle, MMIO_FHOPEN);
		return false;
	}

	// fmt�`�����N�̓ǂݍ���.
	LONG ReadSize = mmioRead(
		mmioHandle,
		(HPSTR)&OutWaveData->WaveFormat,
		sizeof(OutWaveData->WaveFormat));

	if (ReadSize != sizeof(OutWaveData->WaveFormat))
	{
		// �ǂݍ��݃T�C�Y����v���ĂȂ��̂ŃG���[.
		mmioClose(mmioHandle, MMIO_FHOPEN);
		return false;
	}

	// �t�H�[�}�b�g�`�F�b�N.
	if (OutWaveData->WaveFormat.wFormatTag != WAVE_FORMAT_PCM)
	{
		// �t�H�[�}�b�g�G���[.
		mmioClose(mmioHandle, MMIO_FHOPEN);
		return false;
	}

	//fmt�`�����N��ޏo����.
	if (mmioAscend(mmioHandle, &ck_info, 0) != MMSYSERR_NOERROR)
	{
		mmioClose(mmioHandle, MMIO_FHOPEN);
		return false;
	}

	// data�`�����N�ɐi������.
	ck_info.ckid = mmioFOURCC('d', 'a', 't', 'a');
	if (mmioDescend(mmioHandle, &ck_info, &riffck_info, MMIO_FINDCHUNK) != MMSYSERR_NOERROR)
	{
		// �i�����s.
		mmioClose(mmioHandle, MMIO_FHOPEN);
		return false;
	}

	// �T�C�Y��ۑ�.
	OutWaveData->Size = ck_info.cksize;

	// data�`�����N�ǂݍ���.
	OutWaveData->SoundBuffer = new char[ck_info.cksize];
	ReadSize = mmioRead(mmioHandle, (HPSTR)OutWaveData->SoundBuffer, ck_info.cksize);
	if (ReadSize != ck_info.cksize)
	{
		mmioClose(mmioHandle, MMIO_FHOPEN);
		delete[] OutWaveData->SoundBuffer;
		return false;
	}

	// �t�@�C�������.
	mmioClose(mmioHandle, MMIO_FHOPEN);

	return true;
}
