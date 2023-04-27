/**
 * @file    character_manager.h
 *
 * @brief   キャラクターの管理クラス
 * @details Character（の派生クラス）が生成されるとこのマネージャの管理下に置かれる
 *          Characterをリストで保持し、定期的にupdate()する。またコリジョン判定をする機能も持つ
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */

#pragma once

#include <cocos2d.h>
#include <list>
#include "manager/manager.h"
#include "game.h"
#include "scene/base_scene.h"
#include "entity/character/character.h"


/**
 * @brief	キャラクターの管理クラス
 */
class CharacterManager : public Manager<Character*>
{
public:
	// コンストラクタ
	CharacterManager();
	// デストラクタ
	virtual ~CharacterManager();

	// 当たり判定の更新
	void updateCollide();

	// 敵が全滅したかどうかの確認
	bool isWipedOut() const;

	// プレイヤーキャラが全滅したかどうかの確認
	bool isDeadPlayer()const;

	std::vector<SafePointer<Character>> searchEnemys();

	//プレイヤーの生存フラグ取得
	bool getIsCharacterDead() { return is_character_dead; }

private:

	bool is_character_dead = false;				//!< プレイヤーキャラの生存フラグ

};
