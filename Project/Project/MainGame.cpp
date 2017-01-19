#include "MainGame.h"

MainGame::MainGame() {
	this->window = nullptr;
	this->screenWidth = 400;
	this->screenHeight = 400;
	this->gameState = GameState::PLAY;
}
MainGame::~MainGame() {

}

void MainGame::run() {
	init();
	gameLoop();
}

void MainGame::init() {
	SDL_Init(SDL_INIT_EVERYTHING);

	this->window = SDL_CreateWindow("Baseball", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_OPENGL);

	if (window == nullptr) {
		fatalError("SDL Window could not be created");
	}

	SDL_GLContext context = SDL_GL_CreateContext(window);
	if (context == nullptr) {
		fatalError("SDL_GL context could not be created");
	}

	GLenum error = glewInit();
	if (error != GLEW_OK) {
		fatalError("GLEW could not be initialized");
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(0.5f, 0.0f, .6f, 1.0);

}
void MainGame::processInput() {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_QUIT: gameState = GameState::EXIT; break;
		case SDL_MOUSEMOTION: cout << e.motion.x << " " << e.motion.y << endl;
		}
	}
}

void MainGame::drawGame() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableClientState(GL_COLOR_ARRAY);

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(0,0);
	glVertex2f(0, 500);
	glVertex2f(-500, 500);
	glEnd();

	SDL_GL_SwapWindow(window);
}

void MainGame::gameLoop() {
	while (gameState != GameState::EXIT) {
		processInput();
		drawGame();
	}
}

void MainGame::fatalError(string errorString) {
	cout << errorString << endl;
	system("pause");
	SDL_Quit();
}