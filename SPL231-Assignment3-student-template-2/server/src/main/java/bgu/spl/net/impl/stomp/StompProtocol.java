package bgu.spl.net.impl.stomp;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import bgu.spl.net.api.StompMessagingProtocol;
import bgu.spl.net.srv.ConnectionHandler;
import bgu.spl.net.srv.Connections;
import bgu.spl.net.srv.Reactor;

public class StompProtocol<T> implements StompMessagingProtocol<T>{

    private boolean shouldTerminate = false;
    private Connections connections;
    private boolean isConnected;
    private int connectionId;

    // private List<Integer> connectionIds;


    public StompProtocol() {

        // connectionIds = new ArrayList<Integer>();
        this.connections = Reactor.connections;
        isConnected = false;

     
    }

    @Override
    public void start(int connectionId, Connections<T> connections) {
    }

    @Override
    public void process(String message) {

        String response = "";

        // check if message is valid
        if (!StompParser.isValidMessage(message)){
            // send error message
            return;
        }

        //parse message
        Map<String, Object> parsedMessage = StompParser.parseMessage(message);

        if (parsedMessage.get("command").equals("DISCONNECT")){
            terminate();
            return;
        }

        // handle message according to the frame type
        switch ((String)parsedMessage.get("command")) {
            case "CONNECT":

                if(isConnected){
                    // send error message
                    response = "ERROR\nmessage:The client is already logged in, log out before trying again\n\n" + '\0';
                    break;
                }

                // verify the user name and password
                boolean verify = connections.verify((String)parsedMessage.get("login"), (String)parsedMessage.get("passcode"), connectionId);

                if (verify == false){
                    // send error message
                    response = "ERROR\nmessage:Wrong username or password\n\n" + '\0';
                    break;
                }
                else{
                    // send connected message
                    response = "CONNECTED\nversion:1.2\n\n" + '\0';
                    isConnected = true;
                }


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
                connections.send((String)parsedMessage.get("destination"), (String)parsedMessage.get("body"),connectionId);

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
                response = "ERROR\nmessage:Wrong command\n\n" + '\0';
                // send error message
                break;
        }

        if(response != "")
            connections.send(connectionId, response);

            
        }



    private void terminate() {
        // TODO Auto-generated method stub
    }

    @Override
    public boolean shouldTerminate() {
        return false;
    }
   
    
    
}
