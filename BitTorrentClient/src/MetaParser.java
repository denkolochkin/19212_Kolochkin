import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class MetaParser {

	private String meta;

	private String currentServerAddress;

	private int numberOfPieces;

	private int fileSize;

	private String fileName;

	MetaParser() {
		saveMeta();
		parseMeta();
	}

	public void saveMeta() {
		File file = new File("test.torrent");
		FileReader fileReader = null;
		try {
			fileReader = new FileReader("test.torrent");
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		char[] array = new char[(int)file.length()];
		try {
			assert fileReader != null;
			int n = fileReader.read(array);
			if (n == 0) {
				log();
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
		meta = String.copyValueOf(array);
	}

	public void parseMeta() {
		int index = 0;
		StringBuilder address = new StringBuilder();
		while(meta.charAt(index) != '[') {
			address.append(meta.charAt(index));
			index++;
		}
		currentServerAddress = address.toString();
		index++;
		StringBuilder name = new StringBuilder();
		while(meta.charAt(index) != ':') {
			name.append(meta.charAt(index));
			index++;
		}
		fileName = name.toString();
		index += 2;
		StringBuilder number = new StringBuilder();
		while (meta.charAt(index) != ':') {
			number.append(meta.charAt(index));
			index++;
		}
		index += 2;
		StringBuilder size = new StringBuilder();
		while (meta.charAt(index) != ']') {
			size.append(meta.charAt(index));
			index++;
		}
		fileSize = Integer.parseInt(size.toString());
		numberOfPieces = Integer.parseInt(number.toString());
	}

	public int getNumberOfPieces() { return numberOfPieces; }

	public int getFileSize() { return fileSize; }

	public String getCurrentServerAddress() { return currentServerAddress; }

	public String getFileName() { return fileName; }

	private void log() {
		System.out.println("[" + Thread.currentThread().getName() + currentServerAddress +  "] " + "reading error");
	}

}
