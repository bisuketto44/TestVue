/**
 * @file    game.h
 *
 * @brief   ゲームクラス
 * @details ゲーム全体を管理するクラス
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */

#pragma once

#include <cocos2d.h>


class BaseScene;
class GamePad;
class AnimationManager;

/**
 * @brief	ゲームクラス
 */
class Game
{
public:
	/**
	 * @brief	敵味方の区分の定義
	 */
	enum SIDE
	{
		SIDE_NON,				//!< 対象外（背景など）
		SIDE_PLAYER,			//!< プレイヤー側
		SIDE_ENEMY,				//!< 敵側
		SIDE_HOSTILITY,			//!< 常に敵対（誰にも攻撃的）
		SIDE_FRIENDLY,			//!< 常に友好的（誰にも友好的）

		SIDE_NUM
	};

	/**
	 * @brief	ゲーム終了時の状態結果
	 */
	enum RESULT
	{
		CLEAR,                      //!< ステージをクリア
		GAMEOVER,                   //!< 自機キャラがやられてゲームオーバー
	};

	// ゲーム結果をセット
	void setResult(RESULT result) { currentResult = result; }

	// ゲーム結果を取得
	RESULT getResult() { return currentResult; }

	// ゲームクラスの生成
	static void create();

	/**
	 * @brief		シングルトンインスタンスの取得
	 * @return		ゲームクラスインスタンス
	 */
	static Game* getInstance() { return instance__; }

	// コンストラクタ
	Game();

	// デストラクタ
	~Game();

	// 初期化
	void init();

	/**
	 * @brief		現在のシーンの取得
	 * @return		現在のシーンのポインタ
	 */
	BaseScene* getCurrentScene() { return currentScene_; }

	// シーンの切換え
	void changeScene(BaseScene* scene);

	// シーンの一時切換え
	void pushScene(BaseScene* scene);

	// 一次切換えしたシーンに戻す
	void popScene();

	/**
	 * @brief		アニメ機能のマネージャの取得
	 * @return		アニメ機能のマネージャのポインタ
	 */
	AnimationManager* getAnimationManager() { return animationManager_; }

private:
	static Game*	instance__;				//!< インスタンスのポインタ
	RESULT          currentResult;          //!< 遷移時の結果

	SafePointer<BaseScene>			currentScene_;			//!< 現在有効なシーン
	SafePointer<GamePad>			gamePad_;				//!< ゲームパッドの管理クラス
	SafePointer<AnimationManager>	animationManager_;		//!< アニメ機能のマネージャ
	
};
