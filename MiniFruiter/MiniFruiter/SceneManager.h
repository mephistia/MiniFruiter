#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <string.h>

const float SCALE = 30;


// Classe administradora dos objetos físicos
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void inicializar(); // Carregar Assets

	void criaChao(b2World& World, float X, float Y);
	void criaCaixa(b2World& World, int MouseX, int MouseY);

	void drawSprites(b2World &World, sf::RenderWindow &window);

private:
	sf::Texture GroundTexture;
	sf::Texture BoxTexture;

};

