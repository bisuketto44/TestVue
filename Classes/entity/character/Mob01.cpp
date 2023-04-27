/**
 * @file    mob01.cpp
 *
 * @brief   Mob01のキャラクタークラス
 * @details Mob01を登場させたいときはこのクラスを生成する
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */

#include "utility/macro.h"
#include "app_define.h"
#include "entity/character/mob01.h"
#include "controller/pad_controller.h"
#include "controller/mob01_ai_controller.h"
#include "entity/effect/explosion.h"
#include "utility/collision.h"
#include "entity/weapon/normal_attack_01.h"
#include "game.h"
#include "scene/stage_scene.h"



namespace {
	//! Mob01の画像ファイル名
	const char* MOB_01_RESOURCE_NAME = "mob01_action0_0.png";
}


/**
 * @brief		生成
 * @param[in]	controllerType	コントローラ
 * @param[in]	position		初期位置
 * @param[in]	side			敵味方の指定
 */
Mob01* Mob01::create(Controller::TYPE controllerType, const cocos2d::Vec2& position, Game::SIDE side, int HP)
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
		// Mob01用のA)I操作のコントローラを生成
		controller = APP_NEW Mob01AIController();
		flipX = true;
		break;

	case Controller::TYPE_REMOTE:
		// 未実装（この演習では使用しない）
		break;
	}

	// 目的のオブジェクトを生成
	Mob01* object = APP_NEW Mob01(position, side, HP, controller);

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
Mob01::Mob01(const cocos2d::Vec2& position, Game::SIDE side, int HP, Controller* controller)
	: Character(MOB_01_RESOURCE_NAME, position, side, HP, controller, true, true)
{
	CCLOG("Mob01::Mob01()");

	//自身のHPを設定
	ownHp = HP;

	ui_ = nullptr;

	// 表示スケールの調整
	getSprite()->setScale(1.0f);

	// コリジョンを生成
	createCollideCircle(AppDef::STANDERD_CHARACTER_COLLISION_RADIUS);

	// アニメーションを生成
	createAnimation();
	setAnimation(ANIMATION_STAND);	// 立ちのアニメーションをセット

	setCurrentDirection(LEFT);


	//HPバー
	//ui_ = HpFixedBar::create(this, getPosition(), this->getSide(), 350, 25, ownHp, true);
}


/**
 * @brief		デストラクタ
 */
Mob01::~Mob01()
{
	CCLOG("Mob01::~Mob01()");
}


/**
 * @brief		更新
 * @param[in]	deltaTime		前フレームから進行した時間（単位：秒）
 */
void Mob01::update(float deltaTime)
{
	// まずはスーパークラスのupdate
	Character::update(deltaTime);

	// Mob01独自の処理があれば↓に書く



}


// -----------
// updateMove()、updateAction() などにこのクラス独自の処理を入れたい場合は
// Asukaクラスを参考に各関数を追加する
// -----------
void Mob01::attackNormal()
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
 * @brief		解放リクエスト
 */
void Mob01::releaseRequest()
{

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

	Entity::releaseRequest();
}

/**
 * @brief		アニメーションのセット
 * @param[in]	animation		再生したいアニメーション
 */
void Mob01::setAnimation(ANIMATION animation)
{
	animation_ = animation;

	//	"mob01_action0_0.png",		立ち
	//	"mob01_action3_0～7.png",	走り
	//	"mob01_action4_0.png",		攻撃

	switch (animation)
	{
	case ANIMATION_STAND:
		// 立ちのアニメーションをセット
		getAnimation()->clear();
		getAnimation()->addFrame("mob01_action0_0.png", 1.00f);
		getAnimation()->setEndType(AnimationHelper::END_TYPE_STOP);		// 最後のコマを表示し続ける
		break;

	case ANIMATION_MOVE:
		// 移動のアニメーションをセット
		getAnimation()->clear();
		getAnimation()->addFrame("mob01_action3_0.png", 0.05f);
		getAnimation()->addFrame("mob01_action3_1.png", 0.05f);
		getAnimation()->addFrame("mob01_action3_2.png", 0.05f);
		getAnimation()->addFrame("mob01_action3_3.png", 0.05f);
		getAnimation()->addFrame("mob01_action3_4.png", 0.05f);
		getAnimation()->addFrame("mob01_action3_5.png", 0.05f);
		getAnimation()->addFrame("mob01_action3_6.png", 0.05f);
		getAnimation()->addFrame("mob01_action3_7.png", 0.05f);
		getAnimation()->setEndType(AnimationHelper::END_TYPE_LOOP);		// 最初に戻ってループする
		break;
	case ANIMATION_NORMAL_ATTACK:
		// 通常攻撃のアニメーションをセット
		getAnimation()->clear();
		getAnimation()->addFrame("mob01_action4_0.png", 0.20f);
		getAnimation()->setEndType(AnimationHelper::END_TYPE_STOP);		// 最後のコマを表示し続ける
		break;
	}
}

/**
 * @brief		コリジョンヒット時のコールバック
 * @param[in]	target		衝突した相手
 */
void Mob01::collideCallback(Collide::Object* target)
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

			ownHp -= 20;

			if (ownHp <= 0)
			{
				// 自分自身の解放リクエスト
				releaseRequest();
			}


		}
	}
}
