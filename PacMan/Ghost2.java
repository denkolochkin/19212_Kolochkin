package ru.nsu.kolochkin.pacman;

public class Ghost2 implements Entity {

	Model model;
	/**
	 * This method moves a second ghost.
	 */
	@Override
	public void move(Model.CellValue[][] grid) {
		model = Controller.getModel();
		int ghost2X = model.getGhost2X();
		int ghost2Y = model.getGhost2Y();
		Model.Direction ghost2Direction = model.getGhost2Direction();
		if (grid[ghost2X][ghost2Y] == Model.CellValue.pacman) {
			model.setGameOver(true);
			return;
		}
		if (ghost2Direction == Model.Direction.up) {
			Model.CellValue tmp = grid[ghost2X - 1][ghost2Y];
			if (tmp == Model.CellValue.wall || tmp == Model.CellValue.ghost1 || tmp == Model.CellValue.ghost3) {
				int index = (int) (Math.random() * 4);
				ghost2Direction = Model.Direction.values()[index];
				if (ghost2Direction != Model.Direction.down && ghost2Direction != Model.Direction.up) {
					model.setGhost2Direction(ghost2Direction);
				}
				return;
			}
			grid[ghost2X - 1][ghost2Y] = grid[ghost2X][ghost2Y];
			grid[ghost2X][ghost2Y] = tmp;
			ghost2X--;
			model.setGhost2X(ghost2X);
			return;
		}
		if (ghost2Direction == Model.Direction.right) {
			Model.CellValue tmp = grid[ghost2X][ghost2Y + 1];
			if (ghost2Y == columnCount - 2 && tmp != Model.CellValue.wall) {
				ghost2Direction = Model.Direction.left;
				model.setGhost1Direction(ghost2Direction);
				return;
			}
			if (tmp == Model.CellValue.wall || tmp == Model.CellValue.ghost1 || tmp == Model.CellValue.ghost3) {
				int index = (int) (Math.random() * 4);
				ghost2Direction = Model.Direction.values()[index];
				if (ghost2Direction != Model.Direction.right && ghost2Direction != Model.Direction.left) {
					model.setGhost2Direction(ghost2Direction);
				}
				return;
			}
			grid[ghost2X][ghost2Y + 1] = grid[ghost2X][ghost2Y];
			grid[ghost2X][ghost2Y] = tmp;
			ghost2Y++;
			model.setGhost2Y(ghost2Y);
			return;
		}
		if (ghost2Direction == Model.Direction.down) {
			Model.CellValue tmp = grid[ghost2X + 1][ghost2Y];
			if (tmp == Model.CellValue.wall || tmp == Model.CellValue.ghost1 || tmp == Model.CellValue.ghost3) {
				int index = (int) (Math.random() * 4);
				ghost2Direction = Model.Direction.values()[index];
				if (ghost2Direction != Model.Direction.down && ghost2Direction != Model.Direction.up) {
					model.setGhost2Direction(ghost2Direction);
				}
				return;
			}
			grid[ghost2X + 1][ghost2Y] = grid[ghost2X][ghost2Y];
			grid[ghost2X][ghost2Y] = tmp;
			ghost2X++;
			model.setGhost2X(ghost2X);
			return;
		}
		if (ghost2Direction == Model.Direction.left) {
			Model.CellValue tmp = grid[ghost2X][ghost2Y - 1];
			if (ghost2Y == 1 && tmp != Model.CellValue.wall) {
				ghost2Direction = Model.Direction.right;
				model.setGhost2Direction(ghost2Direction);
				return;
			}
			if (tmp == Model.CellValue.wall || tmp == Model.CellValue.ghost1 || tmp == Model.CellValue.ghost3) {
				int index = (int) (Math.random() * 4);
				ghost2Direction = Model.Direction.values()[index];
				if (ghost2Direction != Model.Direction.right && ghost2Direction != Model.Direction.left) {
					model.setGhost2Direction(ghost2Direction);
				}
				return;
			}
			grid[ghost2X][ghost2Y - 1] = grid[ghost2X][ghost2Y];
			grid[ghost2X][ghost2Y] = tmp;
			ghost2Y--;
		}
		model.setGhost2X(ghost2X);
		model.setGhost2Y(ghost2Y);
		model.setGhost2Direction(ghost2Direction);

	}
}
