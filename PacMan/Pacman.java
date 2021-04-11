package ru.nsu.kolochkin.pacman;

public class Pacman implements Entity {

	Model model;
	/**
	 * This method moves a pacman.
	 */
	@Override
	public void move(Model.CellValue[][] grid) {
		model = Controller.getModel();
		int pacmanX = model.getPacmanX();
		int pacmanY = model.getPacmanY();
		Model.Direction pacmanDirection = model.getPacmanDirection();
		int score = model.getScore();
		if (grid[pacmanX][pacmanY] == Model.CellValue.ghost1 ||
				grid[pacmanX][pacmanY] == Model.CellValue.ghost2) {
			model.setGameOver(true);
			return;
		}
		if (pacmanDirection == Model.Direction.none) {
			return;
		}
		if (pacmanDirection == Model.Direction.right) {
			if (pacmanY == columnCount - 2 && grid[pacmanX][pacmanY + 1] != Model.CellValue.wall) {
				pacmanY = 0;
				grid[pacmanX][pacmanY] = grid[pacmanX][columnCount - 2];
				grid[pacmanX][columnCount - 2] = Model.CellValue.empty;
				model.setPacmanY(pacmanY);
				return;
			} else if (grid[pacmanX][pacmanY + 1] == Model.CellValue.wall) {
				return;
			} else if (pacmanY < columnCount && pacmanX < rowCount) {
				grid[pacmanX][pacmanY + 1] = grid[pacmanX][pacmanY];
				grid[pacmanX][pacmanY] = Model.CellValue.empty;
				pacmanY++;
			}
			if (grid[pacmanX][pacmanY + 1] == Model.CellValue.smallDot) {
				score += 10;
			}
			if (grid[pacmanX][pacmanY + 1] == Model.CellValue.bigDot) {
				score += 50;
			}
		}
		if (pacmanDirection == Model.Direction.left) {
			if (pacmanY == 1 && grid[pacmanX][pacmanY - 1] != Model.CellValue.wall) {
				pacmanY = columnCount - 1;
				grid[pacmanX][pacmanY] = grid[pacmanX][1];
				grid[pacmanX][1] = Model.CellValue.empty;
				model.setPacmanY(pacmanY);
				return;
			} else if (grid[pacmanX][pacmanY - 1] == Model.CellValue.wall) {
				return;
			} else if (pacmanY < columnCount && pacmanX < rowCount) {
				grid[pacmanX][pacmanY - 1] = grid[pacmanX][pacmanY];
				grid[pacmanX][pacmanY] = Model.CellValue.empty;
				pacmanY--;
			}
			if (grid[pacmanX][pacmanY - 1] == Model.CellValue.smallDot) {
				score += 10;
			}
			if (grid[pacmanX][pacmanY - 1] == Model.CellValue.bigDot) {
				score += 50;
			}
		}
		if (pacmanDirection == Model.Direction.up) {
			if (grid[pacmanX - 1][pacmanY] == Model.CellValue.smallDot) {
				score += 10;
			}
			if (grid[pacmanX - 1][pacmanY] == Model.CellValue.bigDot) {
				score += 50;
			}
			if (grid[pacmanX - 1][pacmanY] == Model.CellValue.wall) {
				return;
			}
			if (pacmanY <= 28 && pacmanX <= 31) {
				grid[pacmanX - 1][pacmanY] = grid[pacmanX][pacmanY];
				grid[pacmanX][pacmanY] = Model.CellValue.empty;
				pacmanX--;
			}
		}
		if (pacmanDirection == Model.Direction.down) {
			if (grid[pacmanX + 1][pacmanY] == Model.CellValue.smallDot) {
				score += 10;
			}
			if (grid[pacmanX + 1][pacmanY] == Model.CellValue.bigDot) {
				score += 50;
			}
			if (grid[pacmanX + 1][pacmanY] == Model.CellValue.wall) {
				return;
			}
			if (pacmanY <= 28 && pacmanX <= 31) {
				grid[pacmanX + 1][pacmanY] = grid[pacmanX][pacmanY];
				grid[pacmanX][pacmanY] = Model.CellValue.empty;
				pacmanX++;
			}
		}
		model.setScore(score);
		model.setPacmanX(pacmanX);
		model.setPacmanY(pacmanY);
	}
}
