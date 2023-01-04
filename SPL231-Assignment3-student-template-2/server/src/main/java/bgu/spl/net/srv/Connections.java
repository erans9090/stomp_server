package bgu.spl.net.srv;

import java.io.IOException;

public interface Connections<T> {

    /*
     * sends a message T to client represented by the given connectionId.
     */
    boolean send(int connectionId, T msg);

    /*
     * sends a message T to all the clients subscribed to the given channel.
     */
    void send(String channel, T msg);

    /*
     * Removes an active client connectionId from the map
     */
    void disconnect(int connectionId);

    Integer addConnection(ConnectionHandler<T> connectionHandler);


}
