import java.io.*;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.HashMap;
import java.util.Map;

public class Server {

	private final Map<SocketChannel, ByteBuffer> sockets = new HashMap<>();

	private final HashMap<Integer, Boolean> downloaded = new HashMap<>();

	private int serverPort;

	private final MessageHandler handler = new MessageHandler();

	public boolean isSeed = false;

	public void startServer(int serverPort_, boolean isSeed_) throws IOException {
		serverPort = serverPort_;
		isSeed = isSeed_;
		ServerSocketChannel serverChannel = ServerSocketChannel.open();
		serverChannel.socket().bind(new InetSocketAddress(serverPort));
		serverChannel.configureBlocking(false);
		Selector selector = Selector.open();
		serverChannel.register(selector, SelectionKey.OP_ACCEPT);
		int index = -1;
		//for test
		String path = "test";
		Threadpool pool = null;
		if (serverPort == 4243) {
			for (int i = 0; i < 4; i++) {
				if (i != 1) {
					downloaded.put(i, true);
				} else {
					downloaded.put(i, false);
				}
			}
			pool = new Threadpool(3);
		}
		if (serverPort == 4244) {
			for (int i = 0; i < 4; i++) {
				if (i == 1) {
					downloaded.put(i, true);
				} else {
					downloaded.put(i, false);
				}
			}
			pool = new Threadpool(1);
		}
		log("Server started at port " + serverPort + ". Waiting for connections...");
		handler.setServerPort(serverPort);
		while (true) {
			if (isSeed) {
				selector.select();
				for (SelectionKey key : selector.selectedKeys()) {
					if (key.isValid()) {
						try {
							if (key.isAcceptable()) {
								SocketChannel socketChannel = serverChannel.accept();
								socketChannel.configureBlocking(false);
								log("Connected " + socketChannel.getRemoteAddress());
								sockets.put(socketChannel, ByteBuffer.allocate(1000));
								socketChannel.register(selector, SelectionKey.OP_READ);
							} else if (key.isReadable()) {
								SocketChannel socketChannel = (SocketChannel) key.channel();
								ByteBuffer buffer = sockets.get(socketChannel);
								int bytesRead = socketChannel.read(buffer);
								index = handler.checkMessage(buffer, index);
								log("Reading from " + socketChannel.getRemoteAddress() + ", bytes read = " + bytesRead);
								if (bytesRead == -1) {
									log("Connection closed " + socketChannel.getRemoteAddress());
									System.out.println("-------------------------------------------------------------");
									sockets.remove(socketChannel);
									socketChannel.close();
								}
								if (bytesRead > 0 && buffer.get(buffer.position() - 1) == '\n') {
									socketChannel.register(selector, SelectionKey.OP_WRITE);
								}
							} else if (key.isWritable()) {
								SocketChannel socketChannel = (SocketChannel) key.channel();
								ByteBuffer buffer = sockets.get(socketChannel);
								final int index_ = index;
								assert pool != null;
								pool.addTask(() -> handler.send(downloaded, index_, buffer, socketChannel, path));
								if (!buffer.hasRemaining()) {
									buffer.compact();
									socketChannel.register(selector, SelectionKey.OP_READ);
								}
							}
						} catch (IOException e) {
							log("error " + e.getMessage());
							return;
						}
					}
				}
			}
			selector.selectedKeys().clear();
		}
	}

	private void log(String message) {
		System.out.println("[" + Thread.currentThread().getName() + serverPort + "] " + message);
	}
}