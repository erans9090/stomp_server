package bgu.spl.net.impl.echoClients;

import java.net.*;
import java.util.stream.Stream;

import bgu.spl.net.impl.stomp.StompEncoderDecoder;

import java.io.*;

public class EchoClientA {

    public static void main(String[] args) throws IOException {

        String msg1 = "CONNECT\naccept-version:1.2\nhost:stomp.cs.bgu.ac.il\nlogin:eran\npasscode:films\n\n";
        String msg2 = "SUBSCRIBE\ndestination:/germany_spain\nid:17\nreceipt:73\n\n";
        // String msg3 = "UNSUBSCRIBE\nid:17\nreceipt:73\n\n";
        String msg4 = "SEND\ndestination:/germany_spain\n\nHello World!\n\n";


        //BufferedReader and BufferedWriter automatically using UTF-8 encoding
        try (Socket sock = new Socket("localhost", Integer.valueOf("7777"));) {
            BufferedWriter out = new BufferedWriter(new OutputStreamWriter(sock.getOutputStream()));
            BufferedReader in = new BufferedReader(new InputStreamReader(sock.getInputStream()));
            String line = "";


            // ------------- 1 -------------

            System.out.println(">>> sending message 1 to server");
            out.write(msg1 + '\0');
            out.flush();

            System.out.println(">>> awaiting response");

            String msg = "";
            StompEncoderDecoder encdec = new StompEncoderDecoder();
            int read;
            while ((read = in.read()) >= 0) {
                msg = encdec.decodeNextByte((byte) read);
                if (msg != null) {
                    break;
                }
            }
            System.out.println(msg);
            
            
            // ------------- 2 -------------

            System.out.println(">>> sending message 2 to server");
            out.write(msg2 + '\0');
            out.flush();

            msg = "";
            in = new BufferedReader(new InputStreamReader(sock.getInputStream()));
            while ((read = in.read()) >= 0) {
                msg = encdec.decodeNextByte((byte) read);
                if (msg != null) {
                    break;
                }
            }
            if(msg.equals(""))
                System.out.println("the message was empty");
            System.out.println(msg);


            System.out.println(">>> sending message 2 AGAIN to server");
            out.write(msg2 + '\0');
            out.flush();

            msg = "";
            in = new BufferedReader(new InputStreamReader(sock.getInputStream()));
            while ((read = in.read()) >= 0) {
                msg = encdec.decodeNextByte((byte) read);
                if (msg != null) {
                    break;
                }
            }
            if(msg.equals(""))
                System.out.println("the message was empty");
            System.out.println(msg);


            // // ------------- 3 -------------
        
            // System.out.println(">>> sending message 3 to server");
            // out.write(msg3 + '\0');
            // out.flush();

            msg = "";
            in = new BufferedReader(new InputStreamReader(sock.getInputStream()));
            while ((read = in.read()) >= 0) {
                msg = encdec.decodeNextByte((byte) read);
                if (msg != null) {
                    break;
                }
            }
            System.out.println(msg);


        //     // ------------- 4 -------------

        //     System.out.println(">>> sending message 4 to server");
        //     out.write(msg4 + '\0');
        //     out.flush();

        //     msg = "";
        //     in = new BufferedReader(new InputStreamReader(sock.getInputStream()));
        //     while ((read = in.read()) >= 0) {
        //         msg = encdec.decodeNextByte((byte) read);
        //         if (msg != null) {
        //             break;
        //         }
        //     }
        //     System.out.println(msg);


        }
    }
}