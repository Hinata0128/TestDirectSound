#include "CGround.h"

CGround::CGround()
{
}

CGround::~CGround()
{
}

void CGround::Update()
{
	//地面スクロールをここに書く
	//m_vPosition親クラスに書いているからポジションだけでいい.
	//地面の背景スクロールする用の処理
	m_vPosition.z -= 0.2f;
	//-100.0fよりも地位sかうなると初期化してまた始める.
	if (m_vPosition.z < -100.f)
	{
		m_vPosition.z = 0.f;
	}
}
