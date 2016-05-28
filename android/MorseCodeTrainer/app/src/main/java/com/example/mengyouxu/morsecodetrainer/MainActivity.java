package com.example.mengyouxu.morsecodetrainer;

import android.app.Activity;
import android.content.SharedPreferences;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;

import com.google.android.gms.appindexing.Action;
import com.google.android.gms.appindexing.AppIndex;
import com.google.android.gms.common.api.GoogleApiClient;

import java.util.Vector;

public class MainActivity extends Activity {
    String TAG = "AudioTrackPlayer";
    SharedPreferences settings = null;

    /**
     * ATTENTION: This was auto-generated to implement the App Indexing API.
     * See https://g.co/AppIndexing/AndroidStudio for more information.
     */
    private GoogleApiClient client;
    MorseCodePlayer player = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        settings = getPreferences(Activity.MODE_PRIVATE);

        int value = settings.getInt("age", 0);
        Log.d(TAG, "Activity age: " + value);
        value++;
        SharedPreferences.Editor editor = settings.edit();
        editor.putInt("age", value);
        editor.commit();

        // ATTENTION: This was auto-generated to implement the App Indexing API.
        // See https://g.co/AppIndexing/AndroidStudio for more information.
        client = new GoogleApiClient.Builder(this).addApi(AppIndex.API).build();

        player = new MorseCodePlayer();
        Log.d(TAG, "START PLAY");
        try {
            player.playStringAsync("hello world");
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        Log.d(TAG, "END PLAY");
    }

    @Override
    public void onStart() {
        Log.d(TAG, "onStop");
        super.onStart();

        // ATTENTION: This was auto-generated to implement the App Indexing API.
        // See https://g.co/AppIndexing/AndroidStudio for more information.
        client.connect();
        Action viewAction = Action.newAction(
                Action.TYPE_VIEW, // TODO: choose an action type.
                "Main Page", // TODO: Define a title for the content shown.
                // TODO: If you have web page content that matches this app activity's content,
                // make sure this auto-generated web page URL is correct.
                // Otherwise, set the URL to null.
                Uri.parse("http://host/path"),
                // TODO: Make sure this auto-generated app URL is correct.
                Uri.parse("android-app://com.example.mengyouxu.morsecodetrainer/http/host/path")
        );
        AppIndex.AppIndexApi.start(client, viewAction);
    }

    @Override
    public void onStop() {
        Log.d(TAG, "onStop");
        super.onStop();
        if(player != null) {
            try {
                player.stopPlay();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        // ATTENTION: This was auto-generated to implement the App Indexing API.
        // See https://g.co/AppIndexing/AndroidStudio for more information.
        Action viewAction = Action.newAction(
                Action.TYPE_VIEW, // TODO: choose an action type.
                "Main Page", // TODO: Define a title for the content shown.
                // TODO: If you have web page content that matches this app activity's content,
                // make sure this auto-generated web page URL is correct.
                // Otherwise, set the URL to null.
                Uri.parse("http://host/path"),
                // TODO: Make sure this auto-generated app URL is correct.
                Uri.parse("android-app://com.example.mengyouxu.morsecodetrainer/http/host/path")
        );
        AppIndex.AppIndexApi.end(client, viewAction);
        client.disconnect();
    }
    @Override
    public void onPause(){
        Log.d(TAG, "onPause");
        super.onPause();
        if(player != null) {
            try {
                player.stopPlay();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

}
