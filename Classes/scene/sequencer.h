/**
 * @file    sequencer.h
 *
 * @brief   シーケンサのクラス
 * @details 時間によるステージ進行を管理するクラス
 *
 * @author  Kaifu Koji
 * @date    2018/04/06
 * @note    マーベラス開発部新人研修C++演習用
 */

#pragma once

#include <cocos2d.h>
#include "game.h"



/**
 * @brief	シーケンサのクラス
 */
class Sequencer
{
public:
	/**
	 * @brief		トリガ
	 * @note		時間が来たら発動する処理
	 */
	class Trigger
	{
	public:
		// トリガタイプ
		// --- 時間進行に応じて何かをしたい場合はこのIDを追加する
		enum TYPE
		{
			TYPE_MOB01_APPEAR_PATTERN01,					//!< MOB01登場 パターン01
			TYPE_MOB02_APPEAR_PATTERN01,                    //!< MOB02登場 パターン02
			TYPE_WIPED_OUT_DETECTION,				        //!< 敵キャラの全滅検知を開始する
			TYPE_STAGE_CLEAR,								//!< ステージクリア

			TYPE_TABLE_END,									//!< シーケンステーブルの終端

			TYPE_NUM
		};

		TYPE					type_;					//!< タイプ
		float					intervalTime_;			//!< 直前のトリガとの間隔

		// トリガの実行
		void execute();
	};

	// コンストラクタ
	Sequencer(const Trigger* triggerTable);

	// デストラクタ
	virtual ~Sequencer();

	// 更新
	bool update(float deltaTime);

private:
	float					timer_;				//!< タイマー（直前のトリガから）
	int						currentIndex_;		//!< 今実行しているトリガのインデックス
	std::vector<Trigger>	triggerTable_;		//!< トリガテーブル
};
