package com.example.mengyouxu.morsecodetrainer;
import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioTrack;
import android.util.Log;
import java.util.Vector;

/**
 * Created by mengyouxu on 2016/5/28.
 */
public class MorseCodePlayer extends Thread{
    private AudioTrack track = null;
    private String mMessage = null;
    private String TAG = "MorseCodePlayer";
    private long morse_time_unit = 150; /* millisecond */
    private Vector<char[]> morse_code_list = null;
    private boolean playContinue = true;

    private char[] morse_code_0 = {1, 1, 1, 1, 1};
    private char[] morse_code_1 = {0, 1, 1, 1, 1};
    private char[] morse_code_2 = {0, 0, 1, 1, 1};
    private char[] morse_code_3 = {0, 0, 0, 1, 1};
    private char[] morse_code_4 = {0, 0, 0, 0, 1};
    private char[] morse_code_5 = {0, 0, 0, 0, 0};
    private char[] morse_code_6 = {1, 0, 0, 0, 0};
    private char[] morse_code_7 = {1, 1, 0, 0, 0};
    private char[] morse_code_8 = {1, 1, 1, 0, 0};
    private char[] morse_code_9 = {1, 1, 1, 1, 0};

    private char[] morse_code_a = {0, 1};
    private char[] morse_code_b = {1, 0, 0, 0};
    private char[] morse_code_c = {1, 0, 1, 0};
    private char[] morse_code_d = {1, 0, 0};
    private char[] morse_code_e = {0};
    private char[] morse_code_f = {0, 0, 1, 0};
    private char[] morse_code_g = {1, 1, 0};
    private char[] morse_code_h = {0, 0, 0, 0};
    private char[] morse_code_i = {0, 0};
    private char[] morse_code_j = {0, 1, 1, 1};
    private char[] morse_code_k = {1, 0, 1};
    private char[] morse_code_l = {0, 1, 0, 0};
    private char[] morse_code_m = {1, 1};
    private char[] morse_code_n = {1, 0};
    private char[] morse_code_o = {1, 1, 1}; // o: - - -
    private char[] morse_code_p = {0, 1, 1, 0};
    private char[] morse_code_q = {1, 1, 0, 1};
    private char[] morse_code_r = {0, 1, 0};
    private char[] morse_code_s = {0, 0, 0}; // s: . . .
    private char[] morse_code_t = {1};
    private char[] morse_code_u = {0, 0, 1};
    private char[] morse_code_v = {0, 0, 0, 1};
    private char[] morse_code_w = {0, 1, 1};
    private char[] morse_code_x = {1, 0, 0, 1};
    private char[] morse_code_y = {1, 0, 1, 1};
    private char[] morse_code_z = {1, 1, 0, 0};

    public Vector<char[]> create_morse_code_list() {
        Vector<char[]> list = new Vector<char[]>(256);
        char[] x = {0xff};
        for (int i = 0; i < 256; i++) {
            list.add(x);
        }
        list.setElementAt(morse_code_0, '0');
        list.setElementAt(morse_code_1, '1');
        list.setElementAt(morse_code_2, '2');
        list.setElementAt(morse_code_3, '3');
        list.setElementAt(morse_code_4, '4');
        list.setElementAt(morse_code_5, '5');
        list.setElementAt(morse_code_6, '6');
        list.setElementAt(morse_code_7, '7');
        list.setElementAt(morse_code_8, '8');
        list.setElementAt(morse_code_9, '9');
        list.setElementAt(morse_code_a, 'a');
        list.setElementAt(morse_code_b, 'b');
        list.setElementAt(morse_code_c, 'c');
        list.setElementAt(morse_code_d, 'd');
        list.setElementAt(morse_code_e, 'e');
        list.setElementAt(morse_code_f, 'f');
        list.setElementAt(morse_code_g, 'g');
        list.setElementAt(morse_code_h, 'h');
        list.setElementAt(morse_code_i, 'i');
        list.setElementAt(morse_code_j, 'j');
        list.setElementAt(morse_code_k, 'k');
        list.setElementAt(morse_code_l, 'l');
        list.setElementAt(morse_code_m, 'm');
        list.setElementAt(morse_code_n, 'n');
        list.setElementAt(morse_code_o, 'o');
        list.setElementAt(morse_code_p, 'p');
        list.setElementAt(morse_code_q, 'q');
        list.setElementAt(morse_code_r, 'r');
        list.setElementAt(morse_code_s, 's');
        list.setElementAt(morse_code_t, 't');
        list.setElementAt(morse_code_u, 'u');
        list.setElementAt(morse_code_v, 'v');
        list.setElementAt(morse_code_w, 'w');
        list.setElementAt(morse_code_x, 'x');
        list.setElementAt(morse_code_y, 'y');
        list.setElementAt(morse_code_z, 'z');
        return list;
    }
    MorseCodePlayer() {
        morse_code_list = create_morse_code_list();
        initAudioTrack();
    }

    public int playStringAsync(String str) throws InterruptedException {
        Log.d(TAG, "playStringAsync");
        stopPlay();
        mMessage = str;
        playContinue = true;
        start();
        return 0;
    }
    public void stopPlay() throws InterruptedException {
        Log.d(TAG, "stopPlay");
        if(playContinue == true) {
            playContinue = false;
            join();
        }
    }
    public int playString(String str) throws InterruptedException {
        Log.d(TAG, "playString");
        stopPlay();
        mMessage = str;
        playContinue = true;
        start();
        join();
        return 0;
    }
    private static short[] createSoundDataInShortArray(int samples, final int sampleRate, final double freqency, double sweep) {
        final double rad = 2 * Math.PI * freqency / sampleRate;
        short[] vaf = new short[samples];
        sweep = Math.PI * sweep / ((double) sampleRate * vaf.length);
        for (int j = 0; j < vaf.length; j++) {
            vaf[j] = (short) (Math.sin(j * (rad + j * sweep)) * Short.MAX_VALUE);
        }
        return vaf;
    }

    public int getAudioPerSample(int audioFormat) {
        switch (audioFormat) {
            case AudioFormat.ENCODING_PCM_8BIT:
                return 1;
            case AudioFormat.ENCODING_PCM_16BIT:
            case AudioFormat.ENCODING_DEFAULT:
                return 2;
            case AudioFormat.ENCODING_PCM_FLOAT:
                return 4;
            case AudioFormat.ENCODING_INVALID:
                throw new IllegalArgumentException("Bad audio format : " + audioFormat);
        }
        return 0;
    }
    private void initAudioTrack() {
        int ret_val = 0;
        int dataOffset = 0;
        int testStreamType = AudioManager.STREAM_MUSIC;
        int testMode = AudioTrack.MODE_STATIC;
        int testConfig = AudioFormat.CHANNEL_OUT_STEREO;
        int testFormat = AudioFormat.ENCODING_PCM_16BIT;
        int testSampleRate = 8000;
        int minBufferSize = AudioTrack.getMinBufferSize(testSampleRate, testConfig, testFormat);
        int staticBufferSamples = 8000 * 5;
        int staticBufferSize = staticBufferSamples * getAudioPerSample(testFormat); // AudioFormat.getBytesPerSample(testFormat);
        try {
            Log.d(TAG, "new AudioTrack( " + testSampleRate + ", " +
                    testConfig + ", " +
                    testFormat + ", " +
                    2 * minBufferSize + ", " + testMode + ")");
            track = new AudioTrack(testStreamType,
                    testSampleRate,
                    testConfig,
                    testFormat,
                    staticBufferSize/*2 * minBufferSize*/,
                    testMode
            );
        } catch (IllegalArgumentException iae) {
            Log.e(TAG, "AudioTrack create fail : ", iae);
        }
        track.setPlaybackPositionUpdateListener(new AudioTrack.OnPlaybackPositionUpdateListener() {
            @Override
            public void onMarkerReached(AudioTrack track) {
                //Log.i(TAG, "onMarkerReached : " + track.getPlaybackHeadPosition() );
            }

            @Override
            public void onPeriodicNotification(AudioTrack track) {
                //Log.i(TAG, "onPeriodicNotification : " + track.getPlaybackHeadPosition() );
            }
        });
        int trackState = track.getState();
        ret_val = track.setLoopPoints(0, staticBufferSamples / 2, 200);
        Log.d(TAG, "trackState: " + trackState + ", setLoopPoints(0,x, 200) return: " + ret_val);
        short[] data16 = createSoundDataInShortArray(staticBufferSamples, 8000, 500, 0);
        track.write(data16, dataOffset, staticBufferSamples);
        Log.d(TAG, "trackState after write: " + trackState);

        track.setNotificationMarkerPosition(staticBufferSamples / 2);
        track.setPositionNotificationPeriod(testSampleRate);
    }

    private void play_singal_caracter_by_volume(char c, AudioTrack track, long morse_time_unit) throws InterruptedException {
        /*
        International Morse code is composed of five elements:
        1.short mark, dot or "dit" (·) : "dot duration" is one time unit long
        2.longer mark, dash or "dah" (–) : three time units long
        3.inter-element gap between the dots and dashes within a character : one dot duration or one unit long
        4.short gap (between letters) : three time units long
        5.medium gap (between words) : seven time units long
        */
        Log.i(TAG, "play_singal_caracter_by_volume: " + c);
        char[] code = {};
        track.play();
        code = morse_code_list.get(c);

        for (int i = 0; i < code.length; i++) {
            track.setStereoVolume(1.0f, 1.0f);
            if (code[i] == 1) {
                Thread.sleep(morse_time_unit * 3);
            } else if (code[i] == 0) {
                Thread.sleep(morse_time_unit);
            }
            track.setStereoVolume(0.0f, 0.0f);
            Thread.sleep(morse_time_unit);
        }
        Thread.sleep(morse_time_unit * 2);
        track.pause();
        track.setPlaybackHeadPosition(0);
        //Log.i(TAG, "getPlayStare: " + track.getPlayState());
    }
    @Override
    protected void finalize() throws Throwable {
        if (track != null) track.release();
        super.finalize();
    }

    public void run() {
        Log.i(TAG, "morseCodePlayThreadUseAudioTrack RUN, id: " + getId());
        char[] morse_code = mMessage.toCharArray();

        long time_begin = System.currentTimeMillis();
        long time_end = System.currentTimeMillis();

        int i = 0;
        Log.i(TAG, "time_begin: " + time_begin);
        while (i  < morse_code.length) {
            if(playContinue == false) {
                Log.d(TAG, "been stopped!!!!");
                break;
            }
            try {
                play_singal_caracter_by_volume(morse_code[i % morse_code.length], track, morse_time_unit);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            if (i + 1 < morse_code.length && morse_code_list.get(morse_code[i+1])[0] == 0xff) {
                Log.i(TAG, "Before new word");
                try {
                    Thread.sleep(morse_time_unit * 4);
                    i++;
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            i++;
        }
        track.pause();
        Log.d(TAG, "finishi playing message:" + mMessage);
    }
}
