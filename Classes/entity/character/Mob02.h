
/**
 * @file    Mob02.h
 *
 * @brief   Mob02のキャラクタークラス
 * @details Mob02を登場させたいときはこのクラスを生成する
 *
 * @author  Kaifu Koji
 * @date    2018/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */

#pragma once

#include <cocos2d.h>
#include "entity/character/character.h"
#include "controller/controller.h"


 /**
  * @brief	Mob02のキャラクタークラス
  */
class Mob02 : public Character
{
public:
	// 生成
	static Mob02* create(Controller::TYPE controllerType, const cocos2d::Vec2& position, Game::SIDE side, int HP);

	// コンストラクタ
	Mob02(const cocos2d::Vec2& position, Game::SIDE side, int HP, Controller* controller = nullptr);
	// デストラクタ
	virtual ~Mob02();

	// 更新
	virtual void		update(float deltaTime);

	// アニメーションの指定
	virtual void		setAnimation(ANIMATION animation);

	// コリジョンヒット時のコールバック
	virtual void		collideCallback(Collide::Object* target);

	virtual void Mob02::attackNormal();

private:
};
