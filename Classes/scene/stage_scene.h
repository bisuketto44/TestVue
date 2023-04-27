/**
 * @file    stage_scene.h
 *
 * @brief   ステージシーンのクラス
 * @details シューティングゲームのステージ
 *          敵の登場などステージの進行管理などを行う
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */

#pragma once

#include <cocos2d.h>
#include "base_scene.h"


class PadController;
class Sequencer;

/**
 * @brief	ステージシーンのクラス
 */
class StageScene : public BaseScene
{
public:
	/**
	 * @brief	ステート
	 */
	enum STATE
	{
		STATE_INIT,					//!< 初期化中
		STATE_ACTIVE,				//!< アクティブ中
		STATE_PAUSE,				//!< ポーズ中

		STATE_NUM
	};

	// cocos2dのcreate関数
	CREATE_FUNC(StageScene);

	// コンストラクタ
	StageScene();
	// デストラクタ
	virtual ~StageScene();

	// 初期化
	virtual bool init();

	// 更新
	void update(float frame);

	/**
	 * @brief		キャラクターマネージャの取得
	 * @return		キャラクターマネージャのポインタ
	 */
	virtual CharacterManager*	getCharacterManager()	{ return characterManager_; }
	/**
	 * @brief		弾マネージャの取得
	 * @return		弾マネージャのポインタ
	 */
	virtual BulletManager*		getBulletManager()		{ return bulletManager_; }
	/**
	 * @brief		UIマネージャの取得
	 * @return		UIマネージャのポインタ
	 */
	virtual UiManager*		    getUiManager()          { return uiManager_; }


private:
	STATE				state_;						//!< ステート

	SafePointer<CharacterManager>	characterManager_;			//!< キャラクターマネージャのポインタ
	SafePointer<BulletManager>		bulletManager_;				//!< 弾マネージャのポインタ
	SafePointer<UiManager>          uiManager_;                 //!< UIマネージャのポインタ
	SafePointer<Sequencer>			sequencer_;					//!< シーケンサ（時間によるステージ進行管理）
	SafePointer<cocos2d::Label>		pauseLabel_;                //!< ポーズ中のテキスト表示のためのラベルのポインタ
	
};
