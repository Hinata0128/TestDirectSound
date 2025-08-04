#include "CEnemyManager.h"
//�x���ɂ��ẴR�[�h���͂𖳌��ɂ���.4005:�Ē�`.
#pragma warning(disable:4005)

//���������X�g����m_pEnemy()���폜
CEnemyManager::CEnemyManager()
    : m_Player      (nullptr)
{
}

CEnemyManager::~CEnemyManager()
{
    //vector���̃|�C���^�����
    for (CCharacter* enemy : m_pEnemy)
    {
        SAFE_DELETE(enemy);
    }
    m_pEnemy.clear(); // vector�̓��e���N���A
}

void CEnemyManager::Create()
{
}

void CEnemyManager::Update()
{
    //vector�̃T�C�Y���g�p
    for (size_t i = 0; i < m_pEnemy.size(); ++i)
    {
        if (m_pEnemy[i] != nullptr)
        {
            m_pEnemy[i]->Update();

            //�G�����S���Ă�����폜.
            if (m_pEnemy[i]->GetIsDead())
            {
                RemoveEnemy(i);
            }
        }
    }
}

void CEnemyManager::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
    //vector�̃T�C�Y���g�p
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
    //�����̓G���N���A���Ă��烍�[�h
    for (CCharacter* enemy : m_pEnemy)
    {
        SAFE_DELETE(enemy);
    }
    m_pEnemy.clear();

    const char* Path = "Data\\csv\\Position.csv";

    std::ifstream file(Path);
    if (!file.is_open())
    {
        std::cerr << "�G�z�u�t�@�C�����J���܂���ł���: " << Path << std::endl;
        return;
    }

    std::string line;

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string token;

        int index_from_csv = 0; // CSV����ǂݍ��񂾃C���f�b�N�X
        float x = 0.0f, y = 0.0f, z = 0.0f;

        // 1���: �G�ԍ� (0�n�܂�ɕϊ�)
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

        // 2���: x
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
        // 3���: y
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
        // 4���: z
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
            m_pEnemy.resize(index_from_csv + 1, nullptr); // �T�C�Y�𒲐�
        }

        // �G�C���X�^���X�����݂��Ȃ��ꍇ�̂ݐ���
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
        SAFE_DELETE(m_pEnemy[index]);                //�I�u�W�F�N�g�̉��.
        m_pEnemy.erase(m_pEnemy.begin() + index);   //�R���e�i����v�f���폜.
    }
}
