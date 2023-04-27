/**
 * @file    game_pad.cpp
 *
 * @brief   ゲームパット
 * @details ゲームパッドの情報を取得するクラス
 *          Xbox360のパッドを使用することを想定した実装にしています
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */

#include "utility/macro.h"
#include "utility/game_pad.h"
#include "utility/key_emulation/key_emulation_game_pad.h"


//! インスタンスのポインタ
GamePad* GamePad::instance__ = nullptr;

/**
 * @brief		ゲームパッドの生成
 * @return		ゲームパッドクラスインスタンス
 */
GamePad* GamePad::create()
{
	//	生成済みのゲームパッドがあれば消す。念のため。
	APP_SAFE_DELETE(instance__);

	// ゲームパッド0番に接続があるかチェック
	if(glfwJoystickPresent(0) != 0)
	{
		//	接続があれば通常ゲームパッド生成
		instance__ = APP_NEW(GamePad);
	}
	else
	{
		//	接続がなければキーボード入力でエミュレート
		instance__ = APP_NEW(KeyEmulationGamePad);
	}

	return instance__;
}

/**
 * @brief		ゲームパッドの破棄
 */
void GamePad::destroy()
{
	// パッドの解放
	APP_SAFE_DELETE(instance__);
	instance__ = nullptr;
}

/**
 * @brief		コンストラクタ
 */
GamePad::GamePad()
{
	// デバイスクラスにインデックスをセット
	for(uint32_t index=0; index<GAME_PAD_MAX; index++)
		device_[index].setIndex(index);
}


/**
 * @brief		更新
 */
void GamePad::update()
{
	// デバイスの更新
	for(uint32_t index=0; index<GAME_PAD_MAX; index++)
		device_[index].update();
}


/**
 * @brief		PCに接続されたパッド数の取得
 * @return		パッド数
 */
uint32_t GamePad::getPadNum()
{
	uint32_t count = 0;

	// 有効なデバイスの数を数える
	for(uint32_t index=0; index<GAME_PAD_MAX; index++)
		if(device_[index].isAlive()) count++;

	return count;
}


/**
 * @brief		コンストラクタ
 */
GamePad::Device::Device()
 : index_(-1)
{
	// ボタン情報のクリア
	status_.button_.on_      = 0;
	status_.button_.press_   = 0;
	status_.button_.release_ = 0;

	// スティック情報のクリア
	for(uint32_t stick=0; stick<STICK_NUM; stick++)
		status_.stick_[stick].value_ = 0.0f;
}


/**
 * @brief		更新
 * @details		システムから各パッドの入力情報を取得
 */
void GamePad::Device::update()
{
	// 有効なパッドのみ処理
	if(!isAlive())
		return;

	// デバイスからパッド情報を取得
	int32_t buttonNum;
	int32_t axisNum;
	const unsigned char* buttons;
	const float* axes;
	buttons = glfwGetJoystickButtons(index_, &buttonNum);
	axes = glfwGetJoystickAxes(index_, &axisNum);

	// 対応していないゲームパッドの確認
	if(buttonNum < BUTTON_NUM || axisNum < STICK_NUM)
		return;

	// ボタン情報をstatusにセット
	uint32_t old = status_.button_.on_;
	status_.button_.on_ = 0;
	if(buttons[BUTTON_ID_A])     status_.button_.on_ |= BT_A;
	if(buttons[BUTTON_ID_B])     status_.button_.on_ |= BT_B;
	if(buttons[BUTTON_ID_X])     status_.button_.on_ |= BT_X;
	if(buttons[BUTTON_ID_Y])     status_.button_.on_ |= BT_Y;
	if(buttons[BUTTON_ID_LB])    status_.button_.on_ |= BT_LB;
	if(buttons[BUTTON_ID_RB])    status_.button_.on_ |= BT_RB;
	if(buttons[BUTTON_ID_START]) status_.button_.on_ |= BT_START;
	if(buttons[BUTTON_ID_BACK])  status_.button_.on_ |= BT_BACK;
	if(buttons[BUTTON_ID_UP])    status_.button_.on_ |= BT_UP;
	if(buttons[BUTTON_ID_DOWN])  status_.button_.on_ |= BT_DOWN;
	if(buttons[BUTTON_ID_LEFT])  status_.button_.on_ |= BT_LEFT;
	if(buttons[BUTTON_ID_RIGHT]) status_.button_.on_ |= BT_RIGHT;

	// ボタンのトリガ情報を生成
	// --- ボタンを押したフレーム、放したフレームのみビットを立てる
	status_.button_.press_   = (old ^ status_.button_.on_) & status_.button_.on_;		// 直前と変わってる＆ONのビット
	status_.button_.release_ = (old ^ status_.button_.on_) & (~status_.button_.on_);	// 直前と変わってる＆OFFのビット

	// スティック情報をstatusにセット
	status_.stick_[STICK_L_X].value_ = axes[STICK_ID_L_X];
	status_.stick_[STICK_L_Y].value_ = axes[STICK_ID_L_Y];
	status_.stick_[STICK_R_X].value_ = axes[STICK_ID_R_X];
	status_.stick_[STICK_R_Y].value_ = axes[STICK_ID_R_Y];
	status_.stick_[STICK_TL].value_  = axes[STICK_ID_TL] * 0.5f + 0.5f;
	status_.stick_[STICK_TR].value_  = axes[STICK_ID_TR] * 0.5f + 0.5f;
}


/**
 * @brief		パッドが有効か（使用可能か）を確認
 * @return		true 有効／false 無効
 */
bool GamePad::Device::isAlive()
{
	// デバイスに割り当てられたインデックスのパッドが有効かを確認
	return (glfwJoystickPresent(index_) != 0);
}
