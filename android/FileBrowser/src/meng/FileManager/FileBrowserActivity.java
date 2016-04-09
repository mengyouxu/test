package meng.FileManager;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStreamReader;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.AdapterView.OnItemClickListener;

public class FileBrowserActivity extends Activity {

    private String TAG = "Filebrowser";
    private ListView fileListView = null;
    private TextView currentDirTextView = null;
    private String currentDir = null;
    private String[] fileList = null;

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        initFileList();
        updateFileList("/storage/sda1/2_medias");
    }
    
    private void initFileList(){
        setContentView(R.layout.main);
        currentDirTextView = (TextView)findViewById(R.id.currentDir);
        fileListView = (ListView)findViewById(R.id.fileListView);
        fileListView.setOnItemClickListener(fileListListener);
    }
    
    private void showFilelist(){
        setContentView(R.layout.main);
        currentDirTextView = (TextView)findViewById(R.id.currentDir);
        fileListView = (ListView)findViewById(R.id.fileListView);
        fileListView.setOnItemClickListener(fileListListener);
        updateFileList(currentDir);
    }
    
    private void updateFileList(String path){
        currentDirTextView.setText(path);
        setFileListView(getFileList(path));
    }  
    
    private void setFileListView(String[] fileList){
        Log.i(TAG,"File list length = " + fileList.length);
        //for(String fileName:fileList){
        //    Log.i(TAG,fileName);
        //}
        fileListView.setAdapter(new ArrayAdapter<String>(this, android.R.layout.simple_expandable_list_item_1,fileList));
    }
    
    private String[] getFileList(String path){
        String[] fileNameList =  null;
        File dir = null;
        dir =  new File(path);
        fileNameList = dir.list();

        return fileNameList;
    }
    
    private OnItemClickListener fileListListener = new OnItemClickListener(){
        public void onItemClick(AdapterView<?> parent, View view, int position, long id){
            ArrayAdapter<?> tempAdapter = null;
            String filePath = (String) currentDirTextView.getText();
            File fileOnClick = null;
            if(!filePath.endsWith("/")){
                filePath += "/";
            }

            Log.i(TAG,"onItemClick!\n");
            Log.i(TAG,"position = " + position + " / " + "id = " + id);
            switch(position){
            default:
                tempAdapter = (ArrayAdapter<?>) parent.getAdapter();
                filePath += (String) tempAdapter.getItem(position);
                fileOnClick =  new File(filePath);
                if(fileOnClick.isDirectory()){
                    currentDir = filePath;
                    updateFileList(filePath);
                }else if(filePath.endsWith(".mp3")){
                    showMusicPlayer(filePath);
                }else if(filePath.endsWith(".wav")){
                    showMusicPlayer(filePath);
                }else if(filePath.endsWith(".ogg")){
                    showMusicPlayer(filePath);
                }else if(filePath.endsWith(".m4a")){
                    showMusicPlayer(filePath);
                }else if(filePath.endsWith(".aac")){
                    showMusicPlayer(filePath);
                }else if(filePath.endsWith(".ts")){
                    showVideoPlayer(filePath);
                }else if(filePath.endsWith(".mp4")){
                    showVideoPlayer(filePath);
                }else if(filePath.endsWith(".mkv")){
                    showVideoPlayer(filePath);
                }else if(filePath.endsWith(".3gp")){
                    showVideoPlayer(filePath);
                }else if(filePath.endsWith(".ulist")){
                    String filename = parsePlayScript(filePath);
                    Log.i(TAG,"filename : " + filename);
                    if(filename != null) {
                        showVideoPlayer(filename);
                    }
                }
                Log.i(TAG,"filePath = "+ filePath);
                break;
            }
        }
    };

    private void showMusicPlayer(String path){

        Intent intent = new Intent(FileBrowserActivity.this,MusicPlayerActivity.class);
        Bundle bundle_1 = new Bundle();
        bundle_1.putString("file_path",path);

        intent.putExtras(bundle_1);

        startActivity(intent);
    }

    private void showVideoPlayer(String path){
        //ComponentName componentName = new ComponentName(
        //        "meng.FileManager",
        //        "meng.FileManager.VideoPlayer");
        Intent intent = new Intent();

        intent.setClass(FileBrowserActivity.this,VideoPlayerActivity.class);

         Bundle bundle = new Bundle();
         bundle.putString("file_path", path);
         intent.putExtras(bundle);
         //intent.setComponent(componentName);
         startActivity(intent);
    }

    private String parsePlayScript(String path){
        FileInputStream fd = null;
        try {
            fd = new FileInputStream(path);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }

        try {
            InputStreamReader read = new InputStreamReader(fd);
            BufferedReader bufferedReader = new BufferedReader(read);
            return bufferedReader.readLine();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    public boolean onKeyDown(int keyCode, KeyEvent event) {

        File tempFile = null;

        if(keyCode == KeyEvent.KEYCODE_BACK){
            if(currentDir.equals("/")) {
                return super.onKeyDown(keyCode, event);
            }
            File fileOnClick =  new File(currentDir);
            currentDir = fileOnClick.getParent();
            updateFileList(currentDir);
        }
        return true;
    }
}
