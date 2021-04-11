package ru.nsu.kolochkin.pacman;

import java.io.*;
import java.util.*;

public class Model {
	public enum CellValue {
		empty, smallDot, bigDot, wall, ghost1, ghost2, ghost3, pacman
	}

	public enum Direction {
		up, down, left, right, none
	}

	private final Pacman pacman = new Pacman();

	private final Ghost1 ghost1 = new Ghost1();

	private final Ghost2 ghost2 = new Ghost2();

	private final Ghost3 ghost3 = new Ghost3();

	private int rowCount;

	private int columnCount;

	private int score;

	boolean gameOver = false;

	private CellValue[][] grid;

	private Direction pacmanDirection;

	private Direction ghost1Direction = Direction.up;

	private Direction ghost2Direction = Direction.up;

	private Direction ghost3Direction = Direction.up;

	private int pacmanX = 0;

	private int pacmanY = 0;

	private int ghost1X = 0;

	private int ghost1Y = 0;

	private int ghost2X = 0;

	private int ghost2Y = 0;

	private int ghost3X = 0;

	private int ghost3Y = 0;

	public int level;

	public Model(int level_) {
		level = level_;
		startNewGame();
	}
	/**
	 * This method parses a level file and
	 * initializes a new game level.
	 */
	public void initializeLevel() {
		rowCount = 31;
		columnCount = 28;
		Scanner scanner = null;
		try {
			if (level == 1) {
				scanner = new Scanner(new File("src/ru/nsu/kolochkin/PacMan/levels/level1.txt"));
			}
			if (level == 2) {
				scanner = new Scanner(new File("src/ru/nsu/kolochkin/PacMan/levels/level2.txt"));
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		grid = new CellValue[rowCount][columnCount];
		int x = 0;
		while (scanner.hasNextLine()) {
			int y = 0;
			String line = scanner.nextLine();
			Scanner lineScanner = new Scanner(line);
			while (lineScanner.hasNext()) {
				String value = lineScanner.next();
				CellValue current;
				switch (value) {
					case "W" -> current = CellValue.wall;
					case "S" -> current = CellValue.smallDot;
					case "B" -> current = CellValue.bigDot;
					case "1" -> {
						current = CellValue.ghost1;
						ghost1X = x;
						ghost1Y = y;
					}
					case "2" -> {
						current = CellValue.ghost2;
						ghost2X = x;
						ghost2Y = y;
					}
					case "3" -> {
						current = CellValue.ghost3;
						ghost3X = x;
						ghost3Y = y;
					}
					case "P" -> {
						current = CellValue.pacman;
						pacmanX = x;
						pacmanY = y;
					}
					default -> current = CellValue.empty;
				}
				grid[x][y] = current;
				y++;
			}
			x++;
		}
	}
	/**
	 * This method starts a new game.
	 */
	public void startNewGame() {
		rowCount = 0;
		columnCount = 0;
		initializeLevel();
	}

	public void movePacman() { pacman.move(grid); }

	public void moveGhost1() { ghost1.move(grid); }

	public void moveGhost2() { ghost2.move(grid); }

	public void moveGhost3() { ghost3.move(grid); }

	public CellValue getCellValue(int row, int column) { return this.grid[row][column]; }

	public void setCurrentDirection(Direction direction) {
		pacmanDirection = direction;
	}

	public int getScore() { return score; }

	public int getPacmanX() { return pacmanX; }

	public int getPacmanY() { return pacmanY; }

	public Direction getPacmanDirection() { return pacmanDirection; }

	public int getGhost1X() { return ghost1X; }

	public int getGhost1Y() { return ghost1Y; }

	public int getGhost2X() { return ghost2X; }

	public int getGhost2Y() { return ghost2Y; }

	public int getGhost3X() { return ghost3X; }

	public int getGhost3Y() { return ghost3Y; }

	public Direction getGhost1Direction() { return ghost1Direction; }

	public Direction getGhost2Direction() { return ghost2Direction; }

	public Direction getGhost3Direction() { return ghost3Direction; }

	public void setScore(int score_) { score = score_; }

	public void setGameOver(boolean gameOver_) { gameOver = gameOver_; }

	public void setPacmanX(int pacmanX_) { pacmanX = pacmanX_; }

	public void setPacmanY(int pacmanY_) { pacmanY = pacmanY_; }

	public void setGhost1X(int ghost1X_) { ghost1X = ghost1X_; }

	public void setGhost1Y(int ghost1Y_) { ghost1Y = ghost1Y_; }

	public void setGhost2X(int ghost2X_) { ghost2X = ghost2X_; }

	public void setGhost2Y(int ghost2Y_) { ghost2Y = ghost2Y_; }

	public void setGhost3X(int ghost3X_) { ghost3X = ghost3X_; }

	public void setGhost3Y(int ghost3Y_) { ghost3Y = ghost3Y_; }

	public void setGhost1Direction(Direction ghost1Direction_) { ghost1Direction = ghost1Direction_; }

	public void setGhost2Direction(Direction ghost2Direction_) { ghost2Direction = ghost2Direction_; }

	public void setGhost3Direction(Direction ghost3Direction_) { ghost3Direction = ghost3Direction_; }

}
