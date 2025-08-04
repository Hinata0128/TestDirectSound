#include "CEnemyManager.h"
//警告についてのコード分析を無効にする.4005:再定義.
#pragma warning(disable:4005)

//初期化リストからm_pEnemy()を削除
CEnemyManager::CEnemyManager()
    : m_Player      (nullptr)
{
}

CEnemyManager::~CEnemyManager()
{
    //vector内のポインタを解放
    for (CCharacter* enemy : m_pEnemy)
    {
        SAFE_DELETE(enemy);
    }
    m_pEnemy.clear(); // vectorの内容をクリア
}

void CEnemyManager::Create()
{
}

void CEnemyManager::Update()
{
    //vectorのサイズを使用
    for (size_t i = 0; i < m_pEnemy.size(); ++i)
    {
        if (m_pEnemy[i] != nullptr)
        {
            m_pEnemy[i]->Update();

            //敵が死亡していたら削除.
            if (m_pEnemy[i]->GetIsDead())
            {
                RemoveEnemy(i);
            }
        }
    }
}

void CEnemyManager::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
    //vectorのサイズを使用
    for (size_t i = 0; i < m_pEnemy.size(); ++i)
    {
        if (m_pEnemy[i] != nullptr)
        {
            m_pEnemy[i]->Draw(View, Proj, Light, Camera);
        }
    }
}

void CEnemyManager::LoadData()
{
    //既存の敵をクリアしてからロード
    for (CCharacter* enemy : m_pEnemy)
    {
        SAFE_DELETE(enemy);
    }
    m_pEnemy.clear();

    const char* Path = "Data\\csv\\Position.csv";

    std::ifstream file(Path);
    if (!file.is_open())
    {
        std::cerr << "敵配置ファイルが開けませんでした: " << Path << std::endl;
        return;
    }

    std::string line;

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string token;

        int index_from_csv = 0; // CSVから読み込んだインデックス
        float x = 0.0f, y = 0.0f, z = 0.0f;

        // 1列目: 敵番号 (0始まりに変換)
        if (std::getline(iss, token, ','))
        {
            try {
                index_from_csv = std::stoi(token) - 1;
            }
            catch (const std::invalid_argument& ) {
                std::cerr << "Invalid enemy index in CSV: " << token << std::endl;
                continue;
            }
            catch (const std::out_of_range& ) {
                std::cerr << "Enemy index out of range in CSV: " << token << std::endl;
                continue;
            }
        }

        // 2列目: x
        if (std::getline(iss, token, ','))
        {
            try {
                x = std::stof(token);
            }
            catch (const std::invalid_argument& ) {
                std::cerr << "Invalid x position in CSV: " << token << std::endl;
                continue;
            }
            catch (const std::out_of_range& ) {
                std::cerr << "X position out of range in CSV: " << token << std::endl;
                continue;
            }
        }
        // 3列目: y
        if (std::getline(iss, token, ','))
        {
            try {
                y = std::stof(token);
            }
            catch (const std::invalid_argument& ) {
                std::cerr << "Invalid y position in CSV: " << token << std::endl;
                continue;
            }
            catch (const std::out_of_range& ) {
                std::cerr << "Y position out of range in CSV: " << token << std::endl;
                continue;
            }
        }
        // 4列目: z
        if (std::getline(iss, token, ','))
        {
            try {
                z = std::stof(token);
            }
            catch (const std::invalid_argument& ) {
                std::cerr << "Invalid z position in CSV: " << token << std::endl;
                continue;
            }
            catch (const std::out_of_range& ) {
                std::cerr << "Z position out of range in CSV: " << token << std::endl;
                continue;
            }
        }

        if (index_from_csv >= m_pEnemy.size())
        {
            m_pEnemy.resize(index_from_csv + 1, nullptr); // サイズを調整
        }

        // 敵インスタンスが存在しない場合のみ生成
        if (m_pEnemy[index_from_csv] == nullptr)
        {
            m_pEnemy[index_from_csv] = new CEnemyA();
        }
        m_pEnemy[index_from_csv]->SetPosition(x, y, z);
        dynamic_cast<CEnemyA*>(m_pEnemy[index_from_csv])->SetPlayerTarget(m_Player);
    }
    file.close();
}

void CEnemyManager::RemoveEnemy(size_t index)
{
    if (index < m_pEnemy.size())
    {
        SAFE_DELETE(m_pEnemy[index]);                //オブジェクトの解放.
        m_pEnemy.erase(m_pEnemy.begin() + index);   //コンテナから要素を削除.
    }
}
