# YUV-Reader
This repository aims to read YUV frame from a file. I use the newest OpenCV 3.0(above). Feel free to post issues or pull request.

*Usage:

  Init YuvReader object:
  
    YuvReader yuvReader(VIDEO_PATH, VIDEO_WIDTH, VIDEO_HEIGHT, DEBUG = true);
    
  Read each frame by while loop:
  
    Mat frame;
    while (true) {
		  if (!yuvReader.read(frame)) {
			  return 0;
		  }
		  imshow("Video", frame);
		}
  

