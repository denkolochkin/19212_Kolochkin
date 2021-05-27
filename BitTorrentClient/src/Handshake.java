public class Handshake {
	public String generateHandshake(String peerId, String SHA) {
		return "19BitTorrentProtocol" + SHA + peerId;
	}
}
