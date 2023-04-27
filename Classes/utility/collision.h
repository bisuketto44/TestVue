/**
 * @file    collision.h
 *
 * @brief   衝突判定
 * @details 基礎的な2Dの衝突判定を行うクラス
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */

#pragma once

#include <cocos2d.h>


class Entity;

/**
 * @brief	コリジョン処理
 */
namespace Collide
{


/**
 * @brief	コリジョンオブジェクトの基底クラス
 * @note	衝突判定をさせたい形状を作成するときにはこのクラスを基底クラスにする
 */
class Object
{
public:
	/**
	 * @brief		タイプ
	 * @note		今は形状の違いだけですが、形状だけとは限りません。
	 */
	enum TYPE
	{
		TYPE_CIRCLE,		//!< 円
		TYPE_SEGMENT,		//!< 線分（長さの限られた直線）
		TYPE_NUM
	};

	/**
	 * @brief		他のコリジョンオブジェクトとの衝突判定
	 * @param[in]	target		衝突判定する相手
	 * @return		true 衝突している／false 衝突していない
	 * @note		"=0" が付いていると純粋仮想関数になり、継承先で必ず実装する必要がある。
	 */
	virtual bool check(Object* target) = 0;		// 純粋仮想関数

	/**
	 * @brief		タイプの取得
	 * @return		タイプ
	 */
	TYPE getType() const			{ return type_; }

	/**
	 * @brief		オーナーの取得
	 * @return		オーナーのポインタ
	 */
	SafePointer<Entity> getOwner()		{ return owner_; }

	/**
	 * @brief		オーナーの取得（const）
	 * @return		オーナーのconstポインタ
	 */
	const SafePointer<Entity> getOwner() const	{ return owner_; }

	/**
	 * @brief		コリジョン判定をするかのフラグのセット
	 * @param[in]	isEnable	true 判定する／false 判定しない
	 */
	void			setEnable(bool isEnable)	{ isEnable_ = isEnable; }
	/**
	 * @brief		コリジョン判定をするかのフラグの取得
	 * @return		true 判定する／false 判定しない
	 */
	bool			isEnable() const	{ return isEnable_; }

protected:
	// コンストラクタ
	Object(TYPE type, bool isEnable, Entity* owner);

	TYPE					type_;			//!< タイプ
	bool					isEnable_;		//!< コリジョン判定が有効か
	SafePointer<Entity>		owner_;			//!< 
};


/**
 * @brief	円コリジョンの基底クラス
 */
class Circle : public Object
{
	friend class Segment;

public:
	Circle(float radius, bool isEnable, Entity* owner);

	virtual bool check(Object* target);

protected:
	float	radius_;
};


/**
 * @brief	線分コリジョンの基底クラス
 */
class Segment : public Object
{
	friend class Circle;

public:
	Segment(const cocos2d::Vec2& offset0, const cocos2d::Vec2& offset1, bool isEnable, Entity* owner);

	virtual bool check(Object* target);

protected:
	cocos2d::Vec2	offset0_;
	cocos2d::Vec2	offset1_;
};


}	// namespace Collide
