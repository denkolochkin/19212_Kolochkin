import java.io.*;
import java.net.InetAddress;
import java.net.Socket;
import java.nio.charset.StandardCharsets;

public class Client {

    private String currentServerAddress = "";

    private String fileName = "";

    private int numberOfPieces = 0;

    private int fileSize = 0;

    private void parseMeta(String meta) {
        int index = 0;
        while(meta.charAt(index) != '[') {
            currentServerAddress += meta.charAt(index);
            index++;
        }
        index++;
        while(meta.charAt(index) != ':') {
            fileName += meta.charAt(index);
            index++;
        }
        index += 2;
        String number = "";
        while (meta.charAt(index) != ':') {
            number += meta.charAt(index);
            index++;
        }
        index += 2;
        String size = "";
        while (meta.charAt(index) != ']') {
            size += meta.charAt(index);
            index++;
        }
        fileSize = Integer.parseInt(size);
        numberOfPieces = Integer.parseInt(number);
    }

    public void startClient() {
        try {
            Socket socket = new Socket("localhost", 4242);
            PrintWriter writer = new PrintWriter(socket.getOutputStream());

            writer.println("Get meta");
            writer.flush();
            log("Send > " + "Get meta");
            InputStreamReader streamReader = new InputStreamReader(socket.getInputStream());
            BufferedReader reader = new BufferedReader(streamReader);
            String meta = reader.readLine();
            log("Received < " + meta);
            parseMeta(meta);

            Handshake handshake = new Handshake();
            String handshake_ = handshake.generateHandshake(InetAddress.getLocalHost().getHostAddress());
            writer.println(handshake_);
            writer.flush();
            log("Send > " + handshake_);
            String answer = reader.readLine();
            log("Received < " + answer);

            if (answer.equals(handshake_)) {
                File file = new File("/Users/deniskolockin/IdeaProjects/ClientSeverExmaple/(Downloaded)" +
                        fileName);
                FileOutputStream fileOutputStream =
                        new FileOutputStream("/Users/deniskolockin/IdeaProjects/ClientSeverExmaple/(Downloaded)"
                                + fileName);
                file.createNewFile();
                //отправка сообщения для получения куска файла
                writer.println("File");
                writer.flush();
                log("Send > " + "File");
                byte[] piece;
                while((piece = reader.readLine().getBytes(StandardCharsets.UTF_8)) != null) {
                    fileOutputStream.write(piece);
                    fileOutputStream.write("\n".getBytes(StandardCharsets.UTF_8));
                }
            }
            reader.close();
        } catch (IOException e) {
            log("Error " + e.getMessage());
        }
    }

    private static void log(String message) {
        System.out.println("[" + Thread.currentThread().getName() + "] " + message);
    }

}


