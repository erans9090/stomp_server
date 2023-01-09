package bgu.spl.net.impl.echoClients;

import java.net.*;
import java.nio.ByteBuffer;
import java.util.stream.Stream;

import bgu.spl.net.impl.stomp.StompEncoderDecoder;

import java.io.*;

public class EchoClientB {

    static int i = 0;
    public static Socket sock;
    public static BufferedWriter out;
    public static BufferedReader in;

    public static void sendMessage(String msg){

        try {
            String line = "";

            System.out.println(">>> sending message " + i ++  +" to server");
            out.write(msg + '\0');
            out.flush();

            System.out.println(">>> awaiting response");

            String response = "";
            StompEncoderDecoder encdec = new StompEncoderDecoder();
            int read;
            while ((read = in.read()) >= 0) {
                response = encdec.decodeNextByte((byte) read);
                if (response != null) {
                    break;
                }
            }
            System.out.println(response);
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    public static void sendLoginMessage(String userName, String password){
        String msg = "CONNECT\naccept-version:1.2\nhost:stomp.cs.bgu.ac.il\nlogin:" + userName + "\npasscode:" + password + "\n\n";
        sendMessage(msg);

    }

    public static void sendMessageSubscribe (String destination, String id, String receipt){
        String msg = "SUBSCRIBE\ndestination:/" + destination + "\nid:" + id + "\nreceipt:" + receipt + "\n\n";
        sendMessage(msg);
    }

    public static void sendMessageUnsubscribe(String id, String receipt){
        String msg = "UNSUBSCRIBE\nid:" + id + "\nreceipt:" + receipt + "\n\n";
        sendMessage(msg);
    } 

    public static void sendMessageSEND(String destination, String body) {
        String msg = "SEND\ndestination:/" + destination + "\n\n" + body + "\n\n";
        sendMessage(msg);
        
    }

    public static void main(String[] args) throws IOException {

        try{
            sock = new Socket("localhost", Integer.valueOf("7777"));
            out = new BufferedWriter(new OutputStreamWriter(sock.getOutputStream()));
            in = new BufferedReader(new InputStreamReader(sock.getInputStream()));
        

        sendLoginMessage("Amir","films");
        sendMessageSubscribe ("germany_spain","17","73");
        // sendMessageUnsubscribe("17","73");
        sendMessageSEND("germany_spain","Hello World!");
        sendMessageSubscribe("Argentina_Brazil","18","74");
        sendMessageSEND("Argentina_Brazil","Game Started!!");
        sendMessageUnsubscribe("18","74");
        sendMessageSubscribe("Israel_Egypt","19","75");
        sendMessageSubscribe("france_italy","20","76");
        sendMessageSEND("france_italy","Great Game!");

        } catch (IOException e) {
            e.printStackTrace();

        }
    }

}