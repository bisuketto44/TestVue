/**
 * @file    collision.cpp
 *
 * @brief   衝突判定
 * @details 基礎的な2Dの衝突判定を行うクラス
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */

#include "utility/collision.h"
#include "entity/entity.h"

/**
 * @brief		円と円の衝突判定
 * @param[in]	center0		円0の中心
 * @param[in]	radius0		円0の半径
 * @param[in]	center1		円1の中心
 * @param[in]	radius1		円1の半径
 * @return		ture 接触している／false 接触していない
 */
static bool checkCircleVsCircle(const cocos2d::Vec2& center0, float radius0, const cocos2d::Vec2& center1, float radius1)
{
	// --- 中心間の距離が、2つの円の半径の和より小さければ接触している
	// --- 高速化のため距離は平方根をかけず、２乗したままの値で計算する

	float distanceSq = center0.distanceSquared(center1);
	float radiusTotal = radius0 + radius1;
	if(distanceSq < radiusTotal * radiusTotal)
		return true;

	return false;
}


/**
 * @brief		円と線分の衝突判定
 * @param[in]	center		円の中心
 * @param[in]	radius		円の半径
 * @param[in]	point0		線分の片端
 * @param[in]	poiint1		線分の片端
 * @return		ture 接触している／false 接触していない
 */
static bool checkCircleVsSegment(const cocos2d::Vec2& center, float radius, const cocos2d::Vec2& point0, const cocos2d::Vec2& point1)
{
	// --- 中心（円）から直線（線分）への足を求め、中心からの距離が半径より大きければ接触していない。
	// --- 半径より小さい場合は、足が線分内にあれば接触している。
	// --- また、線分の両端の点が円の中に含まれる（円の中心との距離が半径以下）の場合も接触している

	// 円の中心から直線への距離を求め、円の半径と比較する
	float D = abs( (center - point0).cross(point1 - point0) );
	float L = point0.distance(point1);
	float distance = D / L;
	if(distance > radius)
		return false;	// 接触していない

	// 円の中心から直線への足が線分内にあるかを確認する
	// 円の中心と線分の両端の点のなす角が両方直角以下なら垂線の足も線分内
	float DotCP0P1 = (center - point0).dot(point1 - point0);
	float DotCP1P0 = (center - point1).dot(point0 - point1);
	if(DotCP0P1 >= 0.0f && DotCP1P0 >= 0.0f)
		return true;	// 接触している

	// 線分の両端の点が円の中に含まれる（円の中心との距離が半径以下）か確認する
	// 距離を求める際、平方根をかけると処理を食うため二乗したまま比較している
	float distanceSq0 = center.distanceSquared(point0);
	if(distanceSq0 < radius * radius)
		return true;	// 接触している
	float distanceSq1 = center.distanceSquared(point1);
	if(distanceSq1 < radius * radius)
		return true;	// 接触している

	// 接触していない
	return false;
}

namespace Collide
{



/**
 * @brief		コンストラクタ
 * @param[in]	type		タイプ
 * @param[in]	isEnable	初期状態でコリジョン判定を有効にするか
 * @param[in]	owner		持ち主のエンティティ
 */
Object::Object(TYPE type, bool isEnable, Entity* owner)
	: type_(type)
	, isEnable_(isEnable)
	, owner_(owner)
{
}


/**
 * @brief		コンストラクタ
 * @param[in]	radius		円の半径
 * @param[in]	isEnable	初期状態でコリジョン判定を有効にするか
 * @param[in]	owner		持ち主のエンティティ
 */
Circle::Circle(float radius, bool isEnable, Entity* owner)
	: Object(TYPE_CIRCLE, isEnable, owner)
	, radius_(radius)
{
}


/**
 * @brief		衝突判定
 * @param[in]	target		判定する相手のコリジョンオブジェクト
 */
bool Circle::check(Object* target)
{
	// 無効な時は判定しない
	if(!isEnable_)
		return false;
	if(!target->isEnable())
		return false;

	bool isHit = false;

	// 判定する相手のタイプ毎の処理
	switch (target->getType())
	{
	case TYPE_CIRCLE:
		{
			// 円と円の接触判定
			SafePointer<Circle> trgtCircle = dynamic_cast<Circle*>(target);
			const cocos2d::Vec2& myCenter = getOwner()->getPosition();
			const cocos2d::Vec2& trgtCenter = target->getOwner()->getPosition();
			isHit = checkCircleVsCircle(myCenter, radius_, trgtCenter, trgtCircle->radius_);
		}
		break;

	case TYPE_SEGMENT:
		{
			// 円と線分の接触判定
			SafePointer<Segment> trgtSegment = dynamic_cast<Segment*>(target);
			const cocos2d::Vec2& myCenter = getOwner()->getPosition();
			const cocos2d::Vec2& trgtPosition = target->getOwner()->getPosition();
			cocos2d::Vec2 point0 = trgtPosition + trgtSegment->offset0_;
			cocos2d::Vec2 point1 = trgtPosition + trgtSegment->offset1_;
			isHit = checkCircleVsSegment(myCenter, radius_, point0, point1);
		}
		break;
	}

	// 接触していた場合
	if(isHit)
	{
		// コールバック関数の呼び出し
		target->getOwner()->collideCallback(this);
		getOwner()->collideCallback(target);
	}

	return isHit;
}


/**
 * @brief		コンストラクタ
 * @param[in]	offset0		ownerの位置から線分の一端へのオフセット
 * @param[in]	offset1		ownerの位置から線分のもう一端へのオフセット
 * @param[in]	isEnable	初期状態でコリジョン判定を有効にするか
 * @param[in]	owner		持ち主のエンティティ
 */
Segment::Segment(const cocos2d::Vec2& offset0, const cocos2d::Vec2& offset1, bool isEnable, Entity* owner)
	: Object(TYPE_SEGMENT, isEnable, owner)
	, offset0_(offset0)
	, offset1_(offset1)
{
}


/**
 * @brief		衝突判定
 * @param[in]	target		判定する相手のコリジョンオブジェクト
 */
bool Segment::check(Object* target)
{
	// 無効な時は判定しない
	if(!isEnable_)
		return false;
	if(!target->isEnable())
		return false;

	bool isHit = false;

	// 判定する相手のタイプ毎の処理
	switch (target->getType())
		{
		case TYPE_CIRCLE:
		{
			// 線分と円の接触判定
			SafePointer<Circle> trgtCircle = dynamic_cast<Circle*>(target);
			const cocos2d::Vec2& myPosition = getOwner()->getPosition();
			const cocos2d::Vec2& trgtCenter = target->getOwner()->getPosition();
			cocos2d::Vec2 point0 = myPosition + offset0_;
			cocos2d::Vec2 point1 = myPosition + offset1_;
			isHit = checkCircleVsSegment(trgtCenter, trgtCircle->radius_, point0, point1);
		}
		break;

	case TYPE_SEGMENT:
		{
			// 線分と線分の接触判定
			// --- 線分が交わるかどうかの判定
			// --- ほとんど需要が無さそうなので非対応
			// --- 常に接触しない判定を返す
			isHit = false;
		}
		break;
	}

	// 接触していた場合
	if(isHit)
	{
		// コールバック関数の呼び出し
		target->getOwner()->collideCallback(this);
		getOwner()->collideCallback(target);
	}

	return isHit;
}


}	// namespase Collide
