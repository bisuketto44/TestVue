#pragma once
#pragma execution_character_set("utf-8")

#include "HpBar.h"
#include "entity/character/character.h"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::ui;

HpBar::HpBar(Character * owner, const cocos2d::Vec2 & position, Game::SIDE side, const int bar_width, const int bar_height, const unsigned int max, bool isUilayer)
	: Ui(owner, "hp_bar_green.png", position, side, true, true, isUilayer)
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

	addChild(_frame);

	// 初期HPスプライトのバーの大きさを変更
	getSprite()->setContentSize(Size(new_bar_width, new_bar_width));

	//最大HPを登録
	this->_max = max;

	//アンカーを調整
	loadResources(getSprite());

	//キャラクターの下側に固定
	setPosition(position - cocos2d::Vec2(50, 94));
	this->_frame->setPosition(position - cocos2d::Vec2(0, 80));
}

HpBar::~HpBar()
{
	//フレームスプライトを解放
	_frame->removeFromParentAndCleanup(true);
	CC_SAFE_RELEASE_NULL(this->_frame);
}

//HPバーを生成
HpBar * HpBar::create(Character * owner, const cocos2d::Vec2 & position, Game::SIDE side, const int bar_width, const int bar_height, const unsigned int max, bool isUilayer)
{
	//インスタンスを生成
	HpBar* object = APP_NEW HpBar(owner, position, side, bar_width, bar_height, max,isUilayer);
	return object;
}



//HPバーに値を渡して表示
void HpBar::DrawingUpdate()
{
	int value = owner_->getHP();

	//色を変更する処理は一旦保留

	// 管理値の最大値に対する現在値の比率を計算
	float ratio = (float)value / this->_max;

	// 新しいゲージの横幅
	float newWidth = new_bar_width * ratio;
	float newHeight = new_bar_height;
	;

	// 現在のバーサイズを変更
	getSprite()->setContentSize(Size(newWidth, newHeight));

	//位置を変更
	if (!isUiLayer)
	{
		setPosition(owner_->getPosition() - cocos2d::Vec2(50, 94));
		this->_frame->setPosition(owner_->getPosition() - cocos2d::Vec2(0, 80));
	}
	
	if (owner_ == nullptr)
	{
		releaseRequest();
	}

}

void HpBar::loadResources(cocos2d::Sprite* sprite)
{
	//初期HPスプライトのスプライトのアンカーを変更
	getSprite()->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	getSprite()->getTexture()->setAliasTexParameters();
	getSprite()->retain();
}