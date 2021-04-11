package ru.nsu.kolochkin.pacman;

import javafx.fxml.FXML;
import javafx.scene.Group;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import ru.nsu.kolochkin.pacman.Model.CellValue;

public class View extends Group {
	public final static double cellSize = 20.0;
	@FXML private int rowCount;
	@FXML private int columnCount;
	private ImageView[][] field;
	private final Image pacmanRightImage;
	private final Image pacmanUpImage;
	private final Image pacmanDownImage;
	private final Image pacmanLeftImage;
	private final Image ghost1Image;
	private final Image ghost2Image;
	private final Image ghost3Image;
	private final Image wallImage;
	private final Image bigDotImage;
	private final Image smallDotImage;

	public View() {
		pacmanRightImage = new Image(getClass().getResourceAsStream("res/pacmanRight.gif"));
		pacmanUpImage = new Image(getClass().getResourceAsStream("res/pacmanUp.gif"));
		pacmanDownImage = new Image(getClass().getResourceAsStream("res/pacmanDown.gif"));
		pacmanLeftImage = new Image(getClass().getResourceAsStream("res/pacmanLeft.gif"));
		ghost1Image = new Image(getClass().getResourceAsStream("res/redghost.gif"));
		ghost2Image = new Image(getClass().getResourceAsStream("res/ghost2.gif"));
		ghost3Image = new Image(getClass().getResourceAsStream("res/blueghost.gif"));
		wallImage = new Image(getClass().getResourceAsStream("res/wall.png"));
		bigDotImage = new Image(getClass().getResourceAsStream("res/whitedot.png"));
		smallDotImage = new Image(getClass().getResourceAsStream("res/smalldot.png"));
	}
	/**
	 * This method paints a game field.
	 */
	private void initializeGrid() {
		if (rowCount > 0 && columnCount > 0) {
			field = new ImageView[rowCount][columnCount];
			for (int y = 0; y < this.rowCount; y++) {
				for (int x = 0; x < columnCount; x++) {
					ImageView imageView = new ImageView();
					imageView.setX(x * cellSize);
					imageView.setY(y * cellSize);
					imageView.setFitWidth(cellSize);
					imageView.setFitHeight(cellSize);
					field[y][x] = imageView;
					getChildren().add(imageView);
				}
			}
		}
	}
	/**
	 * This method updates a game field
	 * depends on the timer.
	 */
	public void update(Model model) {
		for (int y = 0; y < rowCount; y++) {
			for (int x = 0; x < columnCount; x++){
				CellValue value = model.getCellValue(y, x);
				if (value == CellValue.wall) {
					field[y][x].setImage(wallImage);
				}
				else if (value == CellValue.bigDot) {
					field[y][x].setImage(bigDotImage);
				}
				else if (value == CellValue.smallDot) {
					field[y][x].setImage(smallDotImage);
				}
				else if (value == CellValue.ghost1) {
					field[y][x].setImage(ghost1Image);
				}
				else if (value == CellValue.ghost2) {
					field[y][x].setImage(ghost2Image);
				}
				else if(value == CellValue.ghost3) {
					field[y][x].setImage(ghost3Image);
				}
				else if (value == CellValue.pacman) {
					if (model.getPacmanDirection() == Model.Direction.right) {
						field[y][x].setImage(pacmanRightImage);
					} else if (model.getPacmanDirection() == Model.Direction.left) {
						field[y][x].setImage(pacmanLeftImage);
					} else if (model.getPacmanDirection() == Model.Direction.up) {
						field[y][x].setImage(pacmanUpImage);
					} else if (model.getPacmanDirection() == Model.Direction.down) {
						field[y][x].setImage(pacmanDownImage);
					} else {
						field[y][x].setImage(pacmanRightImage);
					}
				}
				else {
					field[y][x].setImage(null);
				}
			}
		}
	}

	public int getRowCount() { return rowCount; }

	public int getColumnCount() { return columnCount; }

	public void setColumnCount(int count) {
		columnCount = count;
		initializeGrid();
	}

	public void setRowCount(int count) {
		rowCount = count;
		initializeGrid();
	}
}
