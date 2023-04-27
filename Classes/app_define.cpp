/**
 * @file    app_define.cpp
 *
 * @brief   アプリケーション全体の定数定義
 * @details 小規模なアプリなのでここで一括で持ってしまう。
 *          規模が大きくなるならカテゴリ分けしてテーブル化した方がいい
 *          数値をヘッダ側に書いていないのは整数型以外はコンパイルエラーになるため。
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */


#include "app_define.h"


//! updateが呼ばれる単位時間
const float		AppDef::UPDATE_INTERVAL_TIME = 1.0f / 60.0f;

//! ウインドウサイズ（幅）
const int		AppDef::WINDOW_SIZE_WIDTH  = 1280;
//! ウインドウサイズ（高さ）
const int		AppDef::WINDOW_SIZE_HEIGHT = 720;

//! プレイヤーの初期位置（横）
const float		AppDef::PLAYER_START_POSITION_X = 1250.f;
//! プレイヤーの初期位置（縦）
const float		AppDef::PLAYER_START_POSITION_Y = 1250.f;		// 真ん中

//! フィールドの大きさ（幅）
const float		AppDef::FIELD_SIZE_WIDTH = 2500.0f;
//! フィールドの大きさ（高さ）
const float		AppDef::FIELD_SIZE_HEIGHT = 2500.0f;


//! 標準的なキャラクターの大きさ（幅）
const float		AppDef::STANDERD_CHARACTER_SIZE_WIDTH  = 72;
//! 標準的なキャラクターの大きさ（高さ）
const float		AppDef::STANDERD_CHARACTER_SIZE_HEIGHT = 72;

//! 標準的なキャラクターの移動速度
const float		AppDef::STANDERD_CHARACTER_SPEED = 300.0f;

//! 標準的なキャラクターの攻撃発生位置オフセット（縦）
const float		AppDef::STANDERD_CHARACTER_ATTACK_POSITION_OFFSET_X = 40.0f;

//! 標準的なキャラクターの攻撃発生位置オフセット（横）
const float		AppDef::STANDERD_CHARACTER_ATTACK_POSITION_OFFSET_Y = -10.0f;

//! 標準的なキャラクターのコリジョン半径
const float		AppDef::STANDERD_CHARACTER_COLLISION_RADIUS = 40.0f;

//! 標準的な弾の速度
const float		AppDef::STANDERD_BULLET_SPEED = 1000.0f;

//! 標準的な弾のコリジョン半径
const float		AppDef::STANDERD_BULLET_COLLISION_RADIUS = 5.0f;


//! Mob01の初期待機時間
const float		AppDef::MOB01_FIRST_STAY_TIME = 0.5f;

//! Mob01の移動アクション時間
const float		AppDef::MOB01_MOVE_ACTION_TIME = 1.0f;

const int       AppDef::ASUKA_HP = 100;

const int       AppDef::MOB01_HP = 100;
