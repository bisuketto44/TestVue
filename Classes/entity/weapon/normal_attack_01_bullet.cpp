/**
 * @file    normal_attack_01_bullet.cpp
 *
 * @brief   通常攻撃01の弾のクラス(現在はプレイヤーキャラが撃つ砲弾)
 * @details 通常攻撃01の弾を登場させたいときはこのクラスを生成する
 *          このクラスは自己消滅orマネージャによって削除される。
 *          （生成した側で削除する必要はない）
 *
 * @author  Kaifu Koji
 * @date    2018/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */

#include "app_define.h"
#include "entity/weapon/normal_attack_01_bullet.h"
#include "utility/collision.h"


namespace {
	//! 通常攻撃01の弾の画像ファイル名
//	const char* const NORMAL_ATTACK_01_BULLET_RESOURCE_NAME = "bullet_01.png";
	const char* const NORMAL_ATTACK_01_BULLET_RESOURCE_NAME = "bullet_03.png";
};

/**
 * @brief		弾の生成
 * @param[in]	position		初期位置
 * @param[in]	side			敵味方情報
 * @return		生成した弾のポインタ
 */



 //ここに最後の移動方向(キャラの向きを渡す)
NormalAttack01Bullet* NormalAttack01Bullet::create(const cocos2d::Vec2& position, Game::SIDE side, Character::DIRECTION direction)
{
	NormalAttack01Bullet* bullet = APP_NEW NormalAttack01Bullet(position, side, direction);

	//画像反転
	switch (direction)
	{
	case Character::UP:
		break;
	case Character::DOWN:
		break;
	case Character::RIGHT:
		break;
	case Character::LEFT:
	{
		bool flipX = true;
		bullet->setFlipX(flipX);
	}
		break;
	default:
		break;
	}

	return bullet;
}


/**
 * @brief		コンストラクタ
 * @param[in]	position		初期位置
 * @param[in]	side			敵味方情報
 */
NormalAttack01Bullet::NormalAttack01Bullet(const cocos2d::Vec2& position, Game::SIDE side, Character::DIRECTION direction)
	: Bullet(
		NORMAL_ATTACK_01_BULLET_RESOURCE_NAME,
		position,
		side,
		direction
	)
{
	// 表示スケールの調整
//	getSprite()->setScale(2.0f);
	getSprite()->setScale(0.125f);

	// コリジョンを生成
	createCollideCircle(AppDef::STANDERD_BULLET_COLLISION_RADIUS);

	//方向を確認
	ownerDirection = direction;

}


/**
 * @brief		デストラクタ
 */
NormalAttack01Bullet::~NormalAttack01Bullet()
{
}


/**
 * @brief		更新
 * @param[in]	deltaTime		前フレームから進行した時間（単位：秒）
 */
void NormalAttack01Bullet::update(float deltaTime)
{
	// 位置の更新
	cocos2d::Vec2 newPosition = getPosition();

	switch (ownerDirection)
	{
	case Character::UP:
		newPosition.y+= AppDef::STANDERD_BULLET_SPEED * deltaTime;
		break;
	case Character::DOWN:
		newPosition.y -= AppDef::STANDERD_BULLET_SPEED * deltaTime;
		break;
	case Character::RIGHT:
		newPosition.x += AppDef::STANDERD_BULLET_SPEED * deltaTime;
		break;
	case Character::LEFT:
		newPosition.x -= AppDef::STANDERD_BULLET_SPEED * deltaTime;
		break;
	default:
		break;
	}
	
	setPosition(newPosition);

	// 画面外に行くと消える
	if (newPosition.x > AppDef::FIELD_SIZE_WIDTH || newPosition.x < 0 || newPosition.y > AppDef::FIELD_SIZE_HEIGHT || newPosition.y < 0)
	{
		// 自分自身の解放リクエスト
		releaseRequest();
	}
}


/**
 * @brief		コリジョンヒット時のコールバック
 * @param[in]	target		衝突した相手
 */
void NormalAttack01Bullet::collideCallback(Collide::Object* target)
{
	// 敵キャラクターに当たったら弾は消滅
	if (target->getOwner())
	{
		if (
			(target->getOwner()->getSide() != getSide())
			|| (target->getOwner()->getSide() == Game::SIDE_HOSTILITY)
			)
		{
			// 自分自身の解放リクエスト
			releaseRequest();
		}
	}
}
