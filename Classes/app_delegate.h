/**
 * @file    app_delegate.h
 *
 * @brief   デリゲートクラス
 * @details システムとの橋渡しになるクラス
 *          ※元はAppDelegate.cppというファイル名のcocos2d-xが自動生成したファイルです
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */

#pragma once

#include <cocos2d.h>


/**
 * @brief	デリゲートクラス
 */
class AppDelegate : private cocos2d::Application
{
public:
	// コンストラクタ
	AppDelegate();
	// デストラクタ
	virtual ~AppDelegate();

	// GraphicsLibraryのコンテキストアトリビュートの初期化
	virtual void initGLContextAttrs();

	// アプリケーションの初期化が終わった時に呼び出される関数（アプリケーションのスタート関数）
	virtual bool applicationDidFinishLaunching();

	// アプリケーションがバックグラウンド実行になった時に呼び出される関数
	virtual void applicationDidEnterBackground();

	// アプリケーションがフォアグランドに復帰した時に呼び出される関数
	virtual void applicationWillEnterForeground();
};
