package bgu.spl.net.impl.stomp;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import bgu.spl.net.api.StompMessagingProtocol;
import bgu.spl.net.srv.ConnectionHandler;
import bgu.spl.net.srv.Connections;

public class StompProtocol<T> implements StompMessagingProtocol<T>{

    private boolean shouldTerminate = false;

    private List<Integer> connectionIds;


    public StompProtocol() {

        connectionIds = new ArrayList<Integer>();
     
    }
    // private int connectionId;

    @Override
    public void start(int connectionId, Connections<T> connections) {

        // check if client is already connected

        if (connectionIds.contains(connectionId)) {
            // send error message
            return;
        }

        // Integer id = connections.addConnection(new ConnectionHandler<StompProtocol>());



    }

    @Override
    public void process(T message) {

        // shouldTerminate = "bye".equals(message);
        // System.out.println("[" + LocalDateTime.now() + "]: " + message);

        // T ans;
        // return ans;

        /*
         * 1. parse message
         * 2. check if message is valid?
         *  2.1 if not valid, send error message
         * 
         * 3.if valid handle message according to the frame type:
         * 
         * a. CONNECT
         *  a.1 connect to the server
         *  a.2 make a connection handler for the client
         *  a.3 add the connection handler to the connections list
         *  a.4 send connected message
         * 
         * b. SEND
         *  b.1 check if the subscription subscribed to the topic
         *  b.2 if not, send error message
         *  b.3 if yes, send the message to all the subscribers
         *  b.4 if failed, send error message
         * 
         * c. SUBSCRIBE
         *  c.1 check if the topic exists
         *  c.2 if not, create a new topic
         *  c.3 add the client to the topic's subscribers list
         *  c.4 if failed, send error message
         * 
         * d. UNSUBSCRIBE
         *  d.1 delete the client from the topic's subscribers list
         * 
         * e. DISCONNECT
         *  e.1 disconnect the client
         *  e.2 send a receipt message
         *  e.3 terminate the connection
         * 
         * 
        */

        Map<String, Object> parsedMessage = StompParser.parseMessage((String)message);

                            if (parsedMessage == null) {
            // send error message
            return;
        }

        String frameType = (String)parsedMessage.get("frameType");

        if (frameType == null) {
            // send error message
            return;
        }

        switch (frameType) {
            case "CONNECT":
                // do something
                break;
            case "SEND":
                // do something
                break;
            case "SUBSCRIBE":
                // do something
                break;
            case "UNSUBSCRIBE":
                // do something
                break;
            case "DISCONNECT":
                // do something
                break;
            default:
                // send error message
                break;
        }             
        


    }

    @Override
    public boolean shouldTerminate() {
        return false;
    }
   
    
    
}
