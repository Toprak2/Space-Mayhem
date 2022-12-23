#ifndef PLAYER_H
#define PLAYER_H
#include "Bullet.h"

class Player
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::RectangleShape hpBar;

	float moveSpeed;

	float attackCooldown;
	float attackCooldownMax;
	int points;
	float hp;
	float maxHp;



	//Private functions
	void InitVariables();
	void InitTexture();
	void InitSprite();
	
public:
	//Con/Des
	Player();
	~Player();

	//Accessor
	const sf::Vector2f& GetPos();
	const sf::FloatRect GetBounds() const;
	const sf::Vector2f& GetOrigin();
	int GetPoints();
	float GetHp();
	float GetMaxHp();
	
	//Modifiers
	void SetPosition(sf::Vector2f pos);
	void SetPosition(float pos_x, float pos_y);
	void SetPoints(int points);
	void SetHp(float hp);
	void SetMaxHp(float maxHp);
	void IncreaseHp(float hp);
	void IncreaseMaxHp(float hp);

	//Functions
	void Move(const float dirX, const float dirY);

	const bool CanAttack();
	void UpdateAttack();
	void UpdateHpBar();
	void Update();

	void Render(sf::RenderTarget& target);
};

#endif