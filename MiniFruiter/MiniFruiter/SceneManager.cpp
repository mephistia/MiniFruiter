#include "SceneManager.h"



SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}


void SceneManager::inicializar()
{
	if (!GroundTexture.loadFromFile("assets/ground.png")) 
		exit(1);
	

	if (!BoxTexture.loadFromFile("assets/box.png")) // Textura da caixa normal
		exit(1);
	

	if (!PlayerTexture.loadFromFile("assets/circle.png")) // Textura do jogador (mini-fruiter)
		exit(1);

	if (!PH.loadFromFile("assets/edgeh.png")) // Parede horizontal
		exit(1);
	
	if (!PV.loadFromFile("assets/edgev.png")) // Parede vertical
		exit(1);

	release = false;
	
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

	BodyData *data = new BodyData;
	data->ID = PAREDE_H;
	data->fisico = false;
	Body->SetUserData(data);
}

// Paredes da janela
void SceneManager::criaParede(b2World & world, float X, float Y, float altura, float largura)
{
	// Criar corpo físico
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(X / SCALE, Y / SCALE);
	BodyDef.type = b2_staticBody;
	b2Body* Body = world.CreateBody(&BodyDef);


	// Definir a forma
	b2PolygonShape Shape;
	Shape.SetAsBox((largura / 2) / SCALE, (altura / 2) / SCALE);

	// Definir a fixture
	b2FixtureDef FixtureDef;
	FixtureDef.density = 0;
	FixtureDef.shape = &Shape;
	Body->CreateFixture(&FixtureDef);

	BodyData *data = new BodyData;

	if (largura == 800) 
		data->ID = PAREDE_H;
	
	else
		data->ID = PAREDE_V;

	data->fisico = false;

	Body->SetUserData(data);
}



// Caixa dinâmica
void SceneManager::criaCaixa(b2World & World, int X, int Y)
{

	// Criar corpo físico
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(X / SCALE, Y / SCALE);
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

	BodyData *data = new BodyData;
	data->ID = CAIXA;
	data->fisico = true;

	Body->SetUserData(data);
}


// Círculo
void SceneManager::criaPlayer(b2World & world, float X, float Y)
{
	// BodyDef
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(X / SCALE, Y / SCALE);
	BodyDef.type = b2_dynamicBody;
	b2Body *Body = world.CreateBody(&BodyDef);

	// Shape
	b2CircleShape forma;
	forma.m_radius = 0.5;

	// Fixture
	b2FixtureDef fix;
	fix.shape = &forma;
	fix.density = 10;
	fix.friction = 0.5;
	fix.restitution = 0.99;

	Body->CreateFixture(&fix);
	BodyData *data = new BodyData;
	data->ID = MONSTRO;
	data->fisico = false; ; // Iniciar com false

	Body->SetUserData(data);

	Body->SetGravityScale(0);

	

}


void SceneManager::drawSprites(b2World & World, sf::RenderWindow &window)
{

	// Percorrer a lista de body

	for (b2Body* BodyIterator = World.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
	{

		BodyData *bd = (BodyData*)BodyIterator->GetUserData();

		if (bd->ID == CAIXA) // se for obstaculo caixa
		{
			
			sf::Sprite Sprite;
			Sprite.setTexture(BoxTexture);
			Sprite.setOrigin(16.f, 16.f);
			Sprite.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
			Sprite.setRotation(BodyIterator->GetAngle() * 180 / b2_pi);
			window.draw(Sprite);
		}

		else if (bd->ID == PAREDE_H)
		{
			sf::Sprite PHSprite;
			PHSprite.setTexture(PH);
			PHSprite.setOrigin(400.f, 5.f);
			PHSprite.setPosition(BodyIterator->GetPosition().x * SCALE, BodyIterator->GetPosition().y * SCALE);
			PHSprite.setRotation(180 / b2_pi * BodyIterator->GetAngle());
			window.draw(PHSprite);
		}

		else if (bd->ID == PAREDE_V)
		{
			sf::Sprite PVSprite;
			PVSprite.setTexture(PV);
			PVSprite.setOrigin(5.f, 300.f);
			PVSprite.setPosition(BodyIterator->GetPosition().x * SCALE, BodyIterator->GetPosition().y * SCALE);
			PVSprite.setRotation(180 / b2_pi * BodyIterator->GetAngle());
			window.draw(PVSprite);
		}

		else if (bd->ID == MONSTRO) {
			sf::Sprite MonsterSprite;
			MonsterSprite.setTexture(PlayerTexture);
			MonsterSprite.setOrigin(16, 16);
			MonsterSprite.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
			MonsterSprite.setRotation(BodyIterator->GetAngle() * 180 / b2_pi);
			window.draw(MonsterSprite);
		}
	}
}


// pegar um corpo pelo id (primeiro)
b2Body* SceneManager::getBody(int id, b2World &world)
{
	for (b2Body* Body = world.GetBodyList(); Body != 0; Body = Body->GetNext())
	{

		BodyData *bd = (BodyData*)Body->GetUserData();

		if (bd->ID == id) {
			return Body;
		}
	}
}

void SceneManager::setPos(b2Body * Body, float X, float Y, float angle)
{
	b2Vec2 *vector = new b2Vec2(X, Y);
	Body->SetTransform(*vector, angle);
}

