/**
* @file    key_emulation_game_pad.h
*
* @brief   キーボード入力でゲームパッド入力を置き換えるクラス
*
* @author  Tanaka Satoshi
* @date    2017/05/24
* @note    マーベラス開発部新人研修C++演習用
*/
#pragma once

#include "utility/key_emulation/key_input.h"
#include "utility/game_pad.h"
#include <unordered_map>

/**
* @brief   キーボード入力でゲームパッド入力を置き換えるクラス
*/
class KeyEmulationGamePad : public GamePad
{
	friend GamePad;

private:
	//!	どのキーをどのボタンに割り当てるかを決めるマッピングテーブル
	//!	[キーコード => ボタンのビットマスク]	の連想配列
	using KeyMappingTable = std::unordered_map<keyboard::KEY_CODE, GamePad::BUTTON_MASK>;

	//!	キー -> ボタンの割り当てテーブル
	const static KeyMappingTable	KEY_TO_BUTTON_MAPPING_TABLE;

public:

	// 更新処理
	virtual void update();

	/**
	* @brief		パッドの状態を取得
	* @param[in]	index		状態を取得するパッドのインデックス（省略すると0）
	* @return		パッドの状態
	*/
	virtual const Status& getPadStatus(uint32_t index = 0) const
	{
		return dummyGamePadStatus_; 
	}

	// スティック状態のダミー値取得
	float	getDummyStick(STICK stick);

protected:
	// コンストラクタ
	KeyEmulationGamePad() {};

	// デストラクタ
	virtual ~KeyEmulationGamePad() {};

private:
	/**
	 *	@brief		ダミー状態クリア
	 */
	void	clearDummyPadStatus()
	{
		// ボタン情報のクリア
		dummyGamePadStatus_.button_.on_ = 0;
		dummyGamePadStatus_.button_.press_ = 0;
		dummyGamePadStatus_.button_.release_ = 0;

		// スティック情報のクリア
		for(uint32_t stick = 0; stick<STICK_NUM; stick++)
			dummyGamePadStatus_.stick_[stick].value_ = 0.0f;
	}

	Status	dummyGamePadStatus_;	//!<	ダミーのゲームパッド状態、キー入力で更新される
	keyboard::KeyboardInput keyboardInput_;	//!<	キー入力取得オブジェクト
};
