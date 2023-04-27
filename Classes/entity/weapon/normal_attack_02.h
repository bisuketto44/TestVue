#pragma once
/**
 * @file    normal_attack_02.h
 *
 * @brief   �ʏ�U��02�̃N���X
 * @details Character�N���X�Ɏ������邱�ƂŊe�L���������̍U���𔭓�����
 *          �قȂ�L�����N�^�[�������Z���g����悤�ɂ������ăL�����N�^�[�̎����Ƃ͐؂藣��
 *
 * @author  Kaifu Koji
 * @date    2018/04/03
 * @note    �}�[�x���X�J�����V�l���CC++���K�p
 */

#pragma once

#include <cocos2d.h>
#include "entity/weapon/attack.h"


class Character;

/**
 * @brief	�ʏ�U��02�̃N���X
 */
class NormalAttack02 : public Attack
{
public:
	// �R���X�g���N�^
	NormalAttack02(Character* owner, const cocos2d::Vec2& offsetPosition);
	// �f�X�g���N�^
	virtual ~NormalAttack02();

	// �X�V
	virtual void		update(float deltaTime);

	// �e��������
	virtual void		shoot();
};
