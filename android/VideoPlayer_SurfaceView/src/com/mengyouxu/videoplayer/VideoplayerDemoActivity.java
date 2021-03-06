package com.mengyouxu.videoplayer;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class VideoplayerDemoActivity extends Activity {
	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main); 
		
		Button button = (Button) findViewById(R.id.button);
		button.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				switch(v.getId()){
				case R.id.button:
					Log.i("VideoPlayer","R.id.btnLeftTop");
					Intent intent = new Intent();
					intent.setClass(VideoplayerDemoActivity.this,
							MediaPlayerActivity.class);
					startActivity(intent);
					break;
				}
			}
		});
	}
}