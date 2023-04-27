/**
 * @file    controller.h
 *
 * @brief   コントローラの基底クラス
 * @details キャラクターをコントロールするクラスを作成するときに基底にする抽象クラス
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */

#pragma once

#include <cocos2d.h>


class Character;

// 派生クラス
class PadController;
class AIController;
class RemoteController;

/**
 * @brief		コントローラの基底クラス
 */
class Controller
{
public:
	/**
	 * @brief		タイプ
	 */
	enum TYPE
	{
		TYPE_PAD,				// パッド操作
		TYPE_AI,				// AI操作
		TYPE_REMOTE,			// リモート操作（ネットワークマルチプレイ時など。この演習では使用しない）

		TYPE_NUM
	};

	/**
	 * @brief		発射判定の結果
	 */
	struct Shoot
	{
		// 通常攻撃の発射判定
		bool			request_;		//!< リクエストを受けたフラグ
		bool			received_;		//!< リクエストが処理されたフラグ

		// 強攻撃の発射判定
		bool            request_strong_shoot;
		bool            received_strong_shoot;

	};

	// コンストラクタ
	Controller();
	// デストラクタ
	virtual ~Controller();

	/**
	 * @brief		更新処理
	 * @param[in]	deltaTime		前フレームから進行した時間（単位：秒）
	 * @note		"=0" が付いていると純粋仮想関数になり、継承先で必ず実装する必要がある。
	 */
	virtual void	update(float deltaTime) = 0;	// 純粋仮想関数

	/**
	 * @brief		持ち主のセット
	 * @param[in]	owner		このコントローラの持ち主
	 */
	void			setOwner(Character* owner) { owner_ = owner; }

	/**
	 * @brief		持ち主の取得
	 * @return		owner		このコントローラの持ち主
	 */
	Character*		getOwner() { return owner_; }

	/**
	 * @brief		持ち主の取得（const版）
	 * @return		owner		このコントローラの持ち主（const）
	 */
	const Character*	getOwner() const { return owner_; }

	/**
	 * @brief		位置の取得
	 * @return		コントロールした結果の位置
	 */
	const cocos2d::Vec2&	getResultPosition() const { return resultPosition_; }

	/**
	 * @brief		発射判定の取得
	 * @return		コントロールした結果、弾を発射するかの判定を取得
	 */
	Shoot&			getResultShoot() { resultShoot_.received_ = true; return resultShoot_; }
	Shoot&			getResultStrongShoot() { resultShoot_.received_strong_shoot = true; return resultShoot_; }

	/**
	 * @brief		派生クラスのコントローラの取得
	 * @return		パッドコントローラのポインタ（常にnullptr）
	 */
	virtual PadController* getPadController() { return nullptr; }
	/**
	 * @brief		派生クラスのコントローラの取得
	 * @return		AIコントローラのポインタ（常にnullptr）
	 */
	virtual AIController* getAIController() { return nullptr; }
	/**
	 * @brief		派生クラスのコントローラの取得
	 * @return		リモートコントローラのポインタ（常にnullptr）
	 * @note		ネットワークマルチプレイなどの対応時に使用する。今回は使用しない
	 */
	virtual RemoteController* getRemoteController() { return nullptr; }

protected:
	SafePointer<Character>	owner_;					//!< 持ち主のポインタ
	cocos2d::Vec2			resultPosition_;		//!< 結果の位置
	Shoot					resultShoot_;			//!< 結果の発射


private:
};
