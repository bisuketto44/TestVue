/**
 * @file    explosion.h
 *
 * @brief	爆発エフェクト
 * @details 爆発を表示させる機能
 *
 * @author  Kaifu Koji
 * @date    2017/05/02
 * @note    マーベラス開発部新人研修C++演習用
 */

#pragma once

#include <cocos2d.h>
#include "utility/animation_helper.h"
#include "entity/effect/effect.h"


class Explosion
{
public:
	// 爆発エフェクトの再生
	static void play(const cocos2d::Vec2& position, float scale = 1.0f, float randomScale = 0.0f);
};
