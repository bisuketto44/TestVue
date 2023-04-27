/**
 * @file    bullet.cpp
 *
 * @brief   弾の基底クラス
 * @details 弾を作成するときに基底にするクラス
 *          このクラスは自己消滅orマネージャによって削除される。
 *          （生成した側で削除する必要はない）
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */

#include "entity/weapon/bullet.h"
#include "manager/bullet_manager.h"


/**
 * @brief		コンストラクタ
 * @param[in]	imageFilename	画像ファイル名
 * @param[in]	position		初期位置
 * @param[in]	side			敵味方情報
 * @param[in]	direction	    発射元の方向
 */
Bullet::Bullet(const char* imageFilename, const cocos2d::Vec2& position, Game::SIDE side, Character::DIRECTION direction)
 : Entity(
 				imageFilename,
 				position,
 				side,
 				true,
 				true,
	            false
 			)
{
	// 弾マネージャに登録
	BulletManager* bulletManager = Game::getInstance()->getCurrentScene()->getBulletManager();
	if(bulletManager)
		bulletManager->add(this);
}

/**
 * @brief		デストラクタ
 */
Bullet::~Bullet()
{
	// 弾マネージャから登録抹消
	BulletManager* bulletManager = Game::getInstance()->getCurrentScene()->getBulletManager();
	if(bulletManager)
		bulletManager->remove(this);
}
