/**
 * @file    explosion.cpp
 *
 * @brief	爆発エフェクト
 * @details 爆発を表示させる機能
 *
 * @author  Kaifu Koji
 * @date    2017/05/02
 * @note    マーベラス開発部新人研修C++演習用
 */

#include "utility/macro.h"
#include "entity/effect/explosion.h"


/**
 * @brief		爆発エフェクトの再生
 * @param[in]	position		表示位置
 * @param[in]	scale			表示スケール
 * @param[in]	randomScale		スケールにランダムで加減する値
 * @note		生成したEffectはアニメーションの終了時に自動で破棄される
 */
void Explosion::play(const cocos2d::Vec2& position, float scale, float randomScale)
{
	static const Effect::ImageFrame frameTable[] =
	{
		{ "explosion01_01.png",		0.05f },
		{ "explosion01_02.png",		0.05f },
		{ "explosion01_03.png",		0.05f },
		{ "explosion01_04.png",		0.05f },
		{ "explosion01_05.png",		0.05f },
		{ "explosion01_06.png",		0.05f },
		{ "explosion01_07.png",		0.05f },
		{ "explosion01_08.png",		0.05f },
	};

	// テーブルの要素数
	int count = sizeof(frameTable)/sizeof(Effect::ImageFrame);

	// スケールの決定
	scale += (APP_RANDOM_F() - 0.5f) * 2.0f * randomScale;

	// クラスを生成
	Effect::create(frameTable, count, position, scale);
}
