/**
 * @file    character_manager.h
 *
 * @brief   キャラクターの管理クラス
 * @details Character（の派生クラス）が生成されるとこのマネージャの管理下に置かれる
 *          Characterをリストで保持し、定期的にupdate()する。またコリジョン判定をする機能も持つ
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */

#pragma once

#include <cocos2d.h>
#include <list>
#include "manager/manager.h"
#include "game.h"
#include "scene/base_scene.h"
#include "ui.h"
 /**
  * @brief	キャラクターの管理クラス
  */
class UiManager : public Manager<Ui*>
{
public:
	// コンストラクタ
	UiManager();

	// デストラクタ
	virtual ~UiManager();

	void updateUI();

private:


};
