#include "SceneManager.h"



SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}


void SceneManager::inicializar()
{
	
	if (!PlayerTexture.loadFromFile("assets/circle.png")) // Textura do jogador (mini-fruiter)
		exit(1);

	if (!PH.loadFromFile("assets/edgeh.png")) // Parede horizontal
		exit(1);
	
	if (!PV.loadFromFile("assets/edgev.png")) // Parede vertical
		exit(1);

	if (!PlatformTexture.loadFromFile("assets/platform.png")) // Parede vertical
		exit(1);

	if (!BoxTexture.loadFromFile("assets/caixa.png")) // Caixa
		exit(1);

	if (!TrianguloTexture.loadFromFile("assets/triangulo.png")) // Caixa
		exit(1);

	if (!RetanguloTexture.loadFromFile("assets/retangulo.png")) // Caixa
		exit(1);

	if (!PregoTexture.loadFromFile("assets/prego.png")) // Caixa
		exit(1);
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

	data->tamX = largura;
	data->tamY = altura;

	Body->SetUserData(data);
}

void SceneManager::criaPlataforma(b2World & world, float X, float Y, float altura, float largura)
{
	// Criar corpo físico
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(X / SCALE, Y / SCALE);
	BodyDef.type = b2_kinematicBody;
	b2Body* Body = world.CreateBody(&BodyDef);


	// Definir a forma
	b2PolygonShape Shape;
	Shape.SetAsBox((largura / 2) / SCALE, (altura / 2) / SCALE);

	// Fixture
	b2FixtureDef fix;
	fix.shape = &Shape;
	fix.density = 2 / (altura * largura);
	fix.friction = 0;
	fix.restitution = 1;

	Body->CreateFixture(&fix);


	BodyData *data = new BodyData;
	data->ID = PLATAFORMA;
	data->tamX = largura;
	data->tamY = altura;

	Body->SetUserData(data);

	Body->SetGravityScale(0);

}

// Círculo
void SceneManager::criaPlayer(b2World & world, float X, float Y)
{
	float pi = 3.1415;

	float raio = 0.5;

	float semivol = pi * raio;

	// BodyDef
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(X / SCALE, Y / SCALE);
	BodyDef.type = b2_dynamicBody;
	b2Body *Body = world.CreateBody(&BodyDef);

	// Shape
	b2CircleShape forma;
	forma.m_radius = raio;

	

	// Fixture
	b2FixtureDef fix;
	fix.shape = &forma;
	fix.density = 3/(semivol * semivol);
	fix.friction = 0;
	fix.restitution = 0.9;

	Body->CreateFixture(&fix);
	BodyData *data = new BodyData;
	data->ID = MONSTRO;


	Body->SetUserData(data);

	Body->SetGravityScale(0);

	

}

void SceneManager::criaCaixa(b2World & world, float X, float Y, float tamanho)
{
	// Criar corpo físico
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(X / SCALE, Y / SCALE); // Pixels divididos pela escala de metros
	BodyDef.type = b2_staticBody;
	b2Body* Body = world.CreateBody(&BodyDef);


	// Definir a forma
	b2PolygonShape Shape;
	Shape.SetAsBox((tamanho / 2) / SCALE, (tamanho / 2) / SCALE); // Caixa quadrada, tamanhos iguais

	// Definir a fixture
	b2FixtureDef FixtureDef;
	FixtureDef.density = 0;
	FixtureDef.shape = &Shape;
	Body->CreateFixture(&FixtureDef);

	BodyData *data = new BodyData;
	data->ID = CAIXA;
	data->tamX = tamanho;
	data->tamY = tamanho;


	Body->SetUserData(data);

}


// Criar um triângulo equilátero
void SceneManager::criaTriangulo(b2World & world, float X, float Y)
{
	// Criar corpo físico
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(X / SCALE, Y / SCALE); // Pixels divididos pela escala de metros
	BodyDef.type = b2_staticBody;
	b2Body* Body = world.CreateBody(&BodyDef);


	// Definir a forma
	b2PolygonShape Shape;

	b2Vec2 vertices[3];

	vertices[0].Set(0.5, 0 );
	vertices[1].Set(0, 0.5);
	vertices[2].Set(-0.5, 0);


	Shape.Set(vertices, 3);

	// Definir a fixture
	b2FixtureDef fix;
	fix.shape = &Shape;
	fix.density = 0;
	fix.friction = 0.8;
	Body->CreateFixture(&fix);

	BodyData *data = new BodyData;
	data->ID = TRIANGULO;
	data->tamX = 40.; // tamanho do sprite
	data->tamY = 40.;
	


	Body->SetUserData(data);

}

void SceneManager::criaRetanguloComJoint(b2World & world, float X, float Y, float Xprego, float Yprego)
{
	// Criar corpo físico
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(X / SCALE, Y / SCALE);
	BodyDef.type = b2_dynamicBody;
	BodyDef.awake = false;
	b2Body* Body = world.CreateBody(&BodyDef);
	


	// Definir a forma
	b2PolygonShape Shape;
	Shape.SetAsBox((96 / 2) / SCALE, (32 / 2) / SCALE);

	// Fixture
	b2FixtureDef fix;
	fix.shape = &Shape;
	fix.density = 10/(96*32);
	fix.friction = 0;
	fix.restitution = 1;

	Body->CreateFixture(&fix);


	BodyData *data = new BodyData;
	data->ID = RETANGULO_JOINT;
	data->tamX = 96;
	data->tamY = 32;

	Body->SetUserData(data);

	 // ------------------------------------------------------------------

	// criar o círculo de "prego"

	float pi = 3.1415;

	float raio = 0.2;

	float semivol = pi * raio;

	// BodyDef
	b2BodyDef def;
	def.position = b2Vec2(Xprego / SCALE, Yprego / SCALE);
	def.type = b2_staticBody;
	b2Body *Body1 = world.CreateBody(&def);

	// Shape
	b2CircleShape forma;
	forma.m_radius = raio;

	// Fixture
	b2FixtureDef fixture;
	fixture.shape = &forma;
	fixture.density = 1 / (semivol * semivol);
	fixture.friction = 0.4;
	fixture.restitution = 0.2;

	Body1->CreateFixture(&fixture);
	BodyData *dataprego = new BodyData;
	dataprego->ID = PREGO;
	dataprego->tamX = 13;
	dataprego->tamY = 13;

	
	Body1->SetUserData(dataprego);

	Body1->SetGravityScale(0);

	// Criar
	b2RevoluteJointDef jointDef;
	jointDef.bodyA = Body;
	jointDef.bodyB = Body1;	jointDef.collideConnected = false;
	jointDef.localAnchorA.Set(0, 0); 
	jointDef.localAnchorB.Set(0, 0); // centro


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
			Sprite.setOrigin(bd->tamX/2, bd->tamY/2);
			Sprite.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
			Sprite.setRotation(BodyIterator->GetAngle() * 180 / b2_pi);
			window.draw(Sprite);
		}

		else if (bd->ID == PAREDE_H)
		{
			sf::Sprite PHSprite;
			PHSprite.setTexture(PH);
			PHSprite.setOrigin(bd->tamX/2, bd->tamY/2);
			PHSprite.setPosition(BodyIterator->GetPosition().x * SCALE, BodyIterator->GetPosition().y * SCALE);
			PHSprite.setRotation(180 / b2_pi * BodyIterator->GetAngle());
			window.draw(PHSprite);
		}

		else if (bd->ID == PAREDE_V)
		{
			sf::Sprite PVSprite;
			PVSprite.setTexture(PV);
			PVSprite.setOrigin(bd->tamX/2, bd->tamY/2);
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

		else if (bd->ID == PLATAFORMA) {
			sf::Sprite PlataformaSprite;
			PlataformaSprite.setTexture(PlatformTexture);
			PlataformaSprite.setOrigin(bd->tamX/2, bd->tamY/2);
			PlataformaSprite.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
			PlataformaSprite.setRotation(BodyIterator->GetAngle() * 180 / b2_pi);
			window.draw(PlataformaSprite);
		}

		else if (bd->ID == TRIANGULO) {
			sf::Sprite Triangulo;
			Triangulo.setTexture(TrianguloTexture);
			Triangulo.setOrigin(bd->tamX / 2, bd->tamY / 2);
			Triangulo.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
			Triangulo.setRotation(BodyIterator->GetAngle() * 180 / b2_pi);
			window.draw(Triangulo);
		}

		else if (bd->ID == RETANGULO_JOINT) {
			sf::Sprite RJ;
			RJ.setTexture(RetanguloTexture);
			RJ.setOrigin(bd->tamX / 2, bd->tamY / 2);
			RJ.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
			RJ.setRotation(BodyIterator->GetAngle() * 180 / b2_pi);
			window.draw(RJ);
		}

		else if (bd->ID == PREGO) {
			sf::Sprite Prego;
			Prego.setTexture(PregoTexture);
			Prego.setOrigin(bd->tamX / 2, bd->tamY / 2);
			Prego.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
			Prego.setRotation(BodyIterator->GetAngle() * 180 / b2_pi);
			window.draw(Prego);
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

bool SceneManager::isAnyKeyPressed()
{
	for (int k = -1; k < sf::Keyboard::KeyCount; ++k)
	{
		if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(k)))
			return true;
	}
	return false;
}


// chamar na execução do nível com a chamada da leitura do arquivo de caminhos
void SceneManager::lerLevel(std::string arquivo, b2World &world)
{

	std::ifstream Arquivo(arquivo);
	if (Arquivo) {

		int levelAtual, quadrados, retangulos_moveis, circulos, triangulos, retangulos_joint, pendulos, portais;
		float X, Y, Xprego, Yprego, tamanho /* <- apenas para caixa quadrada */, altura, largura, raio;

		Arquivo >> levelAtual;

		Arquivo >> quadrados >> retangulos_moveis >> circulos >> triangulos >> retangulos_joint >> pendulos >> portais;
		

			// ler os quadrados
			for (int i = 0; i < quadrados; i++) {
				Arquivo >> X >> Y >> tamanho;
				criaCaixa(world, X, Y, tamanho);

			}

			// outras criações...
			// ...

			for (int i = 0; i < triangulos; i++) {

				Arquivo >> X >> Y;
				criaTriangulo(world, X, Y);
			}

			for (int i = 0; i < retangulos_joint; i++) {
				Arquivo >> X >> Y >> Xprego >> Yprego;
				criaRetanguloComJoint(world, X, Y, Xprego, Yprego);
			}



	}
		
		
}

void SceneManager::lerCaminhos(std::string arquivo)
{
	int qtd;
	std::string temp;

	std::ifstream Arquivo(arquivo);
	if (Arquivo) {

		// ler quantidade de níveis
		Arquivo >> qtd;

		levelPath = new std::string[qtd];

		// ler o caminho de cada nível
		for (int i = 0; i < qtd; i++) {

			Arquivo >> temp; // pega a string e passa pra temporária
			levelPath[i] = temp; // define o valor da posição i
		}
	}

}

std::string SceneManager::getLevelPath(int i)
{
	return levelPath[i];
}



