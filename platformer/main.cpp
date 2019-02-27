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
#include "MovingPlatform.h"

using namespace std;

// create game object to manage paramaters
Game game;

// opengl function prototypes
void display();				//called in winmain to draw everything to the screen
void reshape(int width, int height);				//called when the window is resized
void init();				//called in winmain when the program starts.
void keyOperations();
void keySpecialOperations();
void update();				//called in winmain to update variables

// game function prototypes
void drawLevel();

// make a vector collection of moving platforms, so they can be collision checked
vector<MovingPlatform*> movingPlatforms;

// object class for all moving objects (ie. things that can move + have collisions 
class Entity {	
	public:
		float posX;	// position
		float posY;
		float velX = 0.0f;	// velocity
		float velY = 0.0f;
		float newPosX;
		float newPosY;
		char tileTL;	// holds the 4 tiles around the entity
		char tileTR;
		char tileBL;
		char tileBR;
		bool onGround; // holds whether entity is jumping or not
		float frame = 0.0f; // tracks the frame for animating the sprite
		char facing = 'r'; // holds direction entity is facing (for sprite mirroring)

		// constructor
		Entity(float x, float y) {
			posX = x;
			posY = y;
		}

		// calculates the tiles around the entity
		void findSurroundingTiles() {
			// calculate x,y coords of surrounding tiles
			// assumes entities are no bigger than 1 standard tile width
			int tileLeft = (int) newPosX / game.tileWidth;
			int tileRight = (int)(newPosX / game.tileWidth) + 1;
			int tileTop = (int) (newPosY / game.tileHeight) + 1;
			int tileBottom = (int) newPosY / game.tileHeight;

			// get the actual tile values from tilemap
			char tileTL = game.getTile(&game, tileLeft, tileTop);
			char tileTR = game.getTile(&game, tileRight, tileTop);
			char tileBL = game.getTile(&game, tileLeft, tileBottom);
			char tileBR = game.getTile(&game, tileRight, tileBottom);
		}

		// check for collisions with tilemap on x axis
		bool isCollidingX() {		
			// calculate x,y coords of surrounding tiles
			// assumes entities are no bigger than 1 standard tile width
			int tileLeft = (int) newPosX / game.tileWidth;
			int tileRight = (int) (newPosX / game.tileWidth) + 1;
			int tileTop = (int) (posY / game.tileHeight) + 1;
			int tileBottom = (int) posY / game.tileHeight;

			// get the actual tile values from tilemap
			char tileTL = game.getTile(&game, tileLeft, tileTop);
			char tileTR = game.getTile(&game, tileRight, tileTop);
			char tileBL = game.getTile(&game, tileLeft, tileBottom);
			char tileBR = game.getTile(&game, tileRight, tileBottom);

			// if any collisions detected, return true
			if (tileTL == '#' || tileTR == '#' || tileBL == '#' || tileBR == '#' ||
				tileTL == 'D' || tileTR == 'D' || tileBL == 'D' || tileBR == 'D')
				return true;

			// if not colliding, return false
			return false;
	}

		// check for collisions with tilemap on y axis
		bool isCollidingY() {
			// calculate x,y coords of surrounding tiles
			// assumes entities are no bigger than 1 standard tile width
			int tileLeft = (int) posX / game.tileWidth;
			int tileRight = (int) (posX / game.tileWidth) + 1;
			int tileTop = (int) (newPosY / game.tileHeight) + 1;
			int tileBottom = (int) newPosY / game.tileHeight;

			// get the actual tile values from tilemap
			char tileTL = game.getTile(&game, tileLeft, tileTop);
			char tileTR = game.getTile(&game, tileRight, tileTop);
			char tileBL = game.getTile(&game, tileLeft, tileBottom);
			char tileBR = game.getTile(&game, tileRight, tileBottom);

			// ceiling collision, set y velocity to 0
			if (tileTL == '#' || tileTR == '#' || tileTL == 'D' || tileTR == 'D') {
				velY = 0;
				return true;
			}

			// ground collision, set jumping flag back to false
			if (tileBL == '#' || tileBR == '#' || tileBL == 'D' || tileBR == 'D') {
				onGround = true;
				return true;
			}

			// if not colliding, return false
			return false;
		}

		bool isCollidingWithMovingPlatform() {			
			// loop through all moving platforms
			for (int i = 0; i < movingPlatforms.size(); i++) {
				// AABB edge overlap checks
				if (newPosX + game.tileWidth >= movingPlatforms.at(i)->posX								&&
					newPosX <= movingPlatforms.at(i)->posX + movingPlatforms.at(i)->platformWidth	&&
					newPosY + game.tileHeight >= movingPlatforms.at(i)->posY							&&
					newPosY <= movingPlatforms.at(i)->posY + game.tileHeight) {

					// if AABB overlap, check if entity is hitting it from the bottom
					if ((newPosX + game.tileHeight) >= movingPlatforms.at(i)->posX &&
						(newPosX + game.tileHeight) < (movingPlatforms.at(i)->posX + game.tileHeight)) {
						velY = 0;
					}
		
					return true;
				}
			}

			// if no edge overlaps detected
			return false;
		}

		void trackMovingPlatforms() {

			// loop through all moving platforms
			for (int i = 0; i < movingPlatforms.size(); i++) {

				// check if within x axis of moving platform
				if (posX >= movingPlatforms.at(i)->posX && (posX + game.tileWidth) < (movingPlatforms.at(i)->posX + movingPlatforms.at(i)->platformWidth)) {

					// check if close enough to surface of moving platform to track movement
					if ((movingPlatforms.at(i)->posY - posY + 32) > -0.3f && (movingPlatforms.at(i)->posY - posY + 32) < 0.3f) {
						posX += movingPlatforms.at(i)->velX;
						velY = 0;
						onGround = true;

					}
				}
				// if out of bounds of moving platform and was on ground
				else {
					if (onGround) {
						velY -= game.gravityRate;
					}
				}
			}
		}

		
		// update entity position based on velocity
		void updatePosition() {
			// update entity's model of the tiles surrounding it
			findSurroundingTiles();

			// calculate proposed new position
			newPosX = posX + velX;
			newPosY = posY + velY;

			// check for collision with tilemap in x axis
			if (!isCollidingX() && !isCollidingWithMovingPlatform())
				posX = newPosX;

			// check for collision in with tilemap y axis
			if (!isCollidingY() && !isCollidingWithMovingPlatform())
				posY = newPosY;

			// deceleration on x axis
			velX = 0;

			trackMovingPlatforms();

			// apply gravity 
			if(!onGround)
				velY -= game.gravityRate;


		}

		// draws the entity
		void draw() {

			updatePosition();

			if (frame > 2) // cycle frame animation back to start
				frame = 0;
			
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, game.playerSprite[(int)frame]);

			glBegin(GL_QUADS);

				glTexCoord2d(0.0, 1.0);
				glVertex2f(posX, posY);

				glTexCoord2d(1.0, 1.0);
				glVertex2f(posX + game.tileWidth, posY);
				
				glTexCoord2d(1.0, 0.0);
				glVertex2f(posX + game.tileWidth, posY + game.tileHeight);
				
				glTexCoord2d(0.0, 0.0);
				glVertex2f(posX, posY + game.tileHeight);
			glEnd();

			glDisable(GL_TEXTURE_2D);
		}
};


// create player entity object
Entity playerEntity(32.0f, 32.0f);



// texture loader
int loadTileTextures()
{
	// loads image directly as texture
	game.tileTextures[0] = SOIL_load_OGL_texture
	(
		"textures/tiles/GrassCliffMid.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	// loads image directly as texture
	game.tileTextures[1] = SOIL_load_OGL_texture
	(
		"textures/tiles/Dirt.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	game.bgTexture[0] = SOIL_load_OGL_texture
	(
		"textures/bg/Background.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	game.playerSprite[0] = SOIL_load_OGL_texture
	(
		"textures/sprites/1/0.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	game.playerSprite[1] = SOIL_load_OGL_texture
	(
		"textures/sprites/1/1.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	game.playerSprite[2] = SOIL_load_OGL_texture
	(
		"textures/sprites/1/2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	game.buttons[0] = SOIL_load_OGL_texture
	(
		"textures/buttons/b-start.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	game.buttons[1] = SOIL_load_OGL_texture
	(
		"textures/buttons/b-quit.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);


	// check for errors
	if (game.tileTextures[0] == 0) {
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

	glBindTexture(GL_TEXTURE_2D, game.playerSprite[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		
	glBindTexture(GL_TEXTURE_2D, game.playerSprite[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	glBindTexture(GL_TEXTURE_2D, game.playerSprite[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, game.buttons[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, game.buttons[1]);
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

			if (tile == '#' || tile == 'D') {

				// enable and bind texture relevant texture
				glEnable(GL_TEXTURE_2D);
				if (tile == '#') { // grass tile
					glBindTexture(GL_TEXTURE_2D, game.tileTextures[0]);
				}
				if (tile == 'D') { // dirt tile
					glBindTexture(GL_TEXTURE_2D, game.tileTextures[1]);
				}

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

void initLevel() {

	// levelMap encodes each tile as a character in a string
	// key: - : empty space
	//      # : ground tile
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
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "D----------------------------------------------#########-------D";
	game.levelMap += "D------------------------------------------------------------##D";
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "D---------------------------------------------------------###--D";
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "D----------------------------------------------#####-----------D";
	game.levelMap += "D-----------------------------------#####----------------------D";
	game.levelMap += "D-----------------------------------DDDDD----------------------D";
	game.levelMap += "###############################################################D";

	// reverses level map string so it is rendered the right way round
	reverse(game.levelMap.begin(), game.levelMap.end());
}

// 5ms timer
void timer(int t) {

	// run timer in 5ms
	glutTimerFunc(5, timer, 0);
}

// resizes opengl windows
void reshape(int width, int height)	{
	game.screenWidth = width; game.screenHeight = height;         // to ensure the mouse coordinates match 
														// we will use these values to set the coordinate system
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();

	gluOrtho2D(0, game.screenWidth, 0, game.screenHeight);        // set the coordinate system for the window

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();
}

// create moving platform object
MovingPlatform platform1(game, 96.0f, 96.0f);

// initialise opengl window
void init() {


	// add entities to vector
	movingPlatforms.push_back(&platform1);
}

// processes key presses
void keyOperations() {

	if (game.keyStates[27]) // escape
		exit(0);

	if (game.keyStates['w']) {
		// check if player is already jumping
		if (playerEntity.onGround) {
			playerEntity.onGround = false;
			playerEntity.velY = game.playerJumpRate;
		}		
	}
	
	if (game.keyStates['a'])
		playerEntity.velX = -game.playerAccelRate;

	if (game.keyStates['d'])
		playerEntity.velX = game.playerAccelRate;

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
		glVertex2f(314.0f, 300.0f);	// bl

		glTexCoord2d(0.0, 0.0);			
		glVertex2f(314.0f, 520.0f);	// br

		glTexCoord2d(1.0, 0.0);
		glVertex2f(628.0f, 520.0f);	// tr

		glTexCoord2d(1.0, 1.0);
		glVertex2f(628.0f, 300.0f); // tl

	glEnd();

	glDisable(GL_TEXTURE_2D);

}

void processTitleScreenInput() {
	if(game.leftPressed) {
		if(game.mouseX >= 314 && game.mouseX <= 628 && game.mouseY >= 300 && game.mouseY <= 520) {
			game.gameStage = "level1";
		}
	}
}

void doTitleScreen() {
	// draw background
	drawTitleScreen();
	processTitleScreenInput();
}

void doGameLevel() {
	moveCamera();
	drawLevel();
	playerEntity.draw();
	playerEntity.frame += 0.01f;	// update frame animation
	for (int i = 0; i < movingPlatforms.size(); i++) {
		movingPlatforms.at(i)->draw();
	}
}

// main display function
void display()
{
	// process key operations
	keyOperations();
	keySpecialOperations();

	// clear buffer, load identity, ready for next frame
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	// game drawing logic
	//if(game.gameStage == "title")
	//	doTitleScreen();
	//if(game.gameStage == "level1")
		doGameLevel();

	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);


	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(game.screenWidth, game.screenHeight);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("Matt's platform game");

	init();
	initLevel();	// run level initialisation
	loadTileTextures();

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


