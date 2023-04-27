/**
 * @file    normal_attack_01_bullet.h
 *
 * @brief   �ʏ�U��01�̒e�̃N���X
 * @details �ʏ�U��01�̒e��o�ꂳ�������Ƃ��͂��̃N���X�𐶐�����
 *          ���̃N���X�͎��ȏ���or�}�l�[�W���ɂ���č폜�����B
 *          �i�����������ō폜����K�v�͂Ȃ��j
 *
 * @author  Kaifu Koji
 * @date    2018/04/03
 * @note    �}�[�x���X�J�����V�l���CC++���K�p
 */

#pragma once

#include <cocos2d.h>
#include "entity/weapon/bullet.h"
#include "game.h"
#include "entity/character/character.h"

 /**
  * @brief	�ʏ�U��01�̒e�̃N���X
  */
class HomingAttack01Bullet : public Bullet
{
public:
	// �e�̐���
	static HomingAttack01Bullet* create(const cocos2d::Vec2& position, Game::SIDE side, Character::DIRECTION direction);

private:
	// �R���X�g���N�^
	HomingAttack01Bullet(const cocos2d::Vec2& position, Game::SIDE side, Character::DIRECTION direction);
	//�G���󂯎�鉼�ϐ�
	std::vector<SafePointer<Character>> enemys;
	cocos2d::Vec2 velo;
	cocos2d::Vec2 acc;
	cocos2d::Vec2 basePos;
	float stime = 1.0f;


public:
	// �f�X�g���N�^
	virtual ~HomingAttack01Bullet();

	// �X�V
	virtual void		update(float deltaTime);

	// �R���W�����q�b�g���̃R�[���o�b�N
	virtual void		collideCallback(Collide::Object* target);

};
