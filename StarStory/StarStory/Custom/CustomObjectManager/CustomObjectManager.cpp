﻿#include"CustomObjectManager.h"

#include <fstream>

// コンストラクタ
CustomObjectManager::CustomObjectManager()
	: m_diamond_part(Diamond::TOP_PART),
	skill_table_tex_id(SkillTable::BASE1) {

	// ひし形生成
	m_diamond_base.push_back(new Diamond(Diamond::TOP_PART, "./Resource/skill_data_01.dat"));
	m_diamond_base.push_back(new Diamond(Diamond::TOP_RIGHT_PART, "./Resource/skill_data.02.dat"));
	m_diamond_base.push_back(new Diamond(Diamond::BOTTOM_RIGHT_PART, "./Resource/skill_data.03.dat"));
	m_diamond_base.push_back(new Diamond(Diamond::BOTTOM_LEFT_PART, "./Resource/skill_data.04.dat"));
	m_diamond_base.push_back(new Diamond(Diamond::TOP_LEFT_PART, "./Resource/skill_data.05.dat"));

	// スキルテーブルの生成
	for (int i = 0; i < SkillTable::MAX_TEX_NUM; ++i) {

		m_skill_table.push_back(new SkillTable(skill_table_tex_id));

		skill_table_tex_id = static_cast<SkillTable::TexID>(skill_table_tex_id + 1);
	}
}

// デストラクタ
CustomObjectManager::~CustomObjectManager() {

	// スキルデータを外部ファイルに保存
	std::fstream file[5];
	file[0].open("./Resource/skill_data_01.dat", std::ios::binary | std::ios::out);
	file[0].write((char*)&m_diamond_base[0]->GetSkillDara(), sizeof(Skill_Data));
	file[0].close();

	file[1].open("./Resource/skill_data.02.dat", std::ios::binary | std::ios::out);
	file[1].write((char*)&m_diamond_base[1]->GetSkillDara(), sizeof(Skill_Data));
	file[1].close();

	file[2].open("./Resource/skill_data.03.dat", std::ios::binary | std::ios::out);
	file[2].write((char*)&m_diamond_base[2]->GetSkillDara(), sizeof(Skill_Data));
	file[2].close();

	file[3].open("./Resource/skill_data.04.dat", std::ios::binary | std::ios::out);
	file[3].write((char*)&m_diamond_base[3]->GetSkillDara(), sizeof(Skill_Data));
	file[3].close();

	file[4].open("./Resource/skill_data.05.dat", std::ios::binary | std::ios::out);
	file[4].write((char*)&m_diamond_base[4]->GetSkillDara(), sizeof(Skill_Data));
	file[4].close();

	// ひし形の削除
	for (auto x : m_diamond_base) {

		delete x;
		x = nullptr;
	}

	// スキルテーブルの削除
	for (auto x : m_skill_table) {

		delete x;
		x = nullptr;
	}
}

// 更新
void CustomObjectManager::Update() {

	// ひし形の更新
	for (auto x : m_diamond_base) {

		x->Update();
	}

	// スキルテーブルの更新
	for (auto x : m_skill_table) {

		x->Update();
	}

	m_skill_table[SkillTable::NORMAL_SKILL]->ClickSkillSet();
	m_skill_table[SkillTable::ACCEL_SKILL]->ClickSkillSet();
	m_skill_table[SkillTable::JUMP_SKILL]->ClickSkillSet();
	m_skill_table[SkillTable::STOP_SKILL]->ClickSkillSet();
}

// 描画
void CustomObjectManager::Draw() {

	// ひし形の描画
	for (auto x : m_diamond_base) {

		x->Draw();
	}

	// スキルテーブルの描画
	for (auto x : m_skill_table) {

		x->Draw();
	}
}

