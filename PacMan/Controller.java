package ru.nsu.kolochkin.pacman;

import javafx.application.Platform;
import javafx.event.Event;
import javafx.fxml.FXML;
import javafx.event.EventHandler;
import javafx.scene.control.Label;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import java.util.Timer;
import java.util.TimerTask;

/**
 * This class controls things that that happen
 * on the game field.
 */
public class Controller implements EventHandler<Event> {

	@FXML public Label infoLabel;

	@FXML private Label scoreLabel;

	@FXML private Label levelLabel;

	@FXML private View view;

	private boolean pause = false;

	private boolean isPause;

	static private Model model;

	private Timer timer;

	private int level = 1;
	/**
	 * This method start a runnable task that
	 * updates a game field.
	 */
	private void startTimer() {
		TimerTask task = new TimerTask() {
			public void run() {
				Platform.runLater(() -> {
					if (!pause) {
						isPause = false;
						if (model.getScore() == 2200 && level == 1) {
							timer.cancel();
							level++;
							initialize();
						}
						if (model.getScore() == 3400 && level == 2) {
							timer.cancel();
							GameOverWindow.showGameOverWindow(model.getScore(), level);
						}
						if (!model.gameOver) {
							model.moveGhost1();
							model.moveGhost2();
							model.moveGhost3();
							model.movePacman();
							scoreLabel.setText(String.format("Score: %d", model.getScore()));
							view.update(model);
						} else {
							timer.cancel();
							if (GameOverWindow.showGameOverWindow(getModel().getScore(), level)) {
								initialize();
							} else {
								Main.getStage().close();
							}
						}
					} else {
						if (!isPause) {
							isPause = true;
							if (PauseMenu.showPauseMenu()) {
								pause = false;
							}
						}
					}
				});
			}
		};
		double frameTimeInMilliseconds = 120.0;
		timer.schedule(task, 0, (long) frameTimeInMilliseconds);
	}
	/**
	 * This method initializes a new level.
	 */
	public void initialize() {
		timer = new Timer();
		model = new Model(level);
		view.update(model);
		infoLabel.setText("Press Enter to pause");
		scoreLabel.setText(String.format("Score: %d", 0));
		levelLabel.setText(String.format("Level: %d", 1));
		startTimer();
	}
	/**
	 * This method catches events from keyboard.
	 */
	@Override
	public void handle(Event event) {
		KeyEvent keyEvent = (KeyEvent) event;
		KeyCode btn = keyEvent.getCode();
		boolean click = true;
		if (btn == KeyCode.ENTER) {
			pause = !pause;
			keyEvent.consume();
			return;
		}
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

	static public Model getModel() { return model; }
}
