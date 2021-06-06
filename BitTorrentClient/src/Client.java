import java.io.*;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;
import java.nio.charset.StandardCharsets;
import java.util.List;

public class Client {

    private final MetaParser metaParser = new MetaParser();

    private int serverPort;

    private List<String> party;

    private String generateGetPieceMessage(int index_) { return "Get" + index_; }

    public boolean isLeech = false;

    private void sendToAll(String message) {
        int port = 0;
        try {
            for (String i : party) {
                port = Integer.parseInt(i);
                Socket socket_ = new Socket(metaParser.getCurrentServerAddress(), Integer.parseInt(i));
                PrintWriter writer_ = new PrintWriter(socket_.getOutputStream());
                InputStreamReader streamReader_ = new InputStreamReader(socket_.getInputStream());
                BufferedReader reader_ = new BufferedReader(streamReader_);
                writer_.println(message);
                writer_.flush();
                log("Send to " + Integer.parseInt(i) + " > " + message);
                log("Received < " + reader_.readLine());
                writer_.close();
            }
        } catch (IOException e) {
            log("Lost connection with " + port);
        }
    }

    private void savePiece(byte[] piece, int index) {
        String path = "pieces/" + index;
        File downloadedFile = new File(path + metaParser.getFileName());
        FileOutputStream downloadedFileStream;
        try {
            downloadedFileStream = new FileOutputStream(path + metaParser.getFileName());
            boolean result = downloadedFile.createNewFile();
            if (!result) {
                log("file already exists");
            }
            downloadedFileStream.write(piece);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void startClient(boolean isLeech_, List<String> party_, int serverPort_) {
        serverPort = serverPort_;
        party = party_;
        isLeech = isLeech_;
        if (isLeech) {
                int count = 0;
                int partyIndex = 0;
                String path = "(Downloaded)";
                File downloadedFile = new File(path + metaParser.getFileName());
                boolean result = false;
                FileOutputStream downloadedFileStream = null;
                try {
                    downloadedFileStream = new FileOutputStream(path + metaParser.getFileName());
                    result = downloadedFile.createNewFile();
                } catch (IOException e) {
                    e.printStackTrace();
                }
                if (!result) {
                    log("file already exists");
                }
                //main loop for downloading pieces.
                //name format of pieces - [number of piece]fileName.
                //for instance - 3file.txt
                Socket currentSocket;
                PrintWriter writer = null;
                BufferedReader reader;
                int currentPort = Integer.parseInt(party.get(partyIndex));
                Threadpool pool = new Threadpool(MetaParser.getNumberOfPieces());
                while (count < MetaParser.getNumberOfPieces()) {
                    try {
                        currentSocket = new Socket(metaParser.getCurrentServerAddress(), currentPort);
                    } catch (IOException e) {
                        partyIndex++;
                        if (partyIndex < party.size()) {
                            currentPort = Integer.parseInt(party.get(partyIndex));
                        } else {
                            partyIndex = 0;
                        }
                        try {
                            currentSocket = new Socket(metaParser.getCurrentServerAddress(), currentPort);
                        } catch (IOException k) {
                            k.printStackTrace();
                            return;
                        }
                    }
                    InputStreamReader streamReader = null;
                    try {
                        writer = new PrintWriter(currentSocket.getOutputStream());
                        streamReader = new InputStreamReader(currentSocket.getInputStream());
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    assert streamReader != null;
                    reader = new BufferedReader(streamReader);
                    Handshake handshake = new Handshake();
                    String SHA = SHA1.generateSHA(count + metaParser.getFileName());
                    String shake = null;
                    try {
                        shake = handshake.generateHandshake(InetAddress.getLocalHost().getHostAddress(), SHA);
                    } catch (UnknownHostException e) {
                        e.printStackTrace();
                    }
                    writer.println(shake);
                    writer.flush();
                    log("Send > " + shake);
                    String answer = null;
                    try {
                        answer = reader.readLine();
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                    log("Received < " + answer);
                    if (handshake.checkHandshake(answer, SHA)) {
                        writer.println(generateGetPieceMessage(count));
                        writer.flush();
                        log("Send > " + generateGetPieceMessage(count));
                        byte[] piece = null;
                        try {
                            piece = reader.readLine().getBytes(StandardCharsets.UTF_8);
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                        sendToAll("Have" + count);
                        final int count_ = count;
                        final byte[] piece_ = piece;
                        pool.addTask(() -> savePiece(piece_, count_));
                        try {
                            assert downloadedFileStream != null;
                            downloadedFileStream.write(piece);
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                        count++;
                        log("Downloaded - " + (double) count / MetaParser.getNumberOfPieces() * 100 + "%");
                        try {
                            Thread.sleep(4000);
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                    } else {
                        partyIndex = (partyIndex + 1) % party.size();
                        currentPort = Integer.parseInt(party.get(partyIndex));
                    }
                }
                if (downloadedFile.length() == metaParser.getFileSize()) {
                    log("Downloading has been ended successful.");
                    isLeech = false;
                }
        }
    }

    private void log(String message) {
        System.out.println("[" + Thread.currentThread().getName() + serverPort +  "] " + message);
    }
}