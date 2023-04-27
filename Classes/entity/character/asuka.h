/**
 * @file    asuka.h
 *
 * @brief   キャラクター：飛鳥のクラス
 * @details 飛鳥を登場させたいときはこのクラスを生成する
 *
 * @author  Kaifu Koji
 * @date    2018/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */

#pragma once

#include <cocos2d.h>
#include "character.h"
#include "game.h"
#include "controller/controller.h"
#include "HpBar.h"


 /**
  * @brief	飛鳥のキャラクタークラス
  */
class Asuka : public Character
{
public:
	// 生成
	static Asuka* create(Controller::TYPE controllerType, const cocos2d::Vec2& position, Game::SIDE side, int HP);

	// コンストラクタ
	Asuka(const cocos2d::Vec2& position, Game::SIDE side, int HP, Controller* controller = nullptr);
	// デストラクタ
	virtual ~Asuka();

	// 更新
	virtual void	update(float deltaTime);

	// 解放リクエスト
	virtual void	releaseRequest();

private:
	// 移動の更新
	virtual bool	updateMove(float deltaTime);

	// アクションの更新（攻撃など移動以外の動作）
	virtual void	updateAction(float deltaTime);

	// アニメーションの指定
	virtual void	setAnimation(ANIMATION animation);

	// 通常攻撃
	virtual void	attackNormal();

	// 強攻撃
	virtual void    attackStrong();

	// コリジョンヒット時のコールバック
	virtual void		collideCallback(Collide::Object* target);

	HpBar* hpBar = nullptr;


};
