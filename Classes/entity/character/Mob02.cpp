/**
 * @file    Mob02.cpp
 *
 * @brief   Mob02のキャラクタークラス
 * @details Mob02を登場させたいときはこのクラスを生成する
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */

#include "utility/macro.h"
#include "app_define.h"
#include "entity/character/Mob02.h"
#include "controller/pad_controller.h"
 //現状は同じAIコントローラーを使っている(仮)
#include "controller/Mob01_ai_controller.h"
#include "entity/effect/explosion.h"
#include "utility/collision.h"
#include "entity/weapon/normal_attack_01.h"
#include "game.h"
#include "ui.h"


namespace {
	//! Mob02の画像ファイル名
	const char* MOB_01_RESOURCE_NAME = "yumi_action0_0.png";
}


/**
 * @brief		生成
 * @param[in]	controllerType	コントローラ
 * @param[in]	position		初期位置
 * @param[in]	side			敵味方の指定
 */
Mob02* Mob02::create(Controller::TYPE controllerType, const cocos2d::Vec2& position, Game::SIDE side, int HP)
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
		// Mob02用のA)I操作のコントローラを生成
		controller = APP_NEW Mob01AIController();
		flipX = true;
		break;

	case Controller::TYPE_REMOTE:
		// 未実装（この演習では使用しない）
		break;
	}

	// 目的のオブジェクトを生成
	Mob02* object = APP_NEW Mob02(position, side, HP, controller);

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
Mob02::Mob02(const cocos2d::Vec2& position, Game::SIDE side, int HP, Controller* controller)
	: Character(MOB_01_RESOURCE_NAME, position, side, HP, controller, true, true)
{
	CCLOG("Mob02::Mob02()");

	// 表示スケールの調整
	getSprite()->setScale(0.25f);

	// コリジョンを生成
	createCollideCircle(AppDef::STANDERD_CHARACTER_COLLISION_RADIUS);

	// アニメーションを生成
	createAnimation();
	setAnimation(ANIMATION_STAND);	// 立ちのアニメーションをセット

	setCurrentDirection(LEFT);
}


/**
 * @brief		デストラクタ
 */
Mob02::~Mob02()
{
	CCLOG("Mob02::~Mob02()");
}


/**
 * @brief		更新
 * @param[in]	deltaTime		前フレームから進行した時間（単位：秒）
 */
void Mob02::update(float deltaTime)
{
	// まずはスーパークラスのupdate
	Character::update(deltaTime);

	// Mob02独自の処理があれば↓に書く



}


// -----------
// updateMove()、updateAction() などにこのクラス独自の処理を入れたい場合は
// Asukaクラスを参考に各関数を追加する
// -----------
void Mob02::attackNormal()
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

/**
 * @brief		アニメーションのセット
 * @param[in]	animation		再生したいアニメーション
 */
void Mob02::setAnimation(ANIMATION animation)
{
	animation_ = animation;

	//	"Mob02_action0_0.png",		立ち
	//	"Mob02_action3_0～7.png",	走り
	//	"Mob02_action4_0.png",		攻撃

	switch (animation)
	{
	case ANIMATION_STAND:
		// 立ちのアニメーションをセット
		getAnimation()->clear();
		getAnimation()->addFrame("yumi_action0_0.png", 1.00f);
		getAnimation()->setEndType(AnimationHelper::END_TYPE_STOP);		// 最後のコマを表示し続ける
		break;

	case ANIMATION_MOVE:
		// 移動のアニメーションをセット
		getAnimation()->clear();
		getAnimation()->addFrame("yumi_action3_0.png", 0.05f);
		getAnimation()->addFrame("yumi_action3_1.png", 0.05f);
		getAnimation()->addFrame("yumi_action3_2.png", 0.05f);
		getAnimation()->setEndType(AnimationHelper::END_TYPE_LOOP);		// 最初に戻ってループする
		break;
	case ANIMATION_NORMAL_ATTACK:
		// 通常攻撃のアニメーションをセット
		getAnimation()->clear();
		getAnimation()->addFrame("yumi_action4_0.png", 0.20f);
		getAnimation()->setEndType(AnimationHelper::END_TYPE_STOP);		// 最後のコマを表示し続ける
		break;
	}
}

/**
 * @brief		コリジョンヒット時のコールバック
 * @param[in]	target		衝突した相手
 */
void Mob02::collideCallback(Collide::Object* target)
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
			releaseRequest();
		}
	}
}
