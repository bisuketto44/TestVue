/**
 * @file    character_manager.cpp
 *
 * @brief   キャラクターの管理クラス
 * @details Character（の派生クラス）が生成されるとこのマネージャの管理下に置かれる
 *          Characterをリストで保持し、定期的にupdate()する。またコリジョン判定をする機能も持つ
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */

#include "manager/ui_manager.h"
#include "game.h"


 /**
  * @brief		コンストラクタ
  */
UiManager::UiManager()
{
}

/**
 * @brief		デストラクタ
 */
UiManager::~UiManager()
{
}


/**
 * @brief		描画の更新(stageScneneで呼ばれる)
 */
void UiManager::updateUI()
{

	// 管理下のすべてのUIを管理
	for (auto itr = objectList_.begin(); itr != objectList_.end(); ++itr)
	{
		SafePointer<Ui> ui = *itr;

		//リリースされていたら処理をスキップ(アクティブでないUIは対象外)
		if (!ui->isActive())
		{
			continue;
		}

		//各UIのアップデート監視して呼ぶ
		ui->DrawingUpdate();
		
	}

}