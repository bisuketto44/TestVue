/**
 * @file    entity.cpp
 *
 * @brief   物体の基底クラス
 * @details ゲームに何か表示を伴う物体を登場させたいときに基底とするクラス
 *          スプライトの表示、定期的なupdate、アニメーション、コリジョンをサポートする
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */

#include "app_define.h"
#include "entity.h"
#include "game.h"
#include "scene/base_scene.h"
#include "manager/animation_manager.h"
#include "utility/collision.h"


/**
 * @brief		コンストラクタ
 * @param[in]	imageFilename	画像ファイル名
 * @param[in]	position		初期位置
 * @param[in]	side			敵味方情報
 * @param[in]	isActive		初期状態で更新有効か
 * @param[in]	isDraw			初期状態で描画有効か
 */
Entity::Entity(const char* imageFilename, const cocos2d::Vec2& position, Game::SIDE side, bool isActive, bool isDraw, bool isUilayer)
 : isActive_(isActive)
 , isFlipX_(false)
 , releaseRequest_(false)
 , sprite_(nullptr)
 , collideObject_(nullptr)
 , animation_(nullptr)
 , side_(side)
 , zeroVectoer_(cocos2d::Vec2(0.0f, 0.0f))
{
	// イメージの指定がある場合はスプライトを生成
	if(imageFilename)
	{
		sprite_ = cocos2d::Sprite::create(imageFilename);
		if(!sprite_)
		{
			CCLOG("ERROR : image file not found !!  [%s]", imageFilename);
			return;
		}

		sprite_->setPosition(position);

		if(!isUilayer)
		{
			addChild(sprite_, 0);

		}
		else
		{
			this->setCameraMask((int)cocos2d::CameraFlag::USER1);
			Game::getInstance()->getCurrentScene()->getuILayer()->addChild(sprite_);
			
		}
		
	}

	// シーンの子に追加
	Game::getInstance()->getCurrentScene()->addChild(this, 0);

	// 表示有り無しの初期化
	setDraw(isDraw);
}


/**
 * @brief		デストラクタ
 */
Entity::~Entity()
{
	// releaseRequest()が呼ばれていなかったら実行を止めるデバッグ用機能
	APP_ASSERT(releaseRequest_, "Not called releaseRequest().");

	// コリジョンを使っていたら削除
	if(collideObject_)
		APP_SAFE_DELETE(collideObject_);

	// アニメーションを使っていたら削除
	if(animation_)
	{
		AnimationManager* animationManager = Game::getInstance()->getAnimationManager();
		if(animationManager)
			animationManager->remove(animation_);

		APP_SAFE_DELETE(animation_);
	}
}


/**
 * @brief		解放リクエスト
 * @details		Entityを解放したいときに呼ぶ。これが呼ばれると次のフレームのupdateの前に解放される
 */
void Entity::releaseRequest()
{
	CCLOG("ENTYTYSINDA");
	isActive_ = false;
	releaseRequest_ = true;

	// シーンのエンティティ削除リストに登録
	Game::getInstance()->getCurrentScene()->addReleaseEntity(this);

	// Layerから外す
	if(sprite_)
	{
		sprite_->removeFromParentAndCleanup(true);
		sprite_ = nullptr;
	}
	//これでENTITYが消える?
	removeFromParentAndCleanup(true);
}


/**
 * @brief		描画するかどうかの指定
 * @param[in]	isDraw		true 描画する／false 描画しない
 */
void Entity::setDraw(bool isDraw)
{
	isDraw_ = isDraw;
	if(sprite_)
		sprite_->setVisible(isDraw_);
}


/**
 * @brief		描画時に横反転するかどうかの指定
 * @param[in]	isDraw		true 描画する／false 描画しない
 */
void Entity::setFlipX(bool isFlip)
{
	isFlipX_ = isFlip;
	if(sprite_)
		sprite_->setFlippedX(isFlipX_);
}


/**
 * @brief		アニメーションヘルパーの生成
 */
void Entity::createAnimation()
{
	// アニメーションヘルパーの生成
	animation_ = APP_NEW AnimationHelper(this);
}


/**
 * @brief		円コリジョンの生成
 * @param[in]	radius			半径
 * @param[in]	isEnable		初期状態（true：有効／false無効）
 * @note		中心はownerの位置。
 */
void Entity::createCollideCircle(float radius, bool isEnable)
{
	// すでに生成済みなら作成しない
	if(collideObject_)
		return;

	// 円コリジョンを生成
	collideObject_ = APP_NEW Collide::Circle(radius, isEnable, this);
}


/**
 * @brief		線分コリジョンの生成
 * @param[in]	offset0			ownerの位置から線分の一端へのオフセット
 * @param[in]	offset1			ownerの位置から線分のもう一端へのオフセット
 * @param[in]	isEnable		初期状態（true：有効／false無効）
 */
void Entity::createCollideSegment(const cocos2d::Vec2& offset0, const cocos2d::Vec2& offset1, bool isEnable)
{
	// すでに生成済みなら作成しない
	if(collideObject_)
		return;

	// 線分コリジョンを生成
	collideObject_ = APP_NEW Collide::Segment(offset0, offset1, isEnable, this);
}
