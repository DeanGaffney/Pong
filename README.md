# Pong
__*C++ version of pong using Opengl and PSP development libraries*__

#### **Features**

##### Refactoring:
    - Implement drawRectangle function [x]
    - Implement setColor function [x]

##### Pimping:
    - [x] *Multiple balls* 
      - Every succesive 5th hit triggers a reward           calculation which can either trigger a new ball 
        to spawn,a power up to spawn or if the required
        calculation is not met the player recieves extra
        points.
    - [x] *Rewards* 
      - I have included several types of power ups they
        are as follows:
          -  Spawn a new ball
          -  Increase paddle to maximum length
          -  Decrease paddle to minimum length
          -  Change the direction of a moving ball
          -  Spawn an exisitng ball in a random location
          -  Destroy a ball (only if more than 1 ball on the screen at the time,otherwise other powerup is used)

        
