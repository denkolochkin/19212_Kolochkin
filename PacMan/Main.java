package ru.nsu.kolochkin.pacman;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.event.EventHandler;
import javafx.fxml.*;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;

public class Main extends Application {

    static Stage stage = null;

    public static Stage getStage() { return stage; }

    @Override
    public void start(Stage primaryStage) throws Exception {
        stage = primaryStage;
        FXMLLoader loader = new FXMLLoader(getClass().getResource("pacman.fxml"));
        Parent root = loader.load();
        primaryStage.setTitle("PacMan");
        Controller controller = loader.getController();
        root.setOnKeyPressed(controller);
        primaryStage.setOnCloseRequest(new EventHandler<WindowEvent>() {
            @Override
            public void handle(WindowEvent windowEvent) {
                Platform.exit();
                System.exit(0);
            }
        });
        primaryStage.setScene(new Scene(root, 560, 690));
        primaryStage.show();
        root.requestFocus();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
