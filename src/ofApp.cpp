#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetLogLevel(OF_LOG_VERBOSE);

	appWidth = 800;
	appHeight = 600;
	appFrameRate = 60;
	ofSetFrameRate(appFrameRate);
	ofSetWindowShape(appWidth, appHeight);

	aImg.load("lenna.png");
	bImg.load("paper.jpg");
	maskImg.load("mask.png");

	recordFbo.allocate(appWidth, appHeight, GL_RGBA);
	recordColorFbo.allocate(appWidth, appHeight, GL_RGB);
	maskFbo.allocate(appWidth, appHeight, GL_RGBA);
	
	maskFbo.begin();
	ofClear(0, 0, 0, 255);
	maskFbo.end();

	recordFbo.begin();
	ofClear(0, 0, 0, 255);
	recordFbo.end();

	recordColorFbo.begin();
	ofClear(0, 0, 0, 255);
	recordColorFbo.end();

	ofEnableAlphaBlending();
	
	effectParamGp.setName("effectSettings");
	effectParamGp.add(parOpacity.set("opacity", 255, 0, 255));
	effectParamGp.add(parBlendMode.set("blend mode", 5, 0, 5));
	//globalColor.set("global color", ofColor(255, 255, 255), ofColor(0, 0, 0), ofColor(255, 255, 255));
	//effectParamGp.add(globalColor);
	guiEffectSettings.setup(effectParamGp,"effectSettings.xml");
	guiEffectSettings.loadFromFile("effectSettings.xml");
	guiEffectSettings.setPosition(512, 120);

	blendMode = getBlendMode(parBlendMode);
	strBlendMode = getBlendModeName(parBlendMode);
	parBlendMode.addListener(this, &ofApp::blendChanged);
}



//--------------------------------------------------------------
void ofApp::blendChanged(int & parBlendMode){
	blendMode = getBlendMode(parBlendMode);
	strBlendMode = getBlendModeName(parBlendMode);
}


//--------------------------------------------------------------
string ofApp::getBlendModeName(int blendMode) {
	string blendName = "Disabled";
	switch (blendMode) {
	case 0:
		blendName = "Disabled";
		break;
	case 1:
		blendName = "Alpha";
		break;
	case 2:
		blendName = "Add";
		break;
	case 3:
		blendName = "Substract";
		break;
	case 4:
		blendName = "Multiply";
		break;
	case 5:
		blendName = "Screen";
		break;
	}
	return blendName;
}

//--------------------------------------------------------------
ofBlendMode ofApp::getBlendMode(int blendMode) {
	ofBlendMode retBlendMode = OF_BLENDMODE_DISABLED;
	switch (blendMode) {
	case 0:
		retBlendMode = OF_BLENDMODE_DISABLED;
		break;
	case 1:
		retBlendMode = OF_BLENDMODE_ALPHA;
		break;
	case 2:
		retBlendMode = OF_BLENDMODE_ADD;
		break;
	case 3:
		retBlendMode = OF_BLENDMODE_SUBTRACT;
		break;
	case 4:
		retBlendMode = OF_BLENDMODE_MULTIPLY;
		break;
	case 5:
		retBlendMode = OF_BLENDMODE_SCREEN;
		break;
	}
	return retBlendMode;
}

//--------------------------------------------------------------
void ofApp::exit(){
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::drawResult() {
	ofSetColor(255, 255, 255);
	ofBackground(0);
	
	maskFbo.begin();
		ofClear(255, 255, 255, 0);
		bImg.draw(0,0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_ZERO, GL_ONE_MINUS_SRC_ALPHA);
		maskImg.draw(0, 0);
		glDisable(GL_BLEND);
	maskFbo.end();
	
	recordFbo.begin();
		ofClear(255, 255, 255, 0);
		aImg.draw(0, 0);
		ofEnableBlendMode(blendMode);
		ofSetColor(255, 255, 255, parOpacity);
		maskFbo.draw(0,0);
		ofSetColor(255, 255, 255);
		ofDisableBlendMode();
	recordFbo.end();

	recordFbo.draw(0, 0);
}


//--------------------------------------------------------------
void ofApp::draw(){
	
	drawResult();

	if (bShowGui) {
		stringstream ss;
		ss << "FPS: " << ofGetFrameRate() << endl
			<< "mouse x: " << ofBaseApp::mouseX << ", y: " << ofBaseApp::mouseY << endl
			<< "blend mode: " << strBlendMode << endl;
		ofFill();
		ofSetColor(0, 0, 0, 100);
		ofRect(512, 0, 260, 120);
		ofSetColor(255, 255, 255);
		ofDrawBitmapString(ss.str(), 512+15, 15);
		
		guiEffectSettings.draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	switch (key){
		case 'g':
		case 'G':
			bShowGui = !bShowGui;
		break;
		default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
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

