
#include "ui.h"
#include "manager/ui_manager.h"

//�R���X�g���N�^
Ui::Ui(Character* owner, const char* imageFilename, const cocos2d::Vec2& position, Game::SIDE side, bool isActive, bool isDraw, bool isUilayer)
	: Entity(imageFilename, position, side, isActive, isDraw, isUilayer)
	,owner_(owner)
{

	

	// ������UI�}�l�[�W���[�ɓo�^
	SafePointer<UiManager> uimanager = Game::getInstance()->getCurrentScene()->getUiManager();
	if (uimanager)
		uimanager->add(this);

	

}

//�f�X�g���N�^
Ui::~Ui()
{
	// ��������UI�}�l�[�W������o�^����
	SafePointer<UiManager> uimanager = Game::getInstance()->getCurrentScene()->getUiManager();
	if (uimanager)
		uimanager->remove(this);

}

void Ui::update(float deltaTime)
{
}

void Ui::DrawingUpdate()
{

}


//	//�X�R�AUI�̐���
//	Game::getInstance()->getCurrentScene()->addChild(this, 2);
//	//int��string�ɕϊ����ăe�L�X�g�Ƃ��ĕ\��
//	scoreText = cocos2d::Label::createWithTTF("SCORE : 0", "fonts/arial.ttf", 24);
//	scoreText->setPosition(scoreLabelPosition);
//	this->addChild(scoreText, 1);
//
//	//���C�tUI�̐���
//	lifeText = cocos2d::Label::createWithTTF("LIFE : 3", "fonts/arial.ttf", 24);
//	lifeText->setPosition(lifeLabelPosition);
//	this->addChild(lifeText, 1);