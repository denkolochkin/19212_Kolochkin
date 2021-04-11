package ru.nsu.kolochkin.pacman;

public class Ghost3 implements Entity {

	Model model;
	/**
	 * This method moves a third ghost.
	 */
	@Override
	public void move(Model.CellValue[][] grid) {
		model = Controller.getModel();
		int ghost3X = model.getGhost3X();
		int ghost3Y = model.getGhost3Y();
		Model.Direction ghost3Direction = model.getGhost3Direction();
		if (grid[ghost3X][ghost3Y] == Model.CellValue.pacman) {
			model.setGameOver(true);
			return;
		}
		if (ghost3Direction == Model.Direction.up) {
			Model.CellValue tmp = grid[ghost3X - 1][ghost3Y];
			if (tmp == Model.CellValue.wall || tmp == Model.CellValue.ghost1 || tmp == Model.CellValue.ghost2) {
				int index = (int) (Math.random() * 4);
				ghost3Direction = Model.Direction.values()[index];
				if (ghost3Direction != Model.Direction.down && ghost3Direction != Model.Direction.up) {
					model.setGhost3Direction(ghost3Direction);
				}
				return;
			}
			grid[ghost3X - 1][ghost3Y] = grid[ghost3X][ghost3Y];
			grid[ghost3X][ghost3Y] = tmp;
			ghost3X--;
			model.setGhost3X(ghost3X);
			return;
		}
		if (ghost3Direction == Model.Direction.right) {
			Model.CellValue tmp = grid[ghost3X][ghost3Y + 1];
			if (ghost3Y == columnCount - 2 && tmp != Model.CellValue.wall) {
				ghost3Direction = Model.Direction.left;
				model.setGhost1Direction(ghost3Direction);
				return;
			}
			if (tmp == Model.CellValue.wall || tmp == Model.CellValue.ghost1  || tmp == Model.CellValue.ghost2) {
				int index = (int) (Math.random() * 4);
				ghost3Direction = Model.Direction.values()[index];
				if (ghost3Direction != Model.Direction.right && ghost3Direction != Model.Direction.left) {
					model.setGhost3Direction(ghost3Direction);
				}
				return;
			}
			grid[ghost3X][ghost3Y + 1] = grid[ghost3X][ghost3Y];
			grid[ghost3X][ghost3Y] = tmp;
			ghost3Y++;
			model.setGhost3Y(ghost3Y);
			return;
		}
		if (ghost3Direction == Model.Direction.down) {
			Model.CellValue tmp = grid[ghost3X + 1][ghost3Y];
			if (tmp == Model.CellValue.wall || tmp == Model.CellValue.ghost1 || tmp == Model.CellValue.ghost2) {
				int index = (int) (Math.random() * 4);
				ghost3Direction = Model.Direction.values()[index];
				if (ghost3Direction != Model.Direction.down && ghost3Direction != Model.Direction.up) {
					model.setGhost3Direction(ghost3Direction);
				}
				return;
			}
			grid[ghost3X + 1][ghost3Y] = grid[ghost3X][ghost3Y];
			grid[ghost3X][ghost3Y] = tmp;
			ghost3X++;
			model.setGhost3X(ghost3X);
			return;
		}
		if (ghost3Direction == Model.Direction.left) {
			Model.CellValue tmp = grid[ghost3X][ghost3Y - 1];
			if (ghost3Y == 1 && tmp != Model.CellValue.wall) {
				ghost3Direction = Model.Direction.right;
				model.setGhost3Direction(ghost3Direction);
				return;
			}
			if (tmp == Model.CellValue.wall || tmp == Model.CellValue.ghost1 || tmp == Model.CellValue.ghost2) {
				int index = (int) (Math.random() * 4);
				ghost3Direction = Model.Direction.values()[index];
				if (ghost3Direction != Model.Direction.right && ghost3Direction != Model.Direction.left) {
					model.setGhost3Direction(ghost3Direction);
				}
				return;
			}
			grid[ghost3X][ghost3Y - 1] = grid[ghost3X][ghost3Y];
			grid[ghost3X][ghost3Y] = tmp;
			ghost3Y--;
		}
		model.setGhost3X(ghost3X);
		model.setGhost3Y(ghost3Y);
		model.setGhost3Direction(ghost3Direction);
	}
}
