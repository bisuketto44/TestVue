/**
 * @file    start_scene.h
 *
 * @brief   ステージシーンのクラス
 * @details シューティングゲームのステージ
 *          敵の登場などステージの進行管理などを行う
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */

#pragma once

#include <cocos2d.h>
#include "base_scene.h"


class PadController;

/**
 * @brief	ステージシーンのクラス
 */
class StartScene : public BaseScene
{
public:
	/**
	 * @brief	ステート
	 */
	enum STATE
	{
		STATE_INIT,					//!< 初期化中
		STATE_ACTIVE,				//!< アクティブ中
		STATE_PAUSE,				//!< ポーズ中

		STATE_NUM
	};

	// cocos2dのcreate関数
	CREATE_FUNC(StartScene);

	// コンストラクタ
	StartScene();
	// デストラクタ
	virtual ~StartScene();

	// 初期化
	virtual bool init();

	// 更新
	void update(float frame);

};
