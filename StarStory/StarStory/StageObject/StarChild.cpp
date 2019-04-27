#include "StarChild.h"
#include "StarObject.h"
#include "ObjectManager.h"
#include "MapObject.h"
#include "../Collision/Collision.h"

//------------------------------------
//�@�R���X�g���N�^
StarChild::StarChild(
	float x,
	float y,
	std::string tex_name,
	Skill skill,
	float rot
) :ObjectBase(x, y, rot){
	m_width    = 46.f;
	m_height   = 64.f;
	m_tex_name = tex_name;
	m_parent   = ObjectManager::GetInstance().FindObject(STAR_OBJ);
	m_map_obj  = ObjectManager::GetInstance().GetGameObjects<MapObject>();
	m_obj_width = 0.f;
	is_hit     = false;
	m_skill    = skill;
	m_obj      = nullptr;
}

//------------------------------------
//�@�X�V����
void StarChild::Update() {

	HitToObject();
	IsHit();
}

//------------------------------------
//�@�`�揈��
void StarChild::Draw() {

	SetVertex();
	Lib::DrawDiamond2D(
		m_tex_name.c_str(),
		m_vtx
	);
}

//-------------------------------------
//���_�̐ݒ�
void StarChild::SetVertex(DWORD color) {
	
	float ox = 0.5f;
	float oy = 0.5f;
	m_vtx[0] = { {(0.5f - ox),oy,0.f,1.f}, color,{0.31f,0.5f} };
	m_vtx[1] = { {ox,(0.5f + oy), 0.f,1.f},color,{0.5f,0.78f} };
	m_vtx[2] = { {(0.5f + ox),oy, 0.f, 1.f},color,{0.69f,0.5f} };
	m_vtx[3] = { {ox,(0.5f - oy), 0.f,1.f},color,{0.5f,0.228f} };

	DiamondLocalTransform(m_vtx, m_width, m_height);
	RefParentVertex(m_vtx);

}

//-------------------------------------
//�e�̍��W�����g�ɔ��f����
void StarChild::RefParentVertex(Vertex vtx[4]) {
	
	//�e�̍��W���擾
	float pos_x = m_parent->GetX();
	float pos_y = m_parent->GetY();
	
	//�e�̉�]�p���擾
	float sin = sinf(D3DXToRadian(m_parent->GetRot()));
	float cos = cosf(D3DXToRadian(m_parent->GetRot()));
	float vtx_pos_x = 0.f;
	float vtx_pos_y = 0.f;
	
	for (int i = 0; i < 4; ++i) {
		//���[�J�����WXY��ۑ�
		vtx_pos_x = vtx[i].pos.x;
		vtx_pos_y = vtx[i].pos.y;
		//��]�����������V���W��ݒ�
		float new_x = (vtx_pos_x * cos) + (vtx_pos_y * -sin);
		float new_y = (vtx_pos_x * sin) + (vtx_pos_y * cos);
		//���΍��W��ݒ肷��
		vtx[i].pos.x = new_x + pos_x;
		vtx[i].pos.y = new_y + pos_y;
	}
}

//--------------------------------------
//�@�I�u�W�F�N�g�Ƃ̓����蔻�����������
void StarChild::HitToObject() {

	SetVertex();
	Vec2 vec = { m_vtx[1].pos.x, m_vtx[1].pos.y };

	for (auto obj : m_map_obj) {
		float width = obj->GetVertex(1).pos.x;
		//���_���I�u�W�F�N�g�̕��̒��Ȃ�ۑ�
		if (vec.x >= obj->GetX() && vec.x <= width) {
			m_obj= obj;
		}
		continue;
	}
}

void StarChild::IsHit() {

	SetVertex();
	
	Vec2 vec = { m_vtx[1].pos.x, m_vtx[1].pos.y };
	if (m_obj != nullptr) {
	
		if (IsHitToUpper(vec, m_obj)) {
			is_hit = true;
			m_obj_width = m_obj->GetVertex(1).pos.x;
		}
		else {
			is_hit = false;
		}
	}
	else {
		return;
	}

}

//-------------------------------
//�@�����蔻��p�ϐ��Q�b�^�[
const bool StarChild::GetHit()const
{
	return is_hit;
}

//-------------------------------
//�@�X�L�����Q�b�^�[
const Skill StarChild::GetSkill()const {
	return m_skill;
}

//--------------------------------
// �}�b�v�I�u�W�F�N�g�Q�b�^�[
float StarChild::GetHitObjWidth() {
	return m_obj_width;
}
