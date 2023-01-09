package bgu.spl.net.impl.stomp;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class User {
    
    private String userName;
    private String password;
    private StompConnectionHandler<String> connectionHandler;
    private int connectionId;
    private HashMap<String,Integer> games;
    private boolean isConnected;

    public User(int connectionId, StompConnectionHandler<String> connectionHandler) {

        this("NONAME", "", connectionHandler, connectionId);
    }

    public User(String userName, String password, StompConnectionHandler<String> connectionHandler, int connectionId) {
        this.userName = userName;
        this.password = password;
        this.connectionHandler = connectionHandler;
        this.connectionId = connectionId;
        games = new HashMap<String,Integer>();
        isConnected = true;
    }
    
    public String getUserName() {
        return userName;
    }

    public void setUserName(String userName) {
        this.userName = userName;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public StompConnectionHandler<String> getConnectionHandler() {
        return connectionHandler;
    }

    public void setConnectionHandler(StompConnectionHandler<String> connectionHandler) {
        this.connectionHandler = connectionHandler;
    }

    public int getConnectionId() {
        return connectionId;
    }

    public void setConnectionId(int connectionId) {
        this.connectionId = connectionId;
    }

    public void addGame(String game, int subId) {
        games.put(game, subId);
    }

    public Map<String, Integer> getGames() {
        return games;
    }

    public void removeGame(String game) {
        games.remove(game);
    }

    public void removeGame(int subId) {
        for(String game : games.keySet()) {
            if(games.get(game) == subId) {
                games.remove(game);
                break;
            }
        }
    }

    public void removeAllGames() {
        games = new HashMap<String,Integer>();
    }

    public boolean isSubscribed(String game) {
        return games.containsKey(game);
    }

    public void send(String msg) {
        connectionHandler.send(msg);
    }

    public void disconnect() {
        this.connectionHandler = null;
        this.connectionId = -1;
    }

    public boolean isConnected() {
        return isConnected;
    }

    public void setConnected(boolean isConnected) {
        this.isConnected = isConnected;
    }

    public String getGame(int subId) {
        for (String game : games.keySet()) {
            if (games.get(game) == subId) {
                return game;
            }
        }
            
        return null;
    }

	public int getSubId(String game) {
        if(games.containsKey(game)) {
            return games.get(game);
        }
		return -1;
	}

}
