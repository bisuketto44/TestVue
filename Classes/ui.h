
#pragma once
#include "utility/macro.h"
#include "game.h"
#include "entity/entity.h"

class Character;

// UI�I�u�W�F�N�g(UI�}�l�[�W���[�ŊǗ�)
class Ui : public Entity
{
public:
	//�R���X�g���N�^	
	Ui(Character * owner, const char * imageFilename, const cocos2d::Vec2 & position, Game::SIDE side, bool isActive, bool isDraw, bool isUilayer);

	//�f�X�g���N�^
	~Ui();

	// �X�V
	virtual void	update(float deltaTime);

	/**
	* @brief		������̃Z�b�g
	* @param[in]	owner		���̃R���g���[���̎�����
	*/
	void			setOwner(Character* owner) { owner_ = owner; }

	/**
	 * @brief		������̎擾
	 * @return		owner		���̃R���g���[���̎�����
	 */
	Character*		getOwner() { return owner_; }

	/**
	 * @brief		������̎擾�iconst�Łj
	 * @return		owner		���̃R���g���[���̎�����iconst�j
	 */
	const Character*	getOwner() const { return owner_; }


	//Ui�̕`��X�V
	virtual void DrawingUpdate();

protected:
	SafePointer<Character>	owner_;					//!< UI�̎�����

private:

};