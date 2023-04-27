/**
 * @file    entity.h
 *
 * @brief   物体の基底クラス
 * @details ゲームに何か表示を伴う物体を登場させたいときに基底とするクラス
 *          スプライトの表示、定期的なupdate、アニメーション、コリジョンをサポートする
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */

#pragma once

#include <cocos2d.h>
#include "utility/macro.h"
#include "game.h"

namespace Collide
{
	class Object;
	class Result;
}
class AnimationHelper;

/**
 * @brief	物体の基底クラス
 * @note	EntityはUnrealEngineで使用されていた用語です。
 * 			エンジン、タイトル、機能設計によって名前が変わります。
 */
class Entity : public cocos2d::Node
{
public:
	// コンストラクタ
	Entity(const char* imageFilename, const cocos2d::Vec2& position, Game::SIDE side, bool isActive, bool isDraw, bool isUilayer);
	// デストラクタ
	virtual ~Entity();

	/**
	 * @brief		更新
	 * @param[in]	deltaTime		前フレームから進行した時間（単位：秒）
	 * @return		true 処理が終了した／false 処理が継続中
	 * @note		更新が必要ないEntityもあるかもしれないので純粋仮想関数にはしない
	 */
	virtual void		update(float deltaTime)		{}

	/**
	 * @brief		更新するかどうかのフラグのセット
	 * @param[in]	isActive	true 更新する／false 更新しない（停止）
	 */
	void				setActive(bool isActive)	{ isActive_ = isActive; }

	// 	描画するかどうかの指定
	void				setDraw(bool isDraw);

	// 描画時に横反転するかどうかの指定
	void				setFlipX(bool isFlip);

	/**
	 * @brief		位置のセット
	 * @param[in]	position	Entityの位置
	 */
	void				setPosition(cocos2d::Vec2 position) { if(sprite_) sprite_->setPosition(position);  }

	// 解放リクエスト
	virtual void		releaseRequest();

	// アニメーションヘルパーの生成
	void				createAnimation();

	// 円コリジョンの生成
	void				createCollideCircle(float radius, bool isEnable = true);

	// 線分コリジョンの生成
	void				createCollideSegment(const cocos2d::Vec2& offset0, const cocos2d::Vec2& offset1, bool isEnable = true);

	/**
	 * @brief		コリジョンヒット時のコールバック
	 * @param[in]	target		衝突した相手
	 * @note		コリジョンが必要ないEntityもあるかもしれないので純粋仮想関数にはしない
	 */
	virtual void		collideCallback(Collide::Object* target) {}

	/**
	 * @brief		更新するかどうかのフラグの取得
	 * @return		true 更新する／false 更新しない（停止）
	 */
	bool				isActive() const			{ return isActive_; }

	/**
	 * @brief		描画するかどうかのフラグの取得
	 * @return		true 描画する／false 描画しない
	 */
	bool				isDraw() const				{ return isDraw_; }

	/**
	 * @brief		解放リクエストが来ているか
	 * @return		true 来ている／false 来ていない
	 */
	bool				isReleased() const			{ return releaseRequest_; }

	/**
	 * @brief		位置の取得
	 * @return		Entityの位置
	 */
	const cocos2d::Vec2& getPosition()				{ return sprite_ ? sprite_->getPosition() : zeroVectoer_; }

	/**
	 * @brief		アニメーションヘルパーの取得
	 * @return		アニメーションヘルパーのポインタ（生成していない場合はnullptr）
	 */
	SafePointer<AnimationHelper>	getAnimation()				{ return animation_; }

	/**
	 * @brief		コリジョンオブジェクトの取得
	 * @return		コリジョンオブジェクトのポインタ（生成していない場合はnullptr）
	 */
	SafePointer<Collide::Object>	getCollideObject()			{ return collideObject_; }

	/**
	 * @brief		スプライトのセット
	 * @param[in]	sprite		スプライトのポインタ（画像を指定しない場合はnullptr）
	 */
	void				setSprite(cocos2d::Sprite* sprite)	{ sprite_ = sprite; }

	/**
	 * @brief		スプライトの取得
	 * @return		スプライトのポインタ（画像を指定していない場合はnullptr）
	 */
	SafePointer<cocos2d::Sprite>	getSprite()					{ return sprite_; }

	/**
	 * @brief		敵味方の取得
	 * @return		敵味方の定義（Game::SIDEを参照してください）
	 */
	Game::SIDE			getSide() const				{ return side_; }

private:
	bool							isActive_;				//!< 更新するかどうかのフラグ
	bool							isDraw_;				//!< 描画するかどうかのフラグ
	bool							isFlipX_;				//!< 描画時に横反転するかどうかのフラグ
	bool							releaseRequest_;		//!< 解放リクエストのフラグ
	SafePointer<cocos2d::Sprite>	sprite_;				//!< スプライトのポインタ
	SafePointer<Collide::Object>	collideObject_;			//!< コリジョンオブジェクトのポインタ
	SafePointer<AnimationHelper>	animation_;				//!< アニメーションヘルパーのポインタ
	Game::SIDE						side_;					//!< 敵味方情報
	cocos2d::Vec2					zeroVectoer_;			//!< 不正返答用のゼロベクトル
};
