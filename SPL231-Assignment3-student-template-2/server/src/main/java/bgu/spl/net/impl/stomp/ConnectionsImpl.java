package bgu.spl.net.impl.stomp;

import java.util.ArrayList;
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

    protected List connectionsList;

    int connectionIdMaker = 0;

    public ConnectionsImpl() {
    
        connectionsList = new ArrayList<ConnectionHandler>();

    }

    @Override
    public boolean send(int connectionId, T msg) {
        // TODO Auto-generated method stub
        return false;
    }

    @Override
    public void send(String channel, T msg) {
        // TODO Auto-generated method stub
        
    }

    @Override
    public void disconnect(int connectionId) {
        // TODO Auto-generated method stub
        
    }

    @Override
    public Integer addConnection(ConnectionHandler<T> connectionHandler) {
        connectionsList.add(connectionHandler);
        return connectionIdMaker++;
    }

    
}
