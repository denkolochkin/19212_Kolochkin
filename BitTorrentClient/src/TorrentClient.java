import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class TorrentClient {

	protected static boolean isSeed = false;

	protected static boolean isLeech = false;

	protected static List<byte[]> downloadedPieces = new ArrayList<>();

	public static void main(String[] args) {
		isLeech =  args[0].equals("leech");
		Thread serverThread = new Thread(() -> {
			Thread.currentThread().setName("Server");
			Server server = new Server();
			try {
				server.startServer();
			} catch (IOException e) {
				e.printStackTrace();
			}
		});
		Thread clientThread = new Thread(() -> {
			Thread.currentThread().setName("Client");
			Client client = new Client();
			client.startClient();
		});
		serverThread.start();
		clientThread.start();
	}
}
