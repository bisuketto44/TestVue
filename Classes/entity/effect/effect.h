/**
 * @file    effect.h
 *
 * @brief	エフェクトの基底クラス
 * @details エフェクトを出したいときはこのクラスを基底として作成する
 *
 * @author  Kaifu Koji
 * @date    2017/05/02
 * @note    マーベラス開発部新人研修C++演習用
 */

#pragma once

#include <cocos2d.h>
#include "utility/animation_helper.h"
#include "entity/entity.h"


/**
 * @brief	エフェクトの基底クラス
 * @note	このクラスはアニメーションの終了時に自動で破棄される
 */
class Effect : public Entity
{
	struct SpriteFrame;

public:
	/**
	 * @brief	画像フレーム構造体
	 * @note	初期化時にしか使用しない
	 */
	struct ImageFrame
	{
		const char*			filename_;		//!< このコマの画像ファイルのポインタ
		float				time_;			//!< このコマの再生時間
	};

	// 画像フレームテーブルによるエフェクトの生成
	static void create(const ImageFrame* imageFrames, int count, const cocos2d::Vec2& position, float scale);

	// コンストラクタ
	Effect(
				const SpriteFrame* spriteFrames, int count,
				const cocos2d::Vec2& position,
				float scale = 1.0f,
				AnimationHelper::END_TYPE endType = AnimationHelper::END_TYPE_ERASE_AND_RELEASE_OWNER,
				bool autoStart = true
			);
	// デストラクタ
	virtual ~Effect();

private:
	/**
	 * @brief	スプライトフレーム構造体
	 */
	struct SpriteFrame
	{
		cocos2d::Sprite*	sprite_;		//!< このコマのスプライトのポインタ ※処理が重くなるのでSafePointer<>は使わないでおく
		float				time_;			//!< このコマの再生時間
	};

	// スプライトフレームテーブルを生成
	static SpriteFrame* createSpriteFlameTable(const ImageFrame* imageFrames, int count);
	// スプライトフレームテーブルを破棄
	static void destroySpriteFlameTable(SpriteFrame* spriteFrames, int count);
};
