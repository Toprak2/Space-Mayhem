#include "Enemy.h"




float Enemy::GetElapsedTimeSec()
{
	
	return  clock.getElapsedTime().asSeconds();
	
}

void Enemy::InitHpBar()
{
	this->hpBar.setFillColor(sf::Color::Red);
	this->hpBar.setPosition(this->GetPos().x , this->GetPos().y );
	this->hpBar.setSize(sf::Vector2f(75.f, 20.f));
}

Enemy::Enemy(int _type,sf::Texture* texture, float pos_x, float pos_y, float _hp, float movement_speed, int _damage,int points,Player *player)
{
	this->type = _type;
	this->enemySprite.setTexture(*texture);
	if (type == 1) 
	{

		this->enemySprite.setOrigin(600.f, 600.f);
		this->enemySprite.setScale(0.05, 0.05);
	}
	else if(type==2)
	{
		this->enemySprite.setOrigin(256.f, 256.f);
		this->enemySprite.setScale(0.1, 0.1);
	}
	this->enemySprite.setPosition(pos_x, pos_y);
	this->hp = _hp;
	this->maxHp = this->hp;
	this ->moveSpeed = movement_speed;
	this->damage = _damage;
	this->points = points;
	this->player = player;
	
	InitHpBar();

	
}

Enemy::~Enemy()
{
	if (type == 1)
	{
		this->player->SetPoints(this->points);
	}
	else if (type == 2)
	{
		this->player->SetPoints(this->points);
	}

}

void Enemy::SetHp(float _damage)
{
	this->hp -= _damage;
}

void Enemy::SetDamage()
{
}

void Enemy::SetPoints()
{
}

float Enemy::GetHp()
{
	return this->hp;
}

float Enemy::GetMaxHp()
{
	return this->maxHp;
}

int Enemy::GetDamage()
{
	return this->damage;
}

const sf::Vector2f& Enemy::GetPos()
{
	return this->enemySprite.getPosition();
}

void Enemy::Move(sf::Vector2f player_pos,float pos)
{

	

	if (this->type == 1)
	{
		sf::Vector2f enemyPosition(enemySprite.getPosition().x, enemySprite.getPosition().y);
		sf::Vector2f direction = player_pos - enemyPosition;
		sf::Vector2f normalizedDir;
		normalizedDir.x = direction.x / sqrt(pow(direction.x, 2) + pow(direction.y, 2));
		normalizedDir.y = direction.y / sqrt(pow(direction.x, 2) + pow(direction.y, 2));
		sf::Vector2f currentSpeed = normalizedDir * moveSpeed;
	
		const float PI = 3.14159265;

		float dx = enemyPosition.x - player_pos.x;
		float dy = enemyPosition.y - player_pos.y;

		float rotation = (atan2(dy, dx)) * 180 / PI;

		enemySprite.setRotation(rotation + 90);


		enemySprite.move(currentSpeed);
		

	}
	else if (this->type == 2)
	{
		if (this->enemySprite.getPosition().y != 100)
		{
			float xpos = this->enemySprite.getPosition().x;
			enemySprite.move(0, 0.5 * moveSpeed);
			
			
		}

		else if (int(this->GetElapsedTimeSec())%2==0)
		{
			enemySprite.move(pos, 0);
		}
		if (int(this->GetElapsedTimeSec()) % 4 == 0)
		{
			enemySprite.move(-2*pos, 0);
		}
	}
}

void Enemy::MoveIntersect(sf::Vector2f player_pos)
{
	if (this->type == 1)
	{
		sf::Vector2f enemyPosition(enemySprite.getPosition().x, enemySprite.getPosition().y);
		sf::Vector2f direction = player_pos - enemyPosition;
		sf::Vector2f normalizedDir;
		normalizedDir.x = direction.x / sqrt(pow(direction.x, 2) + pow(direction.y, 2));
		normalizedDir.y = direction.y / sqrt(pow(direction.x, 2) + pow(direction.y, 2));
		sf::Vector2f currentSpeed = normalizedDir * moveSpeed;

		const float PI = 3.14159265;

		float dx = enemyPosition.x - player_pos.x;
		float dy = enemyPosition.y - player_pos.y;

		float rotation = (atan2(dy, dx)) * 180 / PI;

		enemySprite.setRotation(rotation + 90);


		enemySprite.move(currentSpeed.x * -50, currentSpeed.y * -50);
	}
	
}

const sf::FloatRect Enemy::GetBounds()
{
	return this->enemySprite.getGlobalBounds();;
}

void Enemy::UpdateHpBar()
{
	this->hpBar.setPosition(this->GetPos().x-50.f , this->GetPos().y-60 );
	this->hpBar.setScale(sf::Vector2f(150 * (this->hp / this->maxHp) / 100, 1));
}

void Enemy::Update(sf::Vector2f player_pos,float pos)
{
	this->Move(player_pos,pos);
	this->UpdateHpBar();
}

void Enemy::Render(sf::RenderTarget* target)
{
	target->draw(this->enemySprite);

	target->draw(this->hpBar);
}
