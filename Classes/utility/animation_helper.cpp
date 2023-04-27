/**
 * @file    animation_helper.cpp
 *
 * @brief   アニメーション再生の補助クラス
 * @details Entityのスプライトの画像を、addFrame()で指定された画像・時間間隔で切り替えていく
 *          ※クラス名を単にAnimationとしていない理由は、cocos2d::Animationとかぶるのでこの名とした
 *          ※画像ファイルを読み込むタイミングはaddFrame()した時なので大量に読み込むと処理落ちする可能性があります。
 *          　（通常のゲーム制作ではリソースファイルは事前に読み込んでおきます）
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */

#include "utility/animation_helper.h"
#include "manager/animation_manager.h"
#include "entity/entity.h"


/**	
 * @brief		コンストラクタ
 * @param[in]	owner		アニメーションさせたいEntityのポインタ
 */
AnimationHelper::AnimationHelper(Entity* owner)
 : owner_(owner)
 , totalTime_(0.0f)
 , timer_(0.0f)
 , currentIndex_(-1)
 , currentSprite_(nullptr)
 , endType_(END_TYPE_LOOP)
 , isEnd_(false)
 , releaseRequest_(false)
{
	// アニメーションマネージャに追加
	AnimationManager* animationManager = Game::getInstance()->getAnimationManager();
	if(animationManager)
		animationManager->add(this);

	if(owner_->getSprite())
	{
		// 元々セットされていたテクスチャのポインタを保存
		originalTexture_ = owner_->getSprite()->getTexture();

		// 現在表示しているスプライトを更新
		currentSprite_ = owner_->getSprite();
		currentSprite_->retain();		// 参照カウンタを増やす
	}
}


/**
 * @brief		デストラクタ
 */
AnimationHelper::~AnimationHelper()
{
	// アニメーションマネージャから削除
	AnimationManager* animationManager = Game::getInstance()->getAnimationManager();
	if(animationManager)
		animationManager->remove(this);

	// リソースの解放
	clear();

	// 現在表示中のスプライトの参照カウンタを減らす
	if(currentSprite_)
		currentSprite_->release();
}


/**	
 * @brief		コマの追加（画像ファイル指定）
 * @param[in]	imageFilename	画像ファイル名
 * @param[in]	time			コマを表示する長さ（単位：秒）
 */
void AnimationHelper::addFrame(const char* imageFilename, float time)
{
	// 画像ファイルから cocos2d::SpriteFrame を生成
	cocos2d::Sprite* sprite = cocos2d::Sprite::create(imageFilename);
	if(!sprite)
	{
		CCLOG("ERROR : image file not found !!  [%s]", imageFilename);
		return;
	}

	// スプライト渡しのaddFrameを呼ぶ
	addFrame(sprite, time);
}


/**	
 * @brief		コマの追加（スプライト指定）
 * @param[in]	sprite		適用したい画像のスプライトのポインタ
 * @param[in]	time		コマを表示する長さ（単位：秒）
 */
void AnimationHelper::addFrame(cocos2d::Sprite* sprite, float time)
{
	Frame frame;

	// スプライトのポインタをコマにセット
	frame.sprite_ = sprite;

	// addChildしないので参照カウンタを増やしておく
	if(frame.sprite_)
		frame.sprite_->retain();

	// このイメージの再生終了時間をセット
	totalTime_ += time;
	frame.time_ = totalTime_;

	// リストに積む
	frameList_.push_back(frame);
}


/**	
 * @brief		アニメーションのクリア
 * @details		全てのコマを解放します。現在表示中のコマはそのままになります。
 * @note		reset()との機能の違いに注意
 */
void AnimationHelper::clear()
{
	// 登録されている全てのコマのスプライトを解放（参照カウンタを１つ減らす）
	for(auto itr = frameList_.begin(); itr != frameList_.end(); ++itr)
	{
		Frame& frame = *itr;
		if(frame.sprite_)
			frame.sprite_->release();
	}

	// コマのリストをクリア
	frameList_.clear();

	// 再生情報を初期化
	reset();
	currentIndex_ = -1;
	totalTime_ = 0.0f;

	// --- 今現在表示されているコマは変更していない。
	// --- 最後に表示された状態が維持される
}


/**
 * @brief		更新
 * @param[in]	deltaTime		前フレームから進行した時間（単位：秒）
 */
void AnimationHelper::update(float deltaTime)
{
	// コマが積まれていないときは何もしない
	if(!frameList_.size())
		return;

	// 再生開始直後のみ通る処理
	if(currentIndex_ == -1)
	{
		// 再生のリセット
		reset();
	}

	// 次のフレームに移るかの判定
	if(frameList_[currentIndex_].time_ <= timer_)
	{
		// 次のフレームがあるかの確認
		if( currentIndex_ + 1 < static_cast<int32_t>(frameList_.size()))
		{
			// 次のフレームへ
			currentIndex_++;
			setFrame(frameList_[currentIndex_]);
		} else
		{
			// 次のフレームが無い場合

			// 終了タイプ毎の処理
			switch(endType_)
			{
			// ループする
			case END_TYPE_LOOP:
				// ループして先頭へ戻る
				reset();
				break;

			// 最後のコマをそのまま表示し続ける
			case END_TYPE_STOP:
				// 何もしない

				// 再生終了フラグを立てる
				isEnd_ = true;
				break;

			// 元の画像を表示する
			case END_TYPE_ORIGINAL:
				// 元々セットされていたテクスチャをセット
				setOriginalTexture();

				// 再生終了フラグを立てる
				isEnd_ = true;
				break;

			// 表示を消す
			case END_TYPE_ERASE:
				// 表示を消す
				if(owner_->getSprite())
					owner_->getSprite()->setVisible(false);

				// 再生終了フラグを立てる
				isEnd_ = true;
				break;

			// 自分を消し、オーナーも解放する
			case END_TYPE_ERASE_AND_RELEASE_OWNER:
				// 表示を消す
				if(owner_->getSprite())
					owner_->getSprite()->setVisible(false);

				// オーナーの解放リクエスト
				owner_->releaseRequest();

				// 再生終了フラグを立てる
				isEnd_ = true;

				// 解放したのでfalseを返す
				return;
			}
		}
	}

	// タイマーの更新
	timer_ += deltaTime;
}


/**
 * @brief		再生のリセット
 * @details		再生を最初のコマに戻します。
 * @note		clear()との機能の違いに注意
 */
void AnimationHelper::reset()
{
	// タイマーをクリア
	timer_ = 0;

	// 再生終了フラグをクリア
	isEnd_ = false;

	// 再生中のコマインデックスを最初のフレームに
	currentIndex_ = 0;

	// 最初のフレームをセット
	if(frameList_.size())
		setFrame(frameList_[0]);
}


/**	
 * @brief		コマの適用
 * @details		コマのスプライトのテクスチャをアニメーション対象のスプライトにセットします。
 */
void AnimationHelper::setFrame(const Frame& frame)
{
	if(frame.sprite_)
	{
		// コマにスプライトの指定がある場合

		// フレームのスプライトのテクスチャをセット
		if(owner_->getSprite())
		{
			owner_->getSprite()->setTexture(frame.sprite_->getTexture());
			owner_->getSprite()->setTextureRect(frame.sprite_->getSpriteFrame()->getRect());
		}

		// 今まで表示していたスプライトの参照カウンタを減らす
		if(currentSprite_)
			currentSprite_->release();

		// 現在表示しているスプライトを更新し、参照カウンタを増やす
		currentSprite_ = frame.sprite_;
		currentSprite_->retain();
	} else
	{
		// コマにスプライトの指定が無い場合

		// 元々セットされていたテクスチャをセット
		setOriginalTexture();
	}
}


/**	
 * @brief		元々セットされていたテクスチャをセット
 */
void AnimationHelper::setOriginalTexture()
{
	// 元々セットされていたテクスチャをセット
	if(owner_->getSprite())
	{
		owner_->getSprite()->setTexture(originalTexture_);
		owner_->getSprite()->setTextureRect(owner_->getSprite()->getSpriteFrame()->getRect());
	}

	// 今まで表示していたスプライトの参照カウンタを減らす
	if(currentSprite_)
		currentSprite_->release();

	// 現在表示しているスプライトを更新し、参照カウンタを増やす
	currentSprite_ = owner_->getSprite();
	currentSprite_->retain();
}
