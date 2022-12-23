#include "Game.h"



void Game::InitPlayer()
{
	this->player = new Player();
	this->player->SetPosition(960.f, 540.f);


}

//Private functions 

void Game::InitWindow()
{
	 
	this->window = new sf::RenderWindow(sf::VideoMode(1920,1080), "Space Mayhem",sf::Style::Close |sf::Style::Titlebar | sf::Style::Resize);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

void Game::InitTextures()
{
	this->textures["Bullet"] = new sf::Texture();
	this->textures["Bullet"]->loadFromFile("Texture/bullet.png");
	this->textures["EnemyMelee"] = new sf::Texture();
	this->textures["EnemyMelee"]->loadFromFile("Texture/enemymelee.png");
	this->textures["EnemyRanged"] = new sf::Texture();
	this->textures["EnemyRanged"]->loadFromFile("Texture/enemyranged.png");
	this->textures["Background"] = new sf::Texture();
	this->textures["Background"]->loadFromFile("Texture/background1.jpg");
}

void Game::InitEnemies()
{
	this->spawnTimerMax = 130.f;
	this->spawnTimer = spawnTimerMax;
}

void Game::InitGUI()
{
	//Load font
	this->font.loadFromFile("Fonts/Mangabey.ttf");
	this->pointText.setFont(font);
	this->pointText.setCharacterSize(30);
	this->pointText.setString("Points: 0");
	this->pointText.setPosition(0.f, 0.f);

	this->gameOver.setFont(font);
	this->gameOver.setCharacterSize(80);
	this->gameOver.setFillColor(sf::Color::Red);
	this->gameOver.setString("GAME OVER");
	this->gameOver.setPosition(0.f, 0.f);
	this->gameOver.setPosition(this->window->getSize().x / 2.f - this->gameOver.getGlobalBounds().width / 2.f,
								this->window->getSize().y / 2.f - this->gameOver.getGlobalBounds().height / 2.f);

}

void Game::InitBackground()
{
	this->backgroundSprite.setTexture(*this->textures["Background"]);
	
}

void Game::UpdateInput()
{ 
	//Move player 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->player->Move(-1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->player->Move(1.f , 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->player->Move(0.f, -1.f );
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->player->Move(0.f, 1.f );
	}

	//Spawn bullets
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->CanAttack())
	{
		this->bulletVector.push_back(new Bullet(this->textures["Bullet"], this->player->GetPos().x-16.5, this->player->GetPos().y-51.f, 0.f, -1.f, 10.f));
	}
}

void Game::UpdatePollEvents()
{
	//Quit the game
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
		{
			this->window->close();
		}
		if (e.Event::key.code == sf::Keyboard::Escape) {
			this->window->close();
		}


	}
}

void Game::UpdateBullets()
{
	for (auto* bullet : this -> bulletVector) 
	{
		unsigned counter=0;	
		bullet->Update();

		//Bullet culling (top of screen)
		if (bullet->GetBounds().top + bullet->GetBounds().height < 0.f) 
		{
			//Delete bullet
			delete this->bulletVector.at(counter);
			bulletVector.erase(bulletVector.begin() + counter);
			--counter;
		}
		++counter;

	}

}

void Game::UpdateEnemiesAndCombat()
{
	//Spawn enemies
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax) 
	{
		int randType =  rand() % 2 + 1;
		this->spawnTimer = 0; 
		if (randType == 1)
		{
			float x_pos = rand() % this->window->getSize().x;
			this->enemyVector.push_back(new Enemy(randType, this->textures["EnemyMelee"], x_pos, -40.f, 20, 1.f, 2.5, 5, this->player));
		}
		else if (randType == 2)
		{
			float x_pos = 125+rand() % (this->window->getSize().x-125+1);
			this->enemyVector.push_back(new Enemy(randType, this->textures["EnemyRanged"], x_pos, -40.f, 10, 5, 2.5, 8, this->player));
		}
	}
	

	//Update enemies
	for (unsigned i=0; i < enemyVector.size(); i++)
	{
		//Move enemies
		enemyVector[i]->Update(player->GetPos(),1);

		if (enemyVector[i]->GetBounds().intersects(this->player->GetBounds())) {
			this->player->IncreaseHp(-enemyVector[i]->GetDamage());
			if (enemyVector[i]->type == 1) {
				this->enemyVector[i]->MoveIntersect(this->player->GetPos());
			}
			else if (enemyVector[i]->type == 2)
			{
				delete enemyVector.at(i);
				enemyVector.erase(enemyVector.begin() + i);
				i--;
			}
		}


		


		for ( int j=0; j<bulletVector.size(); j++) 
		{
			//if a bullet intersects with an enemy delete the bullet decrease the hp of the enemy
			if (bulletVector[j]->GetBounds().intersects(enemyVector[i]->GetBounds()))
			{
				//set the new hp of the enemy
				enemyVector[i]->SetHp(bulletVector[j]->getDamage());

				//delete the bullet
				delete bulletVector.at(j);
				this->bulletVector.erase(bulletVector.begin() + j);		
				j--;

				//if an enemy has 0 or less hp destroy it
				if (enemyVector[i]->GetHp() <= 0)
				{
					delete enemyVector.at(i);
					enemyVector.erase(enemyVector.begin() + i);
					i--;
					break;

				}
				break;
				
			}
		}
	}

	//Update if player is hit
	for (int j = 0; j < enemyProjectileVector.size(); j++)
	{
		//if an enemy projectile intersects with the player delete the projectile decrease the hp of the player
		
		if (enemyProjectileVector[j]->GetBounds().intersects(player->GetBounds()))
		{

			//delete the projectile
			//set the new hp of the player
			player->IncreaseHp(-enemyProjectileVector[j]->getDamage());
			delete enemyProjectileVector.at(j);
			this->enemyProjectileVector.erase(enemyProjectileVector.begin() + j);
			j--;




		}
	}

	}
	


//Get time for projectiles as seconds
float Game::getProjectileTimeAsSeconds()
{
	return this->projectileClock.getElapsedTime().asSeconds();
}

void Game::SpawnEnemyProjectiles()
{
	if (this->getProjectileTimeAsSeconds() >= 1.75) {
		projectileClock.restart();
		for (auto* enemyProjectile : enemyVector)
		{
			if (enemyProjectile->type == 2)
			{
				this->enemyProjectileVector.push_back(new EnemyProjectile(this->textures["Bullet"], 
					  enemyProjectile->GetPos().x , enemyProjectile->GetPos().y , 0.f, 1.f, 5.f));
			}
		}
	}
}

void Game::UpdateEnemyProjectiles()
{
	for (auto* enemyProjectile : this->enemyProjectileVector)
	{
		unsigned counter = 0;
		enemyProjectile->Update();

		//Bullet culling (bottom of screen)
		if (enemyProjectile->GetBounds().top  > 1079.f)
		{
			//Delete bullet
			delete this->enemyProjectileVector.at(counter);
			enemyProjectileVector.erase(enemyProjectileVector.begin() + counter);
			--counter;
		}
		++counter;

	}
}

void Game::UpdateGUI()
{
	std::stringstream ss;

	ss << "Score:"<<this->player->GetPoints();
	this->pointText.setString(ss.str());
}

void Game::UpdateWorld()
{
}

//detects if the player is trying to go out of the window

void Game::UpdateCollission()
{
	if (this->player->GetBounds().left < 0.f)
	{
		this->player->SetPosition(this->player->GetPos().x+7, this->player->GetPos().y);
	}

	if (this->player->GetBounds().top < 0.f)
	{
		this->player->SetPosition(this->player->GetPos().x, this->player->GetPos().y+7);
	}
	if (this->player->GetBounds().left+this->player->GetBounds().width >1920.f)
	{
		this->player->SetPosition(this->player->GetPos().x -7, this->player->GetPos().y);
	}
	if (this->player->GetBounds().top+this->player->GetBounds().height > 1080.f)
	{
		this->player->SetPosition(this->player->GetPos().x , this->player->GetPos().y-7);
	}

	//check if ranged enemies are trying to go out of window
	for (auto* enemy : enemyVector) 
	{
		if (enemy->type == 2)
		{
			if (enemy->GetBounds().left < 0.f)
			{
				enemy->Move(this->player->GetPos(), -1);
			}
			if (enemy->GetBounds().left+enemy->GetBounds().width > 1920.f)
			{
				enemy->Move(this->player->GetPos(), -1);
			}
		}


	}
}


void Game::Update()
{


	this->UpdateInput();
	this->UpdateBullets();
	this->player->Update();
	this->UpdateCollission();
	this->UpdateEnemiesAndCombat();
	this->SpawnEnemyProjectiles();
	this->UpdateEnemyProjectiles();
	this->UpdateGUI();

}

void Game::RenderGUI()
{
	this->window->draw(this->pointText);
}

void Game::RenderWorld()
{
	this->window->draw(this->backgroundSprite);
}



void Game::Render()
{
	//Clear old frame
	this->window->clear();

	//Draw all the stuff
	
	//Render the world
	this ->RenderWorld();

	//Render the player
	this->player->Render(*this->window);


	//Render bullets
	for (auto* bullet : this->bulletVector) {
		bullet->Render(this->window);
	}
	for (auto* enemy : this->enemyVector) {
		enemy->Render(this->window);
	}
	for (auto* enemyProjectiles : enemyProjectileVector) {
		enemyProjectiles->Render(this->window);
	}
	this->RenderGUI();
	
	//Game over screen
	if (this->player->GetHp() <= 0)
	{
		this->window->draw(this->gameOver);
		this->pointText.setPosition(this->window->getSize().x / 2.f - this->pointText.getGlobalBounds().width / 2.f,
			this->window->getSize().y / 2 - this->pointText.getGlobalBounds().height / 2.f-200.f);
	}

	//Display all the drawn stuff to the window /Always put this last in Render()!!
	this->window->display();
}

		
float Game::GetPlayerHp()
{
	return this->player->GetHp();
}

//Con/Des
Game::Game()
{ 
	
	this->InitWindow();
	this->InitTextures();
	this->InitBackground();
	this->InitGUI();
	this->InitPlayer();
	this->InitEnemies();
	//icon
	auto image = sf::Image{};
	image.loadFromFile("Texture/logo.png");
	window->setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());

}

Game::~Game()
{
	delete this->player;
	delete this->window;

	//Delete textures
	for (auto &i : this->textures) 
	{
		delete i.second;
	}

	//Delete bullets 
	for (auto* i : this->bulletVector) {

		delete i;
	}
	//Delete enemies
	for (auto* i : this->enemyVector) {

		delete i;
	}
}
 

//Public functions

void Game::Run()
{
	
	//while (this->window->isOpen())
	//{ 
		this->UpdatePollEvents();
		if (this->player->GetHp() > 0) 
		{
			this->Update();
		}
		this->Render();
	//}
}
