import java.io.*;
import java.net.InetAddress;
import java.net.Socket;
import java.nio.charset.StandardCharsets;
import java.util.List;

public class Client {

    private final MetaParser metaParser = new MetaParser();

    private static int serverPort;

    private List<String> party;

    private String generateGetPieceMessage(int index_) { return "Get" + index_; }

    private void sendToAll(String message) {
        try {
            for (String i : party) {
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
            e.printStackTrace();
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

    public void startClient(boolean isLeech, List<String> party_, int serverPort_) {
        serverPort = serverPort_;
        party = party_;
        if (isLeech) {
            try {
                int count = 0;
                int partyIndex = 0;
                String path = "(Downloaded)";
                File downloadedFile = new File(path + metaParser.getFileName());
                FileOutputStream downloadedFileStream = new FileOutputStream(path + metaParser.getFileName());
                boolean result = downloadedFile.createNewFile();
                if (!result) {
                    log("file already exists");
                }
                //main loop for downloading pieces.
                //name format of pieces - [number of piece]fileName.
                //for instance - 3file.txt
                Socket currentSocket;
                PrintWriter writer;
                BufferedReader reader;
                int currentPort = Integer.parseInt(party.get(partyIndex));
                while (count < metaParser.getNumberOfPieces()) {
                    currentSocket = new Socket(metaParser.getCurrentServerAddress(), currentPort);
                    writer = new PrintWriter(currentSocket.getOutputStream());
                    InputStreamReader streamReader = new InputStreamReader(currentSocket.getInputStream());
                    reader = new BufferedReader(streamReader);
                    Handshake handshake = new Handshake();
                    String SHA = SHA1.generateSHA(count + metaParser.getFileName());
                    String shake = handshake.generateHandshake(InetAddress.getLocalHost().getHostAddress(), SHA);
                    writer.println(shake);
                    writer.flush();
                    log("Send > " + shake);
                    String answer = reader.readLine();
                    log("Received < " + answer);
                    if (handshake.checkHandshake(answer, SHA)) {
                        writer.println(generateGetPieceMessage(count));
                        writer.flush();
                        log("Send > " + generateGetPieceMessage(count));
                        byte[] piece = reader.readLine().getBytes(StandardCharsets.UTF_8);
                        Server.getDownloadedPieces().add(piece);
                        sendToAll("Have" + count);
                        downloadedFileStream.write(piece);
                        savePiece(piece, count);
                        count++;
                        log("Downloaded - " + (double) count / metaParser.getNumberOfPieces() * 100 + "%");
                    } else {
                        partyIndex++;
                        if (partyIndex < party.size()) {
                            currentPort = Integer.parseInt(party.get(partyIndex));
                        } else {
                            partyIndex = 0;
                        }
                    }
                    //reader.close();
                }
                if (downloadedFile.length() == metaParser.getFileSize()) {
                    log("Downloading has been ended successful.");
                }
            } catch (IOException e) {
                log("Error " + e.getMessage());
            }
        }
    }

    private static void log(String message) {
        System.out.println("[" + Thread.currentThread().getName() + serverPort +  "] " + message);
    }

}