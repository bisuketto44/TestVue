
#include "background.h"
#include "game.h"
#include "scene/stage_scene.h"


namespace {
	//! �򒹂̉摜�t�@�C����
	const char* BACKGROUND_RESOURCE_NAME = "BackGround_Temp.png";	// �����̊G���Z�b�g
}


BackGround* BackGround::create(const cocos2d::Vec2& position, Game::SIDE side)
{
	
	bool flipX = false;

	// �ړI�̃I�u�W�F�N�g�𐶐�
	BackGround* object = APP_NEW BackGround(position, side);

	// �����]���邩�ǂ���
	object->setFlipX(flipX);

	return object;
}

BackGround::BackGround(const cocos2d::Vec2 & position, Game::SIDE side)
	: Entity(BACKGROUND_RESOURCE_NAME, position, Game::SIDE_NON, true, true,false)
{
	// �\���X�P�[���̒���
	getSprite()->setScale(6.2f);

	// �V�[���̎q�ɒǉ�
	//Game::getInstance()->getCurrentScene()->addChild(this, -1);

}

BackGround::~BackGround()
{
}
