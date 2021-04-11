package ru.nsu.kolochkin.pacman;

import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.layout.Pane;
import javafx.stage.Modality;
import javafx.stage.Stage;
import java.util.concurrent.atomic.AtomicBoolean;

public class PauseMenu {
	/**
	 * This method shows alert with
	 * "help" information.
	 */
	public static void showAlertHelp() {
		Alert alert = new Alert(Alert.AlertType.INFORMATION);
		alert.setTitle("Help");
		alert.setContentText("Control - arrows  Pause - Enter");
		alert.showAndWait();
	}
	/**
	 * This method shows alert with
	 * "about" information.
	 */
	public static void showAlertAbout() {
		Alert alert = new Alert(Alert.AlertType.INFORMATION);
		alert.setTitle("About");
		alert.setContentText("PacMan version 1.4 by Denis Kolochkin \n NSU FIT 2021");
		alert.showAndWait();
	}
	/**
	 * This method creates and shows window
	 * that uses when player pushes on the pause button.
	 */
	public static boolean showPauseMenu() {
		AtomicBoolean flag = new AtomicBoolean(false);
		Pane pane = new Pane();
		Stage window = new Stage();
		Scene scene = new Scene(pane, 300, 350);
		pane.setStyle("-fx-background-color: #1d095a");
		Button continueButton = new Button("Continue");
		Button helpButton = new Button("Help");
		Button aboutButton = new Button("About");
		window.initModality(Modality.APPLICATION_MODAL);
		window.setScene(scene);
		window.setMaxWidth(200);
		window.setMaxHeight(250);
		window.setTitle("Pause");
		continueButton.setOnAction(actionEvent -> {
			flag.set(true);
			window.close();
		});
		helpButton.setOnAction(actionEvent -> {
			showAlertHelp();
		});
		aboutButton.setOnAction(actionEvent -> {
			showAlertAbout();
		});
		continueButton.setStyle("-fx-background-color: #817878");
		helpButton.setStyle("-fx-background-color: #817878");
		aboutButton.setStyle("-fx-background-color: #817878");
		continueButton.setLayoutX(70);
		helpButton.setLayoutX(70);
		aboutButton.setLayoutX(70);
		continueButton.setLayoutY(30);
		helpButton.setLayoutY(80);
		aboutButton.setLayoutY(130);
		continueButton.setMinSize(70, 40);
		helpButton.setMinSize(70,40);
		aboutButton.setMinSize(70, 40);
		pane.getChildren().add(continueButton);
		pane.getChildren().add(helpButton);
		pane.getChildren().add(aboutButton);
		window.showAndWait();
		return flag.get();
	}
}
