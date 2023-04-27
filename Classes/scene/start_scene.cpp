

/**
 * @file    stage_scene.cpp
 *
 * @brief   ステージシーンのクラス
 * @details シューティングゲームのステージ
 *          敵の登場などステージの進行管理などを行う
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */

#pragma execution_character_set("utf-8")

#include "utility/macro.h"
#include "app_define.h"
#include "scene/start_scene.h"
#include "scene/sequencer.h"
#include "manager/character_manager.h"
#include "manager/bullet_manager.h"
#include "entity/character/asuka.h"
#include "entity/character/mob01.h"
#include "controller/pad_controller.h"
#include "utility/game_pad.h"
#include <cocos2d.h>
#include "ftsizes.h"
#include <iostream>
#include "game.h"
#include "scene/stage_scene.h"


 /**
  * @brief		コンストラクタ
  */
StartScene::StartScene()
{
	CCLOG("StartScene::StartScene()");
}


/**
 * @brief		デストラクタ
 */
StartScene::~StartScene()
{

}


/**
 * @brief		初期化
 * @return		true 初期化成功／false 初期化失敗
 */
bool StartScene::init()
{
	CCLOG("StartScene::init()");
	// まずスーパークラスのinitを呼ぶ
	if (!BaseScene::init())
		return false;		// 異常終了

	//スタートテキストを表示
	auto scoreText = cocos2d::Label::createWithTTF("ARE YOU READY ?", "fonts/arial.ttf", 64);
	scoreText->setPosition(cocos2d::Vec2(640.0f, 360.0f));
	this->addChild(scoreText, 1);


	return true;		// 正常終了
}


/**
 * @brief		更新
 * @param[in]	deltaTime		前フレームから進行した時間（単位：秒）
 */
void StartScene::update(float deltaTime)
{
	// Aボタンが押されたらゲーム開始
	if (PAD_BT_PRESS(0, GamePad::BT_A))
	{
		//リザルト画面に遷移
		SafePointer<StageScene> stagescne = StageScene::create();
		Game::getInstance()->changeScene(stagescne);
	}
}
