
#include "background.h"
#include "game.h"
#include "scene/stage_scene.h"


namespace {
	//! 飛鳥の画像ファイル名
	const char* BACKGROUND_RESOURCE_NAME = "BackGround_Temp.png";	// 立ちの絵をセット
}


BackGround* BackGround::create(const cocos2d::Vec2& position, Game::SIDE side)
{
	
	bool flipX = false;

	// 目的のオブジェクトを生成
	BackGround* object = APP_NEW BackGround(position, side);

	// 横反転するかどうか
	object->setFlipX(flipX);

	return object;
}

BackGround::BackGround(const cocos2d::Vec2 & position, Game::SIDE side)
	: Entity(BACKGROUND_RESOURCE_NAME, position, Game::SIDE_NON, true, true,false)
{
	// 表示スケールの調整
	getSprite()->setScale(6.2f);

	// シーンの子に追加
	//Game::getInstance()->getCurrentScene()->addChild(this, -1);

}

BackGround::~BackGround()
{
}
