#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include "Lista.h"


const float SCALE = 40;

enum bodyDataType { MONSTRO, PLATAFORMA, PAREDE_H, PAREDE_V, ITEM, CAIXA, RETANGULO_MOVEL, CIRCULO, TRIANGULO,
					RETANGULO_JOINT, PENDULO, PORTAL, PREGO }; // enum para desenhar




// Classe administradora dos objetos físicos
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void inicializar(); // Carregar Assets

	// Criação de bodies que vão em todas as fases:
	void criaParede(b2World &world, float X, float Y, float altura, float largura);
	void criaPlataforma(b2World &world, float X, float Y, float altura, float largura);
	void criaPlayer(b2World &world, float X, float Y);


	// Criação de bodies por nível:
	void criaCaixa(b2World &world, float X, float Y, float tamanho);
	void criaTriangulo(b2World &world, float X, float Y);
	void criaRetanguloComJoint(b2World &world, float X, float Y, float Xprego, float Yprego);

	// Desenhar sprites na tela
	void drawSprites(b2World &World, sf::RenderWindow &window);
	 
	b2Body* getBody(int id, b2World &world); // pegar um corpo pelo id (primeiro que achar)

	void setPos(b2Body *Body, float X, float Y, float angle);


	bool isAnyKeyPressed();

	void lerLevel(std::string arquivo, b2World &world);

	void lerCaminhos(std::string arquivo);

	std::string getLevelPath(int i);

private:
	sf::Texture  PV, PH, BoxTexture, PlayerTexture, PlatformTexture, TrianguloTexture, PregoTexture,
		RetanguloTexture;

	struct BodyData {
		int ID; // nome por enum
		float tamX; // tamanho para o sprite
		float tamY;
	};


	// criar um arquivo de leitura pra cada nível
	std::string *levelPath;

};

