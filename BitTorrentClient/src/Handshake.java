public class Handshake {

	public boolean checkHandshake(String handshake, String SHA) {
		StringBuilder tmp = new StringBuilder();
		for (int i = 20; i < 60; i++) {
			tmp.append(handshake.charAt(i));
		}
		return tmp.toString().equals(SHA);
	}

	public String generateHandshake(String peerId, String SHA) {
		return "19BitTorrentProtocol" + SHA + peerId;
	}
}
