
#include "ui.h"
#include "manager/ui_manager.h"

//コンストラクタ
Ui::Ui(Character* owner, const char* imageFilename, const cocos2d::Vec2& position, Game::SIDE side, bool isActive, bool isDraw, bool isUilayer)
	: Entity(imageFilename, position, side, isActive, isDraw, isUilayer)
	,owner_(owner)
{

	

	// 生成時UIマネージャーに登録
	SafePointer<UiManager> uimanager = Game::getInstance()->getCurrentScene()->getUiManager();
	if (uimanager)
		uimanager->add(this);

	

}

//デストラクタ
Ui::~Ui()
{
	// 生成時にUIマネージャから登録抹消
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


//	//スコアUIの生成
//	Game::getInstance()->getCurrentScene()->addChild(this, 2);
//	//intをstringに変換してテキストとして表示
//	scoreText = cocos2d::Label::createWithTTF("SCORE : 0", "fonts/arial.ttf", 24);
//	scoreText->setPosition(scoreLabelPosition);
//	this->addChild(scoreText, 1);
//
//	//ライフUIの生成
//	lifeText = cocos2d::Label::createWithTTF("LIFE : 3", "fonts/arial.ttf", 24);
//	lifeText->setPosition(lifeLabelPosition);
//	this->addChild(lifeText, 1);