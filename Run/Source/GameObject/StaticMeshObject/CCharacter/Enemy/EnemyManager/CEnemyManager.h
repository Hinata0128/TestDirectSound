#pragma once
#include "GameObject\StaticMeshObject\CCharacter\Enemy\CEnemy.h"
#include "GameObject\StaticMeshObject\CCharacter\Enemy\EnemyA\CEnemyA.h"
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <memory>

/********************************************************
*	敵マネージャークラス.
**/

class CEnemyManager
{
public:
	
	~CEnemyManager();

	void Create();
	void Update();

	void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj,
		LIGHT& Light, CAMERA& Camera);

	void LoadData();

	void RemoveEnemy(size_t index);


public:
	//インスタンス取得(唯一のアクセス経路).
//※関数の前にstaticを付けることでインスタンス生成しなくても使用できる.
	static CEnemyManager* GetInstance()
	{
		//唯一のインスタンスを作成する.
		//※staticで作成されたので2回目以降は、下の1行は無視される.
		static CEnemyManager s_Instance;	//s_:staticの意味.
		return &s_Instance;
	}

	CCharacter* GetEnemy(size_t No)
	{
		if (No < m_pEnemy.size())
		{
			return m_pEnemy[No];
		}
		return nullptr; // 範囲外の場合はnullptrを返す
	}

	//敵の数を取得する関数
	size_t GetEnemyCount() const { return m_pEnemy.size(); }
	
	//敵の数を取得する関数
	void SetPlayer(CPlayer* pPlayer) { m_Player = pPlayer; }

private:
	//外部からコンストラクタへのアクセスを禁止する.
	CEnemyManager();
	//コピーコンストラクタによるコピーを禁止する.
	//「=delete」で関数の定義を削除できる.
	CEnemyManager(const CEnemyManager& rhs) = delete;
	//代入演算子によるコピーを禁止する.
	//operator(オペレータ):演算子のオーバーロードで、演算の中身を拡張できる.
	CEnemyManager& operator = (const CEnemyManager& rhs) = delete;

private:
	CPlayer* m_Player;
	std::vector<CCharacter*> m_pEnemy;
};