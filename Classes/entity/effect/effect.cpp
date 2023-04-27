/**
 * @file    effect.cpp
 *
 * @brief	エフェクトの基底クラス
 * @details エフェクトを出したいときはこのクラスを基底として作成する
 *
 * @author  Kaifu Koji
 * @date    2017/05/02
 * @note    マーベラス開発部新人研修C++演習用
 */

#include "utility/macro.h"
#include "entity/effect/effect.h"


/**
 * @brief		画像フレームテーブルによるエフェクトの生成
 * @param[in]	imageFrames		ImageFrameの配列のポインタ
 * @param[in]	count			ImageFrameの数
 * @param[in]	position		表示位置
 * @param[in]	scale			表示スケール
 */
void Effect::create(const ImageFrame* imageFrames, int count, const cocos2d::Vec2& position, float scale)
{
	// スプライトフレームテーブルを生成
	SafePointer<SpriteFrame> spriteFrames = Effect::createSpriteFlameTable(imageFrames, count);

	// クラスを生成
	// --- 自動で破棄されるのでポインタは管理しない
	APP_NEW Effect(spriteFrames, count, position, scale);

	// スプライトフレームテーブルの破棄
	destroySpriteFlameTable(spriteFrames, count);
}


/**
 * @brief		スプライトフレームテーブルを生成
 * @param[in]	imageFrames		ImageFrameの配列のポインタ
 * @param[in]	count			ImageFrameの数
 * @return		SpriteFrameの配列のポインタ
 */
Effect::SpriteFrame* Effect::createSpriteFlameTable( const ImageFrame* imageFrames, int count)
{
	// スプライトで初期化するためのワーク
	SafePointer<SpriteFrame> spriteFrame = APP_NEW SpriteFrame[count];

	// 各コマの画像ファイルからスプライトを生成
	for(int i=0; i<count; i++)
	{
		// 画像ファイルから cocos2d::SpriteFrame を生成
		SafePointer<cocos2d::Sprite> sprite = cocos2d::Sprite::create(imageFrames[i].filename_);
		if(!sprite)
		{
			CCLOG("ERROR : image file not found !!  [%s]", imageFrames[i].filename_);
		}
		else {
			spriteFrame[i].sprite_ = sprite;
			sprite->retain();
		}

		// 再生時間をコピー
		spriteFrame[i].time_ = imageFrames[i].time_;
	}

	// 生成したテーブルを返す
	return spriteFrame;
}


/**
 * @brief		スプライトフレームテーブルを破棄
 * @param[in]	spriteFrames		SpriteFrameの配列
 */
void Effect::destroySpriteFlameTable(SpriteFrame* spriteFrames, int count)
{
	// 各コマのスプライトを解放
	for(int i=0; i<count; i++)
	{
		if(spriteFrames[i].sprite_)
			spriteFrames[i].sprite_->release();
	}

	// テーブルを解放
	APP_DELETE_ARRAY(spriteFrames);
}


/**
 * @brief		コンストラクタ
 * @param[in]	spriteFrames	SpriteFrameの配列のポインタ
 * @param[in]	count			SpriteFrameの数
 * @param[in]	position		表示位置
 * @param[in]	scale			表示スケール
 * @param[in]	endType			終了タイプ
 * @param[in]	autoStart		自動的に再生開始
 */
Effect::Effect(
					const SpriteFrame* spriteFrames,
					int count,
					const cocos2d::Vec2& position,
					float scale,
					AnimationHelper::END_TYPE endType,
					bool autoStart
				)
 : Entity(nullptr, position, Game::SIDE_FRIENDLY, autoStart, autoStart,false)
{
//	CCLOG("Effect::Effect()  %p", this);

	// カウント数ゼロは無効
	if(!count)
		return;

	// 最初のフレームのスプライトをセット
	setSprite(spriteFrames[0].sprite_);
	addChild(spriteFrames[0].sprite_, 0);
	getSprite()->retain();		// 参照カウンタを増やす

	// アニメーションを生成
	createAnimation();

	// 各コマを生成
	for(int i=0; i<count; i++)
	{
		getAnimation()->addFrame(spriteFrames[i].sprite_, spriteFrames[i].time_);
	}

	// 終了タイプを指定
	getAnimation()->setEndType(endType);

	// スプライトのセットアップ
	getSprite()->setPosition(position);
	getSprite()->setScale(scale);
	setActive(autoStart);
	setDraw(autoStart);
}


/**
 * @brief		デストラクタ
 */
Effect::~Effect()
{
//	CCLOG("Effect::~Effect()  %p", this);
}


