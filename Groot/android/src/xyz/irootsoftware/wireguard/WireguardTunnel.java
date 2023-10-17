package xyz.irootsoftware.wireguard;


import com.wireguard.android.backend.Tunnel;

public class WireguardTunnel implements Tunnel {
    @Override
    public String getName(){
        return "AnnoyingTunnel";
    }

    @Override
    public void onStateChange(State newState){

    }
}
