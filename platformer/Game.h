#pragma once
#include <string>
#include "freeglut.h"

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
		float playerJumpRate = 0.9f;	// param for player jump rate
		float playerDecelRate = 0.2f;
		float gravityRate = 0.004f;	// the rate gravity works at
										// pre-calculations
		int levelActualWidth = levelWidth * tileWidth;
		int levelActualHeight = levelHeight * tileHeight;

		// arrays to store all possible keystates
		bool* keyStates = new bool[256]();
		bool* keySpecialStates = new bool[256]();

		// camera position
		float camX = 0.0f;
		float camY = 0.0f;
		
		// game variables
		std::string levelMap;		// stores level tilemap
		GLuint tileTextures[2];	// stores level tile textures
		GLuint bgTexture[1];	// stores background textures
		GLuint playerSprite[3];	// stores player sprite
		GLuint buttons[2];		// stores button textures

		static char getTile(Game *game, int x, int y);
};
