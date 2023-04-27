#pragma once
#pragma execution_character_set("utf-8")

#include "ui\UIScale9Sprite.h"
#include "ui.h"

class HpFixedBar : public Ui
{
	// ゲージの枠
	cocos2d::ui::Scale9Sprite* _frame = nullptr;

	unsigned int _max;
	unsigned int _current;

public:

	// コンストラクタ
	HpFixedBar(Character* owner, const cocos2d::Vec2& position, Game::SIDE side, const int bar_width, const int bar_height, const unsigned int max, bool isUilayer);

	// デストラクタ
	~HpFixedBar();

	// 生成処理
	static HpFixedBar* create(Character* owner, const cocos2d::Vec2& position, Game::SIDE side,
const int bar_width, const int bar_height, const unsigned int max, bool isUilayer);

	//Uiの描画更新
	virtual void DrawingUpdate();

	void loadResources(cocos2d::Sprite* sprite);


private:

	int new_bar_width = 0;
	int new_bar_height = 0;
	bool isUiLayer = false;


};