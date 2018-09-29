#include "SceneManager.h"


int main()
{
	// Criar janela
	sf::RenderWindow window(sf::VideoMode(800, 600), "Mini Fruiter");

	// Criar manager
	SceneManager Manager;
	Manager.inicializar();

	// Criar mundo f�sico
	b2Vec2 Gravity(0, 9.8f);
	b2World World(Gravity);

	// Criar o ch�o
	Manager.criaChao(World, 400, 500); // centro da tela, embaixo


	while (window.isOpen()) // Game Loop
	{

		
		// Se o bot�o for pressionado
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			int MouseX = sf::Mouse::getPosition(window).x; // pega posi��o X
			int MouseY = sf::Mouse::getPosition(window).y; // pega posi��o Y
			Manager.criaCaixa(World, MouseX, MouseY);	   // e cria a caixa
		}



		World.Step(1 / 60.f, 8, 3); // Simular um frame

		window.clear(sf::Color::White); // "Limpar" a tela a cada frame

		Manager.drawSprites(World, window);

		window.display();



	}

	return 0;
}