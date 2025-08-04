#pragma once
#include "Scene/CSceneBase.h"
#include "Scene/CTitle/CTitle.h"
#include "Scene/CGameMain/CGameMain.h"
#include "Scene/CGameOver/CGameOver.h"
#include "Scene/CEnding/CEnding.h"

/********************************************
*	�V�[���}�l�[�W���[�N���X.
**/

class CSceneManager
{
public:
	//�V�[�����X�g�̗񋓌^.
	enum List
	{
		Title,
		GameMain,
		GameOver,
		Ending,

		max,
	};

public:
	//�V���O���g���p�^�[��
	static CSceneManager* GetInstance()
	{
		static CSceneManager s_Instance;
		return &s_Instance;
	}
	~CSceneManager();

	HRESULT Create(HWND hWnd);

	void Update();
	void Drae();

	//�V�[���ǂݍ���.
	void LoadScene(List Scene);

	//HWND���擾.
	HWND GetHWND() const;
public:
	void SetDx11(CDirectX11* Dx11) { m_pDx11 = Dx11; }
	void SetDx9(CDirectX9* pDx9) { m_pDx9 = pDx9; }
private:
	//�V�[���쐬.
	void MakeScene(List Scene);
private:
	CSceneManager();
	CSceneManager(const CSceneManager& rhs) = delete;
	CSceneManager& operator = (const CSceneManager& rhs) = delete;

private:
	std::unique_ptr<CSceneBase> m_pScene;
	HWND m_hWnd;

	CDirectX11* m_pDx11;
	CDirectX9*	m_pDx9;
};
