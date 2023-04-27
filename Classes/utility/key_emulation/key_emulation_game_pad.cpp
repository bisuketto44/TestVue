/**
* @file    key_emulation_game_pad.cpp
*
* @brief   キーボード入力でゲームパッド入力を置き換えるクラス

* @author  Tanaka Satoshi
* @date    2017/05/24
* @note    マーベラス開発部新人研修C++演習用
*/
#include "key_emulation_game_pad.h"


//!	変数実体定義部、ここに キー=>ボタンのマッピングを記述していく
const KeyEmulationGamePad::KeyMappingTable KeyEmulationGamePad::KEY_TO_BUTTON_MAPPING_TABLE = 
{
	/**		↓のキーコードを			, ↓のボタンに割り当てる	**/
	{ keyboard::KEY_CODE::KEY_Z			,	BT_X		},
	{ keyboard::KEY_CODE::KEY_X			,	BT_A		},
	{ keyboard::KEY_CODE::KEY_C			,	BT_Y		},
	{ keyboard::KEY_CODE::KEY_V			,	BT_B		},
	{ keyboard::KEY_CODE::KEY_SHIFT		,	BT_LB		},
	{ keyboard::KEY_CODE::KEY_RIGHT_SHIFT,	BT_RB		},
	{ keyboard::KEY_CODE::KEY_ENTER		,	BT_START	},
	{ keyboard::KEY_CODE::KEY_BACKSPACE	,	BT_BACK		},

	{ keyboard::KEY_CODE::KEY_UP_ARROW	,	BT_UP		},
	{ keyboard::KEY_CODE::KEY_DOWN_ARROW,	BT_DOWN		},
	{ keyboard::KEY_CODE::KEY_LEFT_ARROW,	BT_LEFT		},
	{ keyboard::KEY_CODE::KEY_RIGHT_ARROW,	BT_RIGHT	},
};


// 更新処理
void KeyEmulationGamePad::update()
{
	//	キー入力更新
	keyboardInput_.update();


	//	ダミーのデバイス状態更新

	//	前フレーム情報をクリア
	clearDummyPadStatus();

	//	ボタン更新
	for(const auto& keyMapping : KEY_TO_BUTTON_MAPPING_TABLE)
	{
		//	キーボード => ボタンbitマスク の対応を取得
		keyboard::KEY_CODE	inputKey = keyMapping.first;
		BUTTON_MASK			buttonMask = keyMapping.second;

		//	マッピングに使うキーの状態を確認
		const auto& keyState = keyboardInput_.getKeyboardState(inputKey);

		//	ボタン情報をstatusにセット
		if(keyState.on_)
			dummyGamePadStatus_.button_.on_ |= buttonMask;

		if(keyState.press_)
			dummyGamePadStatus_.button_.press_ |= buttonMask;

		if(keyState.release_)
			dummyGamePadStatus_.button_.release_ |= buttonMask;
	}

	//	スティック状態更新
	dummyGamePadStatus_.stick_[STICK_L_X].value_ = getDummyStick(STICK_L_X);
	dummyGamePadStatus_.stick_[STICK_L_Y].value_ = getDummyStick(STICK_L_Y);
	dummyGamePadStatus_.stick_[STICK_R_X].value_ = getDummyStick(STICK_R_X);
	dummyGamePadStatus_.stick_[STICK_R_Y].value_ = getDummyStick(STICK_R_Y);
	
	//	未設定
	//dummyGamePadStatus_.stick_[STICK_TL].value_	 = getDummyStick(STICK_TL);
	//dummyGamePadStatus_.stick_[STICK_TR].value_	 = getDummyStick(STICK_TR);
}


/**
* @brief		スティック状態値取得
* @detail		スティックに対応するキーが押されているかに応じ -1,0,+1のいずれかダミー値を返す
* @param[in]	stick		状態を取得するスティック
* @return		スティック状態値
*/
float KeyEmulationGamePad::getDummyStick(STICK stick)
{
	//	とりあえずswitchで分岐して処理
	switch (stick)
	{
	case STICK::STICK_L_X:
		{
			//	左スティックX
			float stickLX = keyboardInput_.getKeyboardState(keyboard::KEY_CODE::KEY_RIGHT_ARROW).on_;
			return (stickLX - keyboardInput_.getKeyboardState(keyboard::KEY_CODE::KEY_LEFT_ARROW).on_);
		}

	case STICK::STICK_L_Y:
		{
			//	左スティックY
			float stickLY = keyboardInput_.getKeyboardState(keyboard::KEY_CODE::KEY_UP_ARROW).on_;
			return (stickLY - keyboardInput_.getKeyboardState(keyboard::KEY_CODE::KEY_DOWN_ARROW).on_);
		}

	case STICK::STICK_R_X:
		{
			//	右スティックX
			float stickRX = keyboardInput_.getKeyboardState(keyboard::KEY_CODE::KEY_A).on_;
			return (stickRX - keyboardInput_.getKeyboardState(keyboard::KEY_CODE::KEY_D).on_);
		}

	case STICK::STICK_R_Y:
		{
			//	右スティックY
			float stickRY = keyboardInput_.getKeyboardState(keyboard::KEY_CODE::KEY_W).on_;
			return (stickRY - keyboardInput_.getKeyboardState(keyboard::KEY_CODE::KEY_S).on_);
		}

	default:
		//	あとは何とか設定しておいてください
		APP_ASSERT(false, "Unknown stick index.");

	}

	return 0.0f;
}
