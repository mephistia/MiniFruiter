#include "SceneManager.h"
#include <iostream>
#include <ctime>


int main()
{
	// Criar janela
	sf::RenderWindow window(sf::VideoMode(800, 600), "Mini Fruiter");


	// Criar mundo físico
	b2Vec2 Gravity(0, 9.8);
	
	b2World *World = new b2World(Gravity);

	// delta time
	double t = 0.0;
	double dt = 1.0 / 60.0;

	int32 vIt = 8;
	int32 pIt = 3;

	b2Body* temp;

	// Criar manager
	SceneManager Manager;
	Manager.inicializar();

	// Criar o chão
	//Manager.criaChao(World, 400, 500);

	// Criar paredes
	Manager.criaParede(*World, 400, 605, 10, 800);
	Manager.criaParede(*World, -5, 300, 600, 10);
	Manager.criaParede(*World, 805, 300, 600, 10);
	Manager.criaParede(*World, 400, -5, 10, 800);

	// criar a plataforma
	Manager.criaPlataforma(*World, 400, 550, 32, 96);
		
	// Criar personagem bolinha
	Manager.criaPlayer(*World, 400, 5);


	while (window.isOpen()) // Game Loop
	{

		

		// movimentar corpo do jogador se nao estiver ativo
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{

			temp = Manager.getBody(MONSTRO, *World);

			// se não tiver largado o monstro
			if (temp->GetGravityScale() == 0)
				temp->SetLinearVelocity(b2Vec2(-1, 0));

			else {
				temp = Manager.getBody(PLATAFORMA, *World);
			

				if (temp->GetPosition().x < 1) {
					temp->SetLinearVelocity(b2Vec2(0, 0));

				}
				else
					temp->SetLinearVelocity(b2Vec2(-1, 0));
			}
			
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			temp = Manager.getBody(MONSTRO,* World);
			if (temp->GetGravityScale() == 0)
				temp->SetLinearVelocity(b2Vec2(1, 0));

			else {
				temp = Manager.getBody(PLATAFORMA, *World);

				if (temp->GetPosition().x > 19)
					temp->SetLinearVelocity(b2Vec2(0, 0));

				else
					temp->SetLinearVelocity(b2Vec2(1, 0));
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			
			temp = Manager.getBody(MONSTRO, *World);
			temp->SetGravityScale(1);
		}

		if (!Manager.isAnyKeyPressed()) {
			temp = Manager.getBody(MONSTRO, *World);

			if (temp->GetGravityScale() == 0)
				temp->SetLinearVelocity(b2Vec2(0, 0));

			temp = Manager.getBody(PLATAFORMA, *World);
			temp->SetLinearVelocity(b2Vec2(0, 0));

		}


		World->Step(dt,vIt,pIt); // Simular um frame

		window.clear(sf::Color::White); // "Limpar" a tela a cada frame

		Manager.drawSprites(*World, window); // Desenhar sprites

		window.display();


		t += dt;

		std::cout << t << std::endl;


		// Fim do Loop
	}

	return 0;
}