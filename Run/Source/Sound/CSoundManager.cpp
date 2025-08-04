#include "CSoundManager.h"
#include "MyMacro.h"
#include <filesystem>
#include <codecvt>
#include <locale>

namespace
{
	//サウンドのパス.
	//これでパスを書くときに楽できる.
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
	//ダイレクトサウンドを破棄.
	for (auto& Sound : m_pDxSound)
	{
		SAFE_DELETE(Sound.second);
	}

	//DirectSoundインターフェースの解放.
	if (m_lpSoundInterface != NULL)
	{
		m_lpSoundInterface->Release();
		m_lpSoundInterface = NULL;
	}

	m_pDxSound.clear();
}

bool CSoundManager::LoadSound(HWND hWnd)
{
	//インスタンスを取得.
	CSoundManager* pI = GetInstance();

	//DirectSoundの生成.
	if (FAILED(DirectSoundCreate8(
		NULL,						//GUID.
		&pI->m_lpSoundInterface,	//生成したDirectSoundの保存先.
		NULL)))						//NULLで固定.
	{
		//falseで返す.
		return false;
	}

	//協調レベルの設定.
	//音などに優先順位をつける？
	if (FAILED(pI->m_lpSoundInterface->SetCooperativeLevel(
		hWnd,			//ウィンドウハンドル.
		DSSCL_NORMAL)))	//協調レベル.
	{
		//falseで返す.
		return false;
	}

	//読み込み.
	//参照キャプチャーをすることでラムダ式のなかで変数を直接変更ができるようになる.
	auto LoadSound = [&](const std::filesystem::directory_entry& Entry)
	{
		//拡張子.
		const std::string Extension = Entry.path().extension().string();
		//ファイル名.
		const std::string FileName = Entry.path().stem().string();
		//ファイルパス.
		const std::wstring FilePath = Entry.path().wstring();
		//拡張子が".X"でない場合読み込まれない.
		if (Extension != ".wav" && Extension != ".WAV")
		{
			return;
		}
		pI->m_pDxSound[FileName] = new CDirectSound();

		if (pI->m_pDxSound[FileName]->Init(pI->m_lpSoundInterface, FilePath) == false)
		{
			//ファイルが初期化されていない時に入る.
			throw std::runtime_error("Not Init Sound: " + FileName);
		}

		//読み込めたらサウンドリストに追加する.
		pI->m_SoundList.emplace_back(FileName);
	};

	try
	{
		//ファイルを読み込んでいる.
		std::filesystem::recursive_directory_iterator dir_it(PATH), end_it;
		std::for_each(dir_it, end_it, LoadSound);
	}
	catch (const std::exception& e)
	{
		// エラーメッセージを表示.
		std::string str_error = e.what();

		// UTF-8からワイド文字列（UTF-16）に変換するコンバーターを作成
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		std::wstring WStr = converter.from_bytes(str_error);

		_ASSERT_EXPR(false, WStr.c_str());
		return false;
	}
	return true;
}

//サウンドリストを取得.
std::vector<std::string> CSoundManager::GetSoundList()
{
	return GetInstance()->m_SoundList;
}

//音再生.
void CSoundManager::Play(std::string list, bool LoopSound)
{
	GetInstance()->m_pDxSound[list]->Play(LoopSound);
}

//音の停止.
void CSoundManager::Stop(std::string list)
{
	GetInstance()->m_pDxSound[list]->Stop();
}

//全ての音の停止.
void CSoundManager::StopAll()
{
	CSoundManager* pI = GetInstance();

	for (const auto& sound : pI->m_pDxSound)
	{
		sound.second->Stop();
	}
}

//音量調整.
void CSoundManager::SetVolume(std::string list, int volume)
{
	GetInstance()->m_pDxSound[list]->SetVolume(volume);
}

//再生中か.
bool CSoundManager::Playing(std::string list)
{
	//...
	return GetInstance()->m_pDxSound[list]->Playing();
}
