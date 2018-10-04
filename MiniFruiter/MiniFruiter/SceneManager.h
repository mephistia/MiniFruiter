#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <string.h>

const float SCALE = 30;

enum bodyDataType { MONSTRO, PALTAFORMA, PAREDE_H, PAREDE_V, ITEM, CAIXA };




// Classe administradora dos objetos físicos
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void inicializar(); // Carregar Assets

	void criaChao(b2World& World, float X, float Y);
	void criaParede(b2World &world, float X, float Y, float altura, float largura);
	void criaCaixa(b2World& World, int X, int Y);
	void criaPlayer(b2World &world, float X, float Y);


	void drawSprites(b2World &World, sf::RenderWindow &window);
	 
	b2Body* getBody(int id, b2World &world); // pegar um corpo pelo id (primeiro)

	void setPos(b2Body *Body, float X, float Y, float angle);





private:
	sf::Texture GroundTexture;
	sf::Texture PV;
	sf::Texture PH;
	sf::Texture BoxTexture;
	sf::Texture PlayerTexture;

	struct BodyData {
		int ID;
		bool fisico;
	};

	bool release;

};

