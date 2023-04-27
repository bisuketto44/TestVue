/**
 * @file    character_manager.h
 *
 * @brief   �L�����N�^�[�̊Ǘ��N���X
 * @details Character�i�̔h���N���X�j�����������Ƃ��̃}�l�[�W���̊Ǘ����ɒu�����
 *          Character�����X�g�ŕێ����A����I��update()����B�܂��R���W�������������@�\������
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    �}�[�x���X�J�����V�l���CC++���K�p
 */

#pragma once

#include <cocos2d.h>
#include <list>
#include "manager/manager.h"
#include "game.h"
#include "scene/base_scene.h"
#include "ui.h"
 /**
  * @brief	�L�����N�^�[�̊Ǘ��N���X
  */
class UiManager : public Manager<Ui*>
{
public:
	// �R���X�g���N�^
	UiManager();

	// �f�X�g���N�^
	virtual ~UiManager();

	void updateUI();

private:


};
