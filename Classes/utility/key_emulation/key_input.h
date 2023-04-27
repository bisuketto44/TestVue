/**
* @file    key_input.h
*
* @brief   キーボード入力クラス。あんまり処理速度気にせず書いちゃってます。
*
* @author  Tanaka Satoshi
* @date    2017/05/23
* @note    マーベラス開発部新人研修C++演習用
*/
#pragma once

#include <cocos2d.h>
#include <unordered_map>


namespace keyboard {

	//!	一々キーコード入れるのにタイプ量が多く面倒なので短く
	using KEY_CODE = cocos2d::EventKeyboard::KeyCode;

	/**
	* @brief	キーボード入力クラス
	*/
	class KeyboardInput
	{
	public:
		/**
		* @brief	キーの状態
		*/
		struct KeyStatus
		{
			/**
			 * @brief	キーのトリガ状態
			 */
			struct State {
				bool on_;			//<!	キーが押されていたらtrue
				bool press_;		//<!	キーが押された瞬間のみtrue
				bool release_;		//<!	キーが離された瞬間のみtrue
			} state_;

			bool prevOn_;		//<!	直前フレームにキーが押されていたらtrue
			bool currentOn_;	//<!	現在フレームの入力状態、入力の瞬間チェック処理のために直接onには代入しない
		};

		/**
		* @brief		指定したキーの状態を取得
		* @param[in]	keyCode		状態を取得するキーコード
		* @return		指定したキーの状態(on/press/release)
		*/
		const KeyStatus::State& getKeyboardState(KEY_CODE keyCode)
		{
			return keyStatusTable_[keyCode].state_;
		}

		// コンストラクタ
		KeyboardInput();

		// 更新処理
		void update();

	private:
		//!	キー入力のイベントリスナ更新優先順
		//!	@see cocos2d::EventDispatcher::addEventListenerWithFixedPriority
		static const int KEYBOARD_INPUT_EVENT_PRIORITY = -1;

		//!	[cocos2dのキーコード => キー状態]の連想配列
		using KeyStatusTable = std::unordered_map<KEY_CODE, KeyStatus>;
		KeyStatusTable keyStatusTable_;

		// キーが押された際のコールバック
		void keyPressedCallback(KEY_CODE keyCode, cocos2d::Event* event);

		// キーが離された際のコールバック
		void keyReleasedCallback(KEY_CODE keyCode, cocos2d::Event* event);
	};
}
