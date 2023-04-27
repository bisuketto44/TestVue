/**
 * @file    manager.h
 *
 * @brief   マネージャの基底クラス
 * @details 何かを管理するマネージャの基底クラス
 *          管理対象をリストで保持し、定期的にupdate()するための機能を持つ
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */

#pragma once

#include <cocos2d.h>
#include <list>

/**
 * @brief	マネージャの基底クラス（テンプレート）
 * @note	管理する対象を可変にするためにテンプレートを使用しています。
 * @note	マネージャを新しく追加しない限りはテンプレートについて理解している必要はありません。
 */
template<typename T>
class Manager
{
public:
	/**	
	 * @brief		コンストラクタ
	 */
	Manager() {}
	/**
	 * @brief		デストラクタ
	 */
	virtual ~Manager()
	{
		// 管理下のオブジェクトを解放
		// --- ここで解放されては困るものについては事前にマネージャからremoveしておくこと
		for(auto itr = objectList_.begin(); itr != objectList_.end(); ++itr)
			(*itr)->releaseRequest();
	}

	/**
	 * @brief		管理するオブジェクトの追加登録
	 * @param[in]	object		管理したいオブジェクト（Tは継承先のクラス宣言で<～>の形で指定される）
	 */
	void add(T object)
	{
		// リストに追加
		objectList_.push_back(object);
	}

	/**
	 * @brief		管理するオブジェクトの登録抹消
	 * @param[in]	object		登録抹消したいオブジェクト
	 * @note		ここではマネージャへの登録を抹消するだけでオブジェクトの解放はしていない
	 */
	void remove(T object)
	{
		// リストから一致するものを探して登録抹消
		for(auto itr = objectList_.begin(); itr != objectList_.end(); ++itr)
		{
			if(*itr == object)
			{
				objectList_.erase(itr);
				break;
			}
		}
	}

	/**
	 * @brief		更新
	 * @param[in]	deltaTime		前フレームから進行した時間（単位：秒）
	 */
	virtual void update(float deltaTime)
	{
		// 管理下のすべてのオブジェクトを更新
		// --- 単純に登録されたオブジェクトをupdateしていくだけ
		// --- それ以外のことをしたい場合はupdateをオーバーライドする
		for(auto itr = objectList_.begin(); itr != objectList_.end(); )
		{
			(*itr)->update(deltaTime);

			// (*itr)->update()内で解放リクエストが出ていないかチェック
			if((*itr)->isReleased())
			{
				// 解放リクエストが出ていたらリストから消去
				itr = objectList_.erase(itr);
			} else {
				// 出ていなければ次に進む
				++itr;
			}
		}
	}

protected:
	std::list<T>	objectList_;			//!< 管理対象のオブジェクトのリスト

private:
};
