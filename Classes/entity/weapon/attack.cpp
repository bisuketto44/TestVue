/**
 * @file    attack.cpp
 *
 * @brief   攻撃（相手にダメージを与えるアクション）の基底クラス
 * @details 攻撃を作成するときに基底にする抽象クラス（抽象クラスは直接newできない）
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */

#include "entity/weapon/attack.h"
#include "entity/character/character.h"


/**
 * @brief		コンストラクタ
 * @param[in]	imageFilename	画像ファイル名
 * @param[in]	owner			銃の持ち主のポインタ
 * @param[in]	position		初期位置
 */
Attack::Attack(const char* imageFilename, Character* owner, const cocos2d::Vec2& offsetPosition)
 : Entity(
 				imageFilename,
 				cocos2d::Vec2(0.0f, 0.0f),	// 仮の位置を指定
 				owner->getSide(),
 				true,
 				true,
	            false
 			)
 , owner_(owner)
 , offsetPosition_(offsetPosition)
{
	// 位置を指定し直し
	if(getSprite())
	{
		// 銃の位置は親のスプライトの位置に銃毎のオフセットを足したもの
		cocos2d::Vec2 position = owner_->getPosition() + offsetPosition_;
		setPosition(position);
	}
}


/**
 * @brief		デストラクタ
 */
Attack::~Attack()
{
}
