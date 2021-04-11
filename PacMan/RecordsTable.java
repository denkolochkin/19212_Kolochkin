package ru.nsu.kolochkin.pacman;

import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.layout.Pane;
import javafx.stage.Modality;
import javafx.stage.Stage;
import java.util.Map;
import java.util.concurrent.atomic.AtomicInteger;

public class RecordsTable {
	/**
	 * This method creates and shows window
	 * that uses for showing records.
	 */
	public static void showRecordsTable(Map<String, Integer> records, int level) {
		Pane pane = new Pane();
		Stage window = new Stage();
		Scene scene = new Scene(pane, 300, 350);
		pane.setStyle("-fx-background-color: #1d095a");
		window.initModality(Modality.APPLICATION_MODAL);
		window.setScene(scene);
		window.setMaxWidth(300);
		window.setMaxHeight(350);
		window.setTitle("Records Table");
		Label lvl = new Label("Level - " + level);
		lvl.setStyle("-fx-font-size: 30px; -fx-text-fill: #817878;");
		lvl.setLayoutX(50);
		pane.getChildren().add(lvl);
		AtomicInteger dy = new AtomicInteger(30);
		records.entrySet().forEach(entry -> {
			Label record = new Label(entry.getKey() + ": " + entry.getValue());
			record.setStyle("-fx-font-size: 30px; -fx-text-fill: #817878;");
			record.setLayoutX(50);
			record.setLayoutY(dy.get());
			dy.addAndGet(30);
			pane.getChildren().add(record);
		});
		window.showAndWait();
	}
}
