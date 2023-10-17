package xyz.irootsoftware.wireguard;

import com.wireguard.config.BadConfigException;
import com.wireguard.config.Config;
import com.wireguard.config.InetAddresses;
import com.wireguard.config.InetEndpoint;
import com.wireguard.config.InetNetwork;
import com.wireguard.config.Interface;
import com.wireguard.config.ParseException;
import com.wireguard.config.Peer;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.net.InetAddress;
import java.net.UnknownHostException;
import java.util.ArrayList;

public class WireguardCientConfig {

    private String publicKey;
    private String presharedKey;
    private ArrayList<InetNetwork> allowedIPs;
    private String endpoint;
    private int persistentKeepAlive;
    private ArrayList<InetNetwork> address;
    private ArrayList<InetAddress> dnsServers;
    private String privateKey;
    private ArrayList<String> excluded;

    private Peer.Builder peerBuilder = new Peer.Builder();
    private Interface.Builder interfaceBuilder = new Interface.Builder();

    public ArrayList<InetNetwork> getAddress() {
        return address;
    }

    public void setAddress(ArrayList<InetNetwork> address) {
        this.address = address;
    }

    public ArrayList<InetAddress> getDnsServers() {
        return dnsServers;
    }

    public void setDnsServers(ArrayList<InetAddress> dnsServers) {
        this.dnsServers = dnsServers;
    }

    public String getPrivateKey() {
        return privateKey;
    }

    public void setPrivateKey(String privateKey) {
        this.privateKey = privateKey;
    }

    public ArrayList<InetNetwork> getAllowedIPs() {
        return allowedIPs;
    }

    public void setAllowedIPs(ArrayList<InetNetwork> allowedIPs) {
        this.allowedIPs = allowedIPs;
    }

    public String getEndpoint() {
        return endpoint;
    }

    public void setEndpoint(String endpoint) {
        this.endpoint = endpoint;
    }

    public int getPersistentKeepAlive() {
        return persistentKeepAlive;
    }

    public void setPersistentKeepAlive(int persistentKeepAlive) {
        this.persistentKeepAlive = persistentKeepAlive;
    }


    public String getPublicKey() {
        return publicKey;
    }

    public void setPublicKey(String publicKey) {
        this.publicKey = publicKey;
    }

    public Config buildConfig() throws BadConfigException, ParseException {
        Config.Builder cfg = new Config.Builder();
        peerBuilder.parsePublicKey(this.publicKey)
                .parsePreSharedKey(this.presharedKey)
                .addAllowedIps(this.allowedIPs)
                .setEndpoint(InetEndpoint.parse(this.endpoint));
        cfg.addPeer(peerBuilder.build());
        ArrayList<String> excluded = new ArrayList<String>();
        excluded.add("com.tencent.mm");
        excluded.add("com.eg.android.AlipayGphone");
        excluded.add("com.taobao.taobao");

        interfaceBuilder.addAddresses(this.address)
                .addDnsServers(this.dnsServers)
                .parsePrivateKey(this.privateKey)
                .excludeApplications(excluded);
        cfg.setInterface(interfaceBuilder.build());
        return cfg.build();
    }
    public String getPresharedKey() {
        return presharedKey;
    }

    public void setPresharedKey(String presharedKey) {
        this.presharedKey = presharedKey;
    }

    public void configFromJsonString(String cfg) throws JSONException, ParseException, UnknownHostException {
        JSONObject root = new JSONObject(cfg);
        this.setPublicKey(root.get("PublicKey").toString());
        this.setPresharedKey(root.getString("PresharedKey"));
        ArrayList<InetNetwork> allowedIps = new ArrayList<>();
        JSONArray allowedIpArr = root.getJSONArray("AllowedIPs");
        for (int i = 0; i < allowedIpArr.length(); i++) {
            allowedIps.add(InetNetwork.parse(allowedIpArr.getString(i)));
        }
        this.setAllowedIPs(allowedIps);
        this.setEndpoint(root.getString("Endpoint"));
        this.setPersistentKeepAlive(root.getInt("PersistentKeepalive"));

        ArrayList<InetNetwork> addresses = new ArrayList<>();
        JSONArray addresseArray = root.getJSONArray("Address");
        for (int i = 0; i < addresseArray.length(); i++){
            addresses.add(InetNetwork.parse(addresseArray.getString(i)));
        }
        this.setAddress(addresses);

        ArrayList<InetAddress> dnss = new ArrayList<>();
        JSONArray dnsArr = root.getJSONArray("DNS");
        for (int i = 0; i < dnsArr.length(); i++) {
            dnss.add(InetAddress.getByName(dnsArr.getString(i)));
        }

        this.setDnsServers(dnss);
        this.setPrivateKey(root.getString("PrivateKey"));
    }



}
