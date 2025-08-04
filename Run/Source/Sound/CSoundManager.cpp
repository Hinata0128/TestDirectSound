#include "CSoundManager.h"
#include "MyMacro.h"
#include <filesystem>
#include <Windows.h> // �� �ǉ�

namespace
{
	//�T�E���h�̃p�X.
	constexpr char PATH[] = "Data\\Sound";
}

// �ǉ��FUTF-8 �� UTF-16�istd::string �� std::wstring�j�ϊ�
std::wstring ConvertUtf8ToWide(const std::string& utf8Str)
{
	int wideLen = MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, nullptr, 0);
	if (wideLen == 0) {
		throw std::runtime_error("MultiByteToWideChar failed.");
	}

	std::wstring wideStr(wideLen, L'\0');
	MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, &wideStr[0], wideLen);

	if (!wideStr.empty() && wideStr.back() == L'\0') {
		wideStr.pop_back();
	}

	return wideStr;
}

CSoundManager::CSoundManager()
	: m_lpSoundInterface()
	, m_pDxSound()
	, m_SoundList()
{
}

CSoundManager::~CSoundManager()
{
	// �_�C���N�g�T�E���h��j��
	for (auto& Sound : m_pDxSound)
	{
		SAFE_DELETE(Sound.second);
	}

	// DirectSound�C���^�[�t�F�[�X�̉��
	if (m_lpSoundInterface != NULL)
	{
		m_lpSoundInterface->Release();
		m_lpSoundInterface = NULL;
	}

	m_pDxSound.clear();
}

bool CSoundManager::LoadSound(HWND hWnd)
{
	CSoundManager* pI = GetInstance();

	// DirectSound�̐���
	if (FAILED(DirectSoundCreate8(
		NULL,
		&pI->m_lpSoundInterface,
		NULL)))
	{
		return false;
	}

	// �������x���̐ݒ�
	if (FAILED(pI->m_lpSoundInterface->SetCooperativeLevel(
		hWnd,
		DSSCL_NORMAL)))
	{
		return false;
	}

	// �T�E���h�ǂݍ��ݏ���
	auto LoadSound = [&](const std::filesystem::directory_entry& Entry)
	{
		const std::string Extension = Entry.path().extension().string();
		const std::string FileName = Entry.path().stem().string();
		const std::wstring FilePath = Entry.path().wstring();

		if (Extension != ".wav" && Extension != ".WAV")
		{
			return;
		}

		pI->m_pDxSound[FileName] = new CDirectSound();

		if (!pI->m_pDxSound[FileName]->Init(pI->m_lpSoundInterface, FilePath))
		{
			throw std::runtime_error("Not Init Sound: " + FileName);
		}

		pI->m_SoundList.emplace_back(FileName);
	};

	try
	{
		std::filesystem::recursive_directory_iterator dir_it(PATH), end_it;
		std::for_each(dir_it, end_it, LoadSound);
	}
	catch (const std::exception& e)
	{
		std::string str_error = e.what();
		std::wstring WStr = ConvertUtf8ToWide(str_error); // �C���_
		_ASSERT_EXPR(false, WStr.c_str());
		return false;
	}

	return true;
}

std::vector<std::string> CSoundManager::GetSoundList()
{
	return GetInstance()->m_SoundList;
}

void CSoundManager::Play(std::string list, bool LoopSound)
{
	GetInstance()->m_pDxSound[list]->Play(LoopSound);
}

void CSoundManager::Stop(std::string list)
{
	GetInstance()->m_pDxSound[list]->Stop();
}

void CSoundManager::StopAll()
{
	CSoundManager* pI = GetInstance();
	for (const auto& sound : pI->m_pDxSound)
	{
		sound.second->Stop();
	}
}

void CSoundManager::SetVolume(std::string list, int volume)
{
	GetInstance()->m_pDxSound[list]->SetVolume(volume);
}

bool CSoundManager::Playing(std::string list)
{
	return GetInstance()->m_pDxSound[list]->Playing();
}
