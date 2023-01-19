package bgu.spl.net.impl.stomp;

import bgu.spl.net.srv.Server;

public class StompServer {

    public static void main(String[] args) {

        if (args.length != 2) {
            System.out.println("missing argument: TPC or reactor");
            return;
        }

        if (args[1].equals("tpc")){
        Server.threadPerClient(
                7777, //port
                () -> new StompProtocol<String>(), //protocol factory
                StompEncoderDecoder::new //message encoder decoder factory
        ).serve();
        }
        else if (args[1].equals("reactor")){
            Server.reactor(
                Runtime.getRuntime().availableProcessors(),
                7777, //port
                () ->  new StompProtocol<String>(), //protocol factory
                StompEncoderDecoder::new //message encoder decoder factory
        ).serve();
        }
        else{
            System.out.println("invalid argument: TPC or reactor");
            return;
        }

        


    }
}
