#pragma once

#include <string>
#include <list>
#include <vector>
#include <iostream>
#include <fstream>
#include <ctime>
#include <random>
#include <functional>
#include <algorithm>
#include "Team.h"
#include "Game.h"
#include "League.h"
#include <Windows.h>
#include <SDL/SDL.h>
#include <GL/glew.h>

using namespace std;

enum class GameState { PLAY, EXIT };



class MainGame {
private:

	void init();
	void processInput();
	void gameLoop();
	void drawGame();
	void fatalError(string errorString);
	SDL_Window* window;
	int screenWidth, screenHeight;
	GameState gameState;

public:
	MainGame();
	~MainGame();

	void run();

};