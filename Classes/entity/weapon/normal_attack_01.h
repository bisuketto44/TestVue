/**
 * @file    normal_attack_01.h
 *
 * @brief   通常攻撃01のクラス
 * @details Characterクラスに持たせることで各キャラがこの攻撃を発動する
 *          異なるキャラクターが同じ技を使えるようにこうしてキャラクターの実装とは切り離す
 *
 * @author  Kaifu Koji
 * @date    2018/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */

#pragma once

#include <cocos2d.h>
#include "entity/weapon/attack.h"


class Character;

/**
 * @brief	通常攻撃01のクラス
 */
class NormalAttack01 : public Attack
{
public:
	// コンストラクタ
	NormalAttack01(Character* owner, const cocos2d::Vec2& offsetPosition);
	// デストラクタ
	virtual ~NormalAttack01();

	// 更新
	virtual void		update(float deltaTime);

	// 弾を撃つ処理
	virtual void		shoot();
};
