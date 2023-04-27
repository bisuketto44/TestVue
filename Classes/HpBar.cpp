#pragma once
#pragma execution_character_set("utf-8")

#include "HpBar.h"
#include "entity/character/character.h"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::ui;

HpBar::HpBar(Character * owner, const cocos2d::Vec2 & position, Game::SIDE side, const int bar_width, const int bar_height, const unsigned int max, bool isUilayer)
	: Ui(owner, "hp_bar_green.png", position, side, true, true, isUilayer)
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

	addChild(_frame);

	// ����HP�X�v���C�g�̃o�[�̑傫����ύX
	getSprite()->setContentSize(Size(new_bar_width, new_bar_width));

	//�ő�HP��o�^
	this->_max = max;

	//�A���J�[�𒲐�
	loadResources(getSprite());

	//�L�����N�^�[�̉����ɌŒ�
	setPosition(position - cocos2d::Vec2(50, 94));
	this->_frame->setPosition(position - cocos2d::Vec2(0, 80));
}

HpBar::~HpBar()
{
	//�t���[���X�v���C�g�����
	_frame->removeFromParentAndCleanup(true);
	CC_SAFE_RELEASE_NULL(this->_frame);
}

//HP�o�[�𐶐�
HpBar * HpBar::create(Character * owner, const cocos2d::Vec2 & position, Game::SIDE side, const int bar_width, const int bar_height, const unsigned int max, bool isUilayer)
{
	//�C���X�^���X�𐶐�
	HpBar* object = APP_NEW HpBar(owner, position, side, bar_width, bar_height, max,isUilayer);
	return object;
}



//HP�o�[�ɒl��n���ĕ\��
void HpBar::DrawingUpdate()
{
	int value = owner_->getHP();

	//�F��ύX���鏈���͈�U�ۗ�

	// �Ǘ��l�̍ő�l�ɑ΂��錻�ݒl�̔䗦���v�Z
	float ratio = (float)value / this->_max;

	// �V�����Q�[�W�̉���
	float newWidth = new_bar_width * ratio;
	float newHeight = new_bar_height;
	;

	// ���݂̃o�[�T�C�Y��ύX
	getSprite()->setContentSize(Size(newWidth, newHeight));

	//�ʒu��ύX
	if (!isUiLayer)
	{
		setPosition(owner_->getPosition() - cocos2d::Vec2(50, 94));
		this->_frame->setPosition(owner_->getPosition() - cocos2d::Vec2(0, 80));
	}
	
	if (owner_ == nullptr)
	{
		releaseRequest();
	}

}

void HpBar::loadResources(cocos2d::Sprite* sprite)
{
	//����HP�X�v���C�g�̃X�v���C�g�̃A���J�[��ύX
	getSprite()->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	getSprite()->getTexture()->setAliasTexParameters();
	getSprite()->retain();
}