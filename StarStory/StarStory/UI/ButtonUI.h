#pragma once
#include"../StageObject/ObjectBase.h"
#include <string>

class ButtonUI : public ObjectBase {

public:

	//�R���X�g���N�^
	ButtonUI(
		float x, float y,
		std::string tex_name="none",		
		float rot=0.f
	):ObjectBase(x, y, rot) {
		m_width  = 200.f;
		m_height = 100.f;
	}

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�����������ǂ����̃t���O
	void Hit();

	bool GetHit() {
		this->is_hit;
	}
	//is_hit�̃Q�b�^�[

private:

	bool is_hit;

	/*�}�E�X�I�u�W�F�N�g�̓����蔻��������
	  ������is_hit��true�ɂ���
	*/

	//�����������ǂ����̃t���O

};

