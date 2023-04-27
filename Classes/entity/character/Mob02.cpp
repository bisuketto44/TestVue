/**
 * @file    Mob02.cpp
 *
 * @brief   Mob02�̃L�����N�^�[�N���X
 * @details Mob02��o�ꂳ�������Ƃ��͂��̃N���X�𐶐�����
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    �}�[�x���X�J�����V�l���CC++���K�p
 */

#include "utility/macro.h"
#include "app_define.h"
#include "entity/character/Mob02.h"
#include "controller/pad_controller.h"
 //����͓���AI�R���g���[���[���g���Ă���(��)
#include "controller/Mob01_ai_controller.h"
#include "entity/effect/explosion.h"
#include "utility/collision.h"
#include "entity/weapon/normal_attack_01.h"
#include "game.h"
#include "ui.h"


namespace {
	//! Mob02�̉摜�t�@�C����
	const char* MOB_01_RESOURCE_NAME = "yumi_action0_0.png";
}


/**
 * @brief		����
 * @param[in]	controllerType	�R���g���[��
 * @param[in]	position		�����ʒu
 * @param[in]	side			�G�����̎w��
 */
Mob02* Mob02::create(Controller::TYPE controllerType, const cocos2d::Vec2& position, Game::SIDE side, int HP)
{
	Controller* controller = nullptr;
	bool flipX = false;

	// �w�肳�ꂽ�^�C�v�̃R���g���[���𐶐�
	switch (controllerType)
	{
	case Controller::TYPE_PAD:
		// �p�b�h����̃R���g���[���𐶐�
		controller = APP_NEW PadController();
		break;

	case Controller::TYPE_AI:
		// Mob02�p��A)I����̃R���g���[���𐶐�
		controller = APP_NEW Mob01AIController();
		flipX = true;
		break;

	case Controller::TYPE_REMOTE:
		// �������i���̉��K�ł͎g�p���Ȃ��j
		break;
	}

	// �ړI�̃I�u�W�F�N�g�𐶐�
	Mob02* object = APP_NEW Mob02(position, side, HP, controller);

	// �����]���邩�ǂ���
	object->setFlipX(flipX);

	return object;
}


/**
 * @brief		�R���X�g���N�^
 * @param[in]	position		�����ʒu
 * @param[in]	side			�G�����̎w��
 * @param[in]	controller		�R���g���[��
 */
Mob02::Mob02(const cocos2d::Vec2& position, Game::SIDE side, int HP, Controller* controller)
	: Character(MOB_01_RESOURCE_NAME, position, side, HP, controller, true, true)
{
	CCLOG("Mob02::Mob02()");

	// �\���X�P�[���̒���
	getSprite()->setScale(0.25f);

	// �R���W�����𐶐�
	createCollideCircle(AppDef::STANDERD_CHARACTER_COLLISION_RADIUS);

	// �A�j���[�V�����𐶐�
	createAnimation();
	setAnimation(ANIMATION_STAND);	// �����̃A�j���[�V�������Z�b�g

	setCurrentDirection(LEFT);
}


/**
 * @brief		�f�X�g���N�^
 */
Mob02::~Mob02()
{
	CCLOG("Mob02::~Mob02()");
}


/**
 * @brief		�X�V
 * @param[in]	deltaTime		�O�t���[������i�s�������ԁi�P�ʁF�b�j
 */
void Mob02::update(float deltaTime)
{
	// �܂��̓X�[�p�[�N���X��update
	Character::update(deltaTime);

	// Mob02�Ǝ��̏���������΁��ɏ���



}


// -----------
// updateMove()�AupdateAction() �Ȃǂɂ��̃N���X�Ǝ��̏�������ꂽ���ꍇ��
// Asuka�N���X���Q�l�Ɋe�֐���ǉ�����
// -----------
void Mob02::attackNormal()
{
	// �ʏ�U���̃A�j���[�V�����Đ�
	if (animation_ != ANIMATION_NORMAL_ATTACK)
		setAnimation(ANIMATION_NORMAL_ATTACK);

	// ���̎��_��attack_��NULL�̂͂�
	APP_ASSERT(attack_ == nullptr, "attack_ must not be nullptr here.")

		attack_ = APP_NEW NormalAttack01(
			this,
			cocos2d::Vec2(AppDef::STANDERD_CHARACTER_ATTACK_POSITION_OFFSET_X, AppDef::STANDERD_CHARACTER_ATTACK_POSITION_OFFSET_Y)
		);
	state_ = STATE_ATTACK;
}

/**
 * @brief		�A�j���[�V�����̃Z�b�g
 * @param[in]	animation		�Đ��������A�j���[�V����
 */
void Mob02::setAnimation(ANIMATION animation)
{
	animation_ = animation;

	//	"Mob02_action0_0.png",		����
	//	"Mob02_action3_0�`7.png",	����
	//	"Mob02_action4_0.png",		�U��

	switch (animation)
	{
	case ANIMATION_STAND:
		// �����̃A�j���[�V�������Z�b�g
		getAnimation()->clear();
		getAnimation()->addFrame("yumi_action0_0.png", 1.00f);
		getAnimation()->setEndType(AnimationHelper::END_TYPE_STOP);		// �Ō�̃R�}��\����������
		break;

	case ANIMATION_MOVE:
		// �ړ��̃A�j���[�V�������Z�b�g
		getAnimation()->clear();
		getAnimation()->addFrame("yumi_action3_0.png", 0.05f);
		getAnimation()->addFrame("yumi_action3_1.png", 0.05f);
		getAnimation()->addFrame("yumi_action3_2.png", 0.05f);
		getAnimation()->setEndType(AnimationHelper::END_TYPE_LOOP);		// �ŏ��ɖ߂��ă��[�v����
		break;
	case ANIMATION_NORMAL_ATTACK:
		// �ʏ�U���̃A�j���[�V�������Z�b�g
		getAnimation()->clear();
		getAnimation()->addFrame("yumi_action4_0.png", 0.20f);
		getAnimation()->setEndType(AnimationHelper::END_TYPE_STOP);		// �Ō�̃R�}��\����������
		break;
	}
}

/**
 * @brief		�R���W�����q�b�g���̃R�[���o�b�N
 * @param[in]	target		�Փ˂�������
 */
void Mob02::collideCallback(Collide::Object* target)
{
	// �G�̒e�ɓ������������
	if (target->getOwner())
	{
		if (
			(target->getOwner()->getSide() != getSide())
			|| (target->getOwner()->getSide() == Game::SIDE_HOSTILITY)
			)
		{
			// �����G�t�F�N�g��\��
			Explosion::play(getPosition(), 1.0f);


			// �������g�̉�����N�G�X�g
			releaseRequest();
		}
	}
}
