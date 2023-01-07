package bgu.spl.net.srv;

import java.io.IOException;

import bgu.spl.net.impl.stomp.StompConnectionHandler;

public interface Connections<T> {

    /*
     * sends a message T to client represented by the given connectionId.
     */
    boolean send(int connectionId, T msg);

    /*
     * sends a message T to all the clients subscribed to the given channel.
     */
    void send(String channel, T msg, int connectionId);

    /**
     * 
     * @param connectionHandler
     * @return the connectionId of the new connection
     * 
     * add a new connection to the map
     * 
     * verify user name and password
     * send error message if the password is incorrect
     * 
     */
    Integer connect(ConnectionHandler<T> connectionHandler);

    /*
     * Removes an active client connectionId from the map
     */
    void disconnect(int connectionId);


    /**
     * 
     * @param channel
     * @param connectionId
     * 
     * create a new channel if the channel does not exist
     * 
     * add a subscription to a channel 
     * do nothing if the subscription is already subscribed to the channel
     * 
     */
    void addSubscription(String channel, Integer connectionId);

    /**
     * 
     * @param channel
     * @param connectionId
     * 
     * remove a subscription from all channels
     * 
     */
    void unsubscribe(int connectionId);

    String verifyConnection(String string, String string2, int id);


    /**
     * 
     * @param connectionId
     * @param connectionHandler
     */
    void addConnection(int connectionId, StompConnectionHandler<String> connectionHandler);


}
