#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>
#include <iostream>



class Bullet
{
private:
	sf::Sprite shape;

	sf::Vector2f direction;
	float moveSpeed;
	float damage;

	//Private functions

public:

	//Constructor /Destructor

	Bullet(sf::Texture* texture, float pos_x,float pos_y, float dir_x, float dir_y, float movement_speed);
	virtual ~Bullet();

	//Accessor
	const sf::FloatRect GetBounds() ;


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

#endif	
