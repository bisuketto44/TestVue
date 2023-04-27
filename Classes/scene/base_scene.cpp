/**
 * @file    base_scene.cpp
 *
 * @brief   シーンの基底クラス
 * @details シーンを作成したいときに基底とするクラス
 *          Entityの管理、CharacterManagerの管理、BulletManagerの管理を行う
 *          cocos2d::Layerもこのクラスが保持している
 *          ※クラス名は他にならってSceneとするべきだが、cocos2d::Sceneとかぶるのでこの名とした
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */

#include "utility/macro.h"
#include "app_define.h"
#include "game.h"
#include "scene/base_scene.h"
#include "entity/entity.h"
#include "utility/game_pad.h"
#include "manager/animation_manager.h"
#include "manager/character_manager.h"
#include "manager/ui_manager.h"

SafePointer<cocos2d::Layer>		layer_2;				//!< レイヤーのポインタ

/**
 * @brief		初期化
 * @return		true 初期化成功／false 初期化失敗
 */
bool BaseScene::init()
{
	CCLOG("BaseScene::init()");

	// まずスーパークラスのinitを呼ぶ
	if( !cocos2d::Scene::init() )
		return false;

	// プレイ用レイヤーを作成し、子とする
	layer_ = cocos2d::Layer::create();
	cocos2d::Node::addChild(layer_);


	//UI用(画面固定)レイヤーを作成
	uILayer_ = cocos2d::Layer::create();
	cocos2d::Node::addChild(uILayer_);

	//2個目のカメラの生成位置を決定
	auto size = cocos2d::Director::getInstance()->getWinSize();
	auto camera = cocos2d::Camera::createOrthographic(1280.0f, 720.0f, -1024, 1024);
	camera->setPosition(cocos2d::Vec2(0.0f, 0.0f));
	camera->setDepth(0.0f);

	//レイヤーの子としてカメラを設定
	uILayer_->addChild(camera);

	//同じマスク上に配置
	uILayer_->setCameraMask((int)cocos2d::CameraFlag::USER1);
	camera->setCameraFlag(cocos2d::CameraFlag::USER1);

	// ステージ開始からの経過時間をクリア
	timer_ = 0.0f;

	// ポーズフラグをクリア
	isPause_ = false;

	// update関数をスケジューラに登録（これで一定時間毎にupdate()が呼ばれるようになる）
	schedule(schedule_selector(BaseScene::updateBase), AppDef::UPDATE_INTERVAL_TIME);

	return true;
}


/**
 * @brief		更新
 * @param[in]	deltaTime		前フレームから進行した時間（単位：秒）
 */
void BaseScene::updateBase(float deltaTime)
{
	// ステージ開始からの経過時間を加算
	timer_ += deltaTime;
//	CCLOG("BaseScene : Time : %f (+%f)", timer_, deltaTime);

	// 削除リストに登録されたエンティティを削除
	// --- entityのupdate中に削除しないことで、参照中に削除されてフリーズする不具合を避ける
	for(auto itr = releaseList_.begin(); itr != releaseList_.end(); ++itr)
		APP_DELETE(*itr);
	releaseList_.clear();

	// ゲームパッドの更新
	GamePad::getInstance()->update();

	// 派生クラスのupdateを呼ぶ
	update(deltaTime);

	// ポーズ時はやらない処理
	if(!isPause_)
	{
		// コリジョン処理の更新
		CharacterManager* characterManager = Game::getInstance()->getCurrentScene()->getCharacterManager();
		if (characterManager)
		{
			characterManager->updateCollide();
		}

		////各UIの描画更新
		//UiManager* uimanager = Game::getInstance()->getCurrentScene()->getUiManager();
		//if (uimanager)
		//{

		//	uimanager->updateUI();
		//}
		
		// アニメーションの更新
		Game::getInstance()->getAnimationManager()->update(deltaTime);
	}
}