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
#include "entity/weapon/homing_attack_01_bullet.h"
#include "utility/collision.h"
#include "manager/character_manager.h"
#include "game.h"
#include <list>
#include <math.h>


namespace {
	//! 通常攻撃01の弾の画像ファイル名
//	const char* const NORMAL_ATTACK_01_BULLET_RESOURCE_NAME = "bullet_01.png";
	const char* const NORMAL_ATTACK_01_BULLET_RESOURCE_NAME = "bullet_02.png";
};

/**
 * @brief		弾の生成
 * @param[in]	position		初期位置
 * @param[in]	side			敵味方情報
 * @return		生成した弾のポインタ
 */
HomingAttack01Bullet* HomingAttack01Bullet::create(const cocos2d::Vec2& position, Game::SIDE side, Character::DIRECTION direction)
{
	HomingAttack01Bullet* bullet = APP_NEW HomingAttack01Bullet(position, side, direction);
	return bullet;
}


/**
 * @brief		コンストラクタ
 * @param[in]	position		初期位置
 * @param[in]	side			敵味方情報
 */
HomingAttack01Bullet::HomingAttack01Bullet(const cocos2d::Vec2& position, Game::SIDE side, Character::DIRECTION direction)
	: Bullet(
		NORMAL_ATTACK_01_BULLET_RESOURCE_NAME,
		position,
		side,
		direction
	)
{
	// 表示スケールの調整
    getSprite()->setScale(2.0f);
	//getSprite()->setScale(0.125f);

	// コリジョンを生成
	createCollideCircle(AppDef::STANDERD_BULLET_COLLISION_RADIUS);

	// 攻撃可能な敵キャラを検索し配列に格納
	enemys = Game::getInstance()->getCurrentScene()->getCharacterManager()->searchEnemys();

	//空じゃなければ
	if (!enemys.empty())
	{
		//初期位置を取得
		basePos = getPosition();

		//敵とのベクトルを取得
		cocos2d::Vec2 test = enemys[0]->getPosition() - basePos;

		//敵との角度を取得
		auto num = atan2f(test.y, test.x);

		//指定角度(約60度)を敵との相対位置で取る
		float rad = cocos2d::random<float>(0.833f * M_PI, 1.166f*M_PI) + num;

		//初速と角度を決定し打ち出す
		velo = cocos2d::Vec2(1500 * cos(rad), 1500 * sin(rad));
	}

}


/**
 * @brief		デストラクタ
 */
HomingAttack01Bullet::~HomingAttack01Bullet()
{
}

float newrad = 0.0f;

/**
 * @brief		更新
 * @param[in]	deltaTime		前フレームから進行した時間（単位：秒）
 */
void HomingAttack01Bullet::update(float deltaTime)
{

	//配列がからの場合は移動処理を行わない
	if (!enemys.empty())
	{
		//等加速度直線運動の式(ターゲットへの)
		acc = 2.0f / (stime*stime) *(enemys[0]->getPosition() - basePos - stime * velo);

		stime -= deltaTime;
		if (stime < 0.0f)
		{
			return;
		}

		//加速度*時間で速度
		velo += acc * deltaTime;
		//速度*時間で移動距離
		basePos += velo * deltaTime;
		//移動
		setPosition(basePos);

		//角度計算(対象に角度を向ける）
		float angle = atan2f(-velo.y, velo.x) * 180.0f / M_PI;
		getSprite()->setRotation(angle);

	
	}

	// 現在位置の取得
	cocos2d::Vec2 newPosition = getPosition();

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
void HomingAttack01Bullet::collideCallback(Collide::Object* target)
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
