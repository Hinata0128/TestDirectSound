#include "CSoundManager.h"
#include "MyMacro.h"
#include <filesystem>
#include <codecvt>
#include <locale>

namespace
{
	//�T�E���h�̃p�X.
	//����Ńp�X�������Ƃ��Ɋy�ł���.
	constexpr char PATH[] = "Data\\Sound";
}

CSoundManager::CSoundManager()
	: m_lpSoundInterface	()
	, m_pDxSound			()
	, m_SoundList			()
{

}

CSoundManager::~CSoundManager()
{
	//�_�C���N�g�T�E���h��j��.
	for (auto& Sound : m_pDxSound)
	{
		SAFE_DELETE(Sound.second);
	}

	//DirectSound�C���^�[�t�F�[�X�̉��.
	if (m_lpSoundInterface != NULL)
	{
		m_lpSoundInterface->Release();
		m_lpSoundInterface = NULL;
	}

	m_pDxSound.clear();
}

bool CSoundManager::LoadSound(HWND hWnd)
{
	//�C���X�^���X���擾.
	CSoundManager* pI = GetInstance();

	//DirectSound�̐���.
	if (FAILED(DirectSoundCreate8(
		NULL,						//GUID.
		&pI->m_lpSoundInterface,	//��������DirectSound�̕ۑ���.
		NULL)))						//NULL�ŌŒ�.
	{
		//false�ŕԂ�.
		return false;
	}

	//�������x���̐ݒ�.
	//���ȂǂɗD�揇�ʂ�����H
	if (FAILED(pI->m_lpSoundInterface->SetCooperativeLevel(
		hWnd,			//�E�B���h�E�n���h��.
		DSSCL_NORMAL)))	//�������x��.
	{
		//false�ŕԂ�.
		return false;
	}

	//�ǂݍ���.
	//�Q�ƃL���v�`���[�����邱�ƂŃ����_���̂Ȃ��ŕϐ��𒼐ڕύX���ł���悤�ɂȂ�.
	auto LoadSound = [&](const std::filesystem::directory_entry& Entry)
	{
		//�g���q.
		const std::string Extension = Entry.path().extension().string();
		//�t�@�C����.
		const std::string FileName = Entry.path().stem().string();
		//�t�@�C���p�X.
		const std::wstring FilePath = Entry.path().wstring();
		//�g���q��".X"�łȂ��ꍇ�ǂݍ��܂�Ȃ�.
		if (Extension != ".wav" && Extension != ".WAV")
		{
			return;
		}
		pI->m_pDxSound[FileName] = new CDirectSound();

		if (pI->m_pDxSound[FileName]->Init(pI->m_lpSoundInterface, FilePath) == false)
		{
			//�t�@�C��������������Ă��Ȃ����ɓ���.
			throw std::runtime_error("Not Init Sound: " + FileName);
		}

		//�ǂݍ��߂���T�E���h���X�g�ɒǉ�����.
		pI->m_SoundList.emplace_back(FileName);
	};

	try
	{
		//�t�@�C����ǂݍ���ł���.
		std::filesystem::recursive_directory_iterator dir_it(PATH), end_it;
		std::for_each(dir_it, end_it, LoadSound);
	}
	catch (const std::exception& e)
	{
		// �G���[���b�Z�[�W��\��.
		std::string str_error = e.what();

		// UTF-8���烏�C�h������iUTF-16�j�ɕϊ�����R���o�[�^�[���쐬
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		std::wstring WStr = converter.from_bytes(str_error);

		_ASSERT_EXPR(false, WStr.c_str());
		return false;
	}
	return true;
}

//�T�E���h���X�g���擾.
std::vector<std::string> CSoundManager::GetSoundList()
{
	return GetInstance()->m_SoundList;
}

//���Đ�.
void CSoundManager::Play(std::string list, bool LoopSound)
{
	GetInstance()->m_pDxSound[list]->Play(LoopSound);
}

//���̒�~.
void CSoundManager::Stop(std::string list)
{
	GetInstance()->m_pDxSound[list]->Stop();
}

//�S�Ẳ��̒�~.
void CSoundManager::StopAll()
{
	CSoundManager* pI = GetInstance();

	for (const auto& sound : pI->m_pDxSound)
	{
		sound.second->Stop();
	}
}

//���ʒ���.
void CSoundManager::SetVolume(std::string list, int volume)
{
	GetInstance()->m_pDxSound[list]->SetVolume(volume);
}

//�Đ�����.
bool CSoundManager::Playing(std::string list)
{
	//...
	return GetInstance()->m_pDxSound[list]->Playing();
}
