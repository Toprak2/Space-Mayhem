#include "Game.h"
#include <time.h>


int main()
{
	Game* game = new Game;
	srand(static_cast<unsigned int>(time(0)));


	while (true)
	{

		if (game->GetPlayerHp() > 0)
			game->Run();
		if (game->GetPlayerHp() <= 0)
		{
			sf::Event a;
			while (game->window->pollEvent(a))
			{
				if (a.Event::type == sf::Event::Closed)
				{
					game->window->close();
				}
				if (a.Event::key.code == sf::Keyboard::Space) {

					delete game;
					game = new Game;
				}

			}


		}
	}
}