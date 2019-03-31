// UEA Graphics 1 coursework
//
// Author: Matthew Taylor

#include "freeglut.h"
#include <SOIL.h> // include the SOIL header file (for loading images)
#include <iostream>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include "Game.h"
#include "Entities.h"

using namespace std;

// create game object to manage parameters
Game game;

// create entities
Entity playerEntity(game, 32.0f, 32.0f);		// player entity
Enemy enemy1(game, 384.0f, 160.0f);
Enemy enemy2(game, 600.0f, 32.0f);

// create moving platform object
MovingPlatform platform1(game, 96.0f, 96.0f);	// moving platform


// opengl function prototypes
void display();				//called in winmain to draw everything to the screen
void reshape(int width, int height);				//called when the window is resized
void init();				//called in winmain when the program starts.
void keyOperations();
void keySpecialOperations();
void update();				//called in winmain to update variables

// game function prototypes
void drawLevel();

// texture loader
int loadTextures()
{
	// loads image directly as texture
	game.tileTextures.push_back(SOIL_load_OGL_texture
	(
		"textures/tiles/GrassCliffMid.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	// loads image directly as texture
	game.tileTextures.push_back(SOIL_load_OGL_texture
	(
		"textures/tiles/Dirt.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.bgTexture.push_back(SOIL_load_OGL_texture
	(
		"textures/bg/Background.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.bgTexture.push_back(SOIL_load_OGL_texture
	(
		"textures/bg/gameoverbg.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.playerSpriteRunning.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/1/0.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.playerSpriteRunning.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/1/1.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.playerSpriteRunning.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/1/2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.buttons.push_back(SOIL_load_OGL_texture
	(
		"textures/buttons/b-start.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.buttons.push_back(SOIL_load_OGL_texture
	(
		"textures/buttons/b-quit.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.coinSprite.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/2/image 1.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.coinSprite.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/2/image 2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.coinSprite.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/2/image 3.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.coinSprite.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/2/image 4.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.coinSprite.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/2/image 5.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.coinSprite.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/2/image 6.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.coinSprite.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/2/image 7.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.coinSprite.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/2/image 8.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.coinSprite.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/2/image 9.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.coinSprite.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/2/image 10.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.coinSprite.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/2/image 11.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.coinSprite.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/2/image 12.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.coinSprite.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/2/image 13.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.coinSprite.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/2/image 14.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.coinSprite.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/2/image 15.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.coinSprite.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/2/image 16.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.enemy1Texture.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/3/tile000.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.enemy1Texture.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/3/tile001.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.enemy1Texture.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/3/tile002.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.enemy1Texture.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/3/tile003.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));


	// check for errors
	if (game.tileTextures.at(0) == 0) {
		cout << "Error loading textures" << endl;
		exit(0);
	}

	// bind and generate texture
	glBindTexture(GL_TEXTURE_2D, game.tileTextures[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, game.bgTexture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, game.bgTexture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, game.playerSpriteRunning[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			
	glBindTexture(GL_TEXTURE_2D, game.playerSpriteRunning[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	glBindTexture(GL_TEXTURE_2D, game.playerSpriteRunning[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, game.buttons[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, game.buttons[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, game.coinSprite[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, game.coinSprite[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, game.coinSprite[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, game.coinSprite[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, game.coinSprite[4]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, game.coinSprite[5]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, game.coinSprite[6]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, game.coinSprite[7]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, game.coinSprite[8]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, game.coinSprite[9]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, game.coinSprite[10]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, game.coinSprite[11]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, game.coinSprite[12]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, game.coinSprite[13]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, game.coinSprite[14]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, game.coinSprite[15]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, game.enemy1Texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, game.enemy1Texture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, game.enemy1Texture[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// error checking
	GLenum errorCode = glGetError();
	if (errorCode != GL_NO_ERROR) {
		cout << "Problem binding/setting texture parameters" << endl;
	}

	// enable blending on the alpha channel
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// add loaded textures to entities
	playerEntity.spriteSet.push_back(game.playerSpriteRunning);
	enemy1.spriteSet.push_back(game.enemy1Texture);
	enemy2.spriteSet.push_back(game.enemy1Texture);

	return true;
}

void moveCamera() {
	// update camera position variables to follow player
	game.camX = playerEntity.posX - (game.screenWidth / 2);
	game.camY = playerEntity.posY - (game.screenHeight / 2);

	// clamp camera to level edges
	if (game.camX < 0)	// left clamp
		game.camX = 0;
	if (game.camY < 0)	// bottom clamp
		game.camY = 0;
	if (game.camX > game.levelActualWidth - game.screenWidth)	// right clamp
		game.camX = (float)game.levelActualWidth - game.screenWidth;
	if (game.camY > game.levelActualHeight - game.screenHeight)	// top clamp
		game.camY = (float)game.levelActualHeight - game.screenHeight;

	glTranslatef(-game.camX, -game.camY, 0.0f);
}

void drawLevel() {

	// draw background
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, game.bgTexture[0]);

	glBegin(GL_QUADS); 	// draw from bottom left, clockwise
		glTexCoord2d(1.0, 1.0);
		glVertex2f(0, 0);

		glTexCoord2d(1.0, 0.0);
		glVertex2f(0, game.levelActualHeight);

		glTexCoord2d(0.0, 0.0);
		glVertex2f(game.levelActualWidth, game.levelActualHeight);

		glTexCoord2d(0.0, 1.0);
		glVertex2f(game.levelActualWidth, 0);
	glEnd();

	glDisable(GL_TEXTURE_2D);


	// draw tiles
	for (int x = 0; x < game.levelWidth; x++) {
		for (int y = 0; y < game.levelHeight; y++) {
			char tile = game.getTile(&game, x, y);

			if (tile == '#' || tile == 'D' || tile == '1') {

				// enable and bind texture relevant texture
				glEnable(GL_TEXTURE_2D);
				if (tile == '#') { // grass tile
					glBindTexture(GL_TEXTURE_2D, game.tileTextures[0]);
				}
				if (tile == 'D') { // dirt tile
					glBindTexture(GL_TEXTURE_2D, game.tileTextures[1]);
				}

				if (tile == '1') { // collectible coin tile
					glBindTexture(GL_TEXTURE_2D, game.coinSprite[(int)game.coinSpriteFrame]);
				}

				if (game.coinSpriteFrame > 15)
					game.coinSpriteFrame = 0;

				glBegin(GL_POLYGON); 	// draw from bottom left, clockwise

				glTexCoord2d(1.0, 1.0);
				glVertex2f(x * game.tileWidth, y * game.tileHeight);

				glTexCoord2d(1.0, 0.0);
				glVertex2f(x * game.tileWidth, y * game.tileHeight + game.tileHeight);

				glTexCoord2d(0.0, 0.0);
				glVertex2f(x * game.tileWidth + game.tileWidth, y * game.tileHeight + game.tileHeight);

				glTexCoord2d(0.0, 1.0);
				glVertex2f(x * game.tileWidth + game.tileWidth, y * game.tileHeight);
				glEnd();

				glDisable(GL_TEXTURE_2D);
			}
		}
	}
}

void initLevel1() {

	// levelMap encodes each tile as a character in a string
	// key: - : empty space
	//      # : ground tile
	//		D : dirt tile (like ground tile but nothing on top)
	//		1 : collectable (value 1)
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "D-----------------------------------------------1-1-1-1--------D";
	game.levelMap += "D----------------------------------------------#########-----1-D";
	game.levelMap += "D------------------------------------------------------------##D";
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "D----------------------------------------------------------1---D";
	game.levelMap += "D---------------------------------------------------------###--D";
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "D------------------------------------------------1-------------D";
	game.levelMap += "D-------------------------------------1--------#####-----------D";
	game.levelMap += "D-----------------------------------#####----------------------D";
	game.levelMap += "D-----------------------------------DDDDD----------------------D";
	game.levelMap += "###############################################################D";

	// reverses level map string so it is rendered the right way round
	reverse(game.levelMap.begin(), game.levelMap.end());

	// sets positions of entities
	playerEntity.posX = 32.0f;
	playerEntity.posY = 32.0f;	
	enemy1.posX = 384.0f;
	enemy1.posY = 160.0f;
	enemy2.posX = 600.0f;
	enemy2.posY = 32.0f;

		playerEntity.alive = true;
}

// resizes opengl windows
void reshape(int width, int height)	{
	game.screenWidth = width; game.screenHeight = height;	// to ensure the mouse coordinates match 
															// we will use these values to set the coordinate system
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();

	gluOrtho2D(0, game.screenWidth, 0, game.screenHeight);        // set the coordinate system for the window

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();
}

// initialise opengl window
void init() {

	// add entities to vector
	game.movingPlatforms.push_back(&platform1);
	game.enemies.push_back(&enemy1);
	game.enemies.push_back(&enemy2);
}

// processes key presses
void keyOperations() {

	if (game.keyStates[27]) // escape
		exit(0);

	if (game.keyStates['w']) {
		// check if player has left ground
		if (playerEntity.onGround) {
			playerEntity.onGround = false;	// flag player as not being on ground
			playerEntity.jumping = true;	// flag player as jumping
			playerEntity.jumpTime = glutGet(GLUT_ELAPSED_TIME);
			playerEntity.velY = 1.3f;
		}

		// check if player is jumping
		if (playerEntity.jumping) {
			// calculate how long player has been jumping
			int jumpTime = glutGet(GLUT_ELAPSED_TIME) - playerEntity.jumpTime;

			// if player has been jumping less than 100ms, allow more up-velocity to be added
			if (jumpTime < 150) {
				playerEntity.velY = game.playerJumpRate;
			}
		}
	}

	// only allow x-axis movement when player is alive
	if (playerEntity.alive) {
		if (game.keyStates['a'])
			playerEntity.velX = -game.playerAccelRate;

		if (game.keyStates['d'])
			playerEntity.velX = game.playerAccelRate;
	}
}

void keySpecialOperations() {
	// process special keys
}

void keyPressed(unsigned char key, int x, int y) {
	game.keyStates[key] = true;
}

void keySpecialPressed(int key, int x, int y) {
	game.keySpecialStates[key] = true;
}

void keyUp(unsigned char key, int x, int y) {
	game.keyStates[key] = false;
}

void keySpecialUp(int key, int x, int y) {
	game.keySpecialStates[key] = false;
}

void mouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)	{
			game.leftPressed = true;
			game.mouseX = x;
			game.mouseY = y;
		}
		else {
			game.leftPressed = false;
			break;
		}
	case GLUT_RIGHT_BUTTON:
		// do nothing
		break;
	default:
		break;
	}
}

void update() {
	glutPostRedisplay();
}

void drawTitleScreen() {
	// draw background
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, game.bgTexture[0]);

	glBegin(GL_QUADS); 	// draw from bottom left, clockwise
		glTexCoord2d(1.0, 1.0);
		glVertex2f(0, 0);

		glTexCoord2d(1.0, 0.0);
		glVertex2f(0, game.screenHeight);

		glTexCoord2d(0.0, 0.0);
		glVertex2f(game.screenWidth, game.screenHeight);

		glTexCoord2d(0.0, 1.0);
		glVertex2f(game.screenWidth, 0);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	// draw start button
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, game.buttons[0]);

	glBegin(GL_QUADS); 	// draw from bottom left, clockwise
		glTexCoord2d(0.0, 1.0);			
		glVertex2f(400.0f, 200.0f);	// bl

		glTexCoord2d(1.0, 1.0);			
		glVertex2f(500.0f, 200.0f);	// br

		glTexCoord2d(1.0, 0.0);			
		glVertex2f(500.0f, 235.0f);	// tr

		glTexCoord2d(0.0, 0.0);			
		glVertex2f(400.0f, 235.0f); // tl

	glEnd();

	glDisable(GL_TEXTURE_2D);

}

void drawGameOverScreen() {
	// draw background
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, game.bgTexture[1]);

	glBegin(GL_QUADS); 	// draw from bottom left, clockwise
	glTexCoord2d(0.0, 1.0);
	glVertex2f(1.0, 1.0);	// bl

	glTexCoord2d(0.0, 0.0);
	glVertex2f(0, game.screenHeight);	// tl

	glTexCoord2d(1.0, 0.0);
	glVertex2f(game.screenWidth, game.screenHeight);	// tr

	glTexCoord2d(1.0, 1.0);
	glVertex2f(game.screenWidth, 0);	// br
	glEnd();

	glDisable(GL_TEXTURE_2D);

	// draw start button
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, game.buttons[0]);

	glBegin(GL_QUADS); 	// draw from bottom left, clockwise
	glTexCoord2d(0.0, 1.0);
	glVertex2f(400.0f, 200.0f);	// bl

	glTexCoord2d(1.0, 1.0);
	glVertex2f(500.0f, 200.0f);	// br

	glTexCoord2d(1.0, 0.0);
	glVertex2f(500.0f, 235.0f);	// tr

	glTexCoord2d(0.0, 0.0);
	glVertex2f(400.0f, 235.0f); // tl

	glEnd();

	glDisable(GL_TEXTURE_2D);

}

void processTitleScreenInput() {
	if(game.leftPressed) {
		if(game.mouseX >= 400 && game.mouseX <= 500 && game.mouseY >= 465 && game.mouseY <= 500) {
			game.gameStage = "level1";
		}
	}
}

void processGameOverScreenInput() {
	if (game.leftPressed) {
		if (game.mouseX >= 400 && game.mouseX <= 500 && game.mouseY >= 465 && game.mouseY <= 500) {
			initLevel1();
			game.gameStage = "level1";
		}
	}
}

void doTitleScreen() {
	// draw background
	drawTitleScreen();

	// process inputs for buttons
	processTitleScreenInput();
}

void doGameOverScreen() {
	// draw background
	drawGameOverScreen();

	// process inputs for buttons
	processGameOverScreenInput();
}

void doGameLevel() {
	moveCamera();
	drawLevel();
	game.drawScore(&game);
	playerEntity.draw();
	playerEntity.playerSpriteFrame += 0.01f;	// update playerSpriteFrame animation
	game.coinSpriteFrame += 0.01f;				// update coin sprite frame
	
	// draw all moving platforms
	for (int i = 0; i < game.movingPlatforms.size(); i++) {
		game.movingPlatforms.at(i)->draw();
	}

	// draw all enemy objects
	for(int i = 0; i < game.enemies.size(); i++) {
		game.enemies.at(i)->spriteFrame += 0.01f;	// update animation frame
		game.enemies.at(i)->draw();					// draw enemy
	}
}

// main display function
void display()
{
	// get time of start of rendering for calculating delta time
	int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);

	// calculate the time since last playerSpriteFrame was rendered
	game.deltaTime = timeSinceStart - game.oldTimeSinceStart;

	// clamp deltatime to stop weird stuff happening
	if (game.deltaTime < 0)
		game.deltaTime = 0;
	
	// store old timeSinceStart value
	game.oldTimeSinceStart = timeSinceStart;
	
	// process key operations
	keyOperations();
	keySpecialOperations();

	// clear buffer, load identity, ready for next playerSpriteFrame
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	// game drawing logic
	if(game.gameStage == "title")
		doTitleScreen();
	if(game.gameStage == "level1")
		doGameLevel();
	if (game.gameStage == "gameover")
		doGameOverScreen();

	//glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

// 5ms timer
void timer(int t) {


	// run timer in 5ms
	glutTimerFunc(5, timer, 0);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(game.screenWidth, game.screenHeight);
	glutInitWindowPosition(70, 70);

	glutCreateWindow("Matt's platform game");

	init();
	initLevel1();	// run level initialisation
	loadTextures();

	int oldTimeSinceStart = 0; // used to calc delta time

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	// set the timer function
	glutTimerFunc(50, timer, 0);

	glutIdleFunc(display);

	// set keyboard functions
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);
	glutSpecialFunc(keySpecialPressed);
	glutSpecialUpFunc(keySpecialUp);
	glutMouseFunc(mouse);

	glutMainLoop();

	return 0;
}


