/**
 * @file    controller.cpp
 *
 * @brief   コントローラの基底クラス
 * @details キャラクターをコントロールする基底クラス
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */


#include "controller/controller.h"

/**
 * @brief		コンストラクタ
 */
Controller::Controller()
 : owner_(nullptr)
{
	//初期化
	resultShoot_.request_ = false;
	resultShoot_.received_ = false;

	resultShoot_.request_strong_shoot = false;
	resultShoot_.received_strong_shoot = false;

}


/**
 * @brief		デストラクタ
 */
Controller::~Controller()
{
}
