package ru.nsu.kolochkin.pacman;

public class Ghost1 implements Entity {

	Model model;
	/**
	 * This method moves a first ghost.
	 */
	@Override
	public void move(Model.CellValue[][] grid) {
		model = Controller.getModel();
		int ghost1X = model.getGhost1X();
		int ghost1Y = model.getGhost1Y();
		Model.Direction ghost1Direction = model.getGhost1Direction();
		if (grid[ghost1X][ghost1Y] == Model.CellValue.pacman) {
			model.setGameOver(true);
			return;
		}
		if (ghost1Direction == Model.Direction.up) {
			Model.CellValue tmp = grid[ghost1X - 1][ghost1Y];
			if (tmp == Model.CellValue.wall || tmp == Model.CellValue.ghost2 || tmp == Model.CellValue.ghost3) {
				int index = (int) (Math.random() * 4);
				ghost1Direction = Model.Direction.values()[index];
				if (ghost1Direction != Model.Direction.down && ghost1Direction != Model.Direction.up) {
					model.setGhost1Direction(ghost1Direction);
				}
				return;
			}
			grid[ghost1X - 1][ghost1Y] = grid[ghost1X][ghost1Y];
			grid[ghost1X][ghost1Y] = tmp;
			ghost1X--;
			model.setGhost1X(ghost1X);
			return;
		}
		if (ghost1Direction == Model.Direction.right) {
			Model.CellValue tmp = grid[ghost1X][ghost1Y + 1];
			if (ghost1Y == columnCount - 2 && tmp != Model.CellValue.wall) {
				ghost1Direction = Model.Direction.left;
				model.setGhost1Direction(ghost1Direction);
				return;
			}
			if (tmp == Model.CellValue.wall || tmp == Model.CellValue.ghost2 || tmp == Model.CellValue.ghost3) {
				int index = (int) (Math.random() * 4);
				ghost1Direction = Model.Direction.values()[index];
				if (ghost1Direction != Model.Direction.right && ghost1Direction != Model.Direction.left) {
					model.setGhost1Direction(ghost1Direction);
				}
				return;
			}
			grid[ghost1X][ghost1Y + 1] = grid[ghost1X][ghost1Y];
			grid[ghost1X][ghost1Y] = tmp;
			ghost1Y++;
			model.setGhost1Y(ghost1Y);
			return;
		}
		if (ghost1Direction == Model.Direction.down) {
			Model.CellValue tmp = grid[ghost1X + 1][ghost1Y];
			if (tmp == Model.CellValue.wall || tmp == Model.CellValue.ghost2 || tmp == Model.CellValue.ghost3) {
				int index = (int) (Math.random() * 4);
				ghost1Direction = Model.Direction.values()[index];
				if (ghost1Direction != Model.Direction.down && ghost1Direction != Model.Direction.up) {
					model.setGhost1Direction(ghost1Direction);
				}
				return;
			}
			grid[ghost1X + 1][ghost1Y] = grid[ghost1X][ghost1Y];
			grid[ghost1X][ghost1Y] = tmp;
			ghost1X++;
			model.setGhost1X(ghost1X);
			return;
		}
		if (ghost1Direction == Model.Direction.left) {
			Model.CellValue tmp = grid[ghost1X][ghost1Y - 1];
			if (ghost1Y == 1 && tmp != Model.CellValue.wall) {
				ghost1Direction = Model.Direction.right;
				model.setGhost1Direction(ghost1Direction);
				return;
			}
			if (tmp == Model.CellValue.wall || tmp == Model.CellValue.ghost2 || tmp == Model.CellValue.ghost3) {
				int index = (int) (Math.random() * 4);
				ghost1Direction = Model.Direction.values()[index];
				if (ghost1Direction != Model.Direction.right && ghost1Direction != Model.Direction.left) {
					model.setGhost1Direction(ghost1Direction);
				}
				return;
			}
			grid[ghost1X][ghost1Y - 1] = grid[ghost1X][ghost1Y];
			grid[ghost1X][ghost1Y] = tmp;
			ghost1Y--;
		}
		model.setGhost1X(ghost1X);
		model.setGhost1Y(ghost1Y);
		model.setGhost1Direction(ghost1Direction);
	}
}
