#include "Bullet.h"


Bullet::Bullet(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed)
{
	this->shape.setTexture(*texture);
	this->shape.setScale(0.1, 0.1);
	this->shape.setPosition(pos_x, pos_y);
	this->direction.x = dir_x;
	this->direction.y = dir_y; 
	this->moveSpeed = movement_speed;

	this ->InitAll();
}

Bullet::~Bullet()
{
}

const sf::FloatRect Bullet::GetBounds()
{
	return this->shape.getGlobalBounds(); 
}

//Setters

void Bullet::InitAll()
{
	this->damage = 5.f;
}

void Bullet::setDamage(int new_damage)
{
	this->damage = new_damage;
}

//Getters

float Bullet::getDamage()
{
	return damage;
}

void Bullet::Update()
{
	//Movement
	this->shape.move(this->moveSpeed * this->direction);
}

void Bullet::Render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
