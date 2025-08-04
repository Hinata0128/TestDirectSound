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
