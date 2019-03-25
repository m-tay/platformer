#pragma once
#include <string>
#include "freeglut.h"
#include <vector>


using namespace std;

class MovingPlatform;	// forward declares
class Entity;
class Enemy;

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

		// textures
		vector<GLuint> tileTextures;			// stores level tile textures
		vector<GLuint> bgTexture;			// stores background textures
		vector<GLuint> playerSpriteRunning;			// stores player sprite
		vector<GLuint> coinSprite;			// stores spinning coin sprite
		vector<GLuint> enemy1Texture;
		vector<GLuint> buttons;				// stores button textures

		// vector of vectors to store textures
		vector<vector<GLuint> > playerTextures;
		vector<vector<GLuint> > enemy1Textures;

		// vectors to store game objects
		vector<MovingPlatform*> movingPlatforms;
		vector<Enemy*> enemies;

		// utility methods for running the game
		// getTile returns the the tile at a given x,y coordinate
		static char getTile(Game *game, int x, int y);

		// emptyTile sets a tile to blank (for when collectables are collected)
		static void emptyTile(Game *game, int x, int y);

		// draw gamescore on HUD
		static void drawScore(Game *game);

};

