import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.net.InetAddress;
import java.net.UnknownHostException;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;
import java.util.List;

public class MessageHandler {

	private boolean isPieceMessage = false;

	private boolean isHandshake = false;

	private boolean isHave = false;

	private int serverPort;

	public byte[] getPieceBytes(int index, String path) {
		File file = new File("pieces/" + index + path + ".txt");
		byte[] fileInArray = new byte[(int)file.length()];
		FileInputStream fin = null;
		try {
			fin = new FileInputStream( "pieces/" + index + path + ".txt");
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
		return fileInArray;
	}

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

	private void sendData(ByteBuffer buffer, SocketChannel socketChannel, int index, String path) {
		buffer.flip();
		buffer.clear();
		byte[] fileInArray = getPieceBytes(index, path);
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

	public int checkMessage(ByteBuffer buffer, int index) {
		if ((char) buffer.get(0) == 'G') {
			isPieceMessage = true;
		}
		if ((char) buffer.get(0) == '1' && (char)buffer.get(1) == '9') {
			isHandshake = true;
			index++;
		}
		if ((char) buffer.get(0) == 'H') {
			isHave = true;
		}
		return index;
	}

	public void send(List<byte[]> downloadedPieces, int index,
	                 ByteBuffer buffer, SocketChannel socketChannel, String path) {
		if (isHandshake) {
			Handshake handshake = new Handshake();
			String handshake_ = null;
			try {
				if (downloadedPieces.size() > index) {
					handshake_ = handshake.generateHandshake(InetAddress.getLocalHost().getHostAddress(),
							SHA1.generateSHA(index + path + ".txt"));
				} else {
					handshake_ = handshake.generateHandshake(InetAddress.getLocalHost().getHostAddress(),
							SHA1.generateSHA("null"));
				}
			} catch (UnknownHostException e) {
				e.printStackTrace();
			}
			sendString(handshake_, buffer, socketChannel);
			isHandshake = false;
		}
		if (isPieceMessage) {
			sendData(buffer, socketChannel, index, path);
			isPieceMessage = false;
		}
		if (isHave) {
			sendString("Ok", buffer, socketChannel);
			isHave = false;
		}
	}

	private void log(String message) {
		System.out.println("[" + Thread.currentThread().getName() + serverPort +  "] " + message);
	}

	public void setServerPort(int serverPort_) { serverPort = serverPort_; }
}
