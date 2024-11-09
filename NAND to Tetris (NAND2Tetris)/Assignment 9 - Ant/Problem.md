# HW 09: Andy H.J. Ant

### Intro

Langton's ant is a two-dimensional universal Turing machine with a very simple set of rules but complex emergent behavior. It can also be described as a cellular automaton. In this project you will have to implement Andy H.J. Ant, a slightly modified version of Langton's ant that is adapted for living in the world simulated in our Hack-Jack platform.


### Setup

- Prompt user for Andy's initial x, y coordinates.
- Prompt user for Andy's initial direction.
- Set all pixels to white, except for the one that Andy initially occupies (set that one to black).


### Process

Users may resume/pause the process using the "SPACE" key. Initially it is in a paused state.

In a paused state, Andy stops moving and the world freezes.

In running state, Andy moves according to (almost) standard rules:

  - At a white pixel
    * Turns 90° clockwise.
    * Flips the color of the currently occupied pixel.
    * Moves forward one pixel in the current direction.

  - At a black pixel
    * Turns 90° counter-clockwise.
    * Flips the color of the currently occupied pixel.
    * Moves forward one pixel in the current direction.

Except, if at any point, Andy has to pass through the edge of the world,
in which case, wraps around and comes back from the opposite edge.


### Restart

Users may use the "R" key to restart the process. In response,

  - Log Andy's total number of steps on each simulation so far.
  - Start a setup for a new simulation.


### Bonus 2%

Pick Andy's initial coordinates randomly if user does not want to enter them (i.e. hits "ENTER" key without providing any values)