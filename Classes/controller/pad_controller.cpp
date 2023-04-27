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


#include "app_define.h"
#include "controller/pad_controller.h"
#include "entity/character/character.h"
#include "utility/game_pad.h"


/**
 * @brief		更新処理
 * @param[in]	deltaTime		前フレームから進行した時間（単位：秒）
 */
void PadController::update(float deltaTime)
{
	// オーナーが指定されていないのにupdate()が呼ばれるのはおかしい
	APP_ASSERT(owner_, "owner_ must be not nullptr here.")

	// 位置の更新
	updateMove(deltaTime);

	// 弾の発射
	updateShoot(deltaTime);
}


/**
 * @brief		位置の更新
 * @param[in]	deltaTime		前フレームから進行した時間（単位：秒）
 */
void PadController::updateMove(float deltaTime)
{
	// オーナーの現在位置を取得
	cocos2d::Vec2 position = owner_->getPosition();

	// パッドの十字ボタンの左が押されていたら左へ移動
	if(PAD_BT_ON(0, GamePad::BT_LEFT))
	{
		position.x -= AppDef::STANDERD_CHARACTER_SPEED * deltaTime;
		if (position.x < AppDef::STANDERD_CHARACTER_SIZE_WIDTH + AppDef::WINDOW_SIZE_HEIGHT*0.25)
		{
			position.x = AppDef::STANDERD_CHARACTER_SIZE_WIDTH + AppDef::WINDOW_SIZE_HEIGHT*0.25;
		}
		
	    // 発射リクエスト
		if (!PAD_BT_ON(0, GamePad::BT_A))
		{
			//ステイトを左に
			owner_->setCurrentDirection(Character::LEFT);

			//キャラが右を向いていたら反転
			if (isDirectionRight)
			{
				owner_->setFlipX(true);
				isDirectionRight = false;

			}
		}

	}

	// パッドの十字ボタンの右が押されていたら右へ移動
	if(PAD_BT_ON(0, GamePad::BT_RIGHT))
	{
		position.x += AppDef::STANDERD_CHARACTER_SPEED * deltaTime;
		if (position.x > 2500.0f - AppDef::STANDERD_CHARACTER_SIZE_WIDTH - AppDef::WINDOW_SIZE_HEIGHT*0.25)
		{
			position.x = 2500.0f - AppDef::STANDERD_CHARACTER_SIZE_WIDTH - AppDef::WINDOW_SIZE_HEIGHT*0.25;
		}


		// 発射リクエスト
		if (!PAD_BT_ON(0, GamePad::BT_A))
		{
			//ステイトを右に
			owner_->setCurrentDirection(Character::RIGHT);

			//キャラが左を向いていたら反転
			if (!isDirectionRight)
			{
				owner_->setFlipX(false);
				isDirectionRight = true;

			}
		}
	
	}

	// パッドの十字ボタンの上が押されていたら上へ移動
	if(PAD_BT_ON(0, GamePad::BT_UP))
	{
		position.y += AppDef::STANDERD_CHARACTER_SPEED * deltaTime;
		if (position.y > 2500.0f - AppDef::STANDERD_CHARACTER_SIZE_WIDTH - AppDef::WINDOW_SIZE_HEIGHT*0.25)
		{
			position.y = 2500.0f - AppDef::STANDERD_CHARACTER_SIZE_WIDTH - AppDef::WINDOW_SIZE_HEIGHT*0.25;
		}


		// 発射リクエスト
		if (!PAD_BT_ON(0, GamePad::BT_A))
		{

			//ステイトを右上に
			owner_->setCurrentDirection(Character::UP);
		}
			
	}

	// パッドの十字ボタンの下が押されていたら下へ移動
	if(PAD_BT_ON(0, GamePad::BT_DOWN))
	{
		position.y -= AppDef::STANDERD_CHARACTER_SPEED * deltaTime;
		if (position.y < AppDef::STANDERD_CHARACTER_SIZE_WIDTH + AppDef::WINDOW_SIZE_HEIGHT*0.25)
		{
			position.y = AppDef::STANDERD_CHARACTER_SIZE_WIDTH + AppDef::WINDOW_SIZE_HEIGHT*0.25;
		}


		// 発射リクエスト
		if (!PAD_BT_ON(0, GamePad::BT_A))
		{
			//ステイトを下に
			owner_->setCurrentDirection(Character::DOWN);
		}

	}


	// オーナーの新たな位置を結果に保存
	// --- コントローラが直接オーナーの位置を書き換えないのがポイントです
	// --- 位置を書き換えていいかはオーナー自身が判断します
	resultPosition_ = position;
}

/**
 * @brief		弾の発射判定の更新
 * @param[in]	deltaTime		前フレームから進行した時間（単位：秒）
 */
void PadController::updateShoot(float deltaTime)
{
	// 受領済みだったら発射リクエストを初期化(もう一度撃てるようにする)
	if(resultShoot_.received_)
	{
		resultShoot_.received_ = false;
		resultShoot_.request_ = false;
	}

	// 受領済みだったら発射リクエストを初期化(もう一度撃てるようにする)
	if (resultShoot_.received_strong_shoot)
	{
		resultShoot_.request_strong_shoot = false;
		resultShoot_.received_strong_shoot = false;
	}

	// 発射リクエストA
	if (PAD_BT_ON(0, GamePad::BT_A)&& !resultShoot_.request_strong_shoot)
	{
		resultShoot_.request_ = true;
	}
	// 発射リクエストB
	if (PAD_BT_ON(0, GamePad::BT_B)&& !resultShoot_.request_)
	{
		resultShoot_.request_strong_shoot = true;
	}

	
}
