#pragma once
#pragma execution_character_set("utf-8")

#include "HpBar_fixed.h"
#include "entity/character/character.h"
#include "scene/stage_scene.h"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::ui;

HpFixedBar::HpFixedBar(Character * owner, const cocos2d::Vec2 & position, Game::SIDE side, const int bar_width, const int bar_height, const unsigned int max, bool isUilayer)
	: Ui(owner, "hp_bar_red.png", position, side, true, true, isUilayer)
{
	new_bar_width = bar_width;
	new_bar_height = bar_height;
	isUiLayer = isUilayer;

	//// ゲージのフレーム部分の作成
	const Rect outer_rect(0, 0, 24, 24);
	const Rect inner_rect(1, 1, 22, 22);

	////フレームを生成
	_frame = Scale9Sprite::create("hp_frame.png", outer_rect, inner_rect);
	_frame->getTexture()->setAliasTexParameters();
	_frame->setContentSize(Size(new_bar_width, new_bar_height));

	//固定用レイヤーに表示
	//addChild(_frame);
	Game::getInstance()->getCurrentScene()->getuILayer()->addChild(_frame);

	// 初期HPスプライトのバーの大きさを変更
	getSprite()->setContentSize(Size(new_bar_width, new_bar_width));

	//最大HPを登録
	this->_max = max;

	//位置固定
	this->setPosition(cocos2d::Vec2(465.0f, 638.0f));
	this->_frame->setPosition(cocos2d::Vec2(1280.0 / 2.0f, 650.0f));

	//アンカーを調整
	loadResources(getSprite());

	
}

HpFixedBar::~HpFixedBar()
{
	//フレームスプライトを解放
	//this->_frame->removeFromParentAndCleanup(true);
	CC_SAFE_RELEASE_NULL(this->_frame);
}

//HPバーを生成
HpFixedBar * HpFixedBar::create(Character * owner, const cocos2d::Vec2 & position, Game::SIDE side, const int bar_width, const int bar_height, const unsigned int max, bool isUilayer)
{
	//インスタンスを生成
	HpFixedBar* object = APP_NEW HpFixedBar(owner, position, side, bar_width, bar_height, max, isUilayer);
	CCLOG("HpFixedBar_CREATE");

	return object;
}



//HPバーに値を渡して表示
void HpFixedBar::DrawingUpdate()
{
	int value = owner_->getHP();

	//色を変更する処理は一旦保留

	// 管理値の最大値に対する現在値の比率を計算
	float ratio = (float)value / this->_max;

	// 新しいゲージの横幅
	float newWidth = new_bar_width * ratio;
	float newHeight = new_bar_height;

	// 現在のバーサイズを変更
	getSprite()->setContentSize(Size(newWidth, newHeight));

}

void HpFixedBar::loadResources(cocos2d::Sprite* sprite)
{
	//初期HPスプライトのスプライトのアンカーを変更
	getSprite()->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	getSprite()->getTexture()->setAliasTexParameters();
	getSprite()->retain();
}