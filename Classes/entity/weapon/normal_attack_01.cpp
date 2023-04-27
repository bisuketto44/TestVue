/**
 * @file    normal_attack_01.cpp
 *
 * @brief   通常攻撃01のクラス
 * @details Characterクラスに持たせることで各キャラがこの攻撃を発動する
 *          異なるキャラクターが同じ技を使えるようにこうしてキャラクターの実装とは切り離す
 *
 * @author  Kaifu Koji
 * @date    2018/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */

#include "app_define.h"
#include "entity/weapon/normal_attack_01.h"
#include "controller/controller.h"
#include "entity/character/character.h"
#include "entity/weapon/normal_attack_01_bullet.h"


namespace {
	//! 通常攻撃01の画像ファイル名
	const char* NORMAL_ATTACK_01_RESOURCE_NAME = nullptr;		// 表示は無いのでNULL
}

/**
 * @brief		コンストラクタ
 * @param[in]	owner			銃の持ち主のポインタ
 * @param[in]	offsetPosition	攻撃発生位置のオフセット（キャラと同じ座標以外で発生させたいときに指定）
 */
NormalAttack01::NormalAttack01(Character* owner, const cocos2d::Vec2& offsetPosition)
 : Attack(
 			NORMAL_ATTACK_01_RESOURCE_NAME,
 			owner,
 			offsetPosition
 		)
{
}


/**
 * @brief		デストラクタ
 */
NormalAttack01::~NormalAttack01()
{
}


/**
 * @brief		更新
 * @param[in]	deltaTime		前フレームから進行した時間（単位：秒）
 */
void NormalAttack01::update(float deltaTime)
{
	// スプライトがあれば位置を更新
	if(getSprite())
	{
		cocos2d::Vec2 position = owner_->getPosition() + offsetPosition_;
		setPosition(position);
	}

	// 単純に弾を発射してみる
	shoot();

	// 攻撃が終わったら解放リクエストを出す
	releaseRequest();
}


/**
 * @brief		弾を撃つ処理
 */
void NormalAttack01::shoot()
{
	// まずはスーパークラスのshoot
	Attack::shoot();

	// 弾の位置を算出
	cocos2d::Vec2 bulletPosition;
	cocos2d::Vec2 position = owner_->getPosition() + offsetPosition_;
	bulletPosition.x = position.x + 0.0f;
	bulletPosition.y = position.y + 0.0f;

	// SIDE（敵か味方か）の指定
	Game::SIDE side = Game::SIDE_HOSTILITY;
	
	Character::DIRECTION direction = Character::RIGHT;
	
	if (owner_)
	{
		side = owner_->getSide();
		//方向の確認
		direction = owner_->getCurrentDirection();

	}
		
	// 弾を生成
	NormalAttack01Bullet::create(bulletPosition, side, direction);
}
