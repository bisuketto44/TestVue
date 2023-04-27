/**
 * @file    character_manager.cpp
 *
 * @brief   �L�����N�^�[�̊Ǘ��N���X
 * @details Character�i�̔h���N���X�j�����������Ƃ��̃}�l�[�W���̊Ǘ����ɒu�����
 *          Character�����X�g�ŕێ����A����I��update()����B�܂��R���W�������������@�\������
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    �}�[�x���X�J�����V�l���CC++���K�p
 */

#include "manager/ui_manager.h"
#include "game.h"


 /**
  * @brief		�R���X�g���N�^
  */
UiManager::UiManager()
{
}

/**
 * @brief		�f�X�g���N�^
 */
UiManager::~UiManager()
{
}


/**
 * @brief		�`��̍X�V(stageScnene�ŌĂ΂��)
 */
void UiManager::updateUI()
{

	// �Ǘ����̂��ׂĂ�UI���Ǘ�
	for (auto itr = objectList_.begin(); itr != objectList_.end(); ++itr)
	{
		SafePointer<Ui> ui = *itr;

		//�����[�X����Ă����珈�����X�L�b�v(�A�N�e�B�u�łȂ�UI�͑ΏۊO)
		if (!ui->isActive())
		{
			continue;
		}

		//�eUI�̃A�b�v�f�[�g�Ď����ČĂ�
		ui->DrawingUpdate();
		
	}

}