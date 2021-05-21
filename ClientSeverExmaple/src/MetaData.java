import java.io.File;

public class MetaData {

	public String generateMeta(String url, String fileName, int n) {
		String info = "[";
		File file = new File(fileName);
		long length = file.length();
		long pieceLength = length / n;
		String pieces = null;
		return url + info + fileName + "::" + pieceLength + "::" + length + "]";
	}
}
