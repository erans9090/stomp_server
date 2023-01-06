package bgu.spl.net.impl.stomp;


import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.SocketChannel;
import java.util.List;

import bgu.spl.net.api.MessageEncoderDecoder;
import bgu.spl.net.api.MessagingProtocol;
import bgu.spl.net.srv.Connections;
import bgu.spl.net.srv.NonBlockingConnectionHandler;
import bgu.spl.net.srv.Reactor;
import bgu.spl.net.srv.Reactor;

public class StompConnectionHandler<T> extends NonBlockingConnectionHandler<T> {

    // protected String userName;   ?
    // protected String subscriptionId;   ?
    protected int connectionId;
    protected boolean isConnected;
    protected List<channel> channelsList;

    protected final StompProtocol<T> stompProtocol;

    public StompConnectionHandler(
            MessageEncoderDecoder<T> reader,
            StompProtocol<T> protocol,
            SocketChannel chan,
            Reactor reactor,
            int id) {
        super(reader, null, chan, reactor);
        this.stompProtocol = protocol;
        this.connectionId = id;
        this.isConnected = false;
        // is it bidirectional?
        this.channelsList = null;
    }

    // @Override
    // public void close() {
    //     // TODO Auto-generated method stub

    // }

    // @Override
    // public void send(T msg) {
    //     // TODO Auto-generated method stub

    // }

    @Override
    public Runnable continueRead() {
        ByteBuffer buf = super.leaseBuffer();

        boolean success = false;
        try {
            success = chan.read(buf) != -1;
        } catch (IOException ex) {
            ex.printStackTrace();
        }

        if (success) {
            buf.flip();
            return () -> {
                try {
                    while (buf.hasRemaining()) {
                        T nextMessage = encdec.decodeNextByte(buf.get());
                        if (nextMessage != null) 
                        {
                            stompProtocol.process((String)nextMessage);
                        }
                    }
                } finally {
                    releaseBuffer(buf);
                }
            };
        } else {
            releaseBuffer(buf);
            close();
            return null;
        }

    }
    

}
