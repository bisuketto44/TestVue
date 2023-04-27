

/**
 * @file    stage_scene.cpp
 *
 * @brief   �X�e�[�W�V�[���̃N���X
 * @details �V���[�e�B���O�Q�[���̃X�e�[�W
 *          �G�̓o��ȂǃX�e�[�W�̐i�s�Ǘ��Ȃǂ��s��
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    �}�[�x���X�J�����V�l���CC++���K�p
 */

#pragma execution_character_set("utf-8")

#include "utility/macro.h"
#include "app_define.h"
#include "scene/result_scene.h"
#include "scene/sequencer.h"
#include "manager/character_manager.h"
#include "manager/bullet_manager.h"
#include "entity/character/asuka.h"
#include "entity/character/mob01.h"
#include "controller/pad_controller.h"
#include "utility/game_pad.h"
#include <cocos2d.h>
#include "ftsizes.h"
#include <iostream>
#include "game.h"
#include "scene/start_scene.h"


/**	
 * @brief		�R���X�g���N�^
 */
ResultScene::ResultScene()
{
	CCLOG("ResultScene::ResultScene()");

	
}


/**
 * @brief		�f�X�g���N�^
 */
ResultScene::~ResultScene()
{
	
}


/**
 * @brief		������
 * @return		true �����������^false ���������s
 */
bool ResultScene::init()
{
	CCLOG("ResultScene::init()");
	// �܂��X�[�p�[�N���X��init���Ă�
	if (!BaseScene::init())
		return false;		// �ُ�I��

	// ���ʂɂ���ĕ\����ύX
	switch (Game::getInstance()->getResult())
	{
	case Game::RESULT::CLEAR:
	{
		//�N���A�e�L�X�g��\��
		auto scoreText = cocos2d::Label::createWithTTF("CLEAR\nPress A to play again.", "fonts/arial.ttf", 64);
		scoreText->setPosition(cocos2d::
		Vec2(640.0f, 360.0f));
		this->addChild(scoreText, 1);
	}
		break;
	case Game::RESULT::GAMEOVER:
	{
		//�Q�[���I�[�o�[�e�L�X�g��\��
		auto scoreText = cocos2d::Label::createWithTTF("GAME OVER\nPress A to play again.", "fonts/arial.ttf", 64);
		scoreText->setPosition(cocos2d::Vec2(640.0f, 360.0f));
		this->addChild(scoreText, 1);
	}
		break;
	default:
		break;
	}



	return true;		// ����I��
}


/**
 * @brief		�X�V
 * @param[in]	deltaTime		�O�t���[������i�s�������ԁi�P�ʁF�b�j
 */
void ResultScene::update(float deltaTime)
{
	// A�{�^���������ꂽ�������x�Q�[�����J�n
	if (PAD_BT_PRESS(0, GamePad::BT_A))
	{
		//���U���g��ʂɑJ��
		SafePointer<StartScene> stagescne = StartScene::create();
		Game::getInstance()->changeScene(stagescne);
	
	}

}
