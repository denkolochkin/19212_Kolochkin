import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class TorrentClient {

	static boolean isLeech = false;

	static boolean isSeed = false;

	static int serverPort;

	static List<String> party = new ArrayList<>();

	//args - leech/seed/peer, serverPort, ports of participants of the swarm ...
	public static void main(String[] args) {
		isLeech = args[0].equals("leech");
		isSeed = args[0].equals("seed");
		serverPort = Integer.parseInt(args[1]);
		party.addAll(Arrays.asList(args).subList(2, args.length));
		Thread serverThread = new Thread(() -> {
			Thread.currentThread().setName("Server");
			Server server = new Server();
			try {
				server.startServer(serverPort, isSeed);
			} catch (IOException e) {
				e.printStackTrace();
			}
		});
		Thread clientThread = new Thread(() -> {
			Thread.currentThread().setName("Client");
			Client client = new Client();
			client.startClient(isLeech, party, serverPort);
		});
		serverThread.start();
		clientThread.start();
	}
}
