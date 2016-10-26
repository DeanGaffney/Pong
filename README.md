## Pong
###__*C++ version of pong using Opengl and PSP development libraries*__

### Author - __*Dean Gaffney (20067423)*__
###Subject - __*Console Game Development 2*__
---


#### Features

##### Refactoring

   - Implement drawRectangle function __*(working)*__
   - Implement setColor function __*(working)*__

##### Pimping

   - Multiple balls __*(working)*__
       - Every successive 5th hit triggers a reward calculation which can either trigger a new ball 
        to spawn,a power up to spawn or if the required
        calculation is not met the player receives extra
        points. __*(working)*__
---
   - Rewards & Traps __*(working)*__
      - The rewards/traps are implemented using a struct of type PowerUp and an array of strings holding all possible types. A random chance calculator determines if a power up will be spawned and what type of power up it is, and where it's located. I have included several types of power ups they
        are as follows:
          -  Spawn a new ball __*(working)*__
          -  Increase paddle to maximum length __*(working)*__
          -  Decrease paddle to minimum length __*(working)*__
          -  Change the direction of a moving ball__*(working)*__
          -  Spawn an existing ball in a random  location __*(working)*__
          -  Destroy a ball *(only if more than 1 ball on the screen at the time,otherwise another power up is used)* __*(working)*__

#### Overview 
- Player has 3 lives.
- Game starts with one ball and can have a max of 5 balls at any one time.
- Every successful 5th hit triggers a custom calculate function which calculates a chance of spawning a reward,trap, ball or giving the player extra points.
- If a ball hits a power up it is used and applied to the game and the power up is then removed from the game.
- When a ball or power up is *'destroyed'* specific counter variables are updated and the appropriate array indexes are swapped to update the game with the correct number of items to draw on screen.
- A player loses a life if and only if the ball which left the screen was the last ball on the screen.
- Once all lives are lost the game ends.

        
