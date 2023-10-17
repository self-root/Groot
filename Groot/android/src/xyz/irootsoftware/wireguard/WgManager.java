package xyz.irootsoftware.wireguard;

import com.wireguard.android.backend.GoBackend;
import com.wireguard.config.Peer;


public class WgManager{
    String name;
    private GoBackend backend;
    public WgManager(){
        this.name = "WIreguard";
    }

    String getName(){
        Peer.Builder peerBuilder = new Peer.Builder();
        return this.name;
    }

    public static WgManager create(){
        return new WgManager();
    }

    public static void pr(){
        System.out.println("Java from C++");
    }
}
