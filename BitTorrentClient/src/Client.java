import java.io.*;
import java.net.InetAddress;
import java.net.Socket;
import java.nio.charset.StandardCharsets;

public class Client extends TorrentClient {

    private String currentServerAddress;

    private int numberOfPieces;

    private int fileSize;

    private String fileName;

    private String SHA;

    private String meta;

    private void parseMeta(String meta) {
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

    private void saveMeta() {
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
                log("reading error");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        meta = String.copyValueOf(array);
    }

    private boolean checkHandshake(String handshake) {
        StringBuilder tmp = new StringBuilder();
        for (int i = 20; i < 60; i++) {
            tmp.append(handshake.charAt(i));
        }
        return tmp.toString().equals(SHA);
    }

    private String generateGetPieceMessage(int index_) { return "Get" + index_; }

    public void startClient() {
        if (isLeech) {
            try {
                saveMeta();
                parseMeta(meta);
                int count = 0;
                String path = "(Downloaded)";
                File downloadedFile = new File(path + fileName);
                FileOutputStream downloadedFileStream = new FileOutputStream(path + fileName);
                boolean result = downloadedFile.createNewFile();
                isLeech = true;
                if (!result) {
                    log("file already exists");
                }
                //main loop for downloading pieces.
                //name format of pieces - [number of piece]fileName.
                //for instance - 3file.txt
                while (count < numberOfPieces) {
                    Socket socket = new Socket(currentServerAddress, 4242);
                    PrintWriter writer = new PrintWriter(socket.getOutputStream());
                    InputStreamReader streamReader = new InputStreamReader(socket.getInputStream());
                    BufferedReader reader = new BufferedReader(streamReader);
                    Handshake handshake = new Handshake();
                    SHA = SHA1.generateSHA(count + fileName);
                    String handshake_ = handshake.generateHandshake(InetAddress.getLocalHost().getHostAddress(), SHA);
                    writer.println(handshake_);
                    writer.flush();
                    log("Send > " + handshake_);
                    String answer = reader.readLine();
                    log("Received < " + answer);
                    if (checkHandshake(answer)) {
                        writer.println(generateGetPieceMessage(count));
                        writer.flush();
                        log("Send > " + generateGetPieceMessage(count));
                        byte[] piece = reader.readLine().getBytes(StandardCharsets.UTF_8);
                        downloadedPieces.add(piece);
                        downloadedFileStream.write(piece);
                        count++;
                        log("Downloaded - " + (double) count / numberOfPieces * 100 + "%");
                    }
                    reader.close();
                }
                if (downloadedFile.length() == fileSize) {
                    log("Downloading has been ended successful.");
                    isLeech = false;
                }
            } catch (IOException e) {
                log("Error " + e.getMessage());
            }
        }
    }

    private static void log(String message) {
        System.out.println("[" + Thread.currentThread().getName() + "] " + message);
    }

}


