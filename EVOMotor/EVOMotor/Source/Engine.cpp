#include "Include/Engine.h"
#include "Platform/debug.h"

int Engine::windowWidth = 700;
int Engine::windowHeight = 500;

Engine::Engine(void)
{
}

Engine::~Engine(void)
{
	delete graphics;
	delete shader;
	delete viewport;
}

void Engine::init()
{
	graphics = new Graphics(windowWidth,windowHeight);
	viewport = new Viewport((float)windowWidth,(float)windowHeight);
	spriteBatch = new SpriteBatch();
	//texture = Texture::load("Assets/Waluigi.tga");
	//texture2 = Texture::load("Assets/vanaja.tga");
	shader = new Shader("Assets/Shaders/basic.vert", "Assets/Shaders/basic.frag");
	
	spriteBatch->init(shader);
	spriteBatch->addObject("Assets/Waluigi.tga",200,200,200,200);
	spriteBatch->addObject("Assets/vanaja.tga",100,100,400,400);
	//graphics->init();
	fileReader->loadFile("Assets/imadethis.txt");

	/*texture loadTGA("Assets/kuva.tga",header);*/

	//sprite = new SpriteObject(200, 200, 200, 200, texture, shader);
	
	//sprite2 = new SpriteObject(400, 400, 200, 200, texture2, shader);


	red = 0;
	blue = 0;
	green = 0;
}

void Engine::update()
{
	red = rand()%2+0.01f;
	blue = rand()%2+0.01f;
	green = rand()%2+0.01f;

	spriteBatch->spriteList[0]->setColor(glm::vec4(red,blue,green,1.f));
	spriteBatch->spriteList[1]->setPosition(rand()%10+500,rand()%10+300);
	//sprite->setPosition(rand()%10+100,rand()%10+100);
	//sprite->setRotationZ(rand()%10);
	//sprite->setColor(glm::vec4(red,green,blue,1.f));

	//sprite2->setPosition(rand()%10+500,rand()%10+300);
	//sprite2->setRotationZ(rand()%10);
	//sprite2->setColor(glm::vec4(red,green,blue,1.f));
}

void Engine::draw()
{	
	graphics->clear(1.0f,0.0f,1.0f);

	spriteBatch->draw(viewport);

	//viewport->draw(sprite);
	//viewport->draw(sprite2);

//	graphics->draw(window);
}

float Engine::getTotalTime()
{
	return glfwGetTime();
}