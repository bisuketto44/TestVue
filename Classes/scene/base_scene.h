/**
 * @file    base_scene.cpp
 *
 * @brief   シーンの基底クラス
 * @details シーンを作成したいときに基底とする抽象クラス
 *          Entityの管理、CharacterManagerの管理、BulletManagerの管理を行う
 *          cocos2d::Layerもこのクラスが保持している
 *          ※クラス名は他にならってSceneとするべきだが、cocos2d::Sceneとかぶるのでこの名とした
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */

#pragma once

#include <cocos2d.h>


class CharacterManager;
class BulletManager;
class UiManager;
class Entity;

/**
 * @brief	シーンの基底クラス
 */
class BaseScene : public cocos2d::Scene
{
public:
	// 初期化
	virtual bool init();

	// 毎フレームの更新（このクラスのUpdate）
	void updateBase(float frame);

	/**
	 * @brief		更新
	 * @param[in]	deltaTime		前フレームから進行した時間（単位：秒）
	 * @note		"=0" が付いていると純粋仮想関数になり、継承先で必ず実装する必要がある。
	 */
	void update(float frame) = 0;	// 純粋仮想関数

	/**
	 * @brief		レイヤーの取得
	 * @return		レイヤーのポインタ
	 */
	cocos2d::Layer* getLayer()	{ return layer_; }
	cocos2d::Layer* getuILayer() { return uILayer_; }

	/**
	 * @brief		子へ追加（子の追加はレイヤーに追加）
	 * @param[in]	node		追加したい子
	 * @note		Entityを生成すると自動的にaddChild()が呼ばれるのでこの関数をそれ以外の個所で使用することはないはず
	 */
	void addChild(cocos2d::Node* node) { return layer_->addChild(node); }

	/**
	 * @brief		子へ追加（子の追加はレイヤーに追加）
	 * @param[in]	node		追加したい子
	 * @param[in]	zOrder		Z値（描画順番）
	 * @note		Entityを生成すると自動的にaddChild()が呼ばれるのでこの関数をそれ以外の個所で使用することはないはず
	 * @note		背景などを表示する場合はこちらの関数でZ値を渡す必要が出るかもしれません。
	 */
	void addChild(cocos2d::Node* node, int zOrder) { return layer_->addChild(node, zOrder); }

	/**
	 * @brief		シーン開始からのタイマーの取得
	 * @return		シーン開始からのタイマー（単位：秒）
	 */
	float getTimer() const		{ return timer_; }

	/**
	 * @brief		ポーズ状態の設定
	 * @param[in]	isPause		ポーズ状態（true ポーズ／false 動作）
	 */
	void setPause(bool isPause)	{ isPause_ = isPause; }
	/**
	 * @brief		ポーズ状態の取得
	 * @return		ポーズ状態（true ポーズ／false 動作）
	 */
	bool isPause() const		{ return isPause_; }

	/**
	 * @brief		Entityを削除リストに追加
	 * @param[in]	entity		削除したいEntity
	 * @details		この関数を呼ぶと、次のフレームにEntityが解放されます。
	 * @note		Entityを即座に解放すると、Entityやそのリソースを参照している処理で不具合が起きることが多いためこのような遅延解放の仕組みを実装します。
	 */
	void addReleaseEntity(Entity* entity) { releaseList_.push_back(entity); }

	/**
	 * @brief		キャラクターマネージャの取得
	 * @return		キャラクターマネージャのポインタ（基底では常にnullptr）
	 * @note		継承先でキャラクターマネージャを使う場合は継承先でこの関数をオーバーライドする
	 */
	virtual CharacterManager*	getCharacterManager()	{ return nullptr; }

	/**
	 * @brief		弾マネージャの取得
	 * @return		弾マネージャのポインタ（基底では常にnullptr）
	 * @note		継承先で弾マネージャを使う場合は継承先でこの関数をオーバーライドする
	 */
	virtual BulletManager*		getBulletManager()		{ return nullptr; }
	/**
	* @brief		UIマネージャの取得
	* @return		UIマネージャのポインタ
	*/
	virtual UiManager*		    getUiManager() { return nullptr; }

	

private:
	SafePointer<cocos2d::Layer>		layer_;				//!< レイヤーのポインタ
	SafePointer<cocos2d::Layer>     uILayer_;           //!< 固定UIレイヤーのポインタ

	float							timer_;				//!< シーン開始からのタイマー
	bool							isPause_;			//!< シーンのポーズ状態

	std::vector<Entity*>			releaseList_;		//!< Entityの削除リスト
};
