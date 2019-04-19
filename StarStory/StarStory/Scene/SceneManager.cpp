﻿#include "SceneManager.h"
#include "TitleScene.h"
#include "CustomScene.h"
#include "SelectScene.h"
#include "GameScene.h"
#include "ResultScene.h"

//---------------------------------
//インスタンス取得
SceneManager& SceneManager::GetInstance() {
	static SceneManager sm;
	return sm;
}

//--------------------------------
//  シーン初期化
void SceneManager::Init() {

	//シーンの登録
	scene_list.emplace(SC_TITLE,  new TitleScene());
	scene_list.emplace(SC_CUSTOM, new CustomScene());
	scene_list.emplace(SC_SELECT, new SelectScene());
	scene_list.emplace(SC_GAME,   new GameScene());
	scene_list.emplace(SC_RESULT, new ResultScene());

	//初期設定でタイトルをセットする
	auto it = scene_list.find(SC_TITLE);
	m_scene = it->second;
	m_now_id = SC_TITLE;
}

//---------------------------------
//　シーン更新
void SceneManager::Update() {

	SceneID scene_id;

	scene_id = m_scene->Control();
	ChangeScene(scene_id);
}

//-------------------------------------
//　シーン遷移
void SceneManager::ChangeScene(SceneID scene_id) {
	
	if (scene_id != m_now_id) {
		//現在のシ―ンが終了に差しかかった時
		m_now_id = scene_id;
	}
	auto it = scene_list.find(m_now_id);
	m_scene = it->second;
}

//--------------------------------------
//　デストラクタ
SceneManager::~SceneManager() {

	//リスト内の破棄
	for (auto & it : scene_list) {
		delete it.second;
	}
}


