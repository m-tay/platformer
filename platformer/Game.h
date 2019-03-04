#pragma once
#include <string>
#include "freeglut.h"
#include <vector>


using namespace std;

class MovingPlatform;	// forward declare the MovingPlatform class

class Game
{
	public:
		// global parameters
		bool debug = false;	// flag to include debug information
		int screenWidth = 900, screenHeight = 700;
		bool keys[256];
		bool leftPressed = false;
		int mouseX;
		int mouseY;
		std::string gameStage = "title";
		int levelWidth = 64;	// store level dimensions (in tiles)
		int levelHeight = 32;
		int tileWidth = 32;		// store tile dimension information
		int tileHeight = 32;
		float playerAccelRate = 0.35f;	// param for player acceleration
		float playerJumpRate = 0.7f;	// param for player jump rate
		float playerDecelRate = 0.2f;
		float gravityRate = 0.004f;	// the rate gravity works at
									// pre-calculations
		float coinSpriteFrame = 0;
		int playerScore = 0;

		int levelActualWidth = levelWidth * tileWidth;
		int levelActualHeight = levelHeight * tileHeight;

		// deltatime variables
		int oldTimeSinceStart;	// used to calculate deltatime
		int deltaTime;			// used to store deltatime

		// arrays to store all possible keystates
		bool* keyStates = new bool[256]();
		bool* keySpecialStates = new bool[256]();

		// camera position
		float camX = 0.0f;
		float camY = 0.0f;
		
		// game variables
		string levelMap;	// stores level tilemap
		GLuint tileTextures[2];	// stores level tile textures
		GLuint bgTexture[1];	// stores background textures
		GLuint playerSprite[3];	// stores player sprite
		GLuint coinSprite[16];  // stores spinning coin sprite
		GLuint buttons[2];		// stores button textures
		vector<MovingPlatform*> movingPlatforms;


		// utility methods for running the game
		// getTile returns the the tile at a given x,y coordinate
		static char getTile(Game *game, int x, int y);

		// emptyTile sets a tile to blank (for when collectables are collected)
		static void emptyTile(Game *game, int x, int y);

		// draw gamescore on HUD
		static void drawScore(Game *game);

};

