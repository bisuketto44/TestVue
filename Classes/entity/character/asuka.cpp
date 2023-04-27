/**
 * @file    asuka.cpp
 *
 * @brief   キャラクター：飛鳥のクラス
 * @details 飛鳥を登場させたいときはこのクラスを生成する
 *
 * @author  Kaifu Koji
 * @date    2018/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */

#include "utility/macro.h"
#include "app_define.h"
#include "entity/character/asuka.h"
#include "controller/pad_controller.h"
#include "entity/weapon/normal_attack_01.h"
#include "entity/weapon/normal_attack_02.h"
#include "utility/animation_helper.h"
#include "entity/effect/explosion.h"
#include "utility/collision.h"
#include "game.h"
#include "scene/result_scene.h"
#include "app_define.h"


#include "controller/mob01_ai_controller.h"

namespace {
	//! 飛鳥の画像ファイル名
	const char* ASUKA_RESOURCE_NAME = "asuka_action0_0.png";	// 立ちの絵をセット
}


/**
 * @brief		生成
 * @param[in]	controllerType	コントローラ
 * @param[in]	position		初期位置
 * @param[in]	side			敵味方の指定
 */
Asuka* Asuka::create(Controller::TYPE controllerType, const cocos2d::Vec2& position, Game::SIDE side, int HP)
{
	Controller* controller = nullptr;
	bool flipX = false;

	// 指定されたタイプのコントローラを生成
	switch (controllerType)
	{
	case Controller::TYPE_PAD:
		// パッド操作のコントローラを生成
		controller = APP_NEW PadController();
		break;

	case Controller::TYPE_AI:
		// 未実装
		break;

	case Controller::TYPE_REMOTE:
		// 未実装（この演習では使用しない）
		break;
	}

	// 目的のオブジェクトを生成
	Asuka* object = APP_NEW Asuka(position, side, HP, controller);

	// 横反転するかどうか
	object->setFlipX(flipX);

	return object;
}


/**
 * @brief		コンストラクタ
 * @param[in]	position		初期位置
 * @param[in]	side			敵味方の指定
 * @param[in]	controller		コントローラ
 */
Asuka::Asuka(const cocos2d::Vec2& position, Game::SIDE side, int HP, Controller* controller)
	: Character(ASUKA_RESOURCE_NAME, position, side, HP, controller, true, true)
{
	CCLOG("Asuka::Asuka()");

	//自身のHPを設定
	ownHp = HP;

	ui_ = nullptr;

	// 表示スケールの調整
	getSprite()->setScale(0.25f);

	// コントローラが指定されていなかったらAIControllerを生成する
	// --- 今回は飛鳥のAIControllerを用意していないのでコメントアウト
	//	if(!controller)
	//	{
	//		aiController_ = APP_NEW AsukaAIController(this);
	//		setController(aiController_);
	//
	//		// 念のためcontrollerも更新しておくとエンバグが発生し難くなる
	//		// （この後の改修で、controllerを使うコードが追加された場合に備える）
	//		controller = aiController_;
	//	}

	// コリジョンを生成
	createCollideCircle(AppDef::STANDERD_CHARACTER_COLLISION_RADIUS);

	// アニメーションを生成
	createAnimation();
	setAnimation(ANIMATION_STAND);	// 立ちのアニメーションをセット



	//作成
	ui_ = HpBar::create(this, getPosition(), this->getSide(), 100, 25, ownHp, false);
}


/**
 * @brief		デストラクタ
 */
Asuka::~Asuka()
{
	CCLOG("Asuka::~Asuka()");
}


/**
 * @brief		更新
 * @param[in]	deltaTime		前フレームから進行した時間（単位：秒）
 */
void Asuka::update(float deltaTime)
{
	// まずはスーパークラスの関数を実行
	Character::update(deltaTime);

	// 飛鳥独自の処理があれば↓に書く
	// --- 独自の処理が無いのであれば本来このクラスにこの関数を実装する必要は無い
	// --- 拡張時に分かりやすいよう用意しておく



}


/**
 * @brief		移動の更新
 * @param[in]	deltaTime		前フレームから進行した時間（単位：秒）
 * @return		true 移動した / false 移動していない（静止している）
 */
bool Asuka::updateMove(float deltaTime)
{
	// まずはスーパークラスの関数を実行
	bool ret = Character::updateMove(deltaTime);

	// 飛鳥独自の処理があれば↓に書く
	// --- 独自の処理が無いのであれば本来このクラスにこの関数を実装する必要は無い
	// --- 拡張時に分かりやすいよう用意しておく


	return ret;
}


/**
 * @brief		アクションの更新（攻撃など移動以外の動作）
 * @param[in]	deltaTime		前フレームから進行した時間（単位：秒）
 */
void Asuka::updateAction(float deltaTime)
{
	// まずはスーパークラスの関数を実行
	Character::updateAction(deltaTime);

	// 飛鳥独自の処理があれば↓に書く
	// --- 独自の処理が無いのであれば本来このクラスにこの関数を実装する必要は無い
	// --- 拡張時に分かりやすいよう用意しておく



}


/**
 * @brief		アニメーションのセット
 * @param[in]	animation		再生したいアニメーション
 */
void Asuka::setAnimation(ANIMATION animation)
{
	animation_ = animation;

	//	"asuka_action0_0.png",		立ち
	//	"asuka_action1_0.png",		ジャンプ
	//	"asuka_action2_0～2.png",	着地
	//	"asuka_action3_0～5.png",	走り
	//	"asuka_action4_0.png",		攻撃

	switch (animation)
	{
	case ANIMATION_STAND:
		// 立ちのアニメーションをセット
		getAnimation()->clear();
		getAnimation()->addFrame("asuka_action0_0.png", 1.00f);
		getAnimation()->setEndType(AnimationHelper::END_TYPE_STOP);		// 最後のコマを表示し続ける
		break;

	case ANIMATION_MOVE:
		// 移動のアニメーションをセット
		getAnimation()->clear();
		getAnimation()->addFrame("asuka_action3_0.png", 0.05f);
		getAnimation()->addFrame("asuka_action3_1.png", 0.05f);
		getAnimation()->addFrame("asuka_action3_2.png", 0.05f);
		getAnimation()->addFrame("asuka_action3_3.png", 0.05f);
		getAnimation()->addFrame("asuka_action3_4.png", 0.05f);
		getAnimation()->addFrame("asuka_action3_5.png", 0.05f);
		getAnimation()->setEndType(AnimationHelper::END_TYPE_LOOP);		// 最初に戻ってループする
		break;

	case ANIMATION_NORMAL_ATTACK:
		// 通常攻撃のアニメーションをセット
		getAnimation()->clear();
		getAnimation()->addFrame("asuka_action4_0.png", 0.20f);
		getAnimation()->setEndType(AnimationHelper::END_TYPE_STOP);		// 最後のコマを表示し続ける
		break;

	case ANIMATION_JUMP:						//!< ジャンプ
		// ジャンプのアニメーションをセット
		getAnimation()->clear();
		getAnimation()->addFrame("asuka_action1_0.png", 0.40f);
		getAnimation()->addFrame("asuka_action2_0.png", 0.05f);
		getAnimation()->addFrame("asuka_action2_1.png", 0.05f);
		getAnimation()->addFrame("asuka_action2_2.png", 0.05f);
		getAnimation()->setEndType(AnimationHelper::END_TYPE_STOP);		// 最後のコマを表示し続ける
		break;

	case ANIMATION_DEAD:						//!< 死亡
		// 未実装
		break;
	}
}


/**
 * @brief		通常攻撃
 */
void Asuka::attackNormal()
{
	// 通常攻撃のアニメーション再生
	if (animation_ != ANIMATION_NORMAL_ATTACK)
		setAnimation(ANIMATION_NORMAL_ATTACK);

	// この時点でattack_はNULLのはず
	APP_ASSERT(attack_ == nullptr, "attack_ must not be nullptr here.")

		attack_ = APP_NEW NormalAttack01(
			this,
			cocos2d::Vec2(AppDef::STANDERD_CHARACTER_ATTACK_POSITION_OFFSET_X, AppDef::STANDERD_CHARACTER_ATTACK_POSITION_OFFSET_Y)
		);
	state_ = STATE_ATTACK;

}

void Asuka::attackStrong()
{
	// 通常攻撃のアニメーション再生
	if (animation_ != ANIMATION_NORMAL_ATTACK)
		setAnimation(ANIMATION_NORMAL_ATTACK);

	// この時点でattack_はNULLのはず
	APP_ASSERT(attack_ == nullptr, "attack_ must not be nullptr here.")

		attack_ = APP_NEW NormalAttack02(
			this,
			cocos2d::Vec2(AppDef::STANDERD_CHARACTER_ATTACK_POSITION_OFFSET_X, AppDef::STANDERD_CHARACTER_ATTACK_POSITION_OFFSET_Y)
		);
	state_ = STATE_ATTACK;

}




/**
 * @brief		解放リクエスト
 */
void Asuka::releaseRequest()
{
	// 銃の解放リクエスト
	if (attack_)
	{
		attack_->releaseRequest();
		attack_ = nullptr;		// ←ポインタをnullptrに戻しておくこと
	}

	if (ui_)
	{
		ui_->releaseRequest();
		ui_ = nullptr;		// ←ポインタをnullptrに戻しておくこと

	}

	// ベースクラスの解放のリクエスト
	// --- 解放に関する処理は継承先→ベースの順で実行する
	Entity::releaseRequest();
}

/**
 * @brief		コリジョンヒット時のコールバック
 * @param[in]	target		衝突した相手
 */
void Asuka::collideCallback(Collide::Object* target)
{
	// 敵の弾に当たったら消滅
	if (target->getOwner())
	{
		if (
			(target->getOwner()->getSide() != getSide())
			|| (target->getOwner()->getSide() == Game::SIDE_HOSTILITY)
			)
		{
			// 爆発エフェクトを表示
			Explosion::play(getPosition(), 1.0f);
			// 自分自身の解放リクエスト

			ownHp -= 50;

			if (ownHp <= 0)
			{
				releaseRequest();
			}




		}
	}
}

