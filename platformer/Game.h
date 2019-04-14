#pragma once
#include <string>
#include "freeglut.h"
#include <vector>

using namespace std;

// forward declares
class MovingPlatform;	
class Entity;
class Enemy;
class Projectile;

class Game {
public:
	// DEBUG FLAG - set to true to view collision detection drawing 
	bool debug = false;

	// global parameters
	int screenWidth = 900, screenHeight = 700;
	int levelWidth = 64;	// store level dimensions (in tiles)
	int levelHeight = 32;
	int tileWidth = 32;		// store tile dimension information
	int tileHeight = 32;
	float playerAccelRate = 0.35f;	// param for player acceleration
	float playerJumpRate = 0.7f;	// param for player jump rate
	float playerDecelRate = 0.2f;
	float gravityRate = 0.004f;		// the rate gravity works at
	int maxLevels = 3;

	// pre-computes
	int levelActualWidth = levelWidth * tileWidth;
	int levelActualHeight = levelHeight * tileHeight;
	int halfTileH = tileHeight / 2;
	int halfTileW = tileWidth / 2;

	// deltatime variables
	int oldTimeSinceStart;	// used to calculate deltatime
	int deltaTime;			// used to store deltatime
	
	// key and mouse processing
	bool* keyStates = new bool[256]();
	bool* keySpecialStates = new bool[256]();
	bool keys[256];
	bool leftPressed = false;
	int mouseX;
	int mouseY;
	bool canShoot = true;

	// camera position
	float camX = 0.0f;
	float camY = 0.0f;
	
	// game variables
	int onLevel = 1;	// tracks what level the player is on
	string levelMap;	// stores level tilemap
	int playerScore = 0;
	std::string gameStage = "title";	// stores what part of the game is running
	bool gemCollected = false;			// tracks whether player can exit level

	// textures
	vector<GLuint> tileTextures;		// stores level tile textures
	vector<GLuint> bgTexture;			// stores background textures
	vector<GLuint> playerSpriteRunning;	// stores player sprite running
	vector<GLuint> playerSpriteStillShooting;
	vector<GLuint> playerSpriteRunShooting;
	vector<GLuint> bulletSprite;
	vector<GLuint> coinSprite;			// stores spinning coin sprite
	vector<GLuint> enemy1Texture;		// stores sprite for bat enemy
	vector<GLuint> buttons;				// stores button textures
	vector<GLuint> buttonGlow;			// stores button glow textures
	vector<GLuint> gemTexture;			// stores the object gem sprite
	vector<GLuint> doorTexture;			// stores the door texture ([0] for shut, [1] for open)

	// texture frame counters
	float coinSpriteFrame = 0;		// coin spin frame counter
	float gemSpriteFrame = 0;		// gem shine frame counter
	float cloudGlowSpriteFrame = 0;	// cloud glow frame counter

	// vector of vectors to store textures
	vector<vector<GLuint> > playerTextures;
	vector<vector<GLuint> > enemy1Textures;

	// vectors to store game objects
	vector<MovingPlatform*> movingPlatforms;
	vector<Enemy*> enemies;
	vector<Projectile> projectiles;	// keeps track of all bullets 

	// stores selected position on menu screen
	int menuScreenButton = 0;

	// utility methods for running the game
	// getTile returns the the tile at a given x,y coordinate
	static char getTile(Game *game, int x, int y);

	// emptyTile sets a tile to blank (for when collectables are collected)
	static void emptyTile(Game *game, int x, int y);

	// draw gamescore on HUD
	static void drawScore(Game *game);

	// utility function to draw circles
	void drawCircle(float cx, float cy, float r)
	{
		const int circleSegments = 300;

		const float theta = 2 * 3.1415926 / float(circleSegments);
		const float tangetial_factor = tanf(theta);	//calculate the tangential factor 
		const float radial_factor = cosf(theta);	//calculate the radial factor 

		float x = r;	// starts at angle = 0 
		float y = 0;

		// start drawing the line loop
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < circleSegments; i++)
		{
			glVertex2f(x + cx, y + cy);//output vertex 

			//calculate the tangential vector 
			//remember, the radial vector is (x, y) 
			//to get the tangential vector we flip those coordinates and negate one of them 
			float tx = -y;
			float ty = x;

			//add the tangential vector 

			x += tx * tangetial_factor;
			y += ty * tangetial_factor;

			//correct using the radial factor 

			x *= radial_factor;
			y *= radial_factor;
		}
		glEnd();
	}

};

