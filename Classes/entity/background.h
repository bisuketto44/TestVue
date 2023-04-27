/**
 * @file    BackGround.h
 *
 * @brief   �L�����N�^�[�̊��N���X
 * @details �L�����N�^�[���쐬����Ƃ��Ɋ��ɂ��钊�ۃN���X�i���ۃN���X�͒���new�ł��Ȃ��j
 * @note    �L�����N�^�[���ʂ̏����͂��̃N���X�ɏ���
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    �}�[�x���X�J�����V�l���CC++���K�p
 */

#pragma once

#include <cocos2d.h>
#include "entity/entity.h"

/**
 * @brief	�L�����N�^�[�̊��N���X
 * @note	���̃N���X�Ɣh���N���X�͎��ȏ���or�}�l�[�W���ɂ���č폜����܂��B�i�����������ō폜����K�v�͂���܂���j
 * @note	�����������Ń|�C���^��ێ�����ꍇ�́A�L�����N�^�[���Ŏ��Ƀ|�C���^���N���A����悤�Ȏd�g�݂��������Ă��������B
 */
class BackGround : public Entity
{
public:

	static BackGround* create(const cocos2d::Vec2 & position, Game::SIDE side);
	BackGround(const cocos2d::Vec2 & position, Game::SIDE side);
	// �f�X�g���N�^
	virtual ~BackGround();


protected:




private:
	
};
