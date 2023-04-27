/**
 * @file    attack.h
 *
 * @brief   攻撃（相手にダメージを与えるアクション）の基底クラス
 * @details 攻撃を作成するときに基底にする抽象クラス（抽象クラスは直接newできない）
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */

#pragma once

#include <cocos2d.h>
#include "entity/entity.h"


class Character;

/**
 * @brief	銃（弾を発射するもの）の基底クラス
 */
class Attack : public Entity
{
public:
	// コンストラクタ
	Attack(const char* imageFilename, Character* owner, const cocos2d::Vec2& offsetPosition);
	// デストラクタ
	virtual ~Attack();

	/**
	 * @brief		更新
	 * @param[in]	deltaTime		前フレームから進行した時間（単位：秒）
	 * @note		"=0" が付いていると純粋仮想関数になり、継承先で必ず実装する必要がある。
	 */
	virtual void		update(float deltaTime) = 0;	// 純粋仮想関数

	/**
	 * @brief		弾を撃つ処理
	 * @note		弾を撃つタイプの攻撃では継承先クラスでこの関数をオーバーライドした関数を実装する
	 */
	virtual void		shoot()		{}

protected:
	SafePointer<Character>	owner_;					//!< 銃の持ち主のポインタ
	cocos2d::Vec2			offsetPosition_;		//!< 持ち主からの位置オフセット
};
