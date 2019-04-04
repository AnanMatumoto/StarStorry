#include "StarChild.h"
#include "StarObject.h"

//------------------------------------
//�@�R���X�g���N�^
StarChild::StarChild(float x, float y) {

}

void StarChild::Update() {

}

void StarChild::Draw() {

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
		float new_y = (vtx_pos_x * cos) + (vtx_pos_y * sin);
	
		//���΍��W��ݒ肷��
		vtx[i].pos.x = new_x + pos_x;
		vtx[i].pos.y = new_y + pos_y;
	}

}