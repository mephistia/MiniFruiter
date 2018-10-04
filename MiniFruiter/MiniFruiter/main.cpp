#include "SceneManager.h"


int main()
{
	// Criar janela
	sf::RenderWindow window(sf::VideoMode(800, 600), "Mini Fruiter");


	// Criar mundo físico
	b2Vec2 Gravity(0, 1.5f);
	
	b2World World(Gravity);

	float32 timestep = 1.f / 60.f;
	int32 vIt = 6;
	int32 pIt = 2;

	b2Body* temp;

	

	// Criar manager
	SceneManager Manager;
	Manager.inicializar();

	// Criar o chão
	//Manager.criaChao(World, 400, 500);

	// Criar paredes
	Manager.criaParede(World, 400, 605, 10, 800);
	Manager.criaParede(World, -5, 300, 600, 10);
	Manager.criaParede(World, 805, 300, 600, 10);
	Manager.criaParede(World, 400, -5, 10, 800);
		
	// Criar personagem bolinha
	Manager.criaPlayer(World, 400, 5);


	while (window.isOpen()) // Game Loop
	{

		
		// Spawn de caixas
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			int MouseX = sf::Mouse::getPosition(window).x; // pega posição X
			int MouseY = sf::Mouse::getPosition(window).y; // pega posição Y
			Manager.criaCaixa(World, MouseX, MouseY);	   // e cria a caixa
		}

		// movimentar corpo do jogador se nao estiver ativo
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{

			temp = Manager.getBody(MONSTRO, World);
			if (temp->GetGravityScale() == 0)
				temp->ApplyForce(b2Vec2(-0.1572, 0), temp->GetWorldCenter(), true);
			
			
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			temp = Manager.getBody(MONSTRO, World);
			if (temp->GetGravityScale() == 0)
				temp->ApplyForce(b2Vec2(0.1572, 0), temp->GetWorldCenter(), true);

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			
			temp = Manager.getBody(MONSTRO, World);
			temp->SetGravityScale(0.1);
		}


		World.Step(timestep,vIt,pIt); // Simular um frame

		window.clear(sf::Color::White); // "Limpar" a tela a cada frame

		Manager.drawSprites(World, window); // Desenhar sprites

		window.display();



	}

	return 0;
}