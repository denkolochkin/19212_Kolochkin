package pacman;

import javafx.application.Platform;
import javafx.fxml.FXML;
import javafx.event.EventHandler;
import javafx.scene.control.Alert;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;

import java.util.Timer;
import java.util.TimerTask;

public class Controller implements EventHandler<KeyEvent> {

	@FXML private View view;

	private Model model;

	private Timer timer;

	private void startTimer() {
		timer = new java.util.Timer();
		TimerTask task = new TimerTask() {
			public void run() {
				Platform.runLater(new Runnable() {
					public void run() {
						model.movePacman();
						if (model.moveGhost1()) {
							view.update(model);
						} else {
							timer.cancel();
							timer.purge();
							view.showAlert();
						}
					}
				});
			}
		};
		double frameTimeInMilliseconds = 150.0;
		timer.schedule(task, 0, (long) frameTimeInMilliseconds);
	}

	public void initialize() {
		this.model = new Model();
		this.view.update(model);
		startTimer();
	}

	public double getBoardWidth() {
		return View.cellSize * this.view.getColumnCount();
	}

	public double getBoardHeight() {
		return View.cellSize * this.view.getRowCount();
	}

	@Override
	public void handle(KeyEvent keyEvent) {
		KeyCode btn = keyEvent.getCode();
		boolean click = true;
		Model.Direction direction = Model.Direction.none;
		if (btn == KeyCode.DOWN) {
			direction = Model.Direction.down;
		} else if (btn == KeyCode.UP) {
			direction = Model.Direction.up;
		} else if (btn == KeyCode.LEFT) {
			direction = Model.Direction.left;
		} else if (btn == KeyCode.RIGHT){
			direction = Model.Direction.right;
		} else {
			click = false;
		}
		if (click) {
			keyEvent.consume();
			model.setCurrentDirection(direction);
		}
	}
}
