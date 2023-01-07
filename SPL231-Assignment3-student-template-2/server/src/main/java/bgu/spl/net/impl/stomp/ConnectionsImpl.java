package bgu.spl.net.impl.stomp;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;

import bgu.spl.net.srv.ConnectionHandler;
import bgu.spl.net.srv.Connections;

/*
 * This class should map a unique ID for each active client connected
 * to the server. The implementation of Connections is part of the server
 * pattern and not part of the protocol. It has 3 functions that you must
 * implement (You may add more if needed)
 */
public class ConnectionsImpl<T> implements Connections<T> {

    protected HashMap<Integer,StompConnectionHandler<String>> usersIdToCH;
    protected HashMap<String,Integer> usersNameToID;
    protected HashMap<String, LinkedList<String>> channelToPosts;
    protected HashMap<String, LinkedList<Integer>> channelToUsersId;
    protected HashMap<String,String> usersToPassword;

    // private HashMap<String,String> usersToSubscriptionId;?? is neccessary?


    int connectionIdMaker = 0;

    public ConnectionsImpl() {
        usersIdToCH = new HashMap<Integer,StompConnectionHandler<String>>();
        usersNameToID = new HashMap<String,Integer>();
        channelToPosts = new HashMap<String, LinkedList<String>>();
        channelToUsersId = new HashMap<String, LinkedList<Integer>>();
        usersToPassword = new HashMap<String,String>();
    }

    @Override
    public boolean send(int connectionId, T msg) {

        for (Integer id : usersIdToCH.keySet()) {
            if (id == connectionId) {
                usersIdToCH.get(id).send((String)msg);
                return true;
            }
        }          

        return false;
    }

    @Override
    public void send(String channel, T msg, int connectionId) {


        // if subscription is not subscribed to the channel send Error message
        if (!channelToUsersId.get(channel).contains(connectionId)) {
            String error = "ERROR\nmessage: You are not subscribed to this channel\n\n\0";
            send(connectionId, (T)error);
            return;
        }

        if (channelToUsersId.containsKey(channel)) {
            for (Integer id : channelToUsersId.get(channel)) {
                
                // make sure not send a message to yourself??
                
                usersIdToCH.get(id).send((String)msg);
            }
        }
    }

    @Override
    public void disconnect(int connectionId) {

        unsubscribe(connectionId);
        usersIdToCH.remove(connectionId);
        
        // send receipt to client
        String receipt = "RECEIPT\nreceipt-id:" + connectionId + "\n\n\0";
        send(connectionId, (T)receipt);

    }

    // @Override
    // public String connect(String userName, String password) {

    //     // verify user name and password
    //     // if user doesn't exist make a new user with the given password
    //     if(usersToPassword.containsKey(userName)) {
    //         if (!usersToPassword.get(userName).equals(password)) {
    //             // send error message if the password is incorrect
    //             String error = "ERROR\nmessage:Wrong password\n\n\0";\
    //             return error;
    //         }
    //     } else {
    //         usersToPassword.put(userName, password);
    //     }


    //     UsersIdToCH.put(connectionIdMaker, (StompConnectionHandler<String>) connectionHandler);
    //     return (String)(connectionIdMaker++);
    // }

    public void addChannel(String channel) {
        if (!channelToPosts.containsKey(channel)) {
            channelToPosts.put(channel, new LinkedList<String>());
        }
        if (!channelToUsersId.containsKey(channel)) {
            channelToUsersId.put(channel, new LinkedList<Integer>());
        }
    }

    public void addSubscription(String channel, Integer connectionId) {
        
        // if channel doesn't exist create it
        if (!channelToPosts.containsKey(channel)) {
            channelToPosts.put(channel, new LinkedList<String>());
            channelToUsersId.put(channel, new LinkedList<Integer>());
        }

        // if user is'nt subscribed to channel add him
        if (!channelToUsersId.get(channel).contains(connectionId)) {
            channelToUsersId.get(channel).add(connectionId);
            // send SUBSCRIBED message to the client
            String subscribed = "SUBSCRIBED\nsubscription:" + connectionId + "\ndestination:" + channel + "\n\n\0";
            send(connectionId, (T)subscribed);
        }

    }

    public void unsubscribe(int connectionId) {

        for (String channel : channelToUsersId.keySet()) {
            if (channelToUsersId.get(channel).contains(connectionId)) {
                channelToUsersId.get(channel).remove(connectionId);
            }
        }

    }

    private void isConnected(int connectionId) { // throws Exception?
        if (!usersIdToCH.containsKey(connectionId)) {

            // send ERROR message to the client
            String error = "ERROR\nmessage:User is not connected\n\n\0";
            send(connectionId, (T)error);

            // throw new Exception("User is not connected");?
        }
    }

    // ???
    @Override
    public Integer connect(ConnectionHandler<T> connectionHandler) {
        // TODO Auto-generated method stub
        return null;
    }

    public String verifyConnection(String userName, String password, int id) {
        if(usersToPassword.containsKey(userName)) 
        {
            //wrong password:
            if (!usersToPassword.get(userName).equals(password)) 
                return "ERROR\nmessage:Wrong password\n\n" + '\0';
            else { //case password is corrrect:
                if(usersNameToID.get(userName).equals(id))
                    return ("CONNECTED\nversion:1.2\n\n" + "\0");
                else //the user already logged in from a different computer:
                    return "ERROR\nmessage:User already logged in\n\n" + '\0';
            }
        } else { //make a new user:
            usersToPassword.put(userName, password);
            usersNameToID.put(userName, id);
            return "CONNECTED\nversion:1.2\n\n" + '\0';
        }
    }

    @Override
    public void addConnection(int connectionId, StompConnectionHandler<String> connectionHandler) {
        usersIdToCH.put(connectionId, connectionHandler);
    }



    
}
