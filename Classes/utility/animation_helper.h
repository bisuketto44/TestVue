/**
 * @file    animation_helper.h
 *
 * @brief   アニメーション再生の補助クラス
 * @details Entityのスプライトの画像を、addFrame()で指定された画像・時間間隔で切り替えていく
 *          ※クラス名を単にAnimationとしていない理由は、cocos2d::Animationとかぶるのでこの名としました。
 *          ※画像をcocos2d::Spriteで持つのはメモリの無駄が発生しますが、今回は簡易な実装を優先してこの形としました。
 *          ※画像ファイルを読み込むタイミングはaddFrame()した時なので大量に読み込むと処理落ちする可能性があります。
 *          　（通常のゲーム制作ではリソースファイルは事前に読み込んでおきます）
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */

#pragma once

#include <cocos2d.h>

class Entity;


/**
 * @brief	アニメーション再生の補助クラス
 */
class AnimationHelper
{
	/**
	 * @brief	アニメーションの１コマの情報
	 */
	class Frame
	{
	public:
		SafePointer<cocos2d::Sprite>	sprite_;		//!< このコマのスプライトのポインタ
		float							time_;			//!< 次のコマに切り替える時間
	};

public:
	/**
	 * @brief	終了タイプ（最後のコマまで再生した後の挙動）
	 */
	enum END_TYPE
	{
		END_TYPE_LOOP,						//!< ループする（最初のコマに戻る）
		END_TYPE_STOP,						//!< 最後のコマをそのまま表示し続ける
		END_TYPE_ORIGINAL,					//!< 元の画像を表示する
		END_TYPE_ERASE,						//!< 表示を消す
		END_TYPE_ERASE_AND_RELEASE_OWNER,	//!< 表示を消し、オーナーも解放する　※自動破棄していい場合のみ使用可（使い捨てのエフェクトなど）
	};

	// コンストラクタ
	AnimationHelper::AnimationHelper(Entity* owner);
	// デストラクタ
	virtual ~AnimationHelper();

	// コマの追加（画像ファイル指定）
	void addFrame(const char* imageFilename, float time);
	// コマの追加（スプライト指定）
	void addFrame(cocos2d::Sprite* sprite, float time);
	// アニメーションのクリア
	void clear();

	// 更新
	void update(float deltaTime);

	// 再生のリセット
	void reset();

	/**
	 * @brief		終了タイプの設定
	 * @param[in]	endType			終了タイプ
	 * @details		最後のコマまで再生した後の挙動を指定します。（デフォルトはループ）
	 */
	void setEndType(END_TYPE endType)	{ endType_ = endType; }

	/**
	 * @brief		再生が終了しているか
	 * @return		true 終了／false 再生途中
	 * @note		終了タイプがEND_TYPE_LOOPの時は常にfalseを返します。
	 */
	bool isEnd()				{ return isEnd_; }

	/**
	 * @brief		解放リクエスト
	 */
	void releaseRequest()		{ releaseRequest_ = true; };

	/**
	 * @brief		解放リクエストが来ているか
	 * @return		true 解放する／false 解放しない
	 */
	bool				isReleased() const { return releaseRequest_; }

private:
	// コマの適用
	void setFrame(const Frame& frame);

	// 元々セットされていたテクスチャをセット
	void setOriginalTexture();

	SafePointer<Entity>				owner_;						//!< オーナーのポインタ
	SafePointer<cocos2d::Sprite>	sprite_;					//!< スプライトのポインタ
	SafePointer<cocos2d::Texture2D>	originalTexture_;			//!< スプライトに元々セットされていたテクスチャのポインタ
	std::vector<Frame>				frameList_;					//!< コマのリスト
	float							totalTime_;					//!< アニメーションのトータル時間
	float							timer_;						//!< アニメーションの再生タイマ
	int								currentIndex_;				//!< 現在再生しているコマのインデックス
	SafePointer<cocos2d::Sprite>	currentSprite_;				//!< 現在表示しているスプライト
	END_TYPE						endType_;					//!< 終了タイプ
	bool							isEnd_;						//!< 再生終了フラグ
	bool							releaseRequest_;			//!< 解放リクエストのフラグ
};
