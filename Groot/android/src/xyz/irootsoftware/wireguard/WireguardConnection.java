package xyz.irootsoftware.wireguard;

import static com.wireguard.android.backend.Tunnel.State.DOWN;
import static com.wireguard.android.backend.Tunnel.State.UP;
import com.wireguard.android.backend.Tunnel;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.AsyncTask;

import android.util.Log;

import com.wireguard.android.backend.GoBackend;
import com.wireguard.config.Interface;
import com.wireguard.config.ParseException;
import com.wireguard.config.Peer;

import org.json.JSONException;

import java.net.UnknownHostException;

public class WireguardConnection {
    private WireguardTunnel tunnel;
    private GoBackend backend;
    private Peer.Builder peerBuilder = new Peer.Builder();
    private Interface.Builder interfaceBuilder = new Interface.Builder();
    Context context;
    Intent intentPrepare;
    private WireguardCientConfig clientConfig;
    public WireguardConnection(Context context){
        this.context = context;
        backend = new GoBackend(context);
        tunnel = new WireguardTunnel();
    }

    public long getReceivedTraffic()
    {
        return backend.getStatistics(tunnel).totalRx();
    }

    public long getTransmittedTraffic(){
        return backend.getStatistics(tunnel).totalTx();
    }

    public void disconnect() throws Exception {
        backend.setState(this.tunnel, DOWN, this.clientConfig.buildConfig());
    }
    public void startConnection() throws Exception {
        this.connect(this.clientConfig);
    }
    /**
     *
     * @param config a string in jsonFormat that contain the wireguard configuration
     */
    public void setConfig(String config) throws UnknownHostException, JSONException, ParseException {
        this.clientConfig = new WireguardCientConfig();
        this.clientConfig.configFromJsonString(config);
        System.out.println(config);
    }
    public void connect(WireguardCientConfig config) throws Exception{
        this.intentPrepare = GoBackend.VpnService.prepare(this.context);
        if (this.intentPrepare != null) {
            ((Activity) context).startActivityForResult(intentPrepare, 0);
        }
        else {
            AsyncTask.execute(new Runnable() {
                @Override
                public void run() {
                    try {
                        backend.setState(tunnel, UP, config.buildConfig());
                    } catch (Exception e) {
                        Log.println(Log.ERROR, "Err", "Connection Error");
                        e.printStackTrace();
                    }
                }
            });
        }

    }


    public int getTunSTate(){
        Tunnel.State state = backend.getState(tunnel);
        if (state == UP)
        {
            return 1;
        }
        else if (state == DOWN)
        {
            return 0;
        }

        else {return -1;}
    }
    /*public static int getTunnelState(){
        return getTunSTate();
    }*/
}
