package pacman;

import javafx.scene.control.Cell;

import java.io.*;
import java.util.*;

public class Model {
	public enum CellValue {
		empty, smallDot, bigDot, wall, ghost1, ghost2, pacman
	};

	public enum Direction {
		up, down, left, right, none
	};

	private int rowCount;

	private int columnCount;

	boolean gameOver = false;

	private int score;

	private CellValue[][] grid;

	Direction pacmanDirection;

	Direction ghost1Direction;

	private int pacmanX;

	private int pacmanY;

	private int ghost1X = 0;

	private int ghost1Y = 0;

	private int ghost2X = 0;

	private int ghost2Y = 0;

	public Model() { startNewGame(); }


	public void initializeLevel() {
		rowCount = 31;
		columnCount = 28;
		Scanner scanner = null;
		try {
			scanner = new Scanner(new File("src/pacman/levels/level1.txt"));
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

	public void startNewGame() {
		rowCount = 0;
		columnCount = 0;
		initializeLevel();
	}

	public void movePacman() {
		if (pacmanDirection == Direction.none) {
			return;
		}
		if (pacmanDirection == Direction.right) {
			if (pacmanY == columnCount - 1) {
				pacmanY = 0;
				grid[pacmanX][pacmanY] = grid[pacmanX][columnCount - 1];
				grid[pacmanX][columnCount - 1] = CellValue.empty;
				return;
			} else if (grid[pacmanX][pacmanY + 1] == CellValue.wall) {
				pacmanDirection = Direction.none;
				return;
			} else if (pacmanY < columnCount && pacmanX < rowCount) {
				grid[pacmanX][pacmanY + 1] = grid[pacmanX][pacmanY];
				grid[pacmanX][pacmanY] = CellValue.empty;
				pacmanY++;
			}
		}
		if (pacmanDirection == Direction.left) {
			if (pacmanY == 0) {
				pacmanY = columnCount - 1;
				grid[pacmanX][pacmanY] = grid[pacmanX][0];
				grid[pacmanX][0] = CellValue.empty;
			} else if (grid[pacmanX][pacmanY - 1] == CellValue.wall) {
				pacmanDirection = Direction.none;
				return;
			} else if (pacmanY < columnCount && pacmanX < rowCount) {
				grid[pacmanX][pacmanY - 1] = grid[pacmanX][pacmanY];
				grid[pacmanX][pacmanY] = CellValue.empty;
				pacmanY--;
			}
		}
		if (pacmanDirection == Direction.up) {
			if (grid[pacmanX - 1][pacmanY] == CellValue.smallDot) {
				score += 10;
			}
			if (grid[pacmanX - 1][pacmanY] == CellValue.bigDot) {
				score += 50;
			}
			if (grid[pacmanX - 1][pacmanY] == CellValue.wall) {
				pacmanDirection = Direction.none;
				return;
			}
			if (pacmanY <= 28 && pacmanX <= 31) {
				grid[pacmanX - 1][pacmanY] = grid[pacmanX][pacmanY];
				grid[pacmanX][pacmanY] = CellValue.empty;
				pacmanX--;
			}
		}
		if (pacmanDirection == Direction.down) {
			if (grid[pacmanX + 1][pacmanY] == CellValue.smallDot) {
				score += 10;
			}
			if (grid[pacmanX + 1][pacmanY] == CellValue.bigDot) {
				score += 50;
			}
			if (grid[pacmanX + 1][pacmanY] == CellValue.wall) {
				pacmanDirection = Direction.none;
				return;
			}
			if (pacmanY <= 28 && pacmanX <= 31) {
				grid[pacmanX + 1][pacmanY] = grid[pacmanX][pacmanY];
				grid[pacmanX][pacmanY] = CellValue.empty;
				pacmanX++;
			}
		}
	}

	private void swap(CellValue a, CellValue b) {
		CellValue tmp = a;
		a = b;
		b = tmp;
	}

	//todo method for move
	public boolean moveGhost1() {
		if (grid[ghost1X][ghost1Y] == CellValue.pacman) {
			gameOver = true;
			grid[pacmanX][pacmanY] = CellValue.ghost1;
			return false;
		}
		if (grid[ghost1X - 1][ghost1Y] != CellValue.wall) {
			CellValue tmp = grid[ghost1X - 1][ghost1Y];
			grid[ghost1X - 1][ghost1Y] = grid[ghost1X][ghost1Y];
			grid[ghost1X][ghost1Y] = tmp;
			ghost1X--;
			return true;
		}
		if (grid[ghost1X][ghost1Y + 1] != CellValue.wall) {
			CellValue tmp = grid[ghost1X][ghost1Y + 1];
			grid[ghost1X][ghost1Y + 1] = grid[ghost1X][ghost1Y];
			grid[ghost1X][ghost1Y] = tmp;
			ghost1Y++;
			return true;
		}
		if (grid[ghost1X + 1][ghost1Y] != CellValue.wall) {
			CellValue tmp = grid[ghost1X + 1][ghost1Y];
			grid[ghost1X + 1][ghost1Y] = grid[ghost1X][ghost1Y];
			grid[ghost1X][ghost1Y] = tmp;
			ghost1X++;
			return true;
		}
		if (grid[ghost1X][ghost1Y - 1] != CellValue.wall) {
			CellValue tmp = grid[ghost1X][ghost1Y - 1];
			grid[ghost1X][ghost1Y - 1] = grid[ghost1X][ghost1Y];
			grid[ghost1X][ghost1Y] = tmp;
			ghost1Y--;
			return true;
		}
		return true;
	}

	public CellValue getCellValue(int row, int column) { return this.grid[row][column]; }

	public int getRowCount() { return rowCount; }

	public int getColumnCount() { return columnCount; }

	public void setCurrentDirection(Direction direction) {
		pacmanDirection = direction;
	}

	public int getScore() { return score; }

}
