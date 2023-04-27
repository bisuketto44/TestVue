/**
 * @file    normal_attack_01_bullet.cpp
 *
 * @brief   �ʏ�U��01�̒e�̃N���X(���݂̓v���C���[�L���������C�e)
 * @details �ʏ�U��01�̒e��o�ꂳ�������Ƃ��͂��̃N���X�𐶐�����
 *          ���̃N���X�͎��ȏ���or�}�l�[�W���ɂ���č폜�����B
 *          �i�����������ō폜����K�v�͂Ȃ��j
 *
 * @author  Kaifu Koji
 * @date    2018/04/03
 * @note    �}�[�x���X�J�����V�l���CC++���K�p
 */

#include "app_define.h"
#include "entity/weapon/homing_attack_01_bullet.h"
#include "utility/collision.h"
#include "manager/character_manager.h"
#include "game.h"
#include <list>
#include <math.h>


namespace {
	//! �ʏ�U��01�̒e�̉摜�t�@�C����
//	const char* const NORMAL_ATTACK_01_BULLET_RESOURCE_NAME = "bullet_01.png";
	const char* const NORMAL_ATTACK_01_BULLET_RESOURCE_NAME = "bullet_02.png";
};

/**
 * @brief		�e�̐���
 * @param[in]	position		�����ʒu
 * @param[in]	side			�G�������
 * @return		���������e�̃|�C���^
 */
HomingAttack01Bullet* HomingAttack01Bullet::create(const cocos2d::Vec2& position, Game::SIDE side, Character::DIRECTION direction)
{
	HomingAttack01Bullet* bullet = APP_NEW HomingAttack01Bullet(position, side, direction);
	return bullet;
}


/**
 * @brief		�R���X�g���N�^
 * @param[in]	position		�����ʒu
 * @param[in]	side			�G�������
 */
HomingAttack01Bullet::HomingAttack01Bullet(const cocos2d::Vec2& position, Game::SIDE side, Character::DIRECTION direction)
	: Bullet(
		NORMAL_ATTACK_01_BULLET_RESOURCE_NAME,
		position,
		side,
		direction
	)
{
	// �\���X�P�[���̒���
    getSprite()->setScale(2.0f);
	//getSprite()->setScale(0.125f);

	// �R���W�����𐶐�
	createCollideCircle(AppDef::STANDERD_BULLET_COLLISION_RADIUS);

	// �U���\�ȓG�L�������������z��Ɋi�[
	enemys = Game::getInstance()->getCurrentScene()->getCharacterManager()->searchEnemys();

	//�󂶂�Ȃ����
	if (!enemys.empty())
	{
		//�����ʒu���擾
		basePos = getPosition();

		//�G�Ƃ̃x�N�g�����擾
		cocos2d::Vec2 test = enemys[0]->getPosition() - basePos;

		//�G�Ƃ̊p�x���擾
		auto num = atan2f(test.y, test.x);

		//�w��p�x(��60�x)��G�Ƃ̑��Έʒu�Ŏ��
		float rad = cocos2d::random<float>(0.833f * M_PI, 1.166f*M_PI) + num;

		//�����Ɗp�x�����肵�ł��o��
		velo = cocos2d::Vec2(1500 * cos(rad), 1500 * sin(rad));
	}

}


/**
 * @brief		�f�X�g���N�^
 */
HomingAttack01Bullet::~HomingAttack01Bullet()
{
}

float newrad = 0.0f;

/**
 * @brief		�X�V
 * @param[in]	deltaTime		�O�t���[������i�s�������ԁi�P�ʁF�b�j
 */
void HomingAttack01Bullet::update(float deltaTime)
{

	//�z�񂪂���̏ꍇ�͈ړ��������s��Ȃ�
	if (!enemys.empty())
	{
		//�������x�����^���̎�(�^�[�Q�b�g�ւ�)
		acc = 2.0f / (stime*stime) *(enemys[0]->getPosition() - basePos - stime * velo);

		stime -= deltaTime;
		if (stime < 0.0f)
		{
			return;
		}

		//�����x*���Ԃő��x
		velo += acc * deltaTime;
		//���x*���Ԃňړ�����
		basePos += velo * deltaTime;
		//�ړ�
		setPosition(basePos);

		//�p�x�v�Z(�ΏۂɊp�x��������j
		float angle = atan2f(-velo.y, velo.x) * 180.0f / M_PI;
		getSprite()->setRotation(angle);

	
	}

	// ���݈ʒu�̎擾
	cocos2d::Vec2 newPosition = getPosition();

	// ��ʊO�ɍs���Ə�����
	if (newPosition.x > AppDef::FIELD_SIZE_WIDTH || newPosition.x < 0 || newPosition.y > AppDef::FIELD_SIZE_HEIGHT || newPosition.y < 0)
	{
		// �������g�̉�����N�G�X�g
		releaseRequest();
	}
}


/**
 * @brief		�R���W�����q�b�g���̃R�[���o�b�N
 * @param[in]	target		�Փ˂�������
 */
void HomingAttack01Bullet::collideCallback(Collide::Object* target)
{
	// �G�L�����N�^�[�ɓ���������e�͏���
	if (target->getOwner())
	{
		if (
			(target->getOwner()->getSide() != getSide())
			|| (target->getOwner()->getSide() == Game::SIDE_HOSTILITY)
			)
		{
			// �������g�̉�����N�G�X�g
			releaseRequest();
		}
	}
}
