#pragma once
#include <string>
#include <dsound.h>	//DirectSound�����p�w�b�_�[�t�@�C��.
#pragma once(lib, "dsound.lib")	//���y�̍Đ��ŕK�v�ɂȂ�.

/*******************************************
* DirectSound�N���X.
**/

class CDirectSound final
{
public:
	//---------------------
	//���y�����ɕK�v�ȍ\����.
	//---------------------

	//wave�ł̉��y�擾�\����.
	struct MusicWaveStructureData
	{
		//wave�ł̉��y�����̂��߂ɕK�v�ȕϐ�.llll
		//DirectSound���g�p����̂ɕK�v.
		WAVEFORMATEX	WaveFormat;		//�t�H�[�}�b�g
		char*			SoundBuffer;	//�������݃o�b�t�@
		DWORD			Size;			//�o�b�t�@�T�C�Y
	};

public:
	CDirectSound();
	~CDirectSound();

	//������.
	bool Init(const LPDIRECTSOUND8& DirectSound, std::wstring filePath);

	//����֐�.
	void Relese();

	//�����f�[�^�̓ǂݍ���.
	bool LoadSound(std::wstring filename);

	//�Đ�.
	void Play(bool LoopSound);

	//��~.
	void Stop();

	//�����ŏ��ɐݒ肷��֐�.
	void FirstSound();

	//���̉��ʕύX�p�֐�.
	void SetVolume(int volume);

	//�Đ���.
	bool Playing();

private:
	//�ǂݍ���Wave�t�@�C��.
	bool LoadWaveFile(std::wstring FileName, MusicWaveStructureData* OutWaveData);
private:
	LPDIRECTSOUND8		m_lpSoundInterface;
	LPDIRECTSOUNDBUFFER m_lpSoundBuffer;
};