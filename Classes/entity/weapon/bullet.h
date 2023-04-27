/**
 * @file    bullet.h
 *
 * @brief   弾の基底クラス
 * @details 弾を作成するときに基底にする抽象クラス
 *          このクラスは自己消滅orマネージャによって削除される。
 *          （生成した側で削除する必要はない）
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */

#pragma once

#include <cocos2d.h>
#include "game.h"
#include "entity/entity.h"
#include "entity/character/character.h"



/**
 * @brief	弾の基底クラス
 * @note	このクラスは自己消滅orマネージャによって削除される。（生成した側で削除する必要はない）
 */
class Bullet : public Entity
{
protected:
	// コンストラクタ
	Bullet(const char* imageFilename, const cocos2d::Vec2& position, Game::SIDE side, Character::DIRECTION direction);

	//コンストラクタ以下で呼ぶ必要あり
	Character::DIRECTION ownerDirection;

public:
	// デストラクタ
	virtual ~Bullet();

	/**
	 * @brief		更新
	 * @param[in]	deltaTime		前フレームから進行した時間（単位：秒）
	 * @note		"=0" が付いていると純粋仮想関数になり、継承先で必ず実装する必要がある。
	 */
	virtual void update(float deltaTime) = 0;	// 純粋仮想関数
};
