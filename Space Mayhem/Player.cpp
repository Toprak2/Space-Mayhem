#include "Player.h"
//Private functions

void Player::InitVariables()
{
	this->hp = 25;
	this->maxHp = this->hp;
	this->moveSpeed = 7.f;
	this->attackCooldownMax = 30.f;
	this->attackCooldown = this->attackCooldownMax;
	this->points = 0;
	//this->sprite.setRotation(90);
	this->hpBar.setFillColor(sf::Color::Red);
	this->hpBar.setPosition(this->GetPos().x-75,this->GetPos().y-50);
	this->hpBar.setSize(sf::Vector2f(150.f, 20.f));

}

//Load a texture from file
void Player::InitTexture()
{
	if (!this->texture.loadFromFile("Texture/ship.png")) 
	{
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load the texture file" << std::endl;
	}
}

//Set the texture to the sprite
void Player::InitSprite()
{
	//Set the texture to the sprite
	this->sprite.setTexture(this->texture);

	//Set the origin of the sprite
	this->sprite.setOrigin(374.f, 510.5f);
	
	//Resize the sprite 
	this->sprite.scale(0.1f, 0.1f);

}

//con/des
Player::Player()
{
	InitTexture();
	InitSprite();
	InitVariables();


}

Player::~Player()
{
}

//Accessor /access where the player is
const sf::Vector2f& Player::GetPos()
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::GetBounds() const
{
	return this->sprite.getGlobalBounds();
}

const sf::Vector2f& Player::GetOrigin()
{
	return this->sprite.getOrigin();
}

int Player::GetPoints()
{
	return this->points;
}

float Player::GetHp()
{
	return this->hp;
}

float Player::GetMaxHp()
{
	return this->maxHp;
}

void Player::SetPosition(sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Player::SetPosition(float pos_x, float pos_y)
{
	this->sprite.setPosition(pos_x, pos_y);
}

void Player::SetPoints(int points)
{
	this->points += points;
}

void Player::SetHp(float hp)
{
	this->hp = hp;
}

void Player::SetMaxHp(float maxHp)
{
	this->maxHp = maxHp;
}

void Player::IncreaseHp(float hp)
{
	this->hp += hp;
}

void Player::IncreaseMaxHp(float hp)
{
	this->maxHp += hp;
}


void Player::Move(const float dirX, const float dirY)
{
	this->sprite.move(this->moveSpeed * dirX, this->moveSpeed * dirY);
}

const bool Player::CanAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax) 
	{
		this->attackCooldown = 0.f;
		return true;
	}
	return false;
}

void Player::UpdateAttack()
{
	if (this->attackCooldown < this->attackCooldownMax)
	{
		this->attackCooldown += 0.5f;
	}
}

void Player::UpdateHpBar()
{
	this->hpBar.setPosition(this->GetPos().x - 110, this->GetPos().y +50);
	this->hpBar.setScale(sf::Vector2f(150 * (this->hp / this->maxHp)/100, 1));
}

//Public functions
void Player::Update()
{
	this->UpdateAttack();
	this->UpdateHpBar();
}




void Player::Render(sf::RenderTarget& target)
{

	//render player
	target.draw(this->sprite);

	target.draw(this->hpBar);
}


