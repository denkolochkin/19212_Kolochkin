
public class Handshake {
	public String generateHandshake(String peerId) {
		String prot = "19BitTorrentProtocol";
		String sha1 = "SHA1";
		String reserved = "        ";
		return prot + sha1 + reserved + peerId;
	}
}
