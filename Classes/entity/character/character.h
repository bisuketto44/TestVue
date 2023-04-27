/**
 * @file    character.h
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
#include "game.h"
#include "entity/entity.h"

class Controller;
class Attack;
class Ui;

/**
 * @brief	キャラクターの基底クラス
 * @note	このクラスと派生クラスは自己消滅orマネージャによって削除されます。（生成した側で削除する必要はありません）
 * @note	生成した側でポインタを保持する場合は、キャラクター消滅時にポインタをクリアするような仕組みを実装してください。
 */
class Character : public Entity
{
public:
	// コンストラクタ
	Character(const char* imageFilename, const cocos2d::Vec2& position, Game::SIDE side, int Hp, Controller* controller = nullptr, bool isActive = true, bool isDraw = true);
	// デストラクタ
	virtual ~Character();

	// 更新
	virtual void	update(float deltaTime);

	/**
	 * @brief		コントローラのセット
	 * @param[in]	controller		セットしたいコントローラ
	 */
	void			setController(Controller* controller) { nextController_ = controller; isSetNextController_ = true; }

	/**
	 * @brief		現在のコントローラの取得
	 * @return		現在のコントローラ
	 */
	SafePointer<Controller>	getController() { return currectController_; }

	/**
	 * @brief		コントローラが有効になってからの時間の取得
	 * @return		時間（単位：秒）
	 */
	float			getTimer() const { return timer_; }

	/**
	* @brief		向いている方向
	*/
	enum DIRECTION
	{
		UP,				// 上方向
		DOWN,			// 下方向
		RIGHT,          // 右方向
		LEFT,           // 左方向
	};

	/**
	* @brief		現在向きを取得
	* @return		最後に入力された方向を取得する
	*/
	DIRECTION		getCurrentDirection() { return currentDirction; }

	/**
	* @brief		現在向きを設定
	* @return		最後に入力された方向を設定する
	*/
	void		setCurrentDirection(DIRECTION direction) { currentDirction = direction; }

	int         getHP() { return ownHp; }


protected:
	/**
	 * @brief	ステートID
	 * @notef	キャラクターの状態を定義するインデックスです
	 * @notef	必要に応じて追加してください
	 */
	enum STATE
	{
		STATE_NORMAL,					//!< 通常
		STATE_ATTACK,					//!< 攻撃
		STATE_JUMP,						//!< ジャンプ
		STATE_DEAD,						//!< 死亡

		STATE_NUM
	};

	/**
	 * @brief	アニメーションID
	 * @notef	キャラクターのアニメーションを定義するインデックスです
	 * @notef	必要に応じて追加してください
	 */
	enum ANIMATION
	{
		ANIMATION_STAND,					//!< 立ち
		ANIMATION_MOVE,						//!< 移動
		ANIMATION_NORMAL_ATTACK,			//!< 通常攻撃
		ANIMATION_JUMP,						//!< ジャンプ
		ANIMATION_DEAD,						//!< 死亡

		ANIMATION_NUM
	};

	// 移動の更新
	virtual bool	updateMove(float deltaTime);

	// アクションの更新（攻撃など移動以外の動作）
	virtual void	updateAction(float deltaTime);

	/**
	 * @brief		アニメーションの指定
	 * @note		"=0" が付いていると純粋仮想関数になり、継承先で必ず実装する必要がある。
	 */
	virtual void	setAnimation(ANIMATION animation) = 0;	// 純粋仮想関数

	/**
	 * @brief		弾を撃つ処理
	 * @note		通常攻撃を持つキャラクターは継承先クラスでこの関数をオーバーライドした関数を実装する
	 * 				継承先クラスにオーバーライドした関数が無い場合は何もしない
	 */

	 //通常攻撃
	virtual void	attackNormal() {}
	//強攻撃
	virtual void    attackStrong() {}
	//アルティメット攻撃
	virtual void    attackUltimate() {}

	STATE						state_;					//!< ステートID
	ANIMATION					animation_;				//!< アニメーションID

	SafePointer<Attack>			attack_;				    //!< 攻撃のポインタ
	SafePointer<Ui>			    ui_;				        //!< uiのポインタ

	DIRECTION				    currentDirction = RIGHT;//!< 現在の方向

	int                         ownHp = 0;              //!< このキャラクターのHP

private:
	float						timer_;					//!< タイマー

	SafePointer<Controller>		currectController_;		//!< 現在のコントローラ
	SafePointer<Controller>		nextController_;		//!< セットリクエストが来たコントローラ
	bool						isSetNextController_;	//!< セットリクエストが来ているか


};
