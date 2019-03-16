﻿#include "Scene.h"

namespace Scene {

	int g_StateID = SS_INIT;
	int g_SceneID = SC_TITLE;
}

//-----------------------------
//　タイトルシーン初期化
void TitleScene::Init() {

	Scene::g_StateID = SS_UPDATE;
}

//-----------------------------
//　タイトルシーン更新
void TitleScene::Update() {

	Scene::g_StateID = SS_END;
}

//-----------------------------
//  タイトルシーン終了
void TitleScene::End() {

	Scene::g_StateID = SS_INIT;
	Scene::g_SceneID = SC_CUSTOM;
}

//-----------------------------
//　状態管理
void TitleScene::Control() {

	switch (Scene::g_StateID)
	{
	case SS_INIT:
		Init(); break;

	case SS_UPDATE:
		Update(); break;

	case SS_END:
		End(); break;
	}
}

//------------------------------
//　タイトルシーン描画
void TitleScene::Draw() {

}
