/**
 * @file    start_scene.h
 *
 * @brief   �X�e�[�W�V�[���̃N���X
 * @details �V���[�e�B���O�Q�[���̃X�e�[�W
 *          �G�̓o��ȂǃX�e�[�W�̐i�s�Ǘ��Ȃǂ��s��
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    �}�[�x���X�J�����V�l���CC++���K�p
 */

#pragma once

#include <cocos2d.h>
#include "base_scene.h"


class PadController;

/**
 * @brief	�X�e�[�W�V�[���̃N���X
 */
class StartScene : public BaseScene
{
public:
	/**
	 * @brief	�X�e�[�g
	 */
	enum STATE
	{
		STATE_INIT,					//!< ��������
		STATE_ACTIVE,				//!< �A�N�e�B�u��
		STATE_PAUSE,				//!< �|�[�Y��

		STATE_NUM
	};

	// cocos2d��create�֐�
	CREATE_FUNC(StartScene);

	// �R���X�g���N�^
	StartScene();
	// �f�X�g���N�^
	virtual ~StartScene();

	// ������
	virtual bool init();

	// �X�V
	void update(float frame);

};
