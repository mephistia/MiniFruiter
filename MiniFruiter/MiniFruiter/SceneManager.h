#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <string>

const float SCALE = 40;

enum bodyDataType { MONSTRO, PLATAFORMA, PAREDE_H, PAREDE_V, ITEM, CAIXA };




// Classe administradora dos objetos físicos
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void inicializar(); // Carregar Assets

	void criaParede(b2World &world, float X, float Y, float altura, float largura);
	void criaPlataforma(b2World &world, float X, float Y, float altura, float largura);
	void criaPlayer(b2World &world, float X, float Y);


	void drawSprites(b2World &World, sf::RenderWindow &window);
	 
	b2Body* getBody(int id, b2World &world); // pegar um corpo pelo id (primeiro)

	void setPos(b2Body *Body, float X, float Y, float angle);


	bool isAnyKeyPressed();


private:
	sf::Texture GroundTexture;
	sf::Texture PV;
	sf::Texture PH;
	sf::Texture BoxTexture;
	sf::Texture PlayerTexture;
	sf::Texture PlatformTexture;

	struct BodyData {
		int ID;
	};


};

