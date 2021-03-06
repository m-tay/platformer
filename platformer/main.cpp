// UEA Graphics 1 coursework
//
// Author: Matthew Taylor

#include "libs/freeglut/include/GL/freeglut.h"
#include "libs/soil/src/SOIL.h" // include the SOIL header file (for loading images)
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
Entity playerEntity(game, 0,0);		// player entity
Enemy enemy1(game, 0, 0);
Enemy enemy2(game, 0, 0);
Enemy enemy3(game, 0, 0);
Enemy enemy4(game, 0, 0);
Enemy enemy5(game, 0, 0);
Enemy enemy6(game, 0, 0);
Enemy enemy7(game, 0, 0);
Enemy enemy8(game, 0, 0);
Ghost ghost1(game, playerEntity, 0, 200);
Ghost ghost2(game, playerEntity, 400, 670);
Ghost ghost3(game, playerEntity, 600, 800);
Ghost ghost4(game, playerEntity, 2048, 110);
Ghost ghost5(game, playerEntity, 1800, 475);
Ghost ghost6(game, playerEntity, 1000, 950);

// create moving platform object
MovingPlatform platform1(game, 0, 0);	// moving platform
MovingPlatform platform2(game, 0, 0);	// moving platform
MovingPlatform platform3(game, 0, 0);	// moving platform
MovingPlatform platform4(game, 0, 0);	// moving platform

// opengl function prototypes
void display();							//called in winmain to draw everything to the screen
void reshape(int width, int height);	//called when the window is resized
void init();							//called in winmain when the program starts
void keyOperations();					// handles key presses
void keySpecialOperations();			// handles special key presses
void update();							//called in winmain to update variables

// game function prototypes
void drawLevel();

// texture loader
int loadTextures()
{
	// loads image directly as texture
	game.titleIcons.push_back(SOIL_load_OGL_texture
	(
		"textures/bg/title.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.titleIcons.push_back(SOIL_load_OGL_texture
	(
		"textures/bg/objctrl.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.tileTextures.push_back(SOIL_load_OGL_texture
	(
		"textures/tiles/GrassCliffMid.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.tileTextures.push_back(SOIL_load_OGL_texture
	(
		"textures/tiles/Dirt.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.tileTextures.push_back(SOIL_load_OGL_texture
	(
		"textures/tiles/bush.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.tileTextures.push_back(SOIL_load_OGL_texture
	(
		"textures/tiles/Flower-1.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.tileTextures.push_back(SOIL_load_OGL_texture
	(
		"textures/tiles/Flower-2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.tileTextures.push_back(SOIL_load_OGL_texture
	(
		"textures/tiles/Flower-3.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.tileTextures.push_back(SOIL_load_OGL_texture
	(
		"textures/tiles/grass1.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.tileTextures.push_back(SOIL_load_OGL_texture
	(
		"textures/tiles/grass2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.tileTextures.push_back(SOIL_load_OGL_texture
	(
		"textures/tiles/tree.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.waterTexture.push_back(SOIL_load_OGL_texture
	(
		"textures/tiles/water/1.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.waterTexture.push_back(SOIL_load_OGL_texture
	(
		"textures/tiles/water/2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.waterTexture.push_back(SOIL_load_OGL_texture
	(
		"textures/tiles/water/3.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.waterTexture.push_back(SOIL_load_OGL_texture
	(
		"textures/tiles/water/4.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.waterTexture.push_back(SOIL_load_OGL_texture
	(
		"textures/tiles/water/5.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.waterTexture.push_back(SOIL_load_OGL_texture
	(
		"textures/tiles/water/6.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.waterTexture.push_back(SOIL_load_OGL_texture
	(
		"textures/tiles/water/7.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.waterTexture.push_back(SOIL_load_OGL_texture
	(
		"textures/tiles/water/8.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.waterTexture.push_back(SOIL_load_OGL_texture
	(
		"textures/tiles/water/9.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.waterTexture.push_back(SOIL_load_OGL_texture
	(
		"textures/tiles/water/10.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.waterTexture.push_back(SOIL_load_OGL_texture
	(
		"textures/tiles/water/11.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.waterTexture.push_back(SOIL_load_OGL_texture
	(
		"textures/tiles/water/12.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.waterTexture.push_back(SOIL_load_OGL_texture
	(
		"textures/tiles/water/13.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.waterTexture.push_back(SOIL_load_OGL_texture
	(
		"textures/tiles/water/14.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.bgTexture.push_back(SOIL_load_OGL_texture
	(
		"textures/bg/Background.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.bgTexture.push_back(SOIL_load_OGL_texture
	(
		"textures/bg/gameoverbg.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.bgTexture.push_back(SOIL_load_OGL_texture
	(
		"textures/bg/levelcompletebg.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));
	
	game.bgTexture.push_back(SOIL_load_OGL_texture
	(
		"textures/bg/theend.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.playerSpriteRunning.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/player/run/tile000.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.playerSpriteRunning.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/player/run/tile001.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.playerSpriteRunning.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/player/run/tile002.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.playerSpriteRunning.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/player/run/tile003.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.playerSpriteRunning.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/player/run/tile004.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.playerSpriteRunning.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/player/run/tile005.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.playerSpriteRunning.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/player/run/tile006.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.playerSpriteRunning.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/player/run/tile007.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.playerSpriteRunning.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/player/run/tile008.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.playerSpriteRunning.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/player/run/tile009.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.playerSpriteRunShooting.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/player/run-shoot/tile000.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.playerSpriteRunShooting.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/player/run-shoot/tile001.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.playerSpriteRunShooting.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/player/run-shoot/tile002.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.playerSpriteRunShooting.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/player/run-shoot/tile003.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.playerSpriteRunShooting.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/player/run-shoot/tile004.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.playerSpriteRunShooting.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/player/run-shoot/tile005.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.playerSpriteRunShooting.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/player/run-shoot/tile006.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.playerSpriteRunShooting.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/player/run-shoot/tile007.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.playerSpriteRunShooting.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/player/run-shoot/tile008.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.playerSpriteRunShooting.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/player/run-shoot/tile009.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.playerSpriteStillShooting.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/player/shoot/tile000.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.playerSpriteStillShooting.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/player/shoot/tile001.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.playerSpriteIdle.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/player/idle/tile000.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.playerSpriteIdle.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/player/idle/tile001.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.playerSpriteIdle.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/player/idle/tile002.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.playerSpriteIdle.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/player/idle/tile003.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.playerSpriteIdle.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/player/idle/tile004.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.buttons.push_back(SOIL_load_OGL_texture
	(
		"textures/buttons/Cloud_start.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.buttons.push_back(SOIL_load_OGL_texture
	(
		"textures/buttons/Cloud_quit.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.buttons.push_back(SOIL_load_OGL_texture
	(
		"textures/buttons/Cloud_mainmenu.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.buttons.push_back(SOIL_load_OGL_texture
	(
		"textures/buttons/Cloud_nextlevel.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.buttonGlow.push_back(SOIL_load_OGL_texture
	(
		"textures/buttons/Cloud_1.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.buttonGlow.push_back(SOIL_load_OGL_texture
	(
		"textures/buttons/Cloud_2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.buttonGlow.push_back(SOIL_load_OGL_texture
	(
		"textures/buttons/Cloud_3.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.buttonGlow.push_back(SOIL_load_OGL_texture
	(
		"textures/buttons/Cloud_4.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.buttonGlow.push_back(SOIL_load_OGL_texture
	(
		"textures/buttons/Cloud_5.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.buttonGlow.push_back(SOIL_load_OGL_texture
	(
		"textures/buttons/Cloud_4.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.buttonGlow.push_back(SOIL_load_OGL_texture
	(
		"textures/buttons/Cloud_3.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.buttonGlow.push_back(SOIL_load_OGL_texture
	(
		"textures/buttons/Cloud_2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

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

	game.enemy2Texture.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/5/g0.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.enemy2Texture.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/5/g1.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.enemy2Texture.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/5/g2.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.enemy2Texture.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/5/g3.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.gemTexture.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/4/tile000.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.gemTexture.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/4/tile001.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.gemTexture.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/4/tile002.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.gemTexture.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/4/tile003.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.doorTexture.push_back(SOIL_load_OGL_texture
	(
		"textures/tiles/DoorShut.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.doorTexture.push_back(SOIL_load_OGL_texture
	(
		"textures/tiles/DoorOpen.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	game.bulletSprite.push_back(SOIL_load_OGL_texture
	(
		"textures/sprites/player/bullet.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS));

	// check for errors
	if (game.tileTextures.at(0) == 0) {
		cout << "Error loading textures (0)" << endl;
		exit(0);
	}

	if (game.gemTexture[0] == 0) {
		cout << "Error loading textures (1)" << endl;
		exit(0);
	}
	
	// bind and generate texture
	glBindTexture(GL_TEXTURE_2D, game.titleIcons[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, game.titleIcons[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, game.tileTextures[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, game.tileTextures[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// bush texture - clamp wrapping to avoid artifacts
	glBindTexture(GL_TEXTURE_2D, game.tileTextures[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	// flower 1 texture - clamp wrapping to avoid artifacts
	glBindTexture(GL_TEXTURE_2D, game.tileTextures[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	// flower 2 texture - clamp wrapping to avoid artifacts
	glBindTexture(GL_TEXTURE_2D, game.tileTextures[4]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	// flower 3 texture - clamp wrapping to avoid artifacts
	glBindTexture(GL_TEXTURE_2D, game.tileTextures[5]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	// grass texture 1 - clamp wrapping to avoid artifacts
	glBindTexture(GL_TEXTURE_2D, game.tileTextures[6]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	// grass texture 2 - clamp wrapping to avoid artifacts
	glBindTexture(GL_TEXTURE_2D, game.tileTextures[7]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	// tree texture - clamp wrapping to avoid artifacts
	glBindTexture(GL_TEXTURE_2D, game.tileTextures[8]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	// set texture parameters for water animating sprite
	for (int i = 0; i < game.waterTexture.size(); i++) {
		glBindTexture(GL_TEXTURE_2D, game.waterTexture[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}

	glBindTexture(GL_TEXTURE_2D, game.bgTexture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, game.bgTexture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, game.bgTexture[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, game.bgTexture[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// set texture parameters for player running sprite
	for (int i = 0; i < game.playerSpriteRunning.size(); i++) {
		glBindTexture(GL_TEXTURE_2D, game.playerSpriteRunning[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}

	// set texture parameters for player running and shooting sprite
	for(int i = 0; i < game.playerSpriteRunShooting.size(); i++) {
		glBindTexture(GL_TEXTURE_2D, game.playerSpriteRunShooting[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}

	// set texture parameters for player shooting while still sprite
	for (int i = 0; i < game.playerSpriteStillShooting.size(); i++) {
		glBindTexture(GL_TEXTURE_2D, game.playerSpriteStillShooting[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}

	// set texture parameters for player idle sprite
	for (int i = 0; i < game.playerSpriteIdle.size(); i++) {
		glBindTexture(GL_TEXTURE_2D, game.playerSpriteIdle[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}
	
	glBindTexture(GL_TEXTURE_2D, game.buttons[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, game.buttons[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, game.buttons[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, game.buttons[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, game.buttonGlow[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, game.buttonGlow[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, game.buttonGlow[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, game.buttonGlow[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, game.buttonGlow[4]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, game.buttonGlow[5]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, game.buttonGlow[6]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, game.buttonGlow[7]);
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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, game.enemy1Texture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, game.enemy1Texture[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, game.enemy2Texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, game.enemy2Texture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, game.enemy2Texture[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, game.enemy2Texture[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, game.gemTexture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, game.gemTexture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, game.gemTexture[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, game.gemTexture[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, game.doorTexture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, game.doorTexture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, game.bulletSprite[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// error checking
	GLenum errorCode = glGetError();
	if (errorCode != GL_NO_ERROR) {
		cout << "Problem binding/setting texture parameters" << endl;
	}

	// enable blending on the alpha channel so textures have transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// add loaded textures to entities
	playerEntity.spriteSet.push_back(game.playerSpriteRunning);
	playerEntity.spriteSet.push_back(game.playerSpriteIdle);
	enemy1.spriteSet.push_back(game.enemy1Texture);
	enemy2.spriteSet.push_back(game.enemy1Texture);
	enemy3.spriteSet.push_back(game.enemy1Texture);
	enemy4.spriteSet.push_back(game.enemy1Texture);
	enemy5.spriteSet.push_back(game.enemy1Texture);
	enemy6.spriteSet.push_back(game.enemy1Texture);
	enemy7.spriteSet.push_back(game.enemy1Texture);
	enemy8.spriteSet.push_back(game.enemy1Texture);
	ghost1.spriteSet.push_back(game.enemy2Texture);
	ghost2.spriteSet.push_back(game.enemy2Texture);
	ghost3.spriteSet.push_back(game.enemy2Texture);
	ghost4.spriteSet.push_back(game.enemy2Texture);
	ghost5.spriteSet.push_back(game.enemy2Texture);
	ghost6.spriteSet.push_back(game.enemy2Texture);
		
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

			if (tile == '#' || tile == 'D' || tile == '1' || tile == 'G' || tile == 'd' || tile == 'b' || \
				tile == 'q' || tile == 'w' || tile == 'e' || tile == 'W' || tile == 't') {

				// enable and bind texture relevant texture
				glEnable(GL_TEXTURE_2D);
				if (tile == '#') { // grass tile
					glBindTexture(GL_TEXTURE_2D, game.tileTextures[0]);
				}

				if (tile == 'D') { // dirt tile
					glBindTexture(GL_TEXTURE_2D, game.tileTextures[1]);
				}
				
				if (tile == 'W') { // water tile
					glBindTexture(GL_TEXTURE_2D, game.waterTexture[(int)game.waterSpriteFrame]);
				}

				if (tile == 'b') { // bush tile
					glBindTexture(GL_TEXTURE_2D, game.tileTextures[2]);
				}

				if (tile == 'q') { // flower 1 tile
					glBindTexture(GL_TEXTURE_2D, game.tileTextures[3]);
				}

				if (tile == 'w') { // flower 2 tile
					glBindTexture(GL_TEXTURE_2D, game.tileTextures[4]);
				}

				if (tile == 'e') { // flower 3 tile
					glBindTexture(GL_TEXTURE_2D, game.tileTextures[5]);
				}

				if (tile == 't') { // tree tile
					glBindTexture(GL_TEXTURE_2D, game.tileTextures[8]);
				}

				if (tile == '1') { // collectible coin tile
					glBindTexture(GL_TEXTURE_2D, game.coinSprite[(int)game.coinSpriteFrame]);
				}

				if (tile == 'G') { // endgame gem 
					glBindTexture(GL_TEXTURE_2D, game.gemTexture[(int)game.gemSpriteFrame]);
				}

				if (tile == 'd') { // door tile ([0] = shut, [1] = open

					// only draw door open tile when gem is collected
					if (game.gemCollected) {
						glBindTexture(GL_TEXTURE_2D, game.doorTexture[1]);
					}
					else {
						glBindTexture(GL_TEXTURE_2D, game.doorTexture[0]);
					}
				}

				// check and reset frame limit for sprites
				if (game.coinSpriteFrame > 15)
					game.coinSpriteFrame = 0;

				if (game.gemSpriteFrame > 4)
					game.gemSpriteFrame = 0;

				if (game.waterSpriteFrame > 14)
					game.waterSpriteFrame = 0;

				// check if we need to draw anything that isn't exactly tile sized (eg. bushes)
				if(tile == 'b') {	// bush drawing
					glBegin(GL_POLYGON); 	// draw from bottom left, clockwise
					glTexCoord2d(1.0, 1.0);
					glVertex2f(x * game.tileWidth, y * game.tileHeight);

					glTexCoord2d(1.0, 0.0);
					glVertex2f(x * game.tileWidth, y * game.tileHeight + game.tileHeight);

					glTexCoord2d(0.0, 0.0);
					glVertex2f(x * game.tileWidth + (game.tileWidth * 2), y * game.tileHeight + game.tileHeight);

					glTexCoord2d(0.0, 1.0);
					glVertex2f(x * game.tileWidth + (game.tileWidth * 2), y * game.tileHeight);
					glEnd();
				}				
				else if(tile == 't') { // tree drawing
					glBegin(GL_POLYGON); 	// draw from bottom left, clockwise
					glTexCoord2d(1.0, 1.0);
					glVertex2f(x * game.tileWidth - (2 * game.tileWidth), y * game.tileHeight);

					glTexCoord2d(1.0, 0.0);
					glVertex2f(x * game.tileWidth - (2 * game.tileWidth), y * game.tileHeight + (5 * game.tileHeight));

					glTexCoord2d(0.0, 0.0);
					glVertex2f(x * game.tileWidth + (2 * game.tileWidth), y * game.tileHeight + (5 * game.tileHeight));

					glTexCoord2d(0.0, 1.0);
					glVertex2f(x * game.tileWidth + (2 * game.tileWidth), y * game.tileHeight);
					glEnd();
				}
				else {
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
				}
				glDisable(GL_TEXTURE_2D);
			}
		}
	}
}

void drawLevelForeground() {

	// draw tiles
	for (int x = 0; x < game.levelWidth; x++) {
		for (int y = 0; y < game.levelHeight; y++) {
			char tile = game.getTile(&game, x, y);

			if (tile == 'z' || tile == 'x' || tile == 'B' || tile == 'T') {

				// enable and bind texture relevant texture
				glEnable(GL_TEXTURE_2D);
				if (tile == 'z') { // grass tile
					glBindTexture(GL_TEXTURE_2D, game.tileTextures[6]);
				}

				if (tile == 'x') { // grass tile
					glBindTexture(GL_TEXTURE_2D, game.tileTextures[7]);
				}

				if (tile == 'B') { // grass tile
					glBindTexture(GL_TEXTURE_2D, game.tileTextures[2]);
				}

				if (tile == 'T') { // grass tile
					glBindTexture(GL_TEXTURE_2D, game.tileTextures[8]);
				}

				// check if we need to draw anything that isn't exactly tile sized (eg. bushes)
				if (tile == 'B') {
					glBegin(GL_POLYGON); 	// draw from bottom left, clockwise
					glTexCoord2d(1.0, 1.0);
					glVertex2f(x * game.tileWidth, y * game.tileHeight);

					glTexCoord2d(1.0, 0.0);
					glVertex2f(x * game.tileWidth, y * game.tileHeight + game.tileHeight);

					glTexCoord2d(0.0, 0.0);
					glVertex2f(x * game.tileWidth + (game.tileWidth * 2), y * game.tileHeight + game.tileHeight);

					glTexCoord2d(0.0, 1.0);
					glVertex2f(x * game.tileWidth + (game.tileWidth * 2), y * game.tileHeight);
					glEnd();
				}
				else if (tile == 'T') { // tree drawing
					glBegin(GL_POLYGON); 	// draw from bottom left, clockwise
					glTexCoord2d(1.0, 1.0);
					glVertex2f(x * game.tileWidth - (2 * game.tileWidth), y * game.tileHeight);

					glTexCoord2d(1.0, 0.0);
					glVertex2f(x * game.tileWidth - (2 * game.tileWidth), y * game.tileHeight + (5 * game.tileHeight));

					glTexCoord2d(0.0, 0.0);
					glVertex2f(x * game.tileWidth + (2 * game.tileWidth), y * game.tileHeight + (5 * game.tileHeight));

					glTexCoord2d(0.0, 1.0);
					glVertex2f(x * game.tileWidth + (2 * game.tileWidth), y * game.tileHeight);
					glEnd();
				}
				else {
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
				}
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
	//		G : gem (value 10) - level objective
	//		d : door - exits level when gem collected
	//		b : bush
	//		B : foreground bush
	//		q : flower
	//		w : flower
	//		e : flower
	//		W : water
	//		M : stopper for moving platforms
	//		z : foreground grass 1
	//		x : foreground grass 2
	//		t : tree
	//		T : foreground tree
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "D-1-1-1-1-1--zw------------------------------------------------D";
	game.levelMap += "D-----------####-----bxe---------------------------------------D";
	game.levelMap += "D-------------------####--------------w-q-----------------bx-qxD";
	game.levelMap += "D-------------------------------ez----###----------------######D";
	game.levelMap += "D-------------------------q-----###------------bx1xz-----------D";
	game.levelMap += "D----------------wxx-----###------------------#######----------D";
	game.levelMap += "D---------------####-------------------------------------------D";
	game.levelMap += "D------qxbz-----------------------------e----------------------D";
	game.levelMap += "D-----######---------------------------#####-------------------D";
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "D-w-b-zxe----------------1b-------1-------------1b1z1----------D";
	game.levelMap += "D#########-------------#####----#####----------#######---------D";
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "D-----------------------------b----------------------------1-1xD";
	game.levelMap += "D---------b-q----###-------#####--------------------------#####D";
	game.levelMap += "D--------####--------------------------------------------------D";
	game.levelMap += "D---------------------b--------------e-b-Gxzw-------1----------D";
	game.levelMap += "D-----------------q-#####------------#########-----###------q1-D";
	game.levelMap += "D-----------e----###DD--------------------------------------###D";
	game.levelMap += "D----------###-------------------------------------------------D";
	game.levelMap += "D-----1xz----------------qx-------xzz--------------------1w----D";
	game.levelMap += "D---#####---------------###-------###-------------------###----D";
	game.levelMap += "D--------------------------------------xxz-------------#DDD----D";
	game.levelMap += "Dq-w--x-bxe----------------------------###------w-t------------D";
	game.levelMap += "D###########--bz-T-zq---------------------------#####----------D";
	game.levelMap += "DDDDDDDDDDDD#########---------T----------bx--------------------D";
	game.levelMap += "DDDDDDDDDDDDDDDDDDDDD-b---xx-###-------#####-exzxBxzxxz--d---b-D";
	game.levelMap += "#############################DDDWWWWWWWDDDDD###################D";

	// reverses level map string so it is rendered the right way round
	reverse(game.levelMap.begin(), game.levelMap.end());

	// sets positions of entities
	playerEntity.posX = 32.0f;
	playerEntity.posY = 32.0f;	
	enemy1.posX = 1200.0f;
	enemy1.posY = 32.0f;
	enemy2.posX = 736.0f;
	enemy2.posY = 448.0f;
	enemy3.posX = 1000.0f;
	enemy3.posY = 448.0f;
	enemy4.posX = 600.0f;
	enemy4.posY = 160.0f;
	enemy5.posX = 1300.0f;
	enemy5.posY = 256.0f;
	enemy6.posX = 600.0f;
	enemy6.posY = 3000.0f;
	enemy7.posX = 600.0f;
	enemy7.posY = 3000.0f;
	enemy8.posX = 600.0f;
	enemy8.posY = 3000.0f;

	platform1.posX = 632.0f;
	platform1.posY = 512.0f;
	platform2.posX = 1152.0f;
	platform2.posY = 320.0f;
	platform3.posX = 1452.0f;
	platform3.posY = 512.0f;
	platform4.posX = 1728.0f;
	platform4.posY = 832.0f;

	// set player status to be alive (in case of restarting level)
	playerEntity.alive = true;

	// set enemies to be alive
	enemy1.alive = true;
	enemy2.alive = true;
	game.enemies.clear();
	game.enemies.push_back(&enemy1);
	game.enemies.push_back(&enemy2);
	game.enemies.push_back(&enemy3);
	game.enemies.push_back(&enemy4);
	game.enemies.push_back(&enemy5);
	game.enemies.push_back(&enemy6);
	game.enemies.push_back(&enemy7);
	game.enemies.push_back(&enemy8);

	// reset ghosts
	game.deactivateGhosts(&game);

	ghost1.posX = 0;
	ghost1.posY = 200;
	ghost2.posX = 300;
	ghost2.posY = 670;
	ghost3.posX = 700;
	ghost3.posY = 800;
	ghost4.posX = 2048;
	ghost4.posY = 110;
	ghost5.posX = 1600;
	ghost5.posY = 475;
	ghost6.posX = 1250;
	ghost6.posY = 950;

	// set player score to 0
	game.playerScore = 0;

	// set the gem as uncollected
	game.gemCollected = false;
}

void initLevel2() {
	// levelMap encodes each tile as a character in a string
	// key: - : empty space
	//      # : ground tile
	//		D : dirt tile (like ground tile but nothing on top)
	//		1 : collectable (value 1)
	//		G : gem (value 10) - level objective
	//		d : door - exits level when gem collected
	//		b : bush
	//		B : foreground bush
	//		q : flower
	//		w : flower
	//		e : flower
	//		W : water
	//		M : stopper for moving platforms
	//		z : foreground grass 1
	//		x : foreground grass 2
	//		t : tree
	//		T : foreground tree
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "D------------G-------------------------------------------------D";
	game.levelMap += "D-----------###-----ze----xTz---w----1-------------------------D";
	game.levelMap += "D-------------------###---###---##--###------------------------D";
	game.levelMap += "D-------bxq---------------------------------q------------------D";
	game.levelMap += "D------####--------------------------------###-----------------D";
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "Dxb1---------------------------------------------1-txbw--------D";
	game.levelMap += "D####--------------------------xxxb-------------#########------D";
	game.levelMap += "D------xe----------------------#####-------------------------1xD";
	game.levelMap += "D------###--------------------------------------------------###D";
	game.levelMap += "D-------------T-------bw--------------------1----------zxbz----D";
	game.levelMap += "D-----------#####---#####------------------###--------######---D";
	game.levelMap += "D--------------------------------1-1q------------------DDDDD---D";
	game.levelMap += "D-------------------------------#####------------xxe-----------D";
	game.levelMap += "D---------zzbx1---------------------------------#####----------D";
	game.levelMap += "D---------########--------b-q-----------1-1-1------------------D";
	game.levelMap += "D-----------------------#####----------#######-----------------D";
	game.levelMap += "D-----e-------------------------------------------1b-----------D";
	game.levelMap += "D--#####-----------------------------------------####----------D";
	game.levelMap += "D------------d-------------------------------------------------D";
	game.levelMap += "D------xx---###---------------------------------------11-------D";
	game.levelMap += "D-----###--------------------------------------------####------D";
	game.levelMap += "D----------------xbz-------------------------------------------D";
	game.levelMap += "Dxxb------------######----------b-t----------1w1b1-e-----------D";
	game.levelMap += "D#####xqxxz------------------w-#####xzz-----########-----------D";
	game.levelMap += "DDDDDD######--------------#####DDDDD#####----------------------D";
	game.levelMap += "DDDDDDDDDDDDWWWWWWWWWWWWWWDDDDDDDDDDDDDDD-b---xzbzxz--z--xztxx-D";
	game.levelMap += "DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD######################D";

	// reverses level map string so it is rendered the right way round
	reverse(game.levelMap.begin(), game.levelMap.end());

	// sets positions of entities
	playerEntity.posX = 32.0f;
	playerEntity.posY = 32.0f;
	enemy1.posX = 1200.0f;
	enemy1.posY = 192.0f;
	enemy2.posX = 736.0f;
	enemy2.posY = 448.0f;
	enemy3.posX = 1200.0f;
	enemy3.posY = 448.0f;
	enemy4.posX = 600.0f;
	enemy4.posY = 160.0f;
	enemy5.posX = 1300.0f;
	enemy5.posY = 256.0f;
	enemy6.posX = 1000.0f;
	enemy6.posY = 544.0f;
	enemy7.posX = 600.0f;
	enemy7.posY = 3000.0f;
	enemy8.posX = 600.0f;
	enemy8.posY = 3000.0f;

	platform1.posX = 800.0f;
	platform1.posY = 512.0f;
	platform2.posX = 3000.0f;
	platform2.posY = 640.0f;
	platform3.posX = 1100.0f;
	platform3.posY = 3000.0f;
	platform4.posX = 1000.0f;
	platform4.posY = 928.0f;

	// set player status to be alive (in case of restarting level)
	playerEntity.alive = true;

	// set enemies to be alive, add back to enemy list
	enemy1.alive = true;
	enemy2.alive = true;
	game.enemies.clear();
	game.enemies.push_back(&enemy1);
	game.enemies.push_back(&enemy2);
	game.enemies.push_back(&enemy3);
	game.enemies.push_back(&enemy4);
	game.enemies.push_back(&enemy5);
	game.enemies.push_back(&enemy6);
	game.enemies.push_back(&enemy7);
	game.enemies.push_back(&enemy8);

	// reset ghosts
	game.deactivateGhosts(&game);

	ghost1.posX = 0;
	ghost1.posY = 200;
	ghost2.posX = 300;
	ghost2.posY = 670;
	ghost3.posX = 700;
	ghost3.posY = 800;
	ghost4.posX = 2048;
	ghost4.posY = 110;
	ghost5.posX = 1600;
	ghost5.posY = 475;
	ghost6.posX = 1250;
	ghost6.posY = 950;

	// set player score to 0
	game.playerScore = 0;

	// set the gem as uncollected
	game.gemCollected = false;
}

void initLevel3() {
	// levelMap encodes each tile as a character in a string
	// key: - : empty space
	//      # : ground tile
	//		D : dirt tile (like ground tile but nothing on top)
	//		1 : collectable (value 1)
	//		G : gem (value 10) - level objective
	//		d : door - exits level when gem collected
	//		b : bush
	//		B : foreground bush
	//		q : flower
	//		w : flower
	//		e : flower
	//		W : water
	//		M : stopper for moving platforms
	//		z : foreground grass 1
	//		x : foreground grass 2
	//		t : tree
	//		T : foreground tree
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "D----1---------------------------------------------------------D";
	game.levelMap += "D--#####---------1-----q---------1----w-------------b-e--------D";
	game.levelMap += "D---------------###---##---###--###--###---###----######-------D";
	game.levelMap += "D----------b---------------------------------------------------D";
	game.levelMap += "D---------####-----------------------------------------------q-D";
	game.levelMap += "D----------------------------------------------------------####D";
	game.levelMap += "D-----1-1------Gz----------------------------------------------D";
	game.levelMap += "D----#####----###--------------------------------------1-1-zbxzD";
	game.levelMap += "D--------------------xwx----1----------------1b1------#########D";
	game.levelMap += "D--------------------###--------------------#####--------------D";
	game.levelMap += "Dq1x------------------------1--------------#DDDD---------------D";
	game.levelMap += "D###-----------------------###--------zbx--------------------dzD";
	game.levelMap += "D--------b1--------------------------x###---------------e---###D";
	game.levelMap += "D-------####-------------------------#DD---------------###-----D";
	game.levelMap += "D--------------------------------------------------------------D";
	game.levelMap += "Dx1e1---------x1zqw1x---z1x-----1-----------------b------------D";
	game.levelMap += "D#####--------#######---###----###---------------###-----------D";
	game.levelMap += "D-----##-------------------------------------------------------D";
	game.levelMap += "D-------------------------------------xbz---------------wq-----D";
	game.levelMap += "D---------1-q-------------------------###--------------###-----D";
	game.levelMap += "D--------######------------------------------------------------D";
	game.levelMap += "Dx1--------------------zTxxbz---------------zb---------------1xD";
	game.levelMap += "D###------------------########--------zx---####-------------###D";
	game.levelMap += "D------------z----x-----------------tx##xx---------------------D";
	game.levelMap += "Dxzzx----tw-##----##xxbz-----##----###DD####----##---xxzzbxxxxxD";
	game.levelMap += "############DDWWWWDD#########DDWWWWDDDDDDDDDWWWWDD#############D";

	// reverses level map string so it is rendered the right way round
	reverse(game.levelMap.begin(), game.levelMap.end());

	// sets positions of entities
	playerEntity.posX = 32.0f;
	playerEntity.posY = 32.0f;
	enemy1.posX = 1200.0f;
	enemy1.posY = 32.0f;
	enemy2.posX = 736.0f;
	enemy2.posY = 448.0f;
	enemy3.posX = 1000.0f;
	enemy3.posY = 416.0f;
	enemy4.posX = 600.0f;
	enemy4.posY = 32.0f;
	enemy5.posX = 1300.0f;
	enemy5.posY = 256.0f;
	enemy6.posX = 600.0f;
	enemy6.posY = 3000.0f;
	enemy7.posX = 600.0f;
	enemy7.posY = 3000.0f;
	enemy8.posX = 600.0f;
	enemy8.posY = 3000.0f;

	platform1.posX = 632.0f;
	platform1.posY = 5000.0f;
	platform2.posX = 100.0f;
	platform2.posY = 288.0f;
	platform3.posX = 1452.0f;
	platform3.posY = 5000.0f;
	platform4.posX = 1728.0f;
	platform4.posY = 5000.0f;

	// set player status to be alive (in case of restarting level)
	playerEntity.alive = true;

	// set enemies to be alive
	enemy1.alive = true;
	enemy2.alive = true;
	game.enemies.clear();
	game.enemies.push_back(&enemy1);
	game.enemies.push_back(&enemy2);
	game.enemies.push_back(&enemy3);
	game.enemies.push_back(&enemy4);
	game.enemies.push_back(&enemy5);
	game.enemies.push_back(&enemy6);
	game.enemies.push_back(&enemy7);
	game.enemies.push_back(&enemy8);

	// reset ghosts
	game.deactivateGhosts(&game);

	ghost1.posX = 0;
	ghost1.posY = 200;
	ghost2.posX = 300;
	ghost2.posY = 670;
	ghost3.posX = 700;
	ghost3.posY = 800;
	ghost4.posX = 2048;
	ghost4.posY = 110;
	ghost5.posX = 1600;
	ghost5.posY = 475;
	ghost6.posX = 1250;
	ghost6.posY = 950;

	// set player score to 0
	game.playerScore = 0;

	// set the gem as uncollected
	game.gemCollected = false;
}

// resizes opengl windows
void reshape(int width, int height)	{
	game.screenWidth = width; game.screenHeight = height;	

	// set viewport to given dimensions
	glViewport(0, 0, width, height);

	// load projection matrix + reset it
	glMatrixMode(GL_PROJECTION);						
	glLoadIdentity();

	// set the coordinate system for the window
	gluOrtho2D(0, game.screenWidth, 0, game.screenHeight);        

	// load modelview matrix + reset it
	glMatrixMode(GL_MODELVIEW);						
	glLoadIdentity();
}

// initialise opengl window
void init() {

	// add moving platforms to vector
	game.movingPlatforms.push_back(&platform1);
	game.movingPlatforms.push_back(&platform2);
	game.movingPlatforms.push_back(&platform3);
	game.movingPlatforms.push_back(&platform4);

	// add enemies to vector
	game.enemies.push_back(&enemy1);
	game.enemies.push_back(&enemy2);
	game.enemies.push_back(&enemy3);
	game.enemies.push_back(&enemy4);
	game.enemies.push_back(&enemy5);
	game.enemies.push_back(&enemy6);
	game.enemies.push_back(&enemy7);
	game.enemies.push_back(&enemy8);

	game.ghosts.push_back(&ghost1);
	game.ghosts.push_back(&ghost2);
	game.ghosts.push_back(&ghost3);
	game.ghosts.push_back(&ghost4);
	game.ghosts.push_back(&ghost5);
	game.ghosts.push_back(&ghost6);
}

// processes key presses
void keyOperations() {

	// debug only options
	if (game.debug) {
		if (game.keyStates['1']) {
			initLevel1();
			game.onLevel = 1;
			game.gameStage = "level";
		}

		if (game.keyStates['2']) {
			initLevel2();
			game.onLevel = 2;
			game.gameStage = "level";
		}

		if (game.keyStates['3']) {
			initLevel3();
			game.onLevel = 3;
			game.gameStage = "level";
		}
	}

	if (game.keyStates[27]) // escape
		exit(0);

	if (game.keyStates['w']) {

		// check if processing menu screen inputs
		if (game.gameStage == "title") {
			game.menuScreenButton--;	// go up on menu screen
			game.keyStates['w'] = false;
		}
		// otherwise control player entities
		else {
			// check if player has left ground
			if (playerEntity.onGround) {
				playerEntity.onGround = false;	// flag player as not being on ground
				playerEntity.jumping = true;	// flag player as jumping
				playerEntity.jumpTime = glutGet(GLUT_ELAPSED_TIME);
				playerEntity.velY = 2.9f;
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
	}

	// only allow x-axis movement when player is alive	
	if (playerEntity.alive) {
		if (game.keyStates['a'])
			playerEntity.velX = -game.playerAccelRate;

		if (game.keyStates['d'])
			playerEntity.velX = game.playerAccelRate;
	}

	if(game.keyStates['s']) {
		game.menuScreenButton++;	// go down on menu screen
		game.keyStates['s'] = false;
	}

	if (game.keyStates[' ']) { // spacebar
		if(game.gameStage == "title") {
			if(game.menuScreenButton == 0) {
				initLevel1();
				game.gameStage = "level";
				game.canShoot = false;	// set shooting to be false when level starts, to provide buffer from input used to start level
			}
			if(game.menuScreenButton == 1) {
				exit(0);
			}
		}
		else if (game.gameStage == "gameover") {
			game.gameStage = "title";
			game.keyStates[' '] = false;
		}
		else if(game.gameStage == "levelcomplete") {
			// increment level counter
			game.onLevel++;

			// initialise next level
			switch (game.onLevel) {
			case 2: initLevel2(); break;
			case 3: initLevel3(); break;
			}
			
			// set gameStage back to level so next level loads
			game.gameStage = "level";
			game.keyStates[' '] = false;
			game.canShoot = false;
		}
		else if(game.gameStage == "theend") {
			game.gameStage = "title";
			game.keyStates[' '] = false;
		}
		// spacebar pressed when game is running = do some shooting
		else if(game.gameStage == "level") {

			if (game.canShoot) {
				game.canShoot = false;
				// create new bullet projectile entity at players position
				Projectile bullet(game, playerEntity.posX, playerEntity.posY, playerEntity.facing);

				// add bullet to list of projectiles
				game.projectiles.push_back(bullet);
			}
		}
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
	//glutPostRedisplay();
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

	// draw buttons
	const int buttonSize = 150;

	// draw start button
	const int startButtonPosX = 150;
	const int startButtonPosY = 180;


	// glow effect
	if (game.menuScreenButton == 0) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, game.buttonGlow[(int)game.cloudGlowSpriteFrame]);
		glBegin(GL_QUADS);
		glTexCoord2d(0.0, 1.0);
		glVertex2f(startButtonPosX, startButtonPosY);	// bl

		glTexCoord2d(1.0, 1.0);
		glVertex2f(startButtonPosX + buttonSize, startButtonPosY);	// br

		glTexCoord2d(1.0, 0.0);
		glVertex2f(startButtonPosX + buttonSize, startButtonPosY + buttonSize);	// tr

		glTexCoord2d(0.0, 0.0);
		glVertex2f(startButtonPosX, startButtonPosY + buttonSize); // tl
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}

	// button texture
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, game.buttons[0]);
	glBegin(GL_QUADS); 	
		glTexCoord2d(0.0, 1.0);
		glVertex2f(startButtonPosX, startButtonPosY);	// bl

		glTexCoord2d(1.0, 1.0);
		glVertex2f(startButtonPosX + buttonSize, startButtonPosY);	// br

		glTexCoord2d(1.0, 0.0);
		glVertex2f(startButtonPosX + buttonSize, startButtonPosY + buttonSize);	// tr

		glTexCoord2d(0.0, 0.0);
		glVertex2f(startButtonPosX, startButtonPosY + buttonSize); // tl
	glEnd();
	glDisable(GL_TEXTURE_2D);

	// draw quit button
	const int quitButtonPosX = 150;
	const int quitButtonPosY = 30;

	// glow effect
	if (game.menuScreenButton == 1) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, game.buttonGlow[(int)game.cloudGlowSpriteFrame]);
		glBegin(GL_QUADS);
		glTexCoord2d(0.0, 1.0);
		glVertex2f(quitButtonPosX, quitButtonPosY);	// bl

		glTexCoord2d(1.0, 1.0);
		glVertex2f(quitButtonPosX + buttonSize, quitButtonPosY);	// br

		glTexCoord2d(1.0, 0.0);
		glVertex2f(quitButtonPosX + buttonSize, quitButtonPosY + buttonSize);	// tr

		glTexCoord2d(0.0, 0.0);
		glVertex2f(quitButtonPosX, quitButtonPosY + buttonSize); // tl
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}

	// button texture
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, game.buttons[1]);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 1.0);
	glVertex2f(quitButtonPosX, quitButtonPosY);	// bl

	glTexCoord2d(1.0, 1.0);
	glVertex2f(quitButtonPosX + buttonSize, quitButtonPosY);	// br

	glTexCoord2d(1.0, 0.0);
	glVertex2f(quitButtonPosX + buttonSize, quitButtonPosY + buttonSize);	// tr

	glTexCoord2d(0.0, 0.0);
	glVertex2f(quitButtonPosX, quitButtonPosY + buttonSize); // tl
	glEnd();
	glDisable(GL_TEXTURE_2D);

	// title texture
	int titleX = 120;
	int titleY = 349;
	int titleW = 659;
	int titleH = 326;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, game.titleIcons[0]);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 1.0);
	glVertex2f(titleX, titleY);	// bl

	glTexCoord2d(1.0, 1.0);
	glVertex2f(titleX + titleW, titleY);	// br

	glTexCoord2d(1.0, 0.0);
	glVertex2f(titleX + titleW, titleY + titleH);	// tr

	glTexCoord2d(0.0, 0.0);
	glVertex2f(titleX, titleY + titleH); // tl
	glEnd();
	glDisable(GL_TEXTURE_2D);

	// objective/controls texture
	int objX = 450;
	int objY = 50;
	int objW = 400;
	int objH = 256;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, game.titleIcons[1]);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 1.0);
	glVertex2f(objX, objY);	// bl

	glTexCoord2d(1.0, 1.0);
	glVertex2f(objX + objW, objY);	// br

	glTexCoord2d(1.0, 0.0);
	glVertex2f(objX + objW, objY + objH);	// tr

	glTexCoord2d(0.0, 0.0);
	glVertex2f(objX, objY + objH); // tl
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

	// draw buttons
	const int buttonSize = 150;

	// draw main menu button
	const int mainMenuButtonPosX = 375;
	const int mainMenuButtonPosY = 200;

	// glow effect
	glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, game.buttonGlow[(int)game.cloudGlowSpriteFrame]);
		glBegin(GL_QUADS);
		glTexCoord2d(0.0, 1.0);
		glVertex2f(mainMenuButtonPosX, mainMenuButtonPosY);	// bl

		glTexCoord2d(1.0, 1.0);
		glVertex2f(mainMenuButtonPosX + buttonSize, mainMenuButtonPosY);	// br

		glTexCoord2d(1.0, 0.0);
		glVertex2f(mainMenuButtonPosX + buttonSize, mainMenuButtonPosY + buttonSize);	// tr

		glTexCoord2d(0.0, 0.0);
		glVertex2f(mainMenuButtonPosX, mainMenuButtonPosY + buttonSize); // tl
		glEnd();
	glDisable(GL_TEXTURE_2D);

	// button texture
	glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, game.buttons[2]);
		glBegin(GL_QUADS);
		glTexCoord2d(0.0, 1.0);
		glVertex2f(mainMenuButtonPosX, mainMenuButtonPosY);	// bl

		glTexCoord2d(1.0, 1.0);
		glVertex2f(mainMenuButtonPosX + buttonSize, mainMenuButtonPosY);	// br

		glTexCoord2d(1.0, 0.0);
		glVertex2f(mainMenuButtonPosX + buttonSize, mainMenuButtonPosY + buttonSize);	// tr

		glTexCoord2d(0.0, 0.0);
		glVertex2f(mainMenuButtonPosX, mainMenuButtonPosY + buttonSize); // tl
		glEnd();
	glDisable(GL_TEXTURE_2D);
}

void drawLevelCompleteScreen() {
	// draw background
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, game.bgTexture[2]);

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

	// draw main menu button
	const int mainMenuButtonPosX = 375;
	const int mainMenuButtonPosY = 200;
	const int buttonSize = 150;

	// glow effect
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, game.buttonGlow[(int)game.cloudGlowSpriteFrame]);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 1.0);
	glVertex2f(mainMenuButtonPosX, mainMenuButtonPosY);	// bl

	glTexCoord2d(1.0, 1.0);
	glVertex2f(mainMenuButtonPosX + buttonSize, mainMenuButtonPosY);	// br

	glTexCoord2d(1.0, 0.0);
	glVertex2f(mainMenuButtonPosX + buttonSize, mainMenuButtonPosY + buttonSize);	// tr

	glTexCoord2d(0.0, 0.0);
	glVertex2f(mainMenuButtonPosX, mainMenuButtonPosY + buttonSize); // tl
	glEnd();
	glDisable(GL_TEXTURE_2D);

	// button texture
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, game.buttons[3]);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 1.0);
	glVertex2f(mainMenuButtonPosX, mainMenuButtonPosY);	// bl

	glTexCoord2d(1.0, 1.0);
	glVertex2f(mainMenuButtonPosX + buttonSize, mainMenuButtonPosY);	// br

	glTexCoord2d(1.0, 0.0);
	glVertex2f(mainMenuButtonPosX + buttonSize, mainMenuButtonPosY + buttonSize);	// tr

	glTexCoord2d(0.0, 0.0);
	glVertex2f(mainMenuButtonPosX, mainMenuButtonPosY + buttonSize); // tl
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void drawTheEndScreen() {
	// draw background
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, game.bgTexture[3]);

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

	// draw buttons
	const int buttonSize = 150;

	// draw main menu button
	const int mainMenuButtonPosX = 375;
	const int mainMenuButtonPosY = 100;

	// glow effect
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, game.buttonGlow[(int)game.cloudGlowSpriteFrame]);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 1.0);
	glVertex2f(mainMenuButtonPosX, mainMenuButtonPosY);	// bl

	glTexCoord2d(1.0, 1.0);
	glVertex2f(mainMenuButtonPosX + buttonSize, mainMenuButtonPosY);	// br

	glTexCoord2d(1.0, 0.0);
	glVertex2f(mainMenuButtonPosX + buttonSize, mainMenuButtonPosY + buttonSize);	// tr

	glTexCoord2d(0.0, 0.0);
	glVertex2f(mainMenuButtonPosX, mainMenuButtonPosY + buttonSize); // tl
	glEnd();
	glDisable(GL_TEXTURE_2D);

	// button texture
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, game.buttons[2]);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 1.0);
	glVertex2f(mainMenuButtonPosX, mainMenuButtonPosY);	// bl

	glTexCoord2d(1.0, 1.0);
	glVertex2f(mainMenuButtonPosX + buttonSize, mainMenuButtonPosY);	// br

	glTexCoord2d(1.0, 0.0);
	glVertex2f(mainMenuButtonPosX + buttonSize, mainMenuButtonPosY + buttonSize);	// tr

	glTexCoord2d(0.0, 0.0);
	glVertex2f(mainMenuButtonPosX, mainMenuButtonPosY + buttonSize); // tl
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void processTitleScreenInput() {
	// reset button to top if range of buttons exceeded
	if (game.menuScreenButton > 1)
		game.menuScreenButton = 0;

	if (game.menuScreenButton < 0)
		game.menuScreenButton = 1;
}

void processGameOverScreenInput() {
	
}

void processLevelCompleteScreenInput() {
	
}

void doTitleScreen() {
	// update cloud glow animation frames
	game.cloudGlowSpriteFrame += 0.01f;

	// check if frame of cloud glow anim needs resetting
	if (game.cloudGlowSpriteFrame > 8)
		game.cloudGlowSpriteFrame = 0;

	// draw background
	drawTitleScreen();

	// process inputs for buttons
	processTitleScreenInput();
}

void doGameOverScreen() {
	// update cloud glow animation frames
	game.cloudGlowSpriteFrame += 0.01f;

	// check if frame of cloud glow anim needs resetting
	if (game.cloudGlowSpriteFrame > 8)
		game.cloudGlowSpriteFrame = 0;

	// draw background
	drawGameOverScreen();
}

void doLevelCompleteScreen() {
	// draw background
	drawLevelCompleteScreen();
}

void doTheEndScreen() {
	// draw background
	drawTheEndScreen();
}

void doGameLevel() {
	moveCamera();
	drawLevel();
	game.drawScore(&game);
	playerEntity.draw();
	playerEntity.playerSpriteFrame += 0.01f;	// update playerSpriteFrame animation
	game.coinSpriteFrame += 0.01f;				// update coin sprite frame
	game.gemSpriteFrame += 0.01f;				// update gem sprite frame
	game.waterSpriteFrame += 0.03f;				// update water animation frame
	
	// draw all moving platforms
	for (int i = 0; i < game.movingPlatforms.size(); i++) {
		game.movingPlatforms.at(i)->draw();
	}

	// draw all enemy objects
	for(int i = 0; i < game.enemies.size(); i++) {
		game.enemies.at(i)->spriteFrame += 0.01f;	// update animation frame

		// if enemy is alive, draw it
		if (game.enemies.at(i)->alive) {
			game.enemies.at(i)->draw();					// draw enemy
		}
		// if enemy is dead, remove it 
		else {
			game.enemies.erase(game.enemies.begin() + i);
		}
	}

	// draw all ghost objects
	for (int i = 0; i < game.ghosts.size(); i++) {
		game.ghosts.at(i)->spriteFrame += 0.01f;	// update animation frame
		game.ghosts.at(i)->draw();					// draw enemy
	}

	// draw all bullets
	for(int i = 0; i < game.projectiles.size(); i++) {

		// if bullet is active, draw it
		if (game.projectiles.at(i).active) {
			game.projectiles.at(i).draw();
		}
		// if bullet is inactive, remove it
		else {
			game.projectiles.erase(game.projectiles.begin()+i);
		}
	}

	drawLevelForeground();
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
	if (game.gameStage == "level")
		doGameLevel();
	if (game.gameStage == "gameover")
		doGameOverScreen();
	if (game.gameStage == "levelcomplete")
		doLevelCompleteScreen();
	if (game.gameStage == "theend")
		doTheEndScreen();

	// flush and swap buffers to draw to screen
	glFlush();
	glutSwapBuffers();
}

// 50ms timer
void timer(int t) {
	game.canShoot = true;

	// run timer in 250ms
	glutTimerFunc(250, timer, 0);
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


