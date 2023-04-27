/**
 * @file    bullet_manager.h
 *
 * @brief   弾の管理クラス
 * @details Bullet（の派生クラス）が生成されるとこのマネージャの管理下に置かれる
 *          Bulletをリストで保持し、定期的にupdate()する
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */

#pragma once

#include <cocos2d.h>
#include <list>
#include "manager/manager.h"
#include "game.h"
#include "scene/base_scene.h"
#include "entity/weapon/bullet.h"


class Character;

/**
 * @brief	弾の管理クラス
 */
class BulletManager : public Manager<Bullet*>
{
public:
	// コンストラクタ
	BulletManager();
	// デストラクタ
	virtual ~BulletManager();

	// 特定のキャラとの当たり判定
	void updateCollide(Character* character);

private:
};
