/**
 * @file    BackGround.h
 *
 * @brief   キャラクターの基底クラス
 * @details キャラクターを作成するときに基底にする抽象クラス（抽象クラスは直接newできない）
 * @note    キャラクター共通の処理はこのクラスに書く
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */

#pragma once

#include <cocos2d.h>
#include "entity/entity.h"

/**
 * @brief	キャラクターの基底クラス
 * @note	このクラスと派生クラスは自己消滅orマネージャによって削除されます。（生成した側で削除する必要はありません）
 * @note	生成した側でポインタを保持する場合は、キャラクター消滅時にポインタをクリアするような仕組みを実装してください。
 */
class BackGround : public Entity
{
public:

	static BackGround* create(const cocos2d::Vec2 & position, Game::SIDE side);
	BackGround(const cocos2d::Vec2 & position, Game::SIDE side);
	// デストラクタ
	virtual ~BackGround();


protected:




private:
	
};
