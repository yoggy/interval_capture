interval_capture
============
UVCカメラのキャプチャとHTTP POSTで画像を送信するサンプルプログラム。

Raspberry Pi用です。

how to build
============
<pre>
  $ sudo apt-get install libcurl4-openssl-dev
  $ sudo apt-get install libopencv-dev
  $ sudo apt-get install libsdl1.2-dev
  $ sudo apt-get install libboost-all-dev
  $ sudo apt-get install cmake
  $ git clone https://github.com/yoggy/interval_capture.git
  $ cd interval_capture
  $ cmake .
  $ make
</pre>

usage
============
<pre>
  $ ./interval_capture
  usage : ./interval_capture [camera_name] [interval(ms)] [jpeg_quality] [image_post_url]

    example
        ./interval_capture camera0 1000 90 http://example.com/path/to/post

  $ ./interval_capture camera1 100 70 http://example.com/image_post
  
</pre>

