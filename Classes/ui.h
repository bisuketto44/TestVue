
#pragma once
#include "utility/macro.h"
#include "game.h"
#include "entity/entity.h"

class Character;

// UIオブジェクト(UIマネージャーで管理)
class Ui : public Entity
{
public:
	//コンストラクタ	
	Ui(Character * owner, const char * imageFilename, const cocos2d::Vec2 & position, Game::SIDE side, bool isActive, bool isDraw, bool isUilayer);

	//デストラクタ
	~Ui();

	// 更新
	virtual void	update(float deltaTime);

	/**
	* @brief		持ち主のセット
	* @param[in]	owner		このコントローラの持ち主
	*/
	void			setOwner(Character* owner) { owner_ = owner; }

	/**
	 * @brief		持ち主の取得
	 * @return		owner		このコントローラの持ち主
	 */
	Character*		getOwner() { return owner_; }

	/**
	 * @brief		持ち主の取得（const版）
	 * @return		owner		このコントローラの持ち主（const）
	 */
	const Character*	getOwner() const { return owner_; }


	//Uiの描画更新
	virtual void DrawingUpdate();

protected:
	SafePointer<Character>	owner_;					//!< UIの持ち主

private:

};