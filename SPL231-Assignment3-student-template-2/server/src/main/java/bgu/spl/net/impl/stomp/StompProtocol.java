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
    private Connections connections;

    // private List<Integer> connectionIds;


    public StompProtocol(Connections connections) {
        

        // connectionIds = new ArrayList<Integer>();
        this.connections = connections;
     
    }
    // private int connectionId;

    @Override
    public void start(int connectionId, Connections<T> connections) {

        // check if client is already connected

        // Integer id = connections.addConnection(new ConnectionHandler<StompProtocol>());

        // TODO

    }

    @Override
    public void process(T message) {

        // check if message is valid
        if (!StompParser.isValidMessage((String)message)){
            // send error message
            return;
        }

        //parse message
        Map<String, Object> parsedMessage = StompParser.parseMessage((String)message);

        if (parsedMessage.get("command").equals("DISCONNECT")){
            terminate();
            return;
        }

        // handle message according to the frame type
        switch ((String)parsedMessage.get("command")) {
            case "CONNECT":
                // connect to the server
                // make a connection handler for the client
                // add the connection handler to the connections list
                // send connected message


                break;
            case "SEND":

                // check if the subscription subscribed to the channel
                // if not, send error message
                
                // make sure not send a message to yourself??
                // if yes, send the message to all the subscribers
                connections.send((String)parsedMessage.get("destination"), (String)parsedMessage.get("body"));

                break;
            case "SUBSCRIBE":

                // add the subscription to the channel (create the channel if not exists)
                // send subscribed message
                connections.addSubscription((String)parsedMessage.get("destination"), (Integer)parsedMessage.get("id"));

                break;
            case "UNSUBSCRIBE":

                // remove the subscription from all channels
                connections.unsubscribe((int)parsedMessage.get("id"));

                break;
            case "DISCONNECT":
                // remove the connection from the connections list
                // send disconnected message
                // terminate the connection
                connections.disconnect((int)parsedMessage.get("id"));

                break;
            default:
                // send error message
                break;
        }




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
            // send error message
            
        }

        // String frameType = (String)parsedMessage.get("frameType");

        // if (frameType == null) {
        //     // send error message
        //     return;
        // }

        // switch (frameType) {
        //     case "CONNECT":
        //         // do something
        //         break;
        //     case "SEND":
        //         // do something
        //         break;
        //     case "SUBSCRIBE":
        //         // do something
        //         break;
        //     case "UNSUBSCRIBE":
        //         // do something
        //         break;
        //     case "DISCONNECT":
        //         // do something
        //         break;
        //     default:
        //         // send error message
        //         break;
        // }             
        

    private void terminate() {
        // TODO Auto-generated method stub
    }

    @Override
    public boolean shouldTerminate() {
        return false;
    }
   
    
    
}
