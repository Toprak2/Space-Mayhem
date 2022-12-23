#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Player.h"
#include <Windows.h>

class Enemy
{
private:
	sf::Sprite enemySprite;
	sf::Clock clock;
	sf::RectangleShape hpBar;

	float hp;
	float maxHp;
	float moveSpeed;

	int damage;
	int points;
	Player* player;

	float GetElapsedTimeSec();
	void InitHpBar();

	//Initializers


public:
	int type;


	//Cons/dest
	Enemy(int _type, sf::Texture* texture, float pos_x, float pos_y, float _hp, float movement_speed, int _damage,int points,Player *player);
	virtual ~Enemy();

	//public functions

	//Setters
	void SetHp(float _damage);
	void SetDamage();
	void SetPoints();
	//getters
	float GetHp();
	float GetMaxHp();
	int GetDamage();
	const sf::Vector2f& GetPos();


	void Move(sf::Vector2f player_pos, float pos);
	void MoveIntersect(sf::Vector2f player_pos);

	//Accessors
	const sf::FloatRect GetBounds();
	
	void UpdateHpBar();
	void Update(sf::Vector2f player_pos,float pos);
	void Render(sf::RenderTarget* target);
};

#endif