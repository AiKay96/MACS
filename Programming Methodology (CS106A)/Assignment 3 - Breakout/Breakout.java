
/*
 * File: Breakout.java
 * -------------------
 * Name:
 * Section Leader:
 * 
 * This file will eventually implement the game of Breakout.
 */

import acm.graphics.*;
import acm.program.*;
import acm.util.*;

import java.applet.*;
import java.awt.*;
import java.awt.event.*;

public class Breakout extends GraphicsProgram implements MouseListener {

	/** Width and height of application window in pixels */
	public static final int APPLICATION_WIDTH = 400;
	public static final int APPLICATION_HEIGHT = 600;

	/** Dimensions of game board (usually the same) */
	private static final int WIDTH = APPLICATION_WIDTH;
	private static final int HEIGHT = APPLICATION_HEIGHT;

	/** Dimensions of the paddle */
	private static final int PADDLE_WIDTH = 60;
	private static final int PADDLE_HEIGHT = 10;

	/** Offset of the paddle up from the bottom */
	private static final int PADDLE_Y_OFFSET = 30;

	/** Number of bricks per row */
	private static final int NBRICKS_PER_ROW = 10;

	/** Number of rows of bricks */
	private static final int NBRICK_ROWS = 10;

	/** Separation between bricks */
	private static final int BRICK_SEP = 4;

	/** Width of a brick */
	private static final int BRICK_WIDTH = (WIDTH - (NBRICKS_PER_ROW - 1) * BRICK_SEP) / NBRICKS_PER_ROW;

	/** Height of a brick */
	private static final int BRICK_HEIGHT = 8;

	/** Radius of the ball in pixels */
	private static final int BALL_RADIUS = 10;

	/** Offset of the top brick row from the top */
	private static final int BRICK_Y_OFFSET = 70;

	/** Number of turns */
	private static final int NTURNS = 3;
	
	/** Pause time for ball */
	private static final int PAUSE_TIME = 10;
	
	/** Speed and directon for ball */
	private double vx;
	private double vy;
	
	/** Number of bricks */
	private int brickN = NBRICK_ROWS * NBRICKS_PER_ROW;

	private GRect brick;
	private GRect paddle;
	private GOval ball;

	private RandomGenerator rgen = RandomGenerator.getInstance();

	/* Method: run() */
	/** Runs the Breakout program. */
	public void init() {
		setSize(WIDTH, HEIGHT);
		createBall();
		createBrickRows();
		createPaddle();
		addMouseListeners();
		process();
	}
	public void run() {
		getCollidingObject();
	}
	public void mouseMoved(MouseEvent e) {
		if (e.getX() >= PADDLE_WIDTH / 2.0 && e.getX() <= WIDTH - PADDLE_WIDTH / 2.0) {
			paddle.move(e.getX() - paddle.getX() - PADDLE_WIDTH / 2.0, 0);
		}
	}
	private void process() {
		int life = NTURNS;
		while (life > 0) {
			vy = 3.0;
			vx = rgen.nextDouble(1.0, 3.0);
			if (rgen.nextBoolean(0.5)) {
				vx = -vx;
			}
			while (true) {
				ball.move(vx, vy);
				/** reflect from left wall */
				if (ball.getX() <= 0) {
					vx = -vx;
				}
				/** reflect from upper wall */
				if (ball.getY() <= 0) {
					vy = -vy;
				}
				/** reflect from right wall */
				if (ball.getX() >= WIDTH - 2 * BALL_RADIUS) {
					vx = -vx;
				}
				/** if ball collides paddle */
				if (getCollidingObject() == paddle) {
					/** ball only can reflect from top of paddle, if it reflects from other side game will be already over. */
					if (ball.getY() + 2 * BALL_RADIUS <= paddle.getY() + 3)
						reflect(paddle);
				}
				/** if ball collides brick */
				if (getCollidingObject() == brick) {
					reflect(brick);
				}
				pause(PAUSE_TIME);
				/** if ball fell */
				if (ball.getY() + 2 * BALL_RADIUS >= HEIGHT) {
					life--;
					remove(ball);
					break;
				}
				if (brickN == 0) {
					remove(ball);
					break;
				}
			}
			if (brickN != 0) {
				createBall();
			}
		}
		/** if remove all bricks */
		if (brickN == 0) {
			println("YOU WON! GJ");
		/** if we lose 3 times */
		}else if(life == 0) {
			println("LOSER! HAHA");
		}
	}
/** method to reflect ball properly. A is colliding object. */
	private void reflect(GObject A) {
		//object width.
		int W = 0;
		//object height.
		int H = 0;
		boolean remove = false;
		if (A == paddle) {
			W = PADDLE_WIDTH;
			H = PADDLE_HEIGHT;
		}
		if (A == brick) {
			W = BRICK_WIDTH;
			H = BRICK_HEIGHT;
			//we need to remove only bricks.
			remove = true;
		}
		//checks ball's left upper corner. if ball collided
		if (getElementAt(ball.getX(), ball.getY()) != null) {
			
			if (getElementAt(ball.getX() + 3, ball.getY()) != null) {
				//if ball didn't collide from right wall, it needs only y change.
				vy = -vy;
			} else {
				//if ball collide from right wall, it needs only x change.
				vx = -vx;
				if (ball.getX() == A.getX() + W && ball.getY() == A.getY() + H) {
					//only when ball collided from right lower corner, it needs y change too.
					vy = -vy;
				}
			}
			if (remove) {
				//if ball collided brick (remove = true), it will reduce bricks number and also remove it from canvas.
				brickN--;
				println(brickN);
				remove(getElementAt(ball.getX(), ball.getY()));
			}
		//checks ball's right upper corner. if ball collided
		} else if (getElementAt(ball.getX() + 2 * BALL_RADIUS, ball.getY()) != null) {
			if (getElementAt(ball.getX() + 2 * BALL_RADIUS - 3, ball.getY()) != null) {
				//if ball didn't collide from left wall, it needs only y change.
				vy = -vy;
			} else {
				//if ball collide from left wall, it needs only x change.
				vx = -vx;
				if (ball.getX() + 2 * BALL_RADIUS == A.getX() && ball.getY() == A.getY() + H) {
					//only when ball collided from left lower corner, it needs y change too.
					vy = -vy;
				}
			}
			if (remove) {
				//if ball collided brick (remove = true), it will reduce bricks number and also remove it from canvas.
				brickN--;
				println(brickN);
				remove(getElementAt(ball.getX() + 2 * BALL_RADIUS, ball.getY()));
			}
		//checks ball's left lower corner. if ball collided
		} else if (getElementAt(ball.getX(), ball.getY() + 2 * BALL_RADIUS) != null) {
			if (getElementAt(ball.getX() + 3, ball.getY() + 2 * BALL_RADIUS) != null) {
				//if ball didn't collide from right wall, it needs only y change.
				vy = -vy;
			} else {
				//if ball collide from right wall, it needs only x change.
				vx = -vx;
				if (ball.getX() == A.getX() + W && ball.getY() + 2 * BALL_RADIUS == A.getY()) {
					//only when ball collided from right upper corner, it needs y change too.
					vy = -vy;
				}
			}
			if (remove) {
				//if ball collided brick (remove = true), it will reduce bricks number and also remove it from canvas.
				brickN--;
				println(brickN);
				remove(getElementAt(ball.getX(), ball.getY() + 2 * BALL_RADIUS));
			}
		//checks ball's right lower corner. if ball collided
		} else if (getElementAt(ball.getX() + 2 * BALL_RADIUS, ball.getY() + 2 * BALL_RADIUS) != null) {
			if (getElementAt(ball.getX() + 2 * BALL_RADIUS - 3, ball.getY() + 2 * BALL_RADIUS) != null) {
				//if ball didn't collide from left wall, it needs only y change.
				vy = -vy;
			} else {
				//if ball collide from left wall, it needs only x change.
				vx = -vx;
				if (ball.getX() + 2 * BALL_RADIUS == A.getX() && ball.getY() + 2 * BALL_RADIUS == A.getY()) {
					//only when ball collided from left upper corner, it needs y change too.
					vy = -vy;
				}
			}
			if (remove) {
				//if ball collided brick (remove = true), it will reduce bricks number and also remove it from canvas.
				brickN--;
				println(brickN);
				remove(getElementAt(ball.getX() + 2 * BALL_RADIUS, ball.getY() + 2 * BALL_RADIUS));
			}
		}
	}
/** method that checks 4 points(4 ones from docx) and returns relevant object. */
	private GObject getCollidingObject() {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				if (getElementAt(ball.getX() + j * 2 * BALL_RADIUS, ball.getY() + i * 2 * BALL_RADIUS) == paddle) {
					return paddle;
				}
			}
		}
		//if upper code didn't return paddle, that already means that colliding object is not paddle, so we don't need != paddle anymore.
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				if (getElementAt(ball.getX() + j * 2 * BALL_RADIUS, ball.getY() + i * 2 * BALL_RADIUS) != null) {
					return brick;
				}
			}
		}
		return null;
	}
/** creates circle for ball. */
	private void createBall() {
		ball = new GOval(2 * BALL_RADIUS, 2 * BALL_RADIUS);
		ball.setFilled(true);
		add(ball, WIDTH / 2 - BALL_RADIUS, HEIGHT / 2 - BALL_RADIUS);
	}
/** creates rectangle in center for paddle. */
	private void createPaddle() {
		paddle = new GRect(PADDLE_WIDTH, PADDLE_HEIGHT);
		paddle.setFilled(true);
		add(paddle, (WIDTH - PADDLE_WIDTH) / 2, HEIGHT - PADDLE_Y_OFFSET - PADDLE_HEIGHT);
	}
/** builds every brick. */
	private void createBrickRows() {
		int y = BRICK_Y_OFFSET;
		for (int i = 0; i < NBRICK_ROWS; i++) {
			createBrickRow(y, color(i / 2));
			y += BRICK_HEIGHT + BRICK_SEP;
		}
	}
/** method to use colors for two brick rows. */
	private Color color(int i) {
		if (i % 10 == 1) {
			return Color.ORANGE;
		} else if (i % 10 == 2) {
			return Color.YELLOW;
		} else if (i % 10 == 3) {
			return Color.GREEN;
		} else if (i % 10 == 4) {
			return Color.CYAN;
		}
		return Color.RED;
	}
/** creates bricks row. starts from x, y location and fills with color: color. */
	private void createBrickRow(int y, Color color) {
		int x = (WIDTH - (NBRICKS_PER_ROW - 1) * BRICK_SEP - NBRICKS_PER_ROW * BRICK_WIDTH) / 2;
		for (int i = 0; i < NBRICKS_PER_ROW; i++) {
			createBrick(x, y, color);
			x += BRICK_WIDTH + BRICK_SEP;
		}
	}
/**creates brick on location x, y and filled with color: color. */
	private void createBrick(int x, int y, Color color) {
		brick = new GRect(BRICK_WIDTH, BRICK_HEIGHT);
		brick.setColor(color);
		brick.setFilled(true);
		brick.setFillColor(color);
		add(brick, x, y);
	}
}