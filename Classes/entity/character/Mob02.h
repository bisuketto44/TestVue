
/**
 * @file    Mob02.h
 *
 * @brief   Mob02�̃L�����N�^�[�N���X
 * @details Mob02��o�ꂳ�������Ƃ��͂��̃N���X�𐶐�����
 *
 * @author  Kaifu Koji
 * @date    2018/04/03
 * @note    �}�[�x���X�J�����V�l���CC++���K�p
 */

#pragma once

#include <cocos2d.h>
#include "entity/character/character.h"
#include "controller/controller.h"


 /**
  * @brief	Mob02�̃L�����N�^�[�N���X
  */
class Mob02 : public Character
{
public:
	// ����
	static Mob02* create(Controller::TYPE controllerType, const cocos2d::Vec2& position, Game::SIDE side, int HP);

	// �R���X�g���N�^
	Mob02(const cocos2d::Vec2& position, Game::SIDE side, int HP, Controller* controller = nullptr);
	// �f�X�g���N�^
	virtual ~Mob02();

	// �X�V
	virtual void		update(float deltaTime);

	// �A�j���[�V�����̎w��
	virtual void		setAnimation(ANIMATION animation);

	// �R���W�����q�b�g���̃R�[���o�b�N
	virtual void		collideCallback(Collide::Object* target);

	virtual void Mob02::attackNormal();

private:
};
