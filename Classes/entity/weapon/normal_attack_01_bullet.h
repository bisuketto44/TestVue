/**
 * @file    normal_attack_01_bullet.h
 *
 * @brief   通常攻撃01の弾のクラス
 * @details 通常攻撃01の弾を登場させたいときはこのクラスを生成する
 *          このクラスは自己消滅orマネージャによって削除される。
 *          （生成した側で削除する必要はない）
 *
 * @author  Kaifu Koji
 * @date    2018/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */

#pragma once

#include <cocos2d.h>
#include "entity/weapon/bullet.h"
#include "game.h"
#include "entity/character/character.h"

 /**
  * @brief	通常攻撃01の弾のクラス
  */
class NormalAttack01Bullet : public Bullet
{
public:
	// 弾の生成
	static NormalAttack01Bullet* create(const cocos2d::Vec2& position, Game::SIDE side, Character::DIRECTION direction);

private:
	// コンストラクタ
	NormalAttack01Bullet(const cocos2d::Vec2& position, Game::SIDE side, Character::DIRECTION direction);

public:
	// デストラクタ
	virtual ~NormalAttack01Bullet();

	// 更新
	virtual void		update(float deltaTime);

	// コリジョンヒット時のコールバック
	virtual void		collideCallback(Collide::Object* target);

};
