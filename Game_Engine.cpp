#include "Game_Engine.h"



void Game_Engine::initWindow()
{
	vm.height = 500;
	vm.width = 500;

	window = new RenderWindow(vm, "Snake", Style::Titlebar | Style::Close);
	window->setFramerateLimit(20);
}

void Game_Engine::initScore()
{
	font.loadFromFile("C:\\Users\\adria\\source\\repos\\snake\\snake\\VINERITC.ttf");

	score_.setFont(font);
	score_.setCharacterSize(20);
	score_.setFillColor(Color(255,255,255,100));
	score_.setPosition(450, 20);
	score_.setString("0");
}

void Game_Engine::initMap()
{
	for (int i = 0; i < 2; i++)
	{
		wall[i].setFillColor(Color::White);
		wall[i].setSize(Vector2f(5, vm.height));
	}
	for (int i = 2; i < 4; i++)
	{
		wall[i].setFillColor(Color::White);
		wall[i].setSize(Vector2f(vm.width, 5));
	}

	wall[0].setPosition(0, 0);
	wall[1].setPosition(vm.width-5, 0);
	wall[2].setPosition(0, vm.height - 5);
	wall[3].setPosition(0, 0);

	//grid values
	float holder = 5;
	for (int i = 0; i < 49; i++)
	{
		grid_x[i] = holder;
		grid_y[i] = holder;
		holder = holder + 10;
	}
}

void Game_Engine::initSnake()
{
	snake.setSize(Vector2f(10, 10));
	snake.setFillColor(Color::Green);
	snake.setPosition(Vector2f(grid_x[24], grid_y[24]));
	
	snake_pieces.push_back(snake);

	snake_x[0] = 24;
	snake_y[0] = 24;

	snake_piece_count = 0;
}

void Game_Engine::initFood()
{
	food.setFillColor(Color::Red);
	food.setSize(Vector2f(10.f, 10.f));
}
//^^^^^^^^^^^^ init functions

void Game_Engine::renderMap()
{
	for (int i = 0; i < 4; i++)
	{
		window->draw(wall[i]);
	}
}

void Game_Engine::renderText()
{
	window->draw(score_);
}

void Game_Engine::renderSnake()
{
	for (int i = 0; i < snake_piece_count + 1; i++)
	{
		window->draw(snake_pieces[i]);
	}
}

void Game_Engine::renderFood()
{
	window->draw(food);
}
//^^^^^^^^^^^ render functions

void Game_Engine::moveSnake()
{
	int holdx = snake_x[0];
	int holdy = snake_y[0];

	int cnt = snake_piece_count;

	if (snake_piece_count > 0)
	{
		for (int i = cnt; i > 0; i--)
		{
			snake_x[i] = snake_x[i - 1];
			snake_y[i] = snake_y[i - 1];
			snake_pieces[i].setPosition(grid_x[snake_x[i]], grid_y[snake_y[i]]);
		}

		/*snake_x[snake_piece_count] = snake_x[snake_piece_count - 1];
		snake_y[snake_piece_count] = snake_y[snake_piece_count - 1];
		snake_pieces[snake_piece_count].setPosition(grid_x[snake_x[snake_piece_count]], grid_y[snake_y[snake_piece_count]]);

		snake_x[1] = snake_x[0];
		snake_y[1] = snake_y[0];
		
		snake_pieces[1].setPosition(grid_x[snake_x[1]], grid_y[snake_y[1]]);
		*/
		
	}

	if (right)
	{
		snake_x[0] = snake_x[0] + 1;
	}
	else
	{
		if (left)
		{
			snake_x[0] = snake_x[0] - 1;
		}
		else
		{
			if (up)
			{
				snake_y[0] = snake_y[0] - 1;
			}
			else
			{
				if (down)
				{
					snake_y[0] = snake_y[0] + 1;
				}
			}
		}
	}
	snake_pieces[0].setPosition(grid_x[snake_x[0]], grid_y[snake_y[0]]);
}

void Game_Engine::spawnFood()
{
	if (!food_spawned)
	{
		fx = rand() % 49 - 0;
		fy = rand() % 49 - 0;

		food.setPosition(grid_x[fx], grid_y[fy]);
		food_spawned = true;
	}
}

void Game_Engine::eatFood()
{
	if (fx == snake_x[0] && fy == snake_y[0])
	{
		growSnake();
		food_spawned = false;
	}
}

void Game_Engine::growSnake()
{
	int snakex = snake_x[snake_piece_count];
	int snakey = snake_y[snake_piece_count];

	if (snake_piece_count == 0)
	{
		if (right)
		{
			snakex = snakex - 1;
		}
		else
		{
			if (left)
			{
				snakex = snakex + 1;
			}
			else
			{
				if (up)
				{
					snakey = snakey + 1;
				}
				else
				{
					if (down)
					{
						snakey = snakey - 1;
					}
				}
			}
		}
	}
	else
	{
		if (snakex < snake_x[snake_piece_count - 1])
		{
			snakex = snakex - 1;
		}
		else
		{
			if (snakex > snake_x[snake_piece_count - 1])
			{
				snakex = snakex + 1;
			}
			else
			{
				if (snakey > snake_y[snake_piece_count - 1])
				{
					snakey = snakey + 1;
				}
				else
				{
					if (snakey < snake_y[snake_piece_count - 1])
					{
						snakey = snakey - 1;
					}
				}
			}
		}
	}

	snake_piece_count = snake_piece_count + 1;

	snake_x[snake_piece_count] = snakex;
	snake_y[snake_piece_count] = snakey;

	snake.setPosition(grid_x[snakex], grid_y[snakey]);
	snake_pieces.push_back(snake);

	score();
}
//^^^^^^^^^^^ update functions

void Game_Engine::pollevents()
{
	while (window->pollEvent(ev))
	{
		switch (ev.type)
		{
		case Event::Closed:
			window->close();
			break;
		case Event::KeyPressed:
			switch (ev.key.code)
			{
			case Keyboard::A:
				if (!right)
				{
					left = true;
					right = false;
					up = false;
					down = false;
				}
				break;
			case Keyboard::W:
				if (!down)
				{
					left = false;
					right = false;
					up = true;
					down = false;
				}
				break;
			case Keyboard::D:
				if (!left)
				{
					left = false;
					right = true;
					up = false;
					down = false;
				}
				break;
			case Keyboard::S:
				if (!up)
				{
					left = false;
					right = false;
					up = false;
					down = true;
				}
				break;
			}
			break;
		}
	}
}
//^^^^^^^^^^^ event handling

void Game_Engine::collisions()
{
	if (snake_piece_count > 0)
	{
		for (int i = 1; i < snake_piece_count + 1; i++)
		{
			if (snake_x[0] == snake_x[i] && snake_y[0] == snake_y[i])
			{
				EndScreen();
			}
		}
	}

	if (snake_x[0] < 0 || snake_x[0]>48 || snake_y[0] < 0 || snake_y[0]>48)
	{
		EndScreen();
	}

}
//collision functions

void Game_Engine::score()
{
	stringstream ss;
	ss << snake_piece_count;
	score_.setString(ss.str());
}

void Game_Engine::EndScreen()
{
	bool x = false;

	while (!x)
	{
		window->clear();
		stringstream ss;
		ss << "you scored: " << snake_piece_count << "   , press escape to close the game";

		score_.setString(ss.str());
		score_.setFillColor(Color::White);
		score_.setPosition(20, 20);
		score_.setCharacterSize(20);
		window->draw(score_);
		window->display();

		while (window->pollEvent(ev))
		{
			switch (ev.type)
			{
			case Event::Closed:
				window->close();
				break;
			case Event::KeyPressed:
				snake_pieces.erase(snake_pieces.begin());
				for (int i = 0; i < snake_pieces.size(); i++)
				{
					snake_pieces.erase(snake_pieces.begin()+i);
				}
				snake_piece_count = 0;
				snake_x[0] = 24;
				snake_y[0] = 24;
				//snake.setPosition(grid_x[24], grid_y[24]);
				//snake_pieces.push_back(snake);
				
				x = true;
				break;
			}
		}
	}
}
//^^^^^^^^^ Endgame screen and score functions

bool Game_Engine::running()
{
	if (!CloseGame)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Game_Engine::update()
{
	pollevents();
	eatFood();
	spawnFood();
	moveSnake();
	collisions();
}

void Game_Engine::render()
{
	window->clear();

	//
	renderMap();
	renderText();
	renderSnake();
	renderFood();
	//

	window->display();
}
//^^^^^^^^^^^ public functions

Game_Engine::Game_Engine()
{
	initWindow();
	initMap();
	initScore();
	initSnake();
	initFood();
}


Game_Engine::~Game_Engine()
{
	delete window;
}


/*
		THE FOLLOWING IS IMPORTANT FOR FUTURE DEVELOPMENT OF CONSOLE BASED GAMES.  PLEASE READ!!!!!!!!

		NOTES:  *This is a grid based game. The map length and height are divided by 10 to give (in this specific case) 49 segments.
					2 arrays are used to store the x and y coords. These arrays are floats.
					2 more arrays are used to store a number between 0 and 49. These arrays are integers and serve as the indices to the grid arrays
					This is the simplified structure for the x values only:

							grid[49];
							snake_x[2401];			//2401 is the maximum number of possible snake pieces that can fit this specific map

							grid_x[0] = 15;
							snake_x[0] = 1;

							... .setPosition(grid_x[snake_x[0]],...);

							each snake piece is assigned an int value
							this integer is passed to the grid value
							which in turn provides a float value used to set the x position
					 
					 This method allows for easier programming because we only have to deal with the integer values in snake_x,
						which reach a max value of 48.
					 This method also makes the alignment of objects easier as the grid values remain constant

				  *Vectors are used for the snake pieces. This is due the push_back() method that allows for the easy addition of more pieces.
				  
				  *The snake pieces are moved by starting from the last piece and assigning each piece the value of the piece directly infront of it
						A counter is used to keep track of the number of pieces and is also used as an index for the last piece added		

							eg :
							snake_x[2] = snake_x[1];			//remember these value are only between 0 and 48
							snake_x[1] = snake_x[0];

							... .setPosition(grid_x[snake_x[2]], ...);
							... .setPosition(grid_x[snake_x[1]], ...);

							This is where working with grid method is really efficient
							These integer values are much easier to calculate and debug with

						This is only a representation of what is happening. In the actual code, a loop is used and the code is written in a way 
							that allows for the addition of more snake pieces
*/