/**
 * @file    app_define.cpp
 *
 * @brief   アプリケーション全体の定数定義
 * @details 小規模なアプリなのでここで一括で持ってしまう。
            規模が大きくなるならカテゴリ分けしてテーブル化した方がいい
            数値をヘッダ側に書いていないのは整数型以外はコンパイルエラーになるため。
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */

#pragma once

#include <stdint.h>


/**
 * @brief	定数定義クラス
 */
class AppDef
{
public:
	//! updateが呼ばれる単位時間
	const static float		UPDATE_INTERVAL_TIME;

	//! ウインドウサイズ（幅）
	const static int		WINDOW_SIZE_WIDTH;
	//! ウインドウサイズ（高さ）
	const static int		WINDOW_SIZE_HEIGHT;

	//! フィールドの大きさ（幅）
	const static float		FIELD_SIZE_WIDTH;
	//! フィールドの大きさ（高さ）
	const static float		FIELD_SIZE_HEIGHT;

	//! プレイヤーの初期位置（横）
	const static float		PLAYER_START_POSITION_X;
	//! プレイヤーの初期位置（縦）
	const static float		PLAYER_START_POSITION_Y;


	//! 標準的なキャラクターの大きさ（幅）
	const static float		STANDERD_CHARACTER_SIZE_WIDTH;
	//! 標準的なキャラクターの大きさ（高さ）
	const static float		STANDERD_CHARACTER_SIZE_HEIGHT;

	//! 標準的なキャラクターの移動速度
	const static float		STANDERD_CHARACTER_SPEED;

	//! 標準的なキャラクターの攻撃発生位置オフセット（縦）
	const static float		STANDERD_CHARACTER_ATTACK_POSITION_OFFSET_X;
	//! 標準的なキャラクターの攻撃発生位置オフセット（横）
	const static float		STANDERD_CHARACTER_ATTACK_POSITION_OFFSET_Y;

	//! 標準的なキャラクターのコリジョン半径
	const static float		STANDERD_CHARACTER_COLLISION_RADIUS;


	//! 標準的な弾の速度
	const static float		STANDERD_BULLET_SPEED;

	//! 標準的な弾のコリジョン半径
	const static float		STANDERD_BULLET_COLLISION_RADIUS;


	//! Mob01の初期待機時間
	const static float		MOB01_FIRST_STAY_TIME;

	//! Mob01の移動アクション時間
	const static float		MOB01_MOVE_ACTION_TIME;

	//キャラクター達のHP
	const static int        ASUKA_HP;
	const static int        MOB01_HP;
};
