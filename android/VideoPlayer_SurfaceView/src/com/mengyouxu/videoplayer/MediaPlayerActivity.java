package com.mengyouxu.videoplayer;

import java.text.MessageFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

import android.app.Activity;
import android.media.MediaPlayer;
import android.media.MediaPlayer.OnPreparedListener;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ImageView;

import android.widget.MediaController;
import android.widget.RelativeLayout;
import android.widget.TextView;


public class MediaPlayerActivity extends Activity {
	private CustomerVideoView videoView;
	private SurfaceHolder holder;
	private ImageView imageView;
	private TextView timeTextView;
	private TextView titleTextView;
	private TextView clockTextView;
    private Button btnLeftTop;
    private Button btnMiddle720p;
    private Button btnFullScreen;
	private ScheduledExecutorService scheduledExecutorService;
	private Handler handler;
	private SimpleDateFormat dateFormat;
	private RelativeLayout.LayoutParams params_r;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		this.setContentView(R.layout.video);

		this.dateFormat = new SimpleDateFormat("HH:mm:ss");

		this.scheduledExecutorService = Executors.newScheduledThreadPool(2);
		this.handler = new Handler();

		this.videoView = (CustomerVideoView) this.findViewById(R.id.videoView);
		this.imageView = (ImageView) this.findViewById(R.id.image);
		this.imageView.setImageResource(R.drawable.ad);

		this.timeTextView = (TextView) this.findViewById(R.id.timeText);
		this.titleTextView = (TextView) this.findViewById(R.id.videoTitle);
		this.clockTextView = (TextView) this.findViewById(R.id.clockText);

		params_r = (RelativeLayout.LayoutParams)videoView.getLayoutParams();

		params_r.width = 600;
		params_r.height = 400;
		params_r.leftMargin = 212;
		params_r.topMargin = 184;
		//params_r.leftMargin = 0;
		videoView.setLayoutParams(params_r);
		
    	btnLeftTop = (Button)this.findViewById(R.id.btnLeftTop);
    	btnMiddle720p = (Button)this.findViewById(R.id.btnMiddle720p);
    	btnFullScreen = (Button)this.findViewById(R.id.btnFullScreen);
    	
    	btnLeftTop.setOnClickListener(buttonListener);
    	btnMiddle720p.setOnClickListener(buttonListener);
    	btnFullScreen.setOnClickListener(buttonListener);
    	
		MediaController controller = new MediaController(this);
		holder = videoView.getHolder();
		this.videoView.setMediaController(controller);

		//holder.setSizeFromLayout();
		holder.setFixedSize(480,320); 

		//LayoutParams params = new LinearLayout.LayoutParams(480, 320);
		//RelativeLayout.LayoutParams params = (RelativeLayout.LayoutParams)this.videoView.getLayoutParams();
		//params.width = 1280;
		//params.height = 720;
		//this.getWindowManager().getDefaultDisplay().getWidth();
		//this.videoView.setLayoutParams(params);
		
		this.videoView.setOnPreparedListener(new OnPreparedListener() {
			@Override
			public void onPrepared(MediaPlayer mp) {
				// progressBar.setVisibility(View.GONE);
				imageView.setVisibility(View.GONE);
				timeTextView.setVisibility(View.VISIBLE);
				titleTextView.setText("kungfu-panda-4-SSA.mkv");

				mp.start();

				scheduledExecutorService.scheduleAtFixedRate(new Runnable() {

					@Override
					public void run() {
						handler.post(new Runnable() {
							@Override
							public void run() {
								int position = videoView.getCurrentPosition();
								int duration = videoView.getDuration();
								timeTextView.setText(getTimeFormatValue(position)
												+ " / "
												+ getTimeFormatValue(duration));
							}
						});

					}
				}, 1000, 1000, TimeUnit.MILLISECONDS);

				scheduledExecutorService.scheduleWithFixedDelay(new Runnable() {
					@Override
					public void run() {
						handler.post(new Runnable() {

							@Override
							public void run() {
								clockTextView.setText(dateFormat
										.format(new Date()));
							}
						});
					}
				}, 1000, 1000 * 10, TimeUnit.MILLISECONDS);
			}
		});
		//videoView.setVideoURI(Uri.parse("/mnt/extsd/1/kungfu-panda-4-SSA.mkv"));
		videoView.setVideoURI(Uri.parse("/sdcard/test.ts"));
	}

	private static String getTimeFormatValue(long time) {
		return MessageFormat.format(
				"{0,number,00}:{1,number,00}:{2,number,00}",
				time / 1000 / 60 / 60, time / 1000 / 60 % 60, time / 1000 % 60);
	}
	
    private OnClickListener buttonListener =  new OnClickListener(){
		public void onClick(View v) {
			// TODO Auto-generated method stub
			switch(v.getId()){
			case R.id.btnLeftTop:
				Log.i("VideoPlayer","R.id.btnLeftTop");
				videoView.layout(0,0,400,300);
				
				params_r.width = 400;
				params_r.height = 300;
				params_r.leftMargin = 0;
				params_r.topMargin = 100;
				videoView.setLayoutParams(params_r);
				
				//holder.setFixedSize(400,300);
				break;
			case R.id.btnMiddle720p:
				Log.i("VideoPlayer","R.id.btnMiddle720p");
				params_r.width = 600;
				params_r.height = 400;
				params_r.leftMargin = 212;
				params_r.topMargin = 184;
				videoView.setLayoutParams(params_r);
				//holder.setFixedSize(600,400);
				break;
			case R.id.btnFullScreen:
				Log.i("VideoPlayer","R.id.btnFullScreen");
				params_r.width = 800;
				params_r.height = 600;
				params_r.leftMargin = 112;
				params_r.topMargin = 84;
				videoView.setLayoutParams(params_r);
				holder.setFixedSize(800,600);
				break;
			default:
					break;
			}
			
		}
    };
}