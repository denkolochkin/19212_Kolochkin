package ru.nsu.kolochkin.pacman;

public interface Entity {

	int columnCount = 28;

	int rowCount = 31;
	/**
	 * This method move some entity.
	 */
	void move(Model.CellValue[][] grid);

}
