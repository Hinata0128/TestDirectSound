#pragma once
#include "Sound/CDirectSound.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <dsound.h>

#pragma once(lib, "dsound.lib")	//���y�̍Đ��ŕK�v�ɂȂ�.
#pragma comment(lib, "dxguid.lib") 

/**************************************************
*	�T�E���h�}�l�[�W���[�N���X.
**/
class CSoundManager
{
public:

	static CSoundManager* GetInstance()
	{
		static CSoundManager s_Instance;
		return &s_Instance;
	}

	//�����f�[�^�̓ǂݍ���.
	static bool LoadSound(HWND hWnd);

	//�T�E���h���X�g���擾.
	static std::vector<std::string> GetSoundList();

	//���̍Đ�.
	static void Play(std::string list, bool LoopSound = false);
	//���̒�~.
	static void Stop(std::string list);
	//�S�Ẳ����~.
	static void StopAll();
	//���ʒ���.
	static void SetVolume(std::string list, int volume);
	//�Đ�����.
	static bool Playing(std::string list);

private:
	//�R���X�g���N�^�E�f�X�g���N�^��private�ɓ���Ă���(�V���O���g��)�ɂ��Ă��邩��.
	CSoundManager();
	~CSoundManager();
	CSoundManager(const CSoundManager& rhs)					= delete;
	CSoundManager& operator = (const CSoundManager& rhs)	= delete;

private:
	LPDIRECTSOUND8 m_lpSoundInterface;
	//DirectSound.
	std::unordered_map<std::string, CDirectSound*> m_pDxSound;
	//�T�E���h���X�g.
	std::vector<std::string> m_SoundList;
};