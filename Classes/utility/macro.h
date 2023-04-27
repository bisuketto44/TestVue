/**
 * @file    macro.h
 *
 * @brief   汎用のマクロ
 * @details アプリケーション内で汎用的に使用するマクロ定義
 *
 * @author  Kaifu Koji
 * @date    2017/04/03
 * @note    マーベラス開発部新人研修C++演習用
 */

// 

#pragma once


// メモリ回り

/**
 * @brief	newのラッパーマクロ
 * @note	メモリ管理のため、メモリ回りの関数は直接呼び出さずにマクロを使用する
 */
#define	APP_NEW					new

/**
 * @brief	deleteのラッパーマクロ
 * @note	メモリ管理のため、メモリ回りの関数は直接呼び出さずにマクロを使用する
 * @note	特に理由が無ければAPP_SAFE_DELETEの方を使うこと
 */
#define	APP_DELETE(ptr)			delete(ptr);

/**
 * @brief	配列のdeleteのラッパーマクロ
 * @note	メモリ管理のため、メモリ回りの関数は直接呼び出さずにマクロを使用する
 * @note	特に理由が無ければAPP_SAFE_DELETE_ARRAYの方を使うこと
 */
#define	APP_DELETE_ARRAY(ptr)			delete[](ptr);

/**
 * @brief	deleteのラッパーマクロ（NULLチェックおよびNULLクリア付き）
 * @note	特に理由が無ければこちらを使うこと
 */
#define	APP_SAFE_DELETE(ptr)	{ if(ptr){ APP_DELETE(ptr); ptr=nullptr; } }

/**
 * @brief	配列のdeleteのラッパーマクロ（NULLチェックおよびNULLクリア付き）
 * @note	特に理由が無ければこちらを使うこと
 */
#define	APP_SAFE_DELETE_ARRAY(ptr)	{ if(ptr){ APP_DELETE_ARRAY(ptr); ptr=nullptr; } }

/**
 * @brief	mallocのラッパーマクロ
 * @note	メモリ管理のため、メモリ回りの関数は直接呼び出さずにマクロを使用する
 */
#define	APP_MALLOC(size)		malloc(size)

/**
 * @brief	freeのラッパーマクロ
 * @note	メモリ管理のため、メモリ回りの関数は直接呼び出さずにマクロを使用する
 */
#define	APP_FREE(ptr)			free(ptr)


// その他

/**
 * @brief	アサート
 * @note	条件を満たさない時にプログラムを止めるデバッグ用のマクロ
 */
//#define	APP_ASSERT(flag, message, ...)		{ if(!(flag)){ CCLOG("\n\n### ERROR ###\n\n%s()\n%s(%d)", __FUNCTION__, __FILE__, __LINE__); CCLOG(""#message, __VA_ARGS__); assert(false); } }
#define	APP_ASSERT(flag, message, ...)		{ if(!(flag)){ CCLOG("\n\n### ERROR ###\n\n%s()\n%s(%d)", __FUNCTION__, __FILE__, __LINE__); CCLOG(""#message, __VA_ARGS__); *(int*)-1 = 0; } }	// こちらの方がVisualStudioの挙動が分かりやすいため

/**
 * @brief	乱数取得のラッパーマクロ
 * @return	0.0～1.0の実数（1.0を含むので注意）
 * @note	デバッグ時に便利なことがあるので特に理由が無ければこれを使うこと
 */
#define	APP_RANDOM_F()			(((float)(rand() & 0x7fff)) / (float)0x7fff)
