public class Message {

	static class Bitfield {
		public char[] bitField;

		public int bitFiledSize;
	}
	static class Request {
		public int requestIndex;

		public int requestBegin;

		public int requestLength;
	}

	static class Piece {
		public int pieceIndex;

		public int pieceBegin;

		public char[] piece;
	}


	public int messageLength;

	public char messageType;

	int have;

	public void initializeMessage() {

	}

}
