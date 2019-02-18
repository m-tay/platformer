// UEA Graphics 1 coursework
//
// Author: Matthew Taylor

#include "freeglut.h"
#include <SOIL.h> // include the SOIL header file (for loading images)
#include <math.h>
#include <iostream>
#include <algorithm>
#include <iostream>
#include <iterator>

using namespace std;

// global parameters
bool debug = false;	// flag to include debug information
int screenWidth = 900, screenHeight = 700;
bool keys[256];
int levelWidth	= 64;	// store level dimensions (in tiles)
int levelHeight = 32;	
int tileWidth	= 32;		// store tile dimension information
int tileHeight	= 32;
float playerAccelRate	= 0.35f;	// param for player acceleration
float playerJumpRate	= 0.9f;	// param for player jump rate
float playerDecelRate	= 0.2f;
float gravityRate		= 0.004f;	// the rate gravity works at

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
string levelMap;		// stores level tilemap
GLuint tileTextures[1];	// stores level tile textures
GLuint bgTexture[1];	// stores background textures
GLuint playerSprite[3];	// stores player sprite

// opengl function prototypes
void display();				//called in winmain to draw everything to the screen
void reshape(int width, int height);				//called when the window is resized
void init();				//called in winmain when the program starts.
void keyOperations();
void keySpecialOperations();
void update();				//called in winmain to update variables

// game function prototypes
void drawLevel();
char getTile(int x, int y);

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
			int tileLeft = (int) newPosX / tileWidth;
			int tileRight = (int)(newPosX / tileWidth) + 1;
			int tileTop = (int) (newPosY / tileHeight) + 1;
			int tileBottom = (int) newPosY / tileHeight;

			// get the actual tile values from tilemap
			char tileTL = getTile(tileLeft, tileTop);
			char tileTR = getTile(tileRight, tileTop);
			char tileBL = getTile(tileLeft, tileBottom);
			char tileBR = getTile(tileRight, tileBottom);			
		}

		// check for collisions with tilemap on x axis
		bool isCollidingX() {		
			// calculate x,y coords of surrounding tiles
			// assumes entities are no bigger than 1 standard tile width
			int tileLeft = (int) newPosX / tileWidth;
			int tileRight = (int) (newPosX / tileWidth) + 1;
			int tileTop = (int) (posY / tileHeight) + 1;
			int tileBottom = (int) posY / tileHeight;

			// get the actual tile values from tilemap
			char tileTL = getTile(tileLeft, tileTop);
			char tileTR = getTile(tileRight, tileTop);
			char tileBL = getTile(tileLeft, tileBottom);
			char tileBR = getTile(tileRight, tileBottom);

			// if any collisions detected, return true
			if (tileTL == '#' || tileTR == '#' || tileBL == '#' || tileBR == '#')
				return true;

			// if not colliding, return false
			return false;
	}

		// check for collisions with tilemap on y axis
		bool isCollidingY() {
			// calculate x,y coords of surrounding tiles
			// assumes entities are no bigger than 1 standard tile width
			int tileLeft = (int) posX / tileWidth;
			int tileRight = (int) (posX / tileWidth) + 1;
			int tileTop = (int) (newPosY / tileHeight) + 1;
			int tileBottom = (int) newPosY / tileHeight;

			// get the actual tile values from tilemap
			char tileTL = getTile(tileLeft, tileTop);
			char tileTR = getTile(tileRight, tileTop);
			char tileBL = getTile(tileLeft, tileBottom);
			char tileBR = getTile(tileRight, tileBottom);

			// ceiling collision, set y velocity to 0
			if (tileTL == '#' || tileTR == '#') {
				velY = 0;
				return true;
			}

			// ground collision, set jumping flag back to false
			if (tileBL == '#' || tileBR == '#') {
				onGround = false;
				return true;
			}

			// if not colliding, return false
			return false;
		}


		// update entity position based on velocity
		void updatePosition() {
			// update entity's model of the tiles surrounding it
			findSurroundingTiles();

			// calculate proposed new position
			newPosX = posX + velX;
			newPosY = posY + velY;

			// check for collision in x axis
			if (!isCollidingX())
				posX = newPosX;

			if (!isCollidingY())
				posY = newPosY;

			// deceleration on x axis
			velX = 0;

			// apply gravity 
			if(onGround)
				velY -= gravityRate;


		}

		// draws the entity
		void draw() {

			updatePosition();

			if (frame > 2) // cycle frame animation back to start
				frame = 0;
			
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, playerSprite[(int)frame]);

			glBegin(GL_QUADS);

				glTexCoord2d(0.0, 1.0);
				glVertex2f(posX, posY);

				glTexCoord2d(1.0, 1.0);
				glVertex2f(posX + tileHeight, posY);
				
				glTexCoord2d(1.0, 0.0);
				glVertex2f(posX + tileHeight, posY + tileWidth);
				
				glTexCoord2d(0.0, 0.0);
				glVertex2f(posX, posY + tileWidth);
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
	tileTextures[0] = SOIL_load_OGL_texture
	(
		"textures/tiles/GrassCliffMid.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	bgTexture[0] = SOIL_load_OGL_texture
	(
		"textures/bg/Background.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	playerSprite[0] = SOIL_load_OGL_texture
	(
		"textures/sprites/1/0.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	playerSprite[1] = SOIL_load_OGL_texture
	(
		"textures/sprites/1/1.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	playerSprite[2] = SOIL_load_OGL_texture
	(
		"textures/sprites/1/2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);


	// check for errors
	if (tileTextures[0] == 0) {
		cout << "Error loading textures" << endl;
		exit(0);
	}

	// bind and generate texture
	glBindTexture(GL_TEXTURE_2D, tileTextures[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, bgTexture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, playerSprite[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		
	glBindTexture(GL_TEXTURE_2D, playerSprite[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	glBindTexture(GL_TEXTURE_2D, playerSprite[2]);
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
	camX = playerEntity.posX - (screenWidth / 2);
	camY = playerEntity.posY - (screenHeight / 2);

	// clamp camera to level edges
	if (camX < 0)	// left clamp
		camX = 0;
	if (camY < 0)	// bottom clamp
		camY = 0;
	if (camX > levelActualWidth - screenWidth)	// right clamp
		camX = (float) levelActualWidth - screenWidth;
	if (camY > levelActualHeight - screenHeight)	// top clamp
		camY = (float) levelActualHeight - screenHeight;

	glTranslatef(-camX, -camY, 0.0f);
}

// main display function
void display()
{
	// process key operations
	keyOperations();
	keySpecialOperations();

	glClear(GL_COLOR_BUFFER_BIT);
	
	glLoadIdentity();
	moveCamera();
	drawLevel();
	playerEntity.draw();
	playerEntity.frame += 0.01f;	// update frame animation

	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

// gets tile character at (x,y) coordinate
char getTile(int x, int y) {
	if (x >= 0 && x < levelWidth && y >= 0 && y < levelHeight) {
		return levelMap[y * levelWidth + x];
	}
	else {
		return '-';
	}
}

void drawLevel() {

	// draw background
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, bgTexture[0]);

	glBegin(GL_QUADS); 	// draw from bottom left, clockwise
		glTexCoord2d(1.0, 1.0);
		glVertex2f(0, 0);

		glTexCoord2d(1.0, 0.0);
		glVertex2f(0, levelActualHeight);

		glTexCoord2d(0.0, 0.0);
		glVertex2f(levelActualWidth, levelActualHeight);

		glTexCoord2d(0.0, 1.0);
		glVertex2f(levelActualWidth, 0);
	glEnd();

	glDisable(GL_TEXTURE_2D);


	// draw tiles
	for (int x = 0; x < levelWidth; x++) {
		for (int y = 0; y < levelHeight; y++) {
			char tile = getTile(x, y);

			if (tile == '#') {
				// enable and bind texture
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, tileTextures[0]); 

				glBegin(GL_POLYGON); 	// draw from bottom left, clockwise

				glTexCoord2d(1.0, 1.0);
				glVertex2f(x * tileWidth,				y * tileHeight);
				
				glTexCoord2d(1.0, 0.0);
				glVertex2f(x * tileWidth,				y * tileHeight + tileHeight);

				glTexCoord2d(0.0, 0.0);
				glVertex2f(x * tileWidth + tileWidth,	y * tileHeight + tileHeight);

				glTexCoord2d(0.0, 1.0);
				glVertex2f(x * tileWidth + tileWidth,	y * tileHeight);
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
	levelMap += "################################################################";
	levelMap += "#--------------------------------------------------------------#";
	levelMap += "#--------------------------------------------------------------#";
	levelMap += "#--------------------------------------------------------------#";
	levelMap += "#--------------------------------------------------------------#";
	levelMap += "#--------------------------------------------------------------#";
	levelMap += "#--------------------------------------------------------------#";
	levelMap += "#--------------------------------------------------------------#";
	levelMap += "#--------------------------------------------------------------#";
	levelMap += "#--------------------------------------------------------------#";
	levelMap += "#--------------------------------------------------------------#";
	levelMap += "#--------------------------------------------------------------#";
	levelMap += "#--------------------------------------------------------------#";
	levelMap += "#---------------------------------------########---------------#";
	levelMap += "#------------------------------------###-----------------------#";
	levelMap += "#-------------------------###########--------------------------#";
	levelMap += "#----------------------###-------------------------------------#";
	levelMap += "#-------------#########----------------------------------------#";
	levelMap += "#----------###-------------------------------------------------#";
	levelMap += "#--------------------------------------------------------------#";
	levelMap += "#--------------------------------------------------------------#";
	levelMap += "#---#########--------------------------------------------------#";
	levelMap += "#------------##------------------------------------------------#";
	levelMap += "#--------------############------------------------------------#";
	levelMap += "#--------------------------###---------------------------------#";
	levelMap += "#-----------------------------##-------------------------------#";
	levelMap += "#--------------------------------------------------------------#";
	levelMap += "#---------------------------------######-----------------------#";
	levelMap += "#-------------------------########------########---------------#";
	levelMap += "#--------------------------------------------------------------#";
	levelMap += "#--------------------------------------------------------------#";
	levelMap += "################################################################";

	// reverses level map string so it is rendered the right way round
	reverse(levelMap.begin(), levelMap.end());
}

// 5ms timer
void timer(int t) {

	// run timer in 5ms
	glutTimerFunc(5, timer, 0);
}

// resizes opengl windows
void reshape(int width, int height)	{
	screenWidth = width; screenHeight = height;         // to ensure the mouse coordinates match 
														// we will use these values to set the coordinate system
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();

	gluOrtho2D(0, screenWidth, 0, screenHeight);        // set the coordinate system for the window

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();
}

// initialise opengl window
void init() {
	
}

// processes key presses
void keyOperations() {

	if (keyStates[27]) // escape
		exit(0);

	if (keyStates['w']) {
		// check if player is already jumping
		if (!playerEntity.onGround) {
			playerEntity.onGround = true;
			playerEntity.velY = playerJumpRate;
		}		
	}
	
	if (keyStates['a'])
		playerEntity.velX = -playerAccelRate;

	if (keyStates['d'])
		playerEntity.velX = playerAccelRate;

}

void keySpecialOperations() {
	// process special keys
}

void keyPressed(unsigned char key, int x, int y) {
	keyStates[key] = true;
}

void keySpecialPressed(int key, int x, int y) {
	keySpecialStates[key] = true;
}

void keyUp(unsigned char key, int x, int y) {
	keyStates[key] = false;
}

void keySpecialUp(int key, int x, int y) {
	keySpecialStates[key] = false;
}

void update() {
	glutPostRedisplay();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("OpenGL FreeGLUT Template");

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

	glutMainLoop();

	return 0;
}


