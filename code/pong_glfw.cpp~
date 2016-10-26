// ===============================================
// @file   pong_glfw.cpp
// @author kmurphy
// @practical pong
// @brief  GLFW (OpenGL) specific code for Pong implementation
// ===============================================

// ===============================================
// Headers
// ===============================================
#include "pong.h"
#ifndef PSP

//used to calculate RGB values for custom setColor method
const float RGB_DIVIDER = 255;


// helper function taken from GLUI library
// used to render a string 
void _glutBitmapString(void *font, char *s) {
    char *p = s;

    while(*p != '\0') {
        glutBitmapCharacter(font, *p);
        p++;
    }
}


int init(void) {

	static int argc=1;
	static char *argv[1];
	argv[0] = strdup("pong");
	glutInit(&argc, argv);
	
	glfwInit(); 
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
	if( !glfwOpenWindow(WINDOW_WIDTH,WINDOW_HEIGHT, 0,0,0,0,0,0, GLFW_WINDOW) ) { 
		glfwTerminate(); 
		printf("Failed to open window");
		return 1; 
	} 
	glfwSetWindowPos(100,100);
	glfwSetWindowTitle(WINDOW_NAME);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT); 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);
    glMatrixMode(GL_MODELVIEW);
	
	// frame information
    start_time = this_time = glfwGetTime();

	return 0;
}


void deinit(void) {
	glfwTerminate(); 
}


void get_input(void) {

	game_quit = glfwGetKey(GLFW_KEY_ESC) || !glfwGetWindowParam(GLFW_OPENED);
	if (game_quit) return;

    if (glfwGetKey(GLFW_KEY_UP)) {
        paddle_speed = 1;
    } else if (glfwGetKey(GLFW_KEY_DOWN)) {
        paddle_speed = -1;
    } else {
        paddle_speed = 0.0;
    }		
	if (glfwGetKey('A')) auto_mode = !auto_mode;

}


int draw_scene(void) {
	
	glClear(GL_COLOR_BUFFER_BIT); 
	
	draw_walls();

	// paddle
    glPushMatrix();
        glTranslatef(paddle_x_pos-PADDLE_WIDTH/2, paddle_y_pos-paddleLength/2, 0);
        draw_paddle();
    glPopMatrix();

	// ball(s)
	for(int ball = 0; ball < ballCount;ball++){
   	 	glPushMatrix();
        		glTranslatef(balls[ball].x - BALL_SIZE/2, balls[ball].y  - BALL_SIZE/2, 0);
        		draw_ball();
    		glPopMatrix();
	}

	//powerUp(s)
	for(int powerUp = 0; powerUp < powerUpCount;powerUp++){
		glPushMatrix();
			glTranslatef(powerUps[powerUp].x - POWER_UP_SIZE/2,powerUps[powerUp].y - POWER_UP_SIZE/2,0);
			draw_powerUp();
		glPopMatrix();
	}

	draw_status();								// status message

	glfwSwapBuffers(); 

	// update frame timer
	old_time = this_time;
	this_time = glfwGetTime();
	dt = this_time - old_time;
	
	return 0;	// success
}

//(x1,y1) one vertex of shape, (x2,y2) opposite vertex
void drawRectangle(float x,float y, float width, float height){
	glRectf(x,y,width,height);
}

void draw_powerUp(void){
	setColor(66,244,203);

	drawRectangle(0,0,POWER_UP_SIZE,POWER_UP_SIZE);
}

void draw_walls(void) {
	
    //set to red
    setColor(255,0,0);

    //top wall
    drawRectangle(0,WINDOW_HEIGHT-BORDER_SIZE,WINDOW_WIDTH,WINDOW_WIDTH+BORDER_SIZE);
    
    //lower wall
    drawRectangle(0,MARGIN_SIZE,WINDOW_WIDTH,MARGIN_SIZE+BORDER_SIZE);

    //left wall
    drawRectangle(0,BORDER_SIZE,BORDER_SIZE,WINDOW_HEIGHT-BORDER_SIZE);
}


void draw_ball(void)  {
	//set color to green
    setColor(0,255,0);

    //draw ball
    drawRectangle(0,0,BALL_SIZE,BALL_SIZE);
}


void draw_paddle(void)  {
	//set color to blue
    setColor(0,0,255);

    // draw paddle
    drawRectangle(0,0,PADDLE_WIDTH,paddleLength);
}

void draw_status(void)  {
	// buffer to hold output message
	static char mess[300];

	sprintf(mess, 
		"FPS = %4.0f        Score = %3d    Lives = %1d", 1.0/dt, score, lives);

	glRasterPos2i(100, 1);
    _glutBitmapString(GLUT_BITMAP_9_BY_15, mess);
}

void setColor(float R, float G, float B){
	glColor3f(R/RGB_DIVIDER,G/RGB_DIVIDER,B/RGB_DIVIDER);
}

#endif
