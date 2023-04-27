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
class HomingAttack01Bullet : public Bullet
{
public:
	// 弾の生成
	static HomingAttack01Bullet* create(const cocos2d::Vec2& position, Game::SIDE side, Character::DIRECTION direction);

private:
	// コンストラクタ
	HomingAttack01Bullet(const cocos2d::Vec2& position, Game::SIDE side, Character::DIRECTION direction);
	//敵を受け取る仮変数
	std::vector<SafePointer<Character>> enemys;
	cocos2d::Vec2 velo;
	cocos2d::Vec2 acc;
	cocos2d::Vec2 basePos;
	float stime = 1.0f;


public:
	// デストラクタ
	virtual ~HomingAttack01Bullet();

	// 更新
	virtual void		update(float deltaTime);

	// コリジョンヒット時のコールバック
	virtual void		collideCallback(Collide::Object* target);

};
