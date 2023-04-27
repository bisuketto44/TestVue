/**
 * @file    trigger_table_stage_01.h
 *
 * @brief   ステージ01のトリガテーブル
 * @details ステージ01の時間による進行データ
 *
 * @author  Kaifu Koji
 * @date    2018/04/06
 * @note    マーベラス開発部新人研修C++演習用
 */

// ステージ01の進行テーブル
// --- 時間経過と共に実行させたいことを並べていく
Sequencer::Trigger stage_01_table[] =
{
	
	{ Sequencer::Trigger::TYPE_STAGE_CLEAR,		            1.0f},

	



// 未実装のためコメントアウト
//	{ Sequencer::Trigger::TYPE_STAGE_CLEAR,					5.0f},

  { Sequencer::Trigger::TYPE_TABLE_END,					0.0f},
};
