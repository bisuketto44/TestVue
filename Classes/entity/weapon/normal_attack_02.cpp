/**
 * @file    normal_attack_02.cpp
 *
 * @brief   �ʏ�U��02�̃N���X
 * @details Character�N���X�Ɏ������邱�ƂŊe�L���������̍U���𔭓�����
 *          �قȂ�L�����N�^�[�������Z���g����悤�ɂ������ăL�����N�^�[�̎����Ƃ͐؂藣��
 *
 * @author  Kaifu Koji
 * @date    2018/04/03
 * @note    �}�[�x���X�J�����V�l���CC++���K�p
 */

#include "app_define.h"
#include "entity/weapon/normal_attack_02.h"
#include "controller/controller.h"
#include "entity/character/character.h"
#include "entity/weapon/homing_attack_01_bullet.h"


namespace {
	//! �ʏ�U��02�̉摜�t�@�C����
	const char* NORMAL_ATTACK_02_RESOURCE_NAME = nullptr;		// �\���͖����̂�NULL
}

/**
 * @brief		�R���X�g���N�^
 * @param[in]	owner			�e�̎�����̃|�C���^
 * @param[in]	offsetPosition	�U�������ʒu�̃I�t�Z�b�g�i�L�����Ɠ������W�ȊO�Ŕ������������Ƃ��Ɏw��j
 */
NormalAttack02::NormalAttack02(Character* owner, const cocos2d::Vec2& offsetPosition)
	: Attack(
		NORMAL_ATTACK_02_RESOURCE_NAME,
		owner,
		offsetPosition
	)
{
}


/**
 * @brief		�f�X�g���N�^
 */
NormalAttack02::~NormalAttack02()
{
}


/**
 * @brief		�X�V
 * @param[in]	deltaTime		�O�t���[������i�s�������ԁi�P�ʁF�b�j
 */
void NormalAttack02::update(float deltaTime)
{
	// �X�v���C�g������Έʒu���X�V
	if (getSprite())
	{
		cocos2d::Vec2 position = owner_->getPosition() + offsetPosition_;
		setPosition(position);
	}

	// �P���ɒe�𔭎˂��Ă݂�
	shoot();

	// �U�����I������������N�G�X�g���o��
	releaseRequest();
}


/**
 * @brief		�e��������
 */
void NormalAttack02::shoot()
{
	// �܂��̓X�[�p�[�N���X��shoot
	Attack::shoot();

	// �e�̈ʒu���Z�o
	cocos2d::Vec2 bulletPosition;
	cocos2d::Vec2 position = owner_->getPosition() + offsetPosition_;
	bulletPosition.x = position.x + 0.0f;
	bulletPosition.y = position.y + 0.0f;

	// SIDE�i�G���������j�̎w��
	Game::SIDE side = Game::SIDE_HOSTILITY;
	Character::DIRECTION direction = Character::RIGHT;

	if (owner_)
		side = owner_->getSide();

	// �e�𐶐�
	HomingAttack01Bullet::create(bulletPosition, side, direction);
}
