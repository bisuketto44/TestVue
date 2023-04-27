/**
 * @file    game_pad.h
 *
 * @brief   ゲームパット
 * @details ゲームパッドの情報を取得するクラス
 *          Xbox360のパッドを使用することを想定した実装にしています
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */

#pragma once

#include <cocos2d.h>
#include "utility/macro.h"


/**
 * @brief	ボタンが押された状態かを取得するマクロ
 */
#define PAD_BT_ON(index, button)			((GamePad::getInstance()->getPadStatus(index).button_.on_ & (button)) != 0)

/**
 * @brief	ボタンを押したときのトリガを取得するマクロ
 */
#define PAD_BT_PRESS(index, button)			((GamePad::getInstance()->getPadStatus(index).button_.press_ & (button)) != 0)

/**
 * @brief	ボタンを離したときのトリガを取得するマクロ
 */
#define PAD_BT_RELEASE(index, button)		((GamePad::getInstance()->getPadStatus(index).button_.release_ & (button)) != 0)

/**
 * @brief	スティックの値を取得するマクロ
 */
#define PAD_ST(index, stick)				(GamePad::getInstance()->getPadStatus(index).stick_[stick].value_)


/**
 * @brief	ゲームパッドクラス
 */
class GamePad
{
public:
	const static uint32_t GAME_PAD_MAX = GLFW_JOYSTICK_LAST;		//!< ゲームパッドの最大数

	/**
	 * @brief	ボタンのインデックス定義
	 * @note	これらを直接使用することはほぼ無い（下記のBUTTON_MASKのために定義している）
	 */
	enum BUTTON
	{
		BUTTON_A,			//!< Aボタン
		BUTTON_B,			//!< Bボタン
		BUTTON_X,			//!< Xボタン
		BUTTON_Y,			//!< Yボタン
		BUTTON_LB,			//!< Lボタン（L1）
		BUTTON_RB,			//!< Rボタン（R1）
		BUTTON_START,		//!< Startボタン
		BUTTON_BACK,		//!< Backボタン（SELECTボタン）
		BUTTON_UP,			//!< 十字ボタン上
		BUTTON_DOWN,		//!< 十字ボタン下
		BUTTON_LEFT,		//!< 十字ボタン左
		BUTTON_RIGHT,		//!< 十字ボタン右

		BUTTON_NUM
	};

	/**
	 * @brief	ボタンのビットマスク定義
	 * @note	ボタンが押されているかなどを調べるときはこちらを使う
	 */
	enum BUTTON_MASK
	{
		BT_A			= 1 << BUTTON_A,		//!< Aボタン
		BT_B			= 1 << BUTTON_B,		//!< Bボタン
		BT_X			= 1 << BUTTON_X,		//!< Xボタン
		BT_Y			= 1 << BUTTON_Y,		//!< Yボタン
		BT_LB			= 1 << BUTTON_LB,		//!< Lボタン（L1）
		BT_RB			= 1 << BUTTON_RB,		//!< Rボタン（R1）
		BT_START		= 1 << BUTTON_START,	//!< Startボタン
		BT_BACK			= 1 << BUTTON_BACK,		//!< Backボタン（SELECTボタン）
		BT_UP			= 1 << BUTTON_UP,		//!< 十字ボタン上
		BT_DOWN			= 1 << BUTTON_DOWN,		//!< 十字ボタン下
		BT_LEFT			= 1 << BUTTON_LEFT,		//!< 十字ボタン左
		BT_RIGHT		= 1 << BUTTON_RIGHT,	//!< 十字ボタン右

		BT_ALL			= 0xffffffff			//!< すべてのボタンのビットマスク
	};

	/**
	 * @brief	スティックのインデックス定義
	 */
	enum STICK
	{
		STICK_L_X,			//!< 左スティック横(値 -1.0f ～ 1.0f)
		STICK_L_Y,			//!< 左スティック縦(値 -1.0f ～ 1.0f)
		STICK_R_X,			//!< 右スティック横(値 -1.0f ～ 1.0f)
		STICK_R_Y,			//!< 右スティック縦(値 -1.0f ～ 1.0f)
		STICK_TL,			//!< Lトリガー(値 0.0f ～ 1.0f)
		STICK_TR,			//!< Rトリガー(値 0.0f ～ 1.0f)

		STICK_NUM			//!< スティック数（縦横は個別に数える）
	};

	/**
	 * @brief	ゲームパッドの状態
	 */
	struct Status
	{
		/**
		 * @brief	ボタンの状態
		 */
		struct Button
		{
			uint32_t	on_;			//!< 押しているとBUTTON_MASKの対応するBitがtrue
			uint32_t	press_;			//!< 押したフレームのみBUTTON_MASKの対応するBitがtrue
			uint32_t	release_;		//!< 離したフレームのみBUTTON_MASKの対応するBitがtrue
		};

		/**
		 * @brief	スティックの状態
		 */
		struct Stick
		{
			float		value_;			// 値
		};

		Button		button_;			//!< ボタンの状態
		Stick		stick_[STICK_NUM];	//!< スティックの状態の配列
	};

	/**
	 * @brief		シングルトンインスタンスの取得
	 * @return		ゲームパッドクラスインスタンス
	 */
	static GamePad* getInstance() { APP_ASSERT(instance__ != nullptr, "GamePad is not created."); return instance__; }

	// ゲームパッドの生成
	static GamePad* create();

	// ゲームパッドの破棄
	static void destroy();

	// 更新処理
	virtual void update();

	// 接続されているパッドの数を取得
	uint32_t getPadNum();

	/**
	 * @brief		パッドの状態を取得
	 * @param[in]	index		状態を取得するパッドのインデックス（省略すると0）
	 * @return		パッドの状態
	 */
	virtual const Status& getPadStatus(uint32_t index = 0) const { return device_[index].getPadStatus(); }

protected:
	// コンストラクタ
	GamePad();

	// デストラクタ
	virtual ~GamePad() {};

private:
	static GamePad* instance__;				//!< インスタンスのポインタ

	/**
	 * @brief		パッドデバイスを扱うクラス
	 */
	class Device
	{
	public:
		// コンストラクタ
		Device();

		// 更新
		void update();

		/**
		 * @brief		パッドを管理するためのインデックス値を設定
		 * @param[in]	index		インデックス値
		 */
		void setIndex( int32_t index) { index_ = index; }

		/**
		 * @brief		パッドの状態を取得
		 * @return		パッドの状態
		 */
		const Status& getPadStatus() const { return status_; }

		// パッドが有効かを取得
		bool isAlive();

	private:
		/**
		 * @brief		ボタンのインデックス（Xbox360パッドの並び）
		 * @note		360パッドの各ボタンとBUTTONの照合のために定義
		 */
		enum BUTTON_ID
		{
			BUTTON_ID_A		=  0,		//!< Aボタン
			BUTTON_ID_B		=  1,		//!< Bボタン
			BUTTON_ID_X		=  2,		//!< Xボタン
			BUTTON_ID_Y		=  3,		//!< Yボタン
			BUTTON_ID_LB	=  4,		//!< Lボタン（L1）
			BUTTON_ID_RB	=  5,		//!< Rボタン（R1）
			BUTTON_ID_START	=  7,		//!< Startボタン
			BUTTON_ID_BACK	=  6,		//!< Backボタン（SELECTボタン）
			BUTTON_ID_UP	= 10,		//!< 十字ボタン上
			BUTTON_ID_DOWN	= 12,		//!< 十字ボタン下
			BUTTON_ID_LEFT	= 13,		//!< 十字ボタン左
			BUTTON_ID_RIGHT	= 11,		//!< 十字ボタン右
		};

		/**
		 * @brief		スティックのインデックス（Xbox360パッドの並び）
		 * @note		360パッドの各スティックとSTICKの照合のために定義
		 */
		enum STICK_ID
		{
			STICK_ID_L_X	= 0,		//!< 左スティック横(値 -1.0f ～ 1.0f)
			STICK_ID_L_Y	= 1,		//!< 左スティック縦(値 -1.0f ～ 1.0f)
			STICK_ID_R_X	= 2,		//!< 右スティック横(値 -1.0f ～ 1.0f)
			STICK_ID_R_Y	= 3,		//!< 右スティック縦(値 -1.0f ～ 1.0f)
			STICK_ID_TL		= 4,		//!< Lトリガー(値 0.0f ～ 1.0f)
			STICK_ID_TR		= 5,		//!< Rトリガー(値 0.0f ～ 1.0f)
		};

		int32_t		index_;				//!< ゲームパッドのインデックス
		Status		status_;			//!< ゲームパッドの状態
	};

	Device device_[GAME_PAD_MAX];		//!< デバイスの配列
};
