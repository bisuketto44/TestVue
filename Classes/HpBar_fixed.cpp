#pragma once
#pragma execution_character_set("utf-8")

#include "HpBar_fixed.h"
#include "entity/character/character.h"
#include "scene/stage_scene.h"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::ui;

HpFixedBar::HpFixedBar(Character * owner, const cocos2d::Vec2 & position, Game::SIDE side, const int bar_width, const int bar_height, const unsigned int max, bool isUilayer)
	: Ui(owner, "hp_bar_red.png", position, side, true, true, isUilayer)
{
	new_bar_width = bar_width;
	new_bar_height = bar_height;
	isUiLayer = isUilayer;

	//// �Q�[�W�̃t���[�������̍쐬
	const Rect outer_rect(0, 0, 24, 24);
	const Rect inner_rect(1, 1, 22, 22);

	////�t���[���𐶐�
	_frame = Scale9Sprite::create("hp_frame.png", outer_rect, inner_rect);
	_frame->getTexture()->setAliasTexParameters();
	_frame->setContentSize(Size(new_bar_width, new_bar_height));

	//�Œ�p���C���[�ɕ\��
	//addChild(_frame);
	Game::getInstance()->getCurrentScene()->getuILayer()->addChild(_frame);

	// ����HP�X�v���C�g�̃o�[�̑傫����ύX
	getSprite()->setContentSize(Size(new_bar_width, new_bar_width));

	//�ő�HP��o�^
	this->_max = max;

	//�ʒu�Œ�
	this->setPosition(cocos2d::Vec2(465.0f, 638.0f));
	this->_frame->setPosition(cocos2d::Vec2(1280.0 / 2.0f, 650.0f));

	//�A���J�[�𒲐�
	loadResources(getSprite());

	
}

HpFixedBar::~HpFixedBar()
{
	//�t���[���X�v���C�g�����
	//this->_frame->removeFromParentAndCleanup(true);
	CC_SAFE_RELEASE_NULL(this->_frame);
}

//HP�o�[�𐶐�
HpFixedBar * HpFixedBar::create(Character * owner, const cocos2d::Vec2 & position, Game::SIDE side, const int bar_width, const int bar_height, const unsigned int max, bool isUilayer)
{
	//�C���X�^���X�𐶐�
	HpFixedBar* object = APP_NEW HpFixedBar(owner, position, side, bar_width, bar_height, max, isUilayer);
	CCLOG("HpFixedBar_CREATE");

	return object;
}



//HP�o�[�ɒl��n���ĕ\��
void HpFixedBar::DrawingUpdate()
{
	int value = owner_->getHP();

	//�F��ύX���鏈���͈�U�ۗ�

	// �Ǘ��l�̍ő�l�ɑ΂��錻�ݒl�̔䗦���v�Z
	float ratio = (float)value / this->_max;

	// �V�����Q�[�W�̉���
	float newWidth = new_bar_width * ratio;
	float newHeight = new_bar_height;

	// ���݂̃o�[�T�C�Y��ύX
	getSprite()->setContentSize(Size(newWidth, newHeight));

}

void HpFixedBar::loadResources(cocos2d::Sprite* sprite)
{
	//����HP�X�v���C�g�̃X�v���C�g�̃A���J�[��ύX
	getSprite()->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	getSprite()->getTexture()->setAliasTexParameters();
	getSprite()->retain();
}