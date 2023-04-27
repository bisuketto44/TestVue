/**
 * @file    character.cpp
 *
 * @brief   キャラクターの基底クラス
 * @details キャラクターを作成するときに基底にする抽象クラス（抽象クラスは直接newできない）
 * @note    キャラクター共通の処理はこのクラスに書く
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */

#include "entity/character/character.h"
#include "controller/controller.h"
#include "manager/character_manager.h"
#include "entity/weapon/attack.h"
#include "utility/animation_helper.h"


 /**
  * @brief		コンストラクタ
  * @param[in]	imageFilename	画像ファイル名
  * @param[in]	position		初期位置
  * @param[in]	side			敵味方情報
  * @param[in]	isActive		初期状態で更新有効か
  * @param[in]	isDraw			初期状態で描画有効か
  */
Character::Character(const char* imageFilename, const cocos2d::Vec2& position, Game::SIDE side, int Hp, Controller* controller, bool isActive, bool isDraw)
	: Entity(imageFilename, position, side, isActive, isDraw, false)
	, currectController_(controller)
	, nextController_(nullptr)
	, isSetNextController_(false)
	, timer_(0.0f)
	, state_(STATE_NORMAL)
	, attack_(nullptr)
{
	// キャラクターマネージャに登録
	SafePointer<CharacterManager> characterManager = Game::getInstance()->getCurrentScene()->getCharacterManager();
	if (characterManager)
		characterManager->add(this);

	// コントローラのオーナーに自身をセット
	if (currectController_)
		currectController_->setOwner(this);
}

/**
 * @brief		デストラクタ
 */
Character::~Character()
{
	// コントローラを削除
	if (currectController_)
		APP_SAFE_DELETE(currectController_);

	// キャラクターマネージャから登録抹消
	SafePointer<CharacterManager> characterManager = Game::getInstance()->getCurrentScene()->getCharacterManager();
	if (characterManager)
		characterManager->remove(this);
}


/**
 * @brief		更新
 * @param[in]	deltaTime		前フレームから進行した時間（単位：秒）
 */
void Character::update(float deltaTime)
{
	//	CCLOG("Character Update !!");

		// キャラクター固有のタイマーを更新
	timer_ += deltaTime;

	// コントローラの差替え
	// --- 何かのコントロール処理の途中で差し替えてしまうと
	// --- 不具合を誘発することがあるのでこうした形をとる
	if (isSetNextController_)
	{
		// 直前のコントローラのオーナー指定を解除
		if (currectController_) currectController_->setOwner(nullptr);

		// 次のコントローラをセット
		currectController_ = nextController_;
		nextController_ = nullptr;

		// オーナー指定
		currectController_->setOwner(this);

		// セットリクエストのフラグを解除
		isSetNextController_ = false;
	}

	// コントローラのアップデート
	if (currectController_)
		currectController_->update(deltaTime);

	// ステートマシン
	// --- 行動の種類を増やしたいときはここを増やす
	switch (state_)
	{
	case STATE_NORMAL:					//!< 通常
	{
		// 移動の更新
		bool isMove = updateMove(deltaTime);

		// 移動したかをアニメーションに反映
		if (isMove)
		{
			// 移動した
			if (animation_ != ANIMATION_MOVE)
				setAnimation(ANIMATION_MOVE);	// 左移動のアニメーションをセット
		}
		else
		{
			// 移動していない
			if (animation_ != ANIMATION_STAND)
				setAnimation(ANIMATION_STAND);	// 立ちのアニメーションをセット
		}

		// 移動以外のアクションの更新（攻撃など）
		updateAction(deltaTime);
	}
	break;

	case STATE_ATTACK:					//!< 攻撃
	{
		// 移動の更新（攻撃発動中も移移動できるように）
		updateMove(deltaTime);

		// 攻撃処理がある場合
		if (attack_)
		{
			attack_->update(deltaTime);
			if (attack_->isReleased())
			{
				// 攻撃が解放されていたら保持しているポインタをnullptrにしておく
				// --- 必要なくなったポインタは必ずすぐにnullptrにすること
				attack_ = nullptr;
			}
		}

		// アタックが解放されていて、アニメーションも終了していたら通常に戻す
		if (attack_ == nullptr && getAnimation()->isEnd())
		{
			state_ = STATE_NORMAL;
			break;
		}
	}
	break;

	case STATE_JUMP:					//!< ジャンプ
	{
		// 未実装
	}
	break;

	case STATE_DEAD:					//!< 死亡
	{
		// 未実装
	}
	break;
	}
}


/**
 * @brief		移動の更新
 * @param[in]	deltaTime		前フレームから進行した時間（単位：秒）
 * @return		true 移動した / false 移動していない（静止している）
 */
bool Character::updateMove(float deltaTime)
{
	// 移動前の位置を保存
	const cocos2d::Vec2 oldPosition = getPosition();

	// コントローラの処理を反映
	cocos2d::Vec2 newPosition = getController()->getResultPosition();

	// 位置を更新
	setPosition(newPosition);

	// 移動した？
	// --- 移動前と同じ位置かを確認しています
	bool isMove = newPosition.x != oldPosition.x || newPosition.y != oldPosition.y;
	return isMove;
}


/**
 * @brief		移動以外のアクションの更新
 * @param[in]	deltaTime		前フレームから進行した時間（単位：秒）
 */
void Character::updateAction(float deltaTime)
{
	// 自身のコントローラーから通常攻撃のリクエストが出ているか確認
	const Controller::Shoot& shootRequest = getController()->getResultShoot();

	// 自身のコントローラーから強攻撃のリクエストが出ているか確認
	const Controller::Shoot& strongShootRequest = getController()->getResultStrongShoot();


	//今はAが押されたらノーマルアタック関数が起動するようになっている
	if (shootRequest.request_)
	{
		// 通常攻撃
		attackNormal();
	}

	if (shootRequest.request_strong_shoot)
	{
		// 強攻撃
		attackStrong();
	}
}
