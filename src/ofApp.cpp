#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	width = 1024;
	height = 768;
	
	kinectPointsCtr = projPointsCtr = 0;

	gui.setup("kinect_settings","kinect_settings.xml");
	gui.add(minthreshold.setup("MINTHRESHOLD", 20, 0, 4500));
	gui.add(maxthreshold.setup("MAXTHRESHOLD", 40, 0, 4500));
	

	kinect.open();
	kinect.initDepthSource();
	kinect.initColorSource();
	
	ofSetWindowShape(width, height);

	img.allocate(512, 424, OF_IMAGE_COLOR);
	sand.allocate(512,424);
	//cv::Mat img1(400, 400, CV_8UC3);
	//cv::Mat img1 = cv::Mat::zeros(width / 2 + 2, 0, CV_8UC3);
	

	
}

//--------------------------------------------------------------
void ofApp::update() {
	kinect.update();
	if (kinect.isFrameNew()) {
		auto depth = kinect.getDepthSource();

		auto depthPixel = depth->getPixels().getData();

		
		for (int x = 0;x < depth->getWidth(); x++) {
			
			
			for (int y = 0; y < depth->getHeight(); y++) {
				
				
				int set = x + y*depth->getWidth();

				int d = depthPixel[set];

				float a = ofMap(d, minthreshold, maxthreshold, 0, 255, true);

				ofColor pixels;
			
				float r1 = 0,b1 = 0,g1 = 0;
				if (a > 0 && a < 127.5) {


					 r1 = ofMap(a, 0, 127, 255, 0, true);

					 g1 = ofMap(a, 0, 127, 0, 255, true);
					 b1 = 0;
				}
				else if (a>127.5 && a<255){

					 r1 = 0;
					 g1 = ofMap(a, 127, 255, 255, 0, true);
					 b1 = ofMap(a, 127, 255, 0, 255, true);
					
				}


				pixels.r = r1;
				pixels.g = g1;
				pixels.b = b1;

				img.setColor(x, y, pixels);

						
		   
						
						
			}
		}
				

				

			
		
		img.update();
		
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	//kinect.getDepthSource()->draw(0, 0, width, height);
	//kinect.getColorSource()->draw(width/2,0, 320, 240);
	
	img.draw(0,0);
	gui.draw();
	sand.draw(width/2+2,0);
	

    
	





	//cv::Mat my(sand);

	//cv::ellipse(sand, cv::Point(pt.x, pt.y), cv::Size(100.0, 160.0), 45, 0, 360, cv::Scalar(255, 0, 0), 1, 8);
	
	
	



	
	//imshow("Image", img2);
	

	/*
	ofSetColor(ofColor::white);

	ofBeginShape();
	ofRect(points.x, points.y, 10, 10);
	ofEndShape();
	*/

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	for (int n = 0; n < 4; n++)
	{
		cout<<" "<< kinectpoint[n];
	}
	cout << "\n";
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	
	
		pt.x = x;
		pt.y = y;
	
		cout << "\nX" << pt.x;
		cout << "\nY" << pt.y;

		
		
		
		if (kinectPointsCtr < 4) {
			kinectpoint[kinectPointsCtr] = pt;
			kinectPointsCtr++;
		}
		else 
		{
			kinectPointsCtr = 0;
			kinectpoint[kinectPointsCtr] = pt;
			
		}
		

		


		
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}