/**
 * @file    sequencer.cpp
 *
 * @brief   シーケンサのクラス
 * @details 時間によるステージ進行を管理するクラス
 *
 * @author  Kaifu Koji
 * @date    2018/04/06
 * @note    マーベラス開発部新人研修C++演習用
 */

#include "utility/macro.h"
#include "app_define.h"
#include "scene/sequencer.h"
#include "entity/character/mob01.h"
#include "entity/character/mob02.h"
#include "game.h"
#include "scene/result_scene.h"
#include "manager/character_manager.h"



/**
 * @brief		コンストラクタ
 * @param[in]	triggerTable	トリガテーブル
 */
Sequencer::Sequencer(const Trigger* triggerTable)
 : timer_(0.0f)
 , currentIndex_(0)
{
	int index = 0;

	// すべてのトリガをクラス内にコピーする
	while (true)
	{
		// トリガをコピー
		triggerTable_.push_back(triggerTable[index]);

		// テーブルの終端だったら処理を抜ける
		if(triggerTable[index].type_ == Trigger::TYPE_TABLE_END)
			break;

		// インデックスの加算
		index++;
	}
}

/**
 * @brief		デストラクタ
 */
Sequencer::~Sequencer()
{
}


/**
 * @brief	更新処理
 * @param[in]	deltaTime		前フレームから進行した時間（単位：秒）
 * @return	true シーケンス終了 / false シーケンス継続
 */
bool Sequencer::update(float deltaTime)
{
	// タイマーを進める
	timer_ += deltaTime;

	//プレイヤーの生死を確認
	bool ischaracterdead = Game::getInstance()->getCurrentScene()->getCharacterManager()->isDeadPlayer();

	//もしプレイヤーが全滅していたらゲームオーバーへ遷移
	if (ischaracterdead)
	{
		Game::getInstance()->setResult(Game::GAMEOVER);
		//リザルト画面に遷移
		SafePointer<ResultScene> nextscene = ResultScene::create();
		Game::getInstance()->changeScene(nextscene);

		// シーン遷移を行った後はUpdate関数を止める
		return true;
	}


	// 要リファクタリング
	// 今のままでは、先にこの遷移が呼ばれると撃った弾が残るので、移る前にリソースの解放を行う
	//敵を全滅したらリザルトに遷移
	if (triggerTable_[currentIndex_].type_ == Trigger::TYPE_WIPED_OUT_DETECTION)
	{
		// 敵が全滅したかどうかを問い合わせる
		bool iswipiedout = Game::getInstance()->getCurrentScene()->getCharacterManager()->isWipedOut();

		if (iswipiedout)
		{
			//クリアフラグを立てる
			Game::getInstance()->setResult(Game::CLEAR);
			//リザルト画面に遷移
			//SafePointer<ResultScene> nextscene = ResultScene::create();
			//Game::getInstance()->changeScene(nextscene);
		}
		// 全滅するまで待機
		return true;
	}

	// タイマーのチェック
	if(timer_ >= triggerTable_[currentIndex_].intervalTime_)
	{
		// タイマーが次のトリガの実行時間に達している

		// トリガタイプがテーブルの終端だったら終了
		if(triggerTable_[currentIndex_].type_ == Trigger::TYPE_TABLE_END)
			return true;

		// それ以外はトリガを実行
		triggerTable_[currentIndex_].execute();

		// インデックスを先に進め、タイマーをクリア
		currentIndex_++;
		timer_ = 0.0f;
	}

	return false;
}


/**
 * @brief	トリガの実行
 */
void Sequencer::Trigger::execute()
{
	switch (type_)
	{
	case TYPE_MOB01_APPEAR_PATTERN01:
		{
			// 縦位置を乱数で決める
			float y = APP_RANDOM_F() * AppDef::WINDOW_SIZE_HEIGHT * 0.5f + 500.0f;

			// Mob01を１体生成する
			Mob01::create(
							Controller::TYPE_AI,			// AI操作
							cocos2d::Vec2(1000.0f, 1000.0f),
							Game::SIDE_ENEMY,				// 敵側（プレイヤー側を攻撃する）
				            AppDef::MOB01_HP
						);
		}
		break;
	case TYPE_MOB02_APPEAR_PATTERN01:
	{
		// 縦位置を乱数で決める
		float y = APP_RANDOM_F() * AppDef::WINDOW_SIZE_HEIGHT * 0.5f + 500.0f;

		// Mob02を１体生成する
		Mob02::create(
			Controller::TYPE_AI,			// AI操作
			cocos2d::Vec2(1000.0f, y),
			Game::SIDE_ENEMY,               // 敵側（プレイヤー側を攻撃する）
			50
		);
	}
	    break;

	case TYPE_STAGE_CLEAR:
	{
		//クリアフラグを立てる
		Game::getInstance()->setResult(Game::CLEAR);
		//リザルト画面に遷移
		SafePointer<ResultScene> nextscene = ResultScene::create();
		Game::getInstance()->changeScene(nextscene);
	}
	break;

		// --- 「ボスを倒したらクリア」などにしたい場合はそういうタイプを追加してそういう通知をする
		// --- （Sequencer内では「ボスを倒したら」という条件判定は出来ないのでその判定は外で行う）
	}
}
