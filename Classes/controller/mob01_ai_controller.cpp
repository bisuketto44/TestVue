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

#include "controller/mob01_ai_controller.h"
#include "app_define.h"
#include "entity/character/character.h"


/**
 * @brief		コンストラクタ
 */
Mob01AIController::Mob01AIController()
 : actionTimer_(0.0f)
 , state_(STATE_STAY)
{
	CCLOG("Mob01AIController::Mob01AIController()");

}

/**
 * @brief		デストラクタ
 */
Mob01AIController::~Mob01AIController()
{
	CCLOG("Mob01AIController::~Mob01AIController()");

}


/**
 * @brief		更新処理
 * @param[in]	deltaTime		前フレームから進行した時間（単位：秒）
 * @note		ステートマシンになっている。別の行動をさせたいときにはステートを増やしていけばよい
 */
void Mob01AIController::update(float deltaTime)
{
	// オーナーがいない時は何もしない
	if(!owner_)
		return;

	// オーナーの現在位置を取得
	cocos2d::Vec2 position = owner_->getPosition();


	// --- 分かりやすさ優先でアクションタイマーの処理を個々のステートに書いています。
	// --- コードを共通化したい場合はAIControllerクラスに関数として実装するなどするといいです。

	// AIステートマシン
	switch(state_)
	{
	case STATE_STAY:
		// アクションタイマーの更新
		actionTimer_ += deltaTime;
		if(actionTimer_ > AppDef::MOB01_FIRST_STAY_TIME)
		{
			// ステートの変更
			actionTimer_ = 0.0f;
			state_ = STATE_MOVE_TO_DOWN;
		}
		break;

	case STATE_MOVE_TO_DOWN:
		// 左下へ移動
		position.x -= AppDef::STANDERD_CHARACTER_SPEED * deltaTime;
		position.y -= AppDef::STANDERD_CHARACTER_SPEED * deltaTime;

		// アクションタイマーの更新
		actionTimer_ += deltaTime;
		if(actionTimer_ > AppDef::MOB01_MOVE_ACTION_TIME)
		{
			
			actionTimer_ = 0.0f;
			//攻撃を許可
			resultShoot_.request_ = true;
			// ステートの変更
			state_ = STATE_ATTACK;
		}
		break;

	case STATE_MOVE_TO_UP:
		// 右上へ移動
		position.x += AppDef::STANDERD_CHARACTER_SPEED * deltaTime;
		position.y += AppDef::STANDERD_CHARACTER_SPEED * deltaTime;

		// アクションタイマーの更新
		actionTimer_ += deltaTime;
		if(actionTimer_ > AppDef::MOB01_MOVE_ACTION_TIME)
		{
			// ステートの変更
			actionTimer_ = 0.0f;
			state_ = STATE_MOVE_TO_DOWN;
		}
		break;
	case STATE_ATTACK:
		// 受領済みだったら発射リクエストを初期化
		if (resultShoot_.received_)
		{
			resultShoot_.received_ = false;
			resultShoot_.request_ = false;
		}
		state_ = STATE_MOVE_TO_UP;
		
		break;

	
	}

	// オーナーの新たな位置を結果に保存
	// --- コントローラが直接オーナーの位置を書き換えないのがポイントです
	// --- 位置を書き換えていいかはオーナー自身が判断します
	resultPosition_ = position;
}
