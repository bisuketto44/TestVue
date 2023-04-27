/**
 * @file    ai_controller.h
 *
 * @brief   AIコントローラ
 * @details AIによりキャラクターをコントロールするクラスを作成するときに基底にする抽象クラス
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */


#pragma once

#include <cocos2d.h>
#include "controller/controller.h"


/**
 * @brief	AIコントローラ
 */
class AIController : public Controller
{
public:
	/**
	 * @brief		コンストラクタ
	 */
	AIController()			{}
	/**
	 * @brief		デストラクタ
	 */
	virtual ~AIController()	{}

	/**
	 * @brief		更新処理
	 * @param[in]	deltaTime		前フレームから進行した時間（単位：秒）
	 * @note		"=0" が付いていると純粋仮想関数になり、継承先で必ず実装する必要がある。
	 */
	virtual void		update(float deltaTime) = 0;	// 純粋仮想関数

	/**
	 * @brief		AIコントローラの取得
	 */
	virtual AIController* getAIController() { return this; }

private:
	
};
