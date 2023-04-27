

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
#include "scene/stage_scene.h"
#include "scene/sequencer.h"
#include "manager/character_manager.h"
#include "manager/ui_manager.h"
#include "manager/bullet_manager.h"
#include "entity/character/asuka.h"
#include "entity/background.h"
#include "entity/character/mob01.h"
#include "controller/pad_controller.h"
#include "utility/game_pad.h"
#include <cocos2d.h>
#include "ftsizes.h"
#include <iostream>
#include "game.h"

#include "trigger_table_stage_01.inl"


/**	
 * @brief		コンストラクタ
 */
StageScene::StageScene()
 : characterManager_(nullptr)
 , bulletManager_(nullptr)
 , uiManager_(nullptr)
 , sequencer_(nullptr)
 , pauseLabel_(nullptr)
 , state_(STATE_INIT)
{
	CCLOG("StageScene::StageScene()");
}


/**
 * @brief		デストラクタ
 */
StageScene::~StageScene()
{
	CCLOG("StageScene::~StageScene()");

	// キャラクターや弾を管理するマネージャを解放
	APP_SAFE_DELETE(characterManager_);
	APP_SAFE_DELETE(bulletManager_);
	APP_SAFE_DELETE(uiManager_);
	// シーケンサ（時間によるステージ進行管理）を解放
	APP_SAFE_DELETE(sequencer_);


}


/**
 * @brief		初期化
 * @return		true 初期化成功／false 初期化失敗
 */
bool StageScene::init()
{
	CCLOG("StageScene::init()");

	// まずスーパークラスのinitを呼ぶ
	if( !BaseScene::init() )
		return false;		// 異常終了


	// ステート初期化
	state_ = STATE_INIT;

	// キャラクターや弾を管理するマネージャのポインタを初期化
	characterManager_ = nullptr;
	bulletManager_ = nullptr;
	uiManager_ = nullptr;
	sequencer_ = nullptr;

	

	return true;		// 正常終了
}


/**
 * @brief		更新
 * @param[in]	deltaTime		前フレームから進行した時間（単位：秒）
 */
void StageScene::update(float deltaTime)
{
//	CCLOG("StageScene : Time : %f (+%f)", getTimer(), deltaTime);

	// StageSceneのステートマシン
	switch(state_)
	{
	// 初期化中
	case STATE_INIT:
		{
			// マネージャーを生成
			characterManager_ = APP_NEW CharacterManager();
			bulletManager_ = APP_NEW BulletManager();
			uiManager_ = APP_NEW UiManager();

			//背景を生成
			BackGround::create(cocos2d::Vec2(AppDef::PLAYER_START_POSITION_X, AppDef::PLAYER_START_POSITION_Y), Game::SIDE_NON);

			// プレイヤーとして飛鳥を生成
			auto player = Asuka::create(
							Controller::TYPE_PAD,		// パッド操作
							cocos2d::Vec2(AppDef::PLAYER_START_POSITION_X, AppDef::PLAYER_START_POSITION_Y),
							Game::SIDE_PLAYER,			// プレイヤー側（敵側を攻撃する）
				            AppDef::ASUKA_HP
						);

			//カメラがプレイヤーを追従するように設定
		    getLayer()->runAction(cocos2d::Follow::create(player->getSprite(), cocos2d::Rect(0, 0, 2500.0f, 2500.0f)));

			// シーケンサ（時間によるステージ進行管理）の生成
			sequencer_ = APP_NEW Sequencer(stage_01_table);

			// ステート変更
			state_ = STATE_ACTIVE;
		}
		break;

	// アクティブ中
	case STATE_ACTIVE:
		{
			// シーケンサの更新
			bool ret = sequencer_->update(deltaTime);
			if(ret)
			{
				// ステージ終了の処理
				// 未実装
				// --- ステージ終了のステートを用意してそちらに遷移させる（ここに直接終了の処理を書かないこと）
			}

			//ここのupdateは内部更新がメイン
			// キャラクターの更新
			characterManager_->update(deltaTime);

			// 弾の更新
			bulletManager_->update(deltaTime);

			// UIの更新
			uiManager_->update(deltaTime);

			//各UIの描画更新
			uiManager_->updateUI();

			// スタートボタンを押したらポーズに
			if(PAD_BT_PRESS(0, GamePad::BT_START))
			{
				// "PAUSE"表示
				pauseLabel_ = cocos2d::Label::createWithTTF("PAUSE", "fonts/Marker Felt.ttf", 24);
				pauseLabel_->setPosition(cocos2d::Vec2(AppDef::WINDOW_SIZE_WIDTH * 0.5f, AppDef::WINDOW_SIZE_HEIGHT * 0.5f));
				addChild(pauseLabel_, 1);

				// BaseSceneもポーズ状態に
				setPause(true);

				// ステート変更
				state_ = STATE_PAUSE;
			}
		}
		break;

	// ポーズ中
	case STATE_PAUSE:
		{
			// スタートボタンを押したらポーズ解除
			if(PAD_BT_PRESS(0, GamePad::BT_START))
			{
				// "PAUSE"表示の削除
				pauseLabel_->removeFromParentAndCleanup(true);
				pauseLabel_ = nullptr;

				// BaseSceneのポーズ状態を解除
				setPause(false);

				// ステート変更
				state_ = STATE_ACTIVE;
			}
		}
		break;
	}
}
