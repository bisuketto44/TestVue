/**
 * @file    bullet_manager.cpp
 *
 * @brief   弾の管理クラス
 * @details Bullet（の派生クラス）が生成されるとこのマネージャの管理下に置かれる
 *          Bulletをリストで保持し、定期的にupdate()する
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */

#include "manager/bullet_manager.h"
#include "entity/weapon/bullet.h"
#include "entity/character/character.h"
#include "utility/collision.h"


/**	
 * @brief		コンストラクタ
 */
BulletManager::BulletManager()
{
}


/**
 * @brief		デストラクタ
 */
BulletManager::~BulletManager()
{
}


/**
 * @brief		特定のキャラとのコリジョンチェック
 * @param[in]	character	コリジョンチェックするキャラクター
 * @details		指定されたキャラクターと登録下にある全ての弾とのコリジョンチェックを行います。
 */
void BulletManager::updateCollide(Character* character)
{
	// 管理下のすべての弾を処理
	for(auto itr = objectList_.begin(); itr != objectList_.end(); ++itr)
	{
		SafePointer<Bullet> bullet = *itr;

		// アクティブでないBulletは対象外
		if(!bullet->isActive())
			continue;

		// コリジョンオブジェクトの取得
		SafePointer<Collide::Object> BulletCollide = bullet->getCollideObject();

		// コリジョンを持っていないBulletは対象外
		if(!BulletCollide)
			continue;

		// キャラクターとの当たり判定
		// --- 当たっていたらそれぞれのownerのEntityのコールバック関数が呼ばれる
		BulletCollide->check(character->getCollideObject());

		// キャラクターがアクティブではなくなっていたらそれ以上回さない
		// --- 弾に当たって死んだ、など
		if(!character->isActive())
			break;
	}
}
