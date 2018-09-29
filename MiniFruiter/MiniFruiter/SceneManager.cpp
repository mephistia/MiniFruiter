#include "SceneManager.h"



SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}


void SceneManager::inicializar()
{
	if (GroundTexture.loadFromFile("C:/Users/PC Gamer/Documents/GitHub/MiniFruiter/MiniFruiter/MiniFruiter/Assets/ground.png")) {
		printf("Inicializou chao/n");
	}
	
	BoxTexture.loadFromFile("C:/Users/PC Gamer/Documents/GitHub/MiniFruiter/MiniFruiter/MiniFruiter/Assets/box.png");

	
}


// Chão estático
void SceneManager::criaChao(b2World & World, float X, float Y)
{

	// Criar corpo físico
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(X / SCALE, Y / SCALE);
	BodyDef.type = b2_staticBody;
	b2Body* Body = World.CreateBody(&BodyDef);


	// Definir a forma
	b2PolygonShape Shape;
	Shape.SetAsBox((800 / 2) / SCALE, (16 / 2) / SCALE); // Caixa de 800px de largura por 16px de altura


	// Definir a fixture
	b2FixtureDef FixtureDef;
	FixtureDef.density = 0;  
	FixtureDef.shape = &Shape;
	Body->CreateFixture(&FixtureDef); 
}


// Caixa dinâmica
void SceneManager::criaCaixa(b2World & World, int MouseX, int MouseY)
{

	// Criar corpo físico
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(MouseX / SCALE, MouseY / SCALE); // Spawn na posição do mouse
	BodyDef.type = b2_dynamicBody;
	b2Body* Body = World.CreateBody(&BodyDef);

	// Criar a forma
	b2PolygonShape Shape;
	Shape.SetAsBox((32 / 2) / SCALE, (32 / 2) / SCALE);

	// Criar a fixture
	b2FixtureDef FixtureDef;
	FixtureDef.density = 1.f;
	FixtureDef.friction = 0.7f;
	FixtureDef.shape = &Shape;
	Body->CreateFixture(&FixtureDef);
}

void SceneManager::drawSprites(b2World & World, sf::RenderWindow &window)
{

	// Percorrer a lista de body
	for (b2Body* BodyIterator = World.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
	{
		if (BodyIterator->GetType() == b2_dynamicBody) // se for dinamico
		{
			sf::Sprite Sprite;
			Sprite.setTexture(BoxTexture);
			Sprite.setOrigin(16.f, 16.f);
			Sprite.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
			Sprite.setRotation(BodyIterator->GetAngle() * 180 / b2_pi);
			window.draw(Sprite);
		}
		else
		{
			sf::Sprite GroundSprite;
			GroundSprite.setTexture(GroundTexture);
			GroundSprite.setOrigin(400.f, 8.f);
			GroundSprite.setPosition(BodyIterator->GetPosition().x * SCALE, BodyIterator->GetPosition().y * SCALE);
			GroundSprite.setRotation(180 / b2_pi * BodyIterator->GetAngle());
			window.draw(GroundSprite);
		}
	}
}

