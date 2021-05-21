import java.io.IOException;

public class TorrentClient {

	public static void main(String[] args) {
		Thread serverThread = new Thread(new Runnable() {
			@Override
			public void run() {
				Server server = new Server();
				try {
					server.main(args);
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		});
		serverThread.start();

		Client client = new Client();
		client.startClient();

	}
}
