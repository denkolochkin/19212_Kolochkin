package pacman;

import javafx.fxml.FXML;
import javafx.scene.Group;
import javafx.scene.control.Alert;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import pacman.Model.CellValue;

public class View extends Group {
	public final static double cellSize = 20.0;
	@FXML private int rowCount;
	@FXML private int columnCount;
	@FXML private int score;
	private ImageView[][] field;
	private Image pacmanRightImage;
	private Image pacmanUpImage;
	private Image pacmanDownImage;
	private Image pacmanLeftImage;
	private Image ghost1Image;
	private Image ghost2Image;
	private Image wallImage;
	private Image bigDotImage;
	private Image smallDotImage;

	public View() {
		pacmanRightImage = new Image(getClass().getResourceAsStream("res/pacmanRight.gif"));
		pacmanUpImage = new Image(getClass().getResourceAsStream("res/pacmanUp.gif"));
		pacmanDownImage = new Image(getClass().getResourceAsStream("res/pacmanDown.gif"));
		pacmanLeftImage = new Image(getClass().getResourceAsStream("res/pacmanLeft.gif"));
		ghost1Image = new Image(getClass().getResourceAsStream("res/redghost.gif"));
		ghost2Image = new Image(getClass().getResourceAsStream("res/ghost2.gif"));
		wallImage = new Image(getClass().getResourceAsStream("res/wall.png"));
		bigDotImage = new Image(getClass().getResourceAsStream("res/whitedot.png"));
		smallDotImage = new Image(getClass().getResourceAsStream("res/smalldot.png"));
	}

	public void showAlert() {
		Alert alert = new Alert(Alert.AlertType.INFORMATION);
		alert.setTitle("Game Over");
		alert.setContentText("You lose");
		alert.showAndWait();
	}

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

	public void update(Model model) {
		for (int y = 0; y < rowCount; y++) {
			for (int x = 0; x < columnCount; x++){
				CellValue value = model.getCellValue(y, x);
				score = model.getScore();
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
				else if (value == CellValue.pacman) {
					if (model.pacmanDirection == Model.Direction.right) {
						field[y][x].setImage(pacmanRightImage);
					} else if (model.pacmanDirection == Model.Direction.left) {
						field[y][x].setImage(pacmanLeftImage);
					} else if (model.pacmanDirection == Model.Direction.up) {
						field[y][x].setImage(pacmanUpImage);
					} else if (model.pacmanDirection == Model.Direction.down) {
						field[y][x].setImage(pacmanDownImage);
					} else if (model.pacmanDirection == Model.Direction.none){
						continue;
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

	public void setRowCount(int count) {
		rowCount = count;
		initializeGrid();
	}

	public int getColumnCount() { return columnCount; }

	public void setColumnCount(int count) {
		columnCount = count;
		initializeGrid();
	}
}
