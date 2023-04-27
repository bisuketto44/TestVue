/**
 * @file    pad_controller.cpp
 *
 * @brief   パッド操作のコントローラクラス
 * @details キャラクターをゲームパッドによりコントロールするクラス
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */


#pragma once

#include <cocos2d.h>
#include "controller/controller.h"


/**
 * @brief	パッド操作のコントローラクラス
 */
class PadController : public Controller
{
public:
	/**
	 * @brief		コンストラクタ
	 */
	PadController()			{}
	/**
	 * @brief		デストラクタ
	 */
	virtual ~PadController()	{}

	// 更新
	virtual void		update(float deltaTime);

	/**
	 * @brief		パッドコントローラの取得
	 */
	virtual PadController* getPadController() { return this; }

private:
	// 位置の更新
	void				updateMove(float deltaTime);

	// 発射判定の更新
	void				updateShoot(float deltaTime);

	bool                isDirectionRight = true;
};
