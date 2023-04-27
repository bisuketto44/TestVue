/**
 * @file    character_manager.cpp
 *
 * @brief   キャラクターの管理クラス
 * @details Character（の派生クラス）が生成されるとこのマネージャの管理下に置かれる
 *          Characterをリストで保持し、定期的にupdate()する。またコリジョン判定をする機能も持つ
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */

#include "manager/character_manager.h"
#include "entity/character/character.h"
#include "manager/bullet_manager.h"
#include "scene/stage_scene.h"
#include "game.h"


/**	
 * @brief		コンストラクタ
 */
CharacterManager::CharacterManager()
{
}

/**
 * @brief		デストラクタ
 */
CharacterManager::~CharacterManager()
{
}


/**
 * @brief		当たり判定の更新(別途BaseSceneにて呼ばれている : 一時停止を行うため)
 */
void CharacterManager::updateCollide()
{

	// 管理下のすべてのキャラクターを処理
	for(auto itr = objectList_.begin(); itr != objectList_.end(); ++itr)
	{
		SafePointer<Character> character = *itr;

		// アクティブでないCharacterは対象外
		if (!character->isActive())
		{
			continue;
		}

		// コリジョンオブジェクトの取得
		SafePointer<Collide::Object> collideObject = character->getCollideObject();

		// コリジョンを持っていないCharacterは対象外
		if(!collideObject)
			continue;

		// 全ての弾との当たり判定
		// --- 当たっていたらそれぞれのownerのEntityのコールバック関数が呼ばれる
		SafePointer<BulletManager> bulletManager = Game::getInstance()->getCurrentScene()->getBulletManager();
		if (bulletManager)
		{
			bulletManager->updateCollide(character);
			
		}
			
	}


}

// 敵キャラが全滅しているかどうかを確認する
bool CharacterManager::isWipedOut() const
{
	// チェックフラグ
	bool is_complete_destruction = true;
	
	// 管理下のすべてのキャラクターを処理
	for (auto itr = objectList_.begin(); itr != objectList_.end(); ++itr)
	{
		SafePointer<Character> character = *itr;

		// アクティブでないCharacterは対象外
		if (!character->isActive())
		{
			continue;
		}
			
		// 登録されているキャラクタの属性をチェックし、敵がいたらフラグを折る
		if (character->getSide() == Game::SIDE::SIDE_ENEMY)
		{
			is_complete_destruction = false;
		}

	}

	// 結果を返す
	return is_complete_destruction;

}

// 自機が倒れたかどうかをチェックする
bool CharacterManager::isDeadPlayer() const
{
	bool is_character_dead = true;

	// 管理下のすべてのキャラクターを処理
	for (auto itr = objectList_.begin(); itr != objectList_.end(); ++itr)
	{
		SafePointer<Character> character = *itr;

		// アクティブでないCharacterは対象外
		if (!character->isActive())
		{
			continue;
		}

		// 登録されているキャラクタの属性をチェックし、敵がいたらフラグを折る
		if (character->getSide() == Game::SIDE::SIDE_PLAYER)
		{
			is_character_dead = false;
		}


	}

	// 結果を返す
	return is_character_dead;

}

// ステージにポップしている敵キャラを取得する
std::vector<SafePointer<Character>> CharacterManager::searchEnemys()
{
	std::vector<SafePointer<Character>> enemys;
	
	// 管理下のすべてのキャラクターを処理
	for (auto itr = objectList_.begin(); itr != objectList_.end(); ++itr)
	{
		SafePointer<Character> character = *itr;

		// アクティブでないCharacterは対象外
		if (!character->isActive())
		{
			continue;
		}

		// 登録されているキャラクタの属性をチェックし、敵がいたらフラグを折る
		if (character->getSide() == Game::SIDE::SIDE_ENEMY)
		{
			enemys.push_back(character);
		}

	}

	// 現在ポップ中の敵キャラを返却
	return enemys;
}








