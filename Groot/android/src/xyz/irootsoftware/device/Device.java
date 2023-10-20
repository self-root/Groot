package xyz.irootsoftware.device;

import android.os.Build;
import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.ApplicationInfo;
import android.os.Bundle;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.List;

public class Device {
    public static String manufacturer(){
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.DONUT) {
            return Build.MANUFACTURER;
        }
        return "";
    }

    public static String model(){
        return Build.MODEL;
    }

    public static  String getInstalledApps(Context context) throws JSONException {
        List<PackageInfo> packages = context.getPackageManager().getInstalledPackages(PackageManager.GET_META_DATA);
        JSONArray apps = new JSONArray();

        for (int i = 0; i < packages.size(); i++)
        {

            PackageInfo packageInfo = packages.get(i);
            if ((packageInfo.applicationInfo.flags & ApplicationInfo.FLAG_SYSTEM) == 0)
            {
                String packageName = packageInfo.packageName;
                String appName = packageInfo.applicationInfo.loadLabel(context.getPackageManager()).toString();
                JSONObject in = new JSONObject();
                in.put("packageName", packageName);
                in.put("appName", appName);
                apps.put(in);
            }


        }
        return  apps.toString();
    }
}
