package bgu.spl.net.impl.stomp;

import java.nio.channels.SocketChannel;
import java.util.List;

import bgu.spl.net.api.MessageEncoderDecoder;
import bgu.spl.net.api.MessagingProtocol;
import bgu.spl.net.srv.NonBlockingConnectionHandler;
import bgu.spl.net.srv.Reactor;

public class StompConnectionHandler<T> extends NonBlockingConnectionHandler<T> {

    // protected String userName;   ?
    // protected String subscriptionId;   ?
    protected Integer connectionId;
    protected List<channel> channelsList;


    public StompConnectionHandler(
            MessageEncoderDecoder<T> reader,
            MessagingProtocol<T> protocol,
            SocketChannel chan,
            Reactor reactor) {
        super(reader, protocol, chan, reactor);
    }

    // @Override
    // public void close() {
    //     // TODO Auto-generated method stub

    // }

    // @Override
    // public void send(T msg) {
    //     // TODO Auto-generated method stub

    // }
    

}
