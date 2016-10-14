// ===============================================
// @file   pong.cpp
// @author kmurphy
// @practical pong
// @brief  Main code for PSP+GLFW(OpenGL) pong game 
// ===============================================


// ===============================================
// Headers
// ===============================================
#include "pong.h"

// ===============================================
// Global identifiers
// ===============================================

Ball balls[BALL_MAX_COUNT];
int ballCount;

float paddle_x_pos;
float paddle_y_pos;
float paddle_speed;
float paddle_y_min, paddle_y_max;
float paddleLength;

int game_quit = 0;						// flag - true for user want to quit game
int score = 0;							// number bounces off paddle
int lives = 3;							// number of balls left to play						
int auto_mode = 1;						// flag - true for computer playing
										
std::string powerUps[5] = {"","","","",""}; //max of five powerups at any one time

// frame information
double this_time, old_time, dt, start_time;

//clamps values of paddles length
float clamp(float value,float max,float min){
	if(value < min)return min;
	if(value > max)return max;
	
	return value;
}

void start_life() {
	
	// initial ball position and direction
	balls[0].x      = WINDOW_WIDTH/2;
    	balls[0].y     = WINDOW_HEIGHT/2;
	balls[0].angle = 0.961; /* some arbitrary value -- could use rand() */
	
	// initial paddle position
	paddle_x_pos    = WINDOW_WIDTH - PADDLE_WIDTH/2;
	paddle_y_pos    = WINDOW_HEIGHT/2;
	paddleLength = PADDLE_MAX_LEN;

	//set score
	score = 0;

	//reset power up array
	resetPowerUps(powerUps);
	
	//set ball count
	ballCount = 1;
}


void resetPowerUps(std::string []){
	for(int i = 0; i < 5;i++){
		powerUps[i] = "";
	}
}

bool calculateChance(const int& chance){
	const int random = rand() % chance;
	return random == 0;
}

void triggerReward(){
	//1 in 15 to spawn a powerup
	if(calculateChance(15)){
		//put powerup into a vector or add to array (would need to limit power up array then)
	}else if(calculateChance(10)){
		//spawn a trap (vector or limited array for amount of traps)
	}else{
		//if no power up or trap spawned give player extra points
		score += 2;
	}
}

void update() {
	
	// automatically update paddle direction (if required)
	if (auto_mode) {
		if (paddle_y_pos-paddleLength/2>balls[0].y) {
			paddle_speed = -1;
		} else if (paddle_y_pos+paddleLength/2<balls[0].y) {
			paddle_speed = 1;
		}
	}

	// update paddle position
	paddle_y_pos += PADDLE_STEP*paddle_speed;
	
	// calculate limits for paddle movement 
	const float paddle_y_min = (paddleLength/2+MARGIN_SIZE+BORDER_SIZE);
	const float paddle_y_max = (WINDOW_HEIGHT-BORDER_SIZE-paddleLength/2);

	// ensure paddle stays within limits
	if (paddle_y_pos<paddle_y_min) {
		paddle_y_pos = paddle_y_min;
	} else if (paddle_y_pos>paddle_y_max) {
		paddle_y_pos = paddle_y_max;
	}
		
	// update ball position (centre)
	balls[0].x += BALL_STEP*cos(balls[0].angle);
	balls[0].y += BALL_STEP*sin(balls[0].angle);
	
	// calculate limits for ball movement 
	const float ball_y_min = BALL_SIZE/2 + MARGIN_SIZE + BORDER_SIZE;
	const float ball_y_max = WINDOW_HEIGHT - BALL_SIZE/2 - BORDER_SIZE;
	const float ball_x_min = BORDER_SIZE + BALL_SIZE/2;
	const float ball_x_max = WINDOW_WIDTH - PADDLE_WIDTH - BALL_SIZE/2;
	
    	// check - ball hit top or bottom wall
 	if ((balls[0].y <= ball_y_min || balls[0].y >= ball_y_max)) {
        	balls[0].angle = -balls[0].angle;
    	} 

	// check - ball hit left wall
	if  (balls[0].x <= ball_x_min) {
		balls[0].angle = M_PI - balls[0].angle;
	}
	
	// check - ball hits paddle or misses
	if (balls[0].x >= ball_x_max) {
		if(fabs(balls[0].y-paddle_y_pos) <= (paddleLength+BALL_SIZE)/2) {
			score++;
			paddleLength = clamp(paddleLength-5,PADDLE_MIN_LEN,PADDLE_MAX_LEN);
			balls[0].angle = M_PI - balls[0].angle;
		} else {
			lives--;
			start_life();
		}
 	}	


 	//trigger something every 5th hit
 	if(score % 5 == 0){
 		triggerReward();
 	}
}

int main(void) {

	init();							// initial graphics/sound components
	start_life();					// reset game to starting state

	while (!game_quit && lives>0) {
		draw_scene();
		get_input();
		update();	
	}
	deinit();
	return 0;
}

