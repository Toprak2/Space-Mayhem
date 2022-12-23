#pragma once
#include "SFML/Graphics.hpp"
class EnemyProjectile
{
private:
	sf::Sprite shape;

	sf::Vector2f direction;
	float moveSpeed;
	float damage;
	
	//Private functions

public:

	//Constructor /Destructor

	EnemyProjectile(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed);
	virtual ~EnemyProjectile();

	//Accessor
	const sf::FloatRect GetBounds();


	//Public functions

	//Initializers
	void InitAll();

	//setters
	void setDamage(int new_damage);

	//Getters
	float getDamage();

	void Update();
	void Render(sf::RenderTarget* target);

};

