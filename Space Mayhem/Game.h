#ifndef GAME_H
#define GAME_H

#include "EnemyProjectile.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Player.h"
#include <map>
#include <vector>
#include <sstream>
#include <string>

class Game
{
private:


	//Time
	sf::Clock projectileClock;

	//Player
	Player* player;

	//GUI
	sf::Font font;
	sf::Text pointText;

	sf::Text gameOver;

	//Background
	sf::Sprite backgroundSprite;


	//Resources
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bulletVector;
	std::vector<Enemy*> enemyVector;
	std::vector<EnemyProjectile*> enemyProjectileVector;
	std::vector<sf::RectangleShape*> hpBarVector;


	//Enemies
	float spawnTimer;
	float spawnTimerMax;

	//Private functions
	void InitPlayer();
	void InitWindow();
	void InitTextures();
	void InitEnemies();
	void InitGUI();
	void InitBackground();
	
	void UpdateInput();
	void UpdateBullets();
	void UpdateEnemiesAndCombat();
	float getProjectileTimeAsSeconds();
	void SpawnEnemyProjectiles();
	void UpdateEnemyProjectiles();
	void UpdateGUI();
	void UpdateWorld();
	void UpdateCollission();
	void Update();
	void RenderGUI();
	void RenderWorld();
	void Render();
	
	
public:
	//Window
	void UpdatePollEvents();
	sf::RenderWindow* window;
	float GetPlayerHp();
	Game();
	~Game();


	//Functions
	

	void Run();	

};

#endif