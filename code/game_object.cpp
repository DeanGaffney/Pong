// ===============================================
// @file   pong.h
// @author dean gaffney
// @practical pong
// @brief  Base class for game objects
// ===============================================

class GameObject{
	public:
		float positionX;
		float positionY;
		float width;
		float heigth;
		float center;
		float angle;
		float speed;


		virtual void draw(float x1,float y1, float x2, float y2) = 0;			//each element will draw differently
};