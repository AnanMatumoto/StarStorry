#include "StarChild.h"
#include "StarObject.h"
#include "ObjectManager.h"


//------------------------------------
//�@�R���X�g���N�^
StarChild::StarChild(
	float x,
	float y,
	float rot
):ObjectBase(x,y, rot){

	m_width   = 46.f;
	m_height  = 64.f;
}


void StarChild::Update() {
}

void StarChild::Draw() {

	SetVertex();
	Lib::DrawDiamond2D(
		"piyo",
		 vtx
	);
}

//-------------------------------------
//���_�̐ݒ�
void StarChild::SetVertex(DWORD color) {

	float ox = 0.5f;
	float oy = 0.5f;

	vtx[0] = {{(0.5f-ox),oy,0.f,1.f}, color,{0.f,0.5f}};
	vtx[1] = {{ox,(0.5f+oy), 0.f,1.f},color,{0.5f,1.f}};
	vtx[2] = {{(0.5f+ox),oy, 0.f, 1.f},color,{1.f,0.5f}};
	vtx[3] = {{ox,(0.5f-oy), 0.f,1.f},color,{0.5f,0.f}};

	DiamondLocalTransform(vtx, m_width, m_height,m_rot);
	RefParentVertex(vtx);
}

//-------------------------------------
//�e�̍��W�����g�ɔ��f����
void StarChild::RefParentVertex(Vertex vtx[4]) {

  m_parent = ObjectManager::GetInstance().GetPtr(STAR_OBJ);

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

