#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include <string.h>
#include <cstring>
#include <vector>
#include <ctime>
#include <sstream>

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"

using namespace sf;
using namespace std;

class Game_Engine
{
private:
	//window variables
	RenderWindow* window;
	VideoMode vm;
	Event ev;

	//snake variables
	vector<RectangleShape>snake_pieces;
	RectangleShape snake;
	int snake_x[2401];
	int snake_y[2401];
	float movement = 10;
	bool right = true;
	bool left = false;
	bool up = false;
	bool down = false;
	int snake_piece_count;

	//score variables
	Font font;
	Text score_;

	//Food variables
	RectangleShape food;
	bool food_spawned = false;
	int fx;
	int fy;

	//map variables
	RectangleShape wall[4];
	float grid_x[49];
	float grid_y[49];

	//game end and score variables
	bool EndGame = false;
	bool CloseGame = false;

	//init functions
	void initWindow();
	void initScore();
	void initMap();
	void initSnake();
	void initFood();

	//render functions
	void renderMap();
	void renderText();
	void renderSnake();
	void renderFood();

	//update functons
	void moveSnake();
	void spawnFood();
	void eatFood();
	void growSnake();

	//polling function
	void pollevents();

	//collision functions
	void collisions();

	//End of game screen and score functions
	void score();

public:
	bool running();
	void EndScreen();

	void update();
	void render();

	Game_Engine();
	virtual ~Game_Engine();
};

