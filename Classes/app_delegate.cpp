/**
 * @file    app_delegate.cpp
 *
 * @brief   デリゲートクラス
 * @details cocos2dエンジンとの橋渡しになるクラス
 *          ※元はAppDelegate.cppというファイル名のcocos2d-xが自動生成したファイルです
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */


#include "app_delegate.h"
#include "app_define.h"
#include "game.h"


USING_NS_CC;

/**
 * @brief		コンストラクタ
 */
AppDelegate::AppDelegate()
{
}

/**
 * @brief		デストラクタ
 */
AppDelegate::~AppDelegate() 
{
}

/**
 * @brief		GraphicsLibraryのコンテキストアトリビュートの初期化
 * @note		if you want a different context, modify the value of glContextAttrs
 * 				it will affect all platforms
 */
void AppDelegate::initGLContextAttrs()
{
	// set OpenGL context attributes: red,green,blue,alpha,depth,stencil
	GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

	GLView::setGLContextAttrs(glContextAttrs);
}

/**
 * @brief	アプリケーションの初期化が終わった時に呼び出される関数（アプリケーションのスタート関数）
 * @return	true	Initialize success, app continue.
 * @return	false	Initialize failed, app terminate.
 * @note	Implement Director and Scene init code here.
 */
bool AppDelegate::applicationDidFinishLaunching()
{
	// Directorの初期化
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if(!glview)
	{
		glview = GLViewImpl::createWithRect("MyShooting", cocos2d::Rect(0, 0, AppDef::WINDOW_SIZE_WIDTH, AppDef::WINDOW_SIZE_HEIGHT));
		director->setOpenGLView(glview);
	}

	// FPSを設定
	director->setAnimationInterval(AppDef::UPDATE_INTERVAL_TIME);

	// 描画解像度の設定
	glview->setDesignResolutionSize(AppDef::WINDOW_SIZE_WIDTH, AppDef::WINDOW_SIZE_HEIGHT, ResolutionPolicy::NO_BORDER);

	// 縦横比が異なるモニタへの対応（今回は使用しない）
	//director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));

	// ゲーム本体の生成
	Game::create();

	// 正常終了
	return true;
}

/**
 * @brief		アプリケーションがバックグラウンド実行になった時に呼び出される関数
 * @note		This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
 */
void AppDelegate::applicationDidEnterBackground()
{
	Director::getInstance()->stopAnimation();

	// if you use SimpleAudioEngine, it must be paused
	// SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

/**
 * @brief		アプリケーションがフォアグランドに復帰した時に呼び出される関数
 * @note		this function will be called when the app is active again
 */
void AppDelegate::applicationWillEnterForeground()
{
	Director::getInstance()->startAnimation();

	// if you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
