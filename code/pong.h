// ===============================================
// @file   pong.h
// @author kmurphy
// @practical pong
// @brief  Headfile for PSP+GLFW(OpenGL) pong game
// ===============================================

#ifndef PONG_H
#define PONG_H

// uncomment next line for PSP executable
//#define PSP 1
 
// ===============================================
// Headers
// ===============================================
#ifdef PSP								// PSP specific headers
	#include <psptypes.h>
	#include <kernel.h>
	#include <psperror.h>		
	#include <displaysvc.h>
	#include <ctrlsvc.h>				// controller 
	#include <libgu.h>					// basic graphics
	#include <libgum.h>					// 3D "OpenGLish" graphics 

#else          						// Unix based system specific
	#include <GL/gl.h>          
	#include <GL/glu.h>         
	#include <GL/glut.h>  
	#include <GL/glfw.h> 
#endif

#include <stdio.h>      				// for sprintf()
#include <stdlib.h>     				// for atof() 
#include <string.h>     				// for strcpy()
#include <string>
#include <math.h>       				// for cos(), sin()

// ===============================================
// Global identifiers
// ===============================================

// window & scene
#ifdef PSP   							// psp data types (see psptypes.h)
	#define WINDOW_WIDTH    SCEGU_SCR_WIDTH
	#define WINDOW_HEIGHT   SCEGU_SCR_HEIGHT
	#define MARGIN_SIZE      20
	#define BORDER_SIZE      10
#else
	#define WINDOW_NAME     "Pong using GLFW"
	#define WINDOW_WIDTH    640
	#define WINDOW_HEIGHT   480
	#define MARGIN_SIZE      15
	#define BORDER_SIZE      18
#endif

// ball
#define BALL_SIZE        15
#ifdef PSP   					
	#define BALL_STEP    5  			// distance ball travels per time step
#else
	#define BALL_STEP    dt*600  	
#endif

// paddle
#define PADDLE_WIDTH     BORDER_SIZE
#define PADDLE_MAX_LEN	 150
#define PADDLE_START_LEN 100
#define PADDLE_MIN_LEN   30
extern float paddleLength;				//varies paddle length through gameplay

#ifdef PSP   		
	#define PADDLE_STEP  10    			// distance paddle travels per time step
#else
	#define PADDLE_STEP  dt*520
#endif

//ball struct
struct Ball{
	float x,y,angle;
	bool isActive;
};
const int BALL_MAX_COUNT = 5;
extern Ball balls[BALL_MAX_COUNT];
extern int ballCount;

//paddle 
extern float paddle_x_pos;
extern float paddle_y_pos;
extern float paddle_speed;

const float POWER_UP_SIZE = 20;
struct PowerUp{					//used for spawning rewards and traps in game
	float x,y;
	bool isActive;
	std::string powers [4] = {"PADDLE_MAX","PADDLE_MIN","EXTRA_POINTS","DESTROY_BALL"};
	std::string type;
};
//power up array size
const int POWER_UP_TYPE_MAX_COUNT = 4;
const int POWER_UP_MAX_COUNT = 5;
extern PowerUp powerUps[POWER_UP_MAX_COUNT];
extern int powerUpCount;


extern int game_quit;					// flag - true for user want to quit game
extern int auto_mode;					// flag - true for computer playing
extern int score;						// number bounces off paddle
extern int lives;						// number of balls left to play			

// frame information
extern double this_time, old_time, dt, start_time;

// ===============================================
// Function prototypes
// ===============================================

// platform generic functions
void start_life(void);					// restart game for new life
void update(void);						// update game entities
bool calculateChance(const int& chance); //calculate chance of spawning item after nth hit
void triggerReward();					 //triggers trap,reward or extra points.
void resetPowerUps(std::string []); 	//reset power up array to null

// function with platform specific implementations in pong_*.c
int init(void);							// initialise graphics system
void deinit(void);						// release resources

void draw_powerUp(void);					//draws active powerups on screen
void draw_walls(void);					
void draw_ball(void);
void draw_paddle(void); 
int draw_scene(void);						// draw scene by calling draw_* functions
void draw_status(void);						// draw status message
void drawRectangle(float x,float y, float width, float height);    //draws rectangle
void setColor(float R, float G, float B); 			//accepts RGB floats each from 0-255
float clamp(float value,float max, float min);		//clamps values
void get_input(void);								//keyboard/mouse/pad input
void spawnBall(float x,float y,float angle);		//spawns a ball with values.
void destroyBall(int index);						//destroys ball at specified index
void spawnPowerUp(float x,float y);					//spawns a power up
void destroyPowerUp(int index);						//destroys a power up
int randomNumber(int min, int max);			// generates random numbers between max and min
bool checkBallCollisionWithPowerUp(Ball &ball,PowerUp &powerUp);

void activatePowerUp(PowerUp &powerUp);				//applies power up.
#endif
