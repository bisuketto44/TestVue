/**
 * @file    mob01_ai_controller.cpp
 *
 * @brief   Mob01用のAI操作のコントローラクラス
 * @details AIによりMob01をコントロールするクラス
 *
 * @author  Kaifu Koji
 * @date    2018/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */

#pragma once

#include <cocos2d.h>
#include "controller/ai_controller.h"


/**
 * @brief	Mob01用のAI操作のコントローラクラス
 */
class Mob01AIController : public AIController
{
public:
	/**
	 * @brief	ステート
	 * @notef	サンプルとしてシンプルな動きを作りました。自由に変えて構いません
	 */
	enum STATE
	{
		STATE_STAY,					//!< 待機
		STATE_MOVE_TO_DOWN,			//!< 下へ移動中
		STATE_MOVE_TO_UP,			//!< 上へ移動中
		STATE_ATTACK,               //!< 攻撃中
		STATE_NUM
	};

	// コンストラクタ
	Mob01AIController();
	// デストラクタ
	virtual ~Mob01AIController();

	// 更新
	virtual void		update(float deltaTime);

private:
	STATE		state_;				//!< ステート
	float		actionTimer_;		//!< アクションの動作タイマー
};
