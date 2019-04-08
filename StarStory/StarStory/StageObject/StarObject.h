﻿#pragma once
#include "../Common/Common.h"
#include "ObjectBase.h"
#include "StarChild.h"

//=================================
// 星オブジェクト親クラス
//=================================

class StarObject : public ObjectBase{

public:
	StarObject(float x, float y, float rot);
	~StarObject()override{}

private:

	// 更新処理
	void Update()override;
	//描画処理
	void Draw()override;
	//　頂点座標の設定
	void SetVertex(DWORD color = 0x00ffffff)override;
	// 自動操作
	void AutomaticMove();

private:
	Vec2 m_vel;		     //速さ
	float m_speed;
};