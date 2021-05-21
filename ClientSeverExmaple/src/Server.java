import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.nio.charset.StandardCharsets;
import java.util.HashMap;
import java.util.Map;

public class Server {

	private static final Map<SocketChannel, ByteBuffer> sockets = new HashMap<>();

	private static int piecesNumber = 9;

	private static String path = "/Users/deniskolockin/IdeaProjects/ClientSeverExmaple/test.txt";

	private static void sendString(String data, ByteBuffer buffer, SocketChannel socketChannel) {
		buffer.flip();
		String response = data + "\r\n";
		buffer.clear();
		buffer.put(ByteBuffer.wrap(response.getBytes()));
		buffer.flip();
		try {
			int bytesWritten = socketChannel.write(buffer);
			log("Writing to " + socketChannel.getRemoteAddress() + ", bytes writteb=" + bytesWritten);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	private static void sendData(ByteBuffer buffer, SocketChannel socketChannel) {
		buffer.flip();
		buffer.clear();
		File file = new File(path);
		byte[] fileInArray = new byte[(int)file.length()];
		FileInputStream fin = null;
		try {
			fin = new FileInputStream(path);
		}  catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		try {
			fin.read(fileInArray,0, (int)file.length());
		} catch (IOException e) {
			e.printStackTrace();
		}
		buffer.put(ByteBuffer.wrap(fileInArray));
		buffer.put(ByteBuffer.wrap("\r\n".getBytes()));
		buffer.flip();
		try {
			int bytesWritten = socketChannel.write(buffer);
			log("Writing to " + socketChannel.getRemoteAddress() + ", bytes writteb=" + bytesWritten);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public static void main(String[] args) throws IOException {
		ServerSocketChannel serverChannel = ServerSocketChannel.open();
		serverChannel.socket().bind(new InetSocketAddress(4242));
		serverChannel.configureBlocking(false);
		Selector selector = Selector.open();
		serverChannel.register(selector, SelectionKey.OP_ACCEPT);
		boolean isMeta = false;
		boolean isHandshake = false;
		log("Server started at port 4242. Waiting for connections...");
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
							if ((char)buffer.get(0) == 'G') {
								isMeta = true;
							}
							if ((char)buffer.get(0) == '1' && (char)buffer.get(1) == '9') {
								isHandshake = true;
							}
							log("Reading from " + socketChannel.getRemoteAddress() + ", bytes read=" + bytesRead);
							if (bytesRead == -1) {
								log("Connection closed " + socketChannel.getRemoteAddress());
								sockets.remove(socketChannel);
								socketChannel.close();
							}
							if (bytesRead > 0 && buffer.get(buffer.position() - 1) == '\n') {
								socketChannel.register(selector, SelectionKey.OP_WRITE);
							}
						} else if (key.isWritable()) {
							SocketChannel socketChannel = (SocketChannel) key.channel();
							ByteBuffer buffer = sockets.get(socketChannel);
							if (isMeta) {
								MetaData metaData = new MetaData();
								String meta = metaData.generateMeta(InetAddress.getLocalHost().getHostAddress(),
										"test.txt", piecesNumber);
								sendString(meta, buffer, socketChannel);
								isMeta = false;

							}
							if (isHandshake) {
								Handshake handshake = new Handshake();
								String handshake_ = handshake.generateHandshake(InetAddress.getLocalHost().getHostAddress());
								sendString(handshake_, buffer, socketChannel);
								isHandshake = false;
							}
							if (buffer.get(0) == 'F') {
								sendData(buffer, socketChannel);
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