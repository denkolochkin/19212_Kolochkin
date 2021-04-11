package ru.nsu.kolochkin.pacman;

import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.Pane;
import javafx.stage.Modality;
import javafx.stage.Stage;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.atomic.AtomicBoolean;

public class GameOverWindow {

	static Map<String, Integer> records = new HashMap<String, Integer>();
	/**
	 * This method creates and shows window
	 * that uses when game is over.
	 */
	public static boolean showGameOverWindow(int score, int level) {
		AtomicBoolean flag = new AtomicBoolean(false);
		Pane pane = new Pane();
		Stage window = new Stage();
		Scene scene = new Scene(pane, 250, 250);
		pane.setStyle("-fx-background-color: #1d095a");
		Label label = new Label("Name:");
		TextField name = new TextField();
		Button endButton = new Button("Exit");
		Button restartButton = new Button("Restart");
		Button tableButton = new Button("Records");
		name.setLayoutX(70);
		name.setLayoutY(20);
		name.setMaxWidth(100);
		label.setLayoutY(20);
		label.setLayoutX(10);
		label.setStyle("-fx-text-fill: #817878; -fx-font-size: 20px;");
		endButton.setStyle("-fx-background-color: #817878");
		restartButton.setStyle("-fx-background-color: #817878");
		tableButton.setStyle("-fx-background-color: #817878");
		window.initModality(Modality.APPLICATION_MODAL);
		window.setScene(scene);
		window.setMaxWidth(200);
		window.setMaxHeight(250);
		window.setTitle("Game Over");
		endButton.setOnAction(actionEvent -> {
			records.put(name.getText(), score);
			window.close();
		});
		restartButton.setOnAction(actionEvent -> {
			records.put(name.getText(), score);
			window.close();
			flag.set(true);
		});
		tableButton.setOnAction(actionEvent -> {
			records.put(name.getText(), score);
			RecordsTable.showRecordsTable(records, level);
		});
		endButton.setLayoutX(70);
		restartButton.setLayoutX(70);
		tableButton.setLayoutX(70);
		endButton.setLayoutY(110);
		restartButton.setLayoutY(60);
		tableButton.setLayoutY(160);
		endButton.setMinSize(70, 40);
		restartButton.setMinSize(70,40);
		tableButton.setMinSize(70, 40);
		pane.getChildren().add(label);
		pane.getChildren().add(name);
		pane.getChildren().add(endButton);
		pane.getChildren().add(restartButton);
		pane.getChildren().add(tableButton);
		window.showAndWait();
		return flag.get();
	}
}
