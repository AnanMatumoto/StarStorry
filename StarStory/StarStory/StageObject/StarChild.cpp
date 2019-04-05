#include "StarChild.h"
#include "StarObject.h"
#include "ObjectManager.h"


//------------------------------------
//�@�R���X�g���N�^
StarChild::StarChild(
	float x,
	float y
):ObjectBase(x,y){

	m_width   = 46.f;
	m_height  = 64.f;
	m_rot = 3.f;
	is_delete = false;

}


void StarChild::Update() {
}

void StarChild::Draw() {


	Lib::Texture tex("Resource/test_img/Player.jpg");

	////Todo: ���̏�����Lib�Ɉړ�����
	float ox = 0.5f;
	float oy = 0.5f;
	DWORD color = D3DCOLOR_ARGB(255, 255, 255, 255);
	
	Vertex vtx[4] ={
		{{-ox,(0.5f - oy),0.f,1.f}, color,{0.f,0.5f}},
		{{(0.5f - ox), -oy,0.f,1.f},color,{0.5f,1.f}},
		{{(1.f - ox),(0.5f - oy),0.f, 1.f},color,{1.f,0.5f}},
		{{(0.5f-ox),(1.f - oy),0.f,1.f},color,{0.5f,0.f}}
	};

	LocalTransform(vtx, m_width, m_height);
	RefParentVertex(vtx);


	Lib::dev->SetTexture(0, tex);
	Lib::dev->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	Lib::dev->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vtx, sizeof(Vertex));

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
		float new_y = (vtx_pos_x * cos) + (vtx_pos_y * sin);
	
		//���΍��W��ݒ肷��
		vtx[i].pos.x = new_x + pos_x;
		vtx[i].pos.y = new_y + pos_y;
	}

}