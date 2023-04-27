/**
 * @file    animation_manager.h
 *
 * @brief   アニメーションの管理クラス
 * @details AnimationHelperが生成されるとこのマネージャの管理下に置かれる
 *          AnimationHelperをリストで保持し、定期的にupdate()する
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */

#pragma once

#include <cocos2d.h>
#include "manager/manager.h"
#include "utility/animation_helper.h"
#include "game.h"


class AnimationHelper;

/**
 * @brief	アニメーションの管理クラス
 */
class AnimationManager : public Manager<AnimationHelper*>
{
public:
	// コンストラクタ
	AnimationManager();
	// デストラクタ
	virtual ~AnimationManager();

private:
};
