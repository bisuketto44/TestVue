/**
 * @file    game.cpp
 *
 * @brief   ゲームクラス
 * @details ゲーム全体を管理するクラス
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */


#include "utility/macro.h"
#include "app_define.h"
#include "game.h"
#include "scene/stage_scene.h"
#include "scene/result_scene.h"
#include "scene/start_scene.h"
#include "utility/game_pad.h"
#include "manager/animation_manager.h"
#include "ui.h"


//! インスタンスのポインタ
Game*	Game::instance__ = nullptr;


/**
 * @brief		ゲームクラスの生成
 */
void Game::create()
{
	// インスタンスの生成
	instance__ = APP_NEW Game();

	// 初期化
	instance__->init();
}

/**
 * @brief		コンストラクタ
 */
Game::Game()
{
}

/**
 * @brief		デストラクタ
 */
Game::~Game()
{
	// パッドの破棄
	GamePad::destroy();

	// インスタンスのポインタをNULLクリア
	instance__ = nullptr;
}


/**
 * @brief		初期化
 */
void Game::init()
{
	// パッドの生成
	GamePad::create();

	// アニメ機能のマネージャの生成
	animationManager_ = APP_NEW AnimationManager();

	// 最初のシーンを生成
	// --- ベースプログラムではいきなりステージを起動しています。
	//SafePointer<StageScene> scene = StageScene::create();

	SafePointer<StartScene> scene = StartScene::create();

	// 最初のシーンを実行
	cocos2d::Director::getInstance()->runWithScene(scene);
	currentScene_ = scene;

}


/**
 * @brief		シーンの切換え
 * @param[in]	scene
 */
void Game::changeScene(BaseScene* scene)
{
	// Directorによるシーンの切替え
	cocos2d::Director::getInstance()->replaceScene(scene);
	currentScene_ = scene;
}


/**
 * @brief		シーンの一時切換え
 * @param[in]	scene
 */
void Game::pushScene(BaseScene* scene)
{
	// Directorによるシーンの一時切替え
	cocos2d::Director::getInstance()->pushScene(scene);
	currentScene_ = scene;
}


/**
 * @brief		一次切換えしたシーンに戻す
 */
void Game::popScene()
{
	// Directorにより一時切替えしたシーンに戻す
	cocos2d::Director::getInstance()->popScene();
	currentScene_ = dynamic_cast<BaseScene*>(cocos2d::Director::getInstance()->getRunningScene());
}
