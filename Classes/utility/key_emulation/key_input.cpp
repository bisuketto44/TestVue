/**
* @file    key_input.h
*
* @brief   キーボード入力クラス
*
* @author  Tanaka Satoshi
* @date    2017/05/23
* @note    マーベラス開発部新人研修C++演習用
*/
#include "key_input.h"

#include "utility/macro.h"


namespace keyboard
{
	/**
	 * @brief		コンストラクタ
	 */
	KeyboardInput::KeyboardInput()
	{
		cocos2d::Director* director = cocos2d::Director::getInstance();

		//	キー操作イベントリスナ設定
		auto keyEventListener = cocos2d::EventListenerKeyboard::create();

		keyEventListener->onKeyPressed	= CC_CALLBACK_2(KeyboardInput::keyPressedCallback, this);
		keyEventListener->onKeyReleased	= CC_CALLBACK_2(KeyboardInput::keyReleasedCallback,this);

		//	スプライトへのイベントディスパッチ直前に処理を走らせる
		director->getEventDispatcher()->addEventListenerWithFixedPriority(
			keyEventListener, KEYBOARD_INPUT_EVENT_PRIORITY
		);
	}

	/**
	 * @brief	毎フレーム処理前更新
	 * @note	入力更新->入力瞬間の判定->ゲーム処理->入力状態クリア　の流れを保つ
	 */
	void KeyboardInput::update()
	{
		//	keyStatusは[cocos2dのキーコード => キー状態]のペア
		for(auto& keyStatus : keyStatusTable_)
		{
			//	コード見やすくするための参照代入
			KeyStatus& status = keyStatus.second;

			//	直前情報保存、現在の入力を反映
			status.prevOn_		= status.state_.on_;
			status.state_.on_	= status.currentOn_;

			//	直前での入力と現在の入力を比較し、押された/離された瞬間を取得
			// 直前と変わってる&入力ON
			status.state_.press_	= (status.prevOn_ != status.state_.on_) && status.state_.on_;
			// 直前と変わってる&入力OFF
			status.state_.release_ = (status.prevOn_ != status.state_.on_) && (!status.state_.on_);
		}
	}

	/**
	 * @brief		キーが押された際のコールバック
	 * @param[in]	keyCode	入力キーコード
	 * @param[in]	event	発生イベント、キーボードイベントを受ける
	 */
	void KeyboardInput::keyPressedCallback(KEY_CODE keyCode, cocos2d::Event * event)
	{
		keyStatusTable_[keyCode].currentOn_ = true;
	}

	/**
	* @brief		キーが離された際のコールバック
	* @param[in]	keyCode	入力キーコード
	* @param[in]	event	発生イベント、キーボードイベントを受ける
	*/
	void KeyboardInput::keyReleasedCallback(KEY_CODE keyCode, cocos2d::Event * event)
	{
		keyStatusTable_[keyCode].currentOn_ = false;
	}
}
