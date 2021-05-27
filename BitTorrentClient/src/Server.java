import java.io.*;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.HashMap;
import java.util.Map;

public class Server extends TorrentClient {

	private final Map<SocketChannel, ByteBuffer> sockets = new HashMap<>();

	private final String path = "test";

	public int port = 4242;

	private void sendString(String data, ByteBuffer buffer, SocketChannel socketChannel) {
		buffer.flip();
		String response = data + "\r\n";
		buffer.clear();
		buffer.put(ByteBuffer.wrap(response.getBytes()));
		buffer.flip();
		try {
			int bytesWritten = socketChannel.write(buffer);
			log("Writing to " + socketChannel.getRemoteAddress() + ", bytes written = " + bytesWritten);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	private void sendData(ByteBuffer buffer, SocketChannel socketChannel, int index) {
		buffer.flip();
		buffer.clear();
		File file = new File("pieces/" + index + path + ".txt");
		byte[] fileInArray = new byte[(int)file.length()];
		FileInputStream fin = null;
		try {
			fin = new FileInputStream("pieces/" + index + path + ".txt");
		}  catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		try {
			assert fin != null;
			int n = fin.read(fileInArray,0, (int)file.length());
			if (n == -1) {
				log("No more data");
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
		buffer.put(ByteBuffer.wrap(fileInArray));
		buffer.put(ByteBuffer.wrap("\r\n".getBytes()));
		buffer.flip();
		try {
			int bytesWritten = socketChannel.write(buffer);
			log("Writing to " + socketChannel.getRemoteAddress() + ", bytes written = " + bytesWritten);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public void startServer() throws IOException {
		ServerSocketChannel serverChannel = ServerSocketChannel.open();
		serverChannel.socket().bind(new InetSocketAddress(port));
		serverChannel.configureBlocking(false);
		Selector selector = Selector.open();
		serverChannel.register(selector, SelectionKey.OP_ACCEPT);
		boolean isHandshake = false;
		boolean isPieceMessage = false;
		int index = -1;
		System.out.println("-----------------------------------------------------------------");
		log("Server started at port " + port + ". Waiting for connections...");
		while (true) {
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
							if ((char) buffer.get(0) == 'G') {
								isSeed = true;
								isPieceMessage = true;
							}
							if ((char) buffer.get(0) == '1' && (char)buffer.get(1) == '9') {
								isHandshake = true;
								index++;
							}
							log("Reading from " + socketChannel.getRemoteAddress() + ", bytes read = " + bytesRead);
							if (bytesRead == -1) {
								isSeed = false;
								log("Connection closed " + socketChannel.getRemoteAddress());
								System.out.println("-----------------------------------------------------------------");
								sockets.remove(socketChannel);
								socketChannel.close();
							}
							if (bytesRead > 0 && buffer.get(buffer.position() - 1) == '\n') {
								socketChannel.register(selector, SelectionKey.OP_WRITE);
							}
						} else if (key.isWritable()) {
							SocketChannel socketChannel = (SocketChannel) key.channel();
							ByteBuffer buffer = sockets.get(socketChannel);
							if (isHandshake) {
								Handshake handshake = new Handshake();
								String handshake_ = handshake.generateHandshake(InetAddress.getLocalHost().
												getHostAddress(), SHA1.generateSHA(index + path + ".txt"));
								sendString(handshake_, buffer, socketChannel);
								isHandshake = false;
							}
							if (isPieceMessage) {
								sendData(buffer, socketChannel, index);
								isPieceMessage = false;
							}
							if (!buffer.hasRemaining()) {
								buffer.compact();
								socketChannel.register(selector, SelectionKey.OP_READ);
							}
						}
					} catch (IOException e) {
						log("error " + e.getMessage());
					}
				}
			}
			selector.selectedKeys().clear();
		}
	}

	private static void log(String message) {
		System.out.println("[" + Thread.currentThread().getName() + "] " + message);
	}
}