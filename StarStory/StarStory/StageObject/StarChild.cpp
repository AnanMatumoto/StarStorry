#include "StarChild.h"
#include "StarObject.h"
#include "ObjectManager.h"
#include "ObjectTest1.h"

DWORD red = 0;//����ŏ���

			  //------------------------------------
//�@�R���X�g���N�^
StarChild::StarChild(
	float x,
	float y,
	std::string tex_name,
	float rot
) :ObjectBase(x, y, rot) {
	m_width = 46.f;
	m_height = 64.f;
	m_tex_name = tex_name;
	m_parent = ObjectManager::GetInstance().FindObject(STAR_OBJ);
	m_hit_obj = ObjectManager::GetInstance().GetGameObjects<ObjectTest1>();
	is_hit = false;
}

//------------------------------------
//�@�X�V����
void StarChild::Update() {

}

//------------------------------------
//�@�`�揈��
void StarChild::Draw() {
	SetVertex(red);//��
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
	m_vtx[0] = { {(0.5f - ox),oy,0.f,1.f}, color,{0.f,0.5f} };
	m_vtx[1] = { {ox,(0.5f + oy), 0.f,1.f},color,{0.5f,1.f} };
	m_vtx[2] = { {(0.5f + ox),oy, 0.f, 1.f},color,{1.f,0.5f} };
	m_vtx[3] = { {ox,(0.5f - oy), 0.f,1.f},color,{0.5f,0.f} };
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

//---------------------------------------
//�@�����蔻��p�t���O�Q�b�^�[
void StarChild::IsHitToObject() {

	Vec2 vec = { m_vtx[1].pos.x, m_vtx[1].pos.y };

	for (auto it : m_hit_obj) {
		if (vec.x <= it->GetWidth()) {
			//�I�u�W�F�N�g�̕��ɒ��_�����邩
			if (IsHitToSurface(vec, it)) {
				//���_���������Ă��邩
				red = 0x00ff0000;
				is_hit = true;
			}
			else {
				red = 0x00ff0000;
				is_hit = true;
			}
		}
		else {
			red = 0;//��
			is_hit = false;
		}
	}
}

//-------------------------------
//�@�����蔻��p�ϐ��Q�b�^�[
const bool StarChild::GetHit()const {
	return is_hit;
}


//-------------------------------
//	�����蔻��p�ϐ��Z�b�^�[
void StarChild::SetHit(bool is_hit_) {
	is_hit = is_hit_;
}

