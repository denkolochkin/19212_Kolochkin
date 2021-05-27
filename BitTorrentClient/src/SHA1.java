import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Formatter;

public class SHA1 {
	public static String byteToHex(final byte[] hash) {
		Formatter formatter = new Formatter();
		for (byte b : hash) {
			formatter.format("%02x", b);
		}
		String result = formatter.toString();
		formatter.close();
		return result;
	}

	public static String generateSHA(String name) {
		String SHA1= "";
		try {
			MessageDigest crypt = MessageDigest.getInstance("SHA-1");
			crypt.reset();
			crypt.update(name.getBytes(StandardCharsets.UTF_8));
			SHA1 = byteToHex(crypt.digest());
		} catch(NoSuchAlgorithmException e) {
			e.printStackTrace();
		}
		return SHA1;
	}
}
