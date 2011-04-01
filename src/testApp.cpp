#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
	
	
	ofBackground(0, 0, 0);
	recordContext.setup();
	recordContext.setupUsingXMLFile();
	recordDepth.setup(&recordContext);
	recordImage.setup(&recordContext);
	
	recordUser.setup(&recordContext, &recordDepth, &recordImage);
	
	recordDepth.toggleRegisterViewport(&recordImage);
	recordContext.toggleMirror();
	
	oniRecorder.setup(&recordContext, &recordDepth, &recordImage);
	found = false;
	branchA = singleBranchController(1);
	branchB = singleBranchController(1);
	shader.setup("glass", "glass");
}


//--------------------------------------------------------------
void testApp::update(){
	if (!found) {
		recordContext.update();
		recordUser.update();
	}
	//
	users.clear();
	users  = recordUser.getTrackedUsers();
	if (users.size()>=1 && !found) {
		found = true;
		ofxTrackedUser * u = users[0];
		limbs.clear();
		limbs.push_back(u->neck);
		limbs.push_back(u->left_shoulder);
		limbs.push_back(u->left_upper_arm);
		limbs.push_back(u->left_lower_arm);
		limbs.push_back(u->right_shoulder);
		limbs.push_back(u->right_upper_arm);
		limbs.push_back(u->right_lower_arm);
		limbs.push_back(u->left_upper_torso);
		limbs.push_back(u->right_upper_torso);
		limbs.push_back(u->left_lower_torso);
		limbs.push_back(u->left_upper_leg);
		limbs.push_back(u->left_lower_leg);
		limbs.push_back(u->right_lower_torso);
		limbs.push_back(u->right_upper_leg);
		limbs.push_back(u->right_lower_leg);
		limbs.push_back(u->hip);
		
		//
		u->left_lower_leg.begin.z =0;
		u->left_lower_leg.end.z =0;
		u->left_upper_leg.begin.z =0;
		u->left_upper_leg.end.z =0;
		u->left_lower_torso.begin.z =0;
		u->left_lower_torso.end.z =0;
		u->left_upper_torso.begin.z =0;
		u->left_upper_torso.end.z =0;
		u->left_upper_arm.begin.z =0;
		u->left_upper_arm.end.z =0;
		u->left_lower_arm.begin.z =0;
		u->left_lower_arm.end.z =0;
		//
		u->right_lower_leg.begin.z =0;
		u->right_lower_leg.end.z =0;
		u->right_upper_leg.begin.z =0;
		u->right_upper_leg.end.z =0;
		u->right_lower_torso.begin.z =0;
		u->right_lower_torso.end.z =0;
		u->right_upper_torso.begin.z =0;
		u->right_upper_torso.end.z =0;
		u->right_upper_arm.begin.z =0;
		u->right_upper_arm.end.z =0;
		u->right_lower_arm.begin.z =0;
		u->right_lower_arm.end.z =0;
		
		
		//
		
		
		pathA.addPoint(u->left_lower_leg.end);
		pathA.addPoint(u->left_lower_leg.begin);
		
		pathA.addPoint(u->left_upper_leg.end);
		pathA.addPoint(u->left_upper_leg.begin);
		pathA.addPoint(u->left_lower_torso.end);
		pathA.addPoint(u->left_lower_torso.begin);
		
		pathA.addPoint(u->left_upper_torso.end);
		pathA.addPoint(u->left_upper_torso.begin);
		
		pathA.addPoint(u->left_upper_torso.end);
		pathA.addPoint(u->left_upper_torso.begin);
		
		pathA.addPoint(u->left_upper_arm.end);
		pathA.addPoint(u->left_upper_arm.begin);
		//
		
		pathB.addPoint(u->right_lower_leg.end);
		pathB.addPoint(u->right_lower_leg.begin);
		
		pathB.addPoint(u->right_upper_leg.end);
		pathB.addPoint(u->right_upper_leg.begin);
		pathB.addPoint(u->right_lower_torso.end);
		pathB.addPoint(u->right_lower_torso.begin);
		
		pathB.addPoint(u->right_upper_torso.end);
		pathB.addPoint(u->right_upper_torso.begin);
		
		pathB.addPoint(u->right_upper_torso.end);
		pathB.addPoint(u->right_upper_torso.begin);
		
		pathB.addPoint(u->right_upper_arm.end);
		pathB.addPoint(u->right_upper_arm.begin);
		
		
		branchA.setPath(&pathA);
		branchB.setPath(&pathB);
	}
	branchA.update();
	branchB.update();
}

//--------------------------------------------------------------
void testApp::draw(){
	cam.place();
	shader.begin();
	shader.setUniform("edgefalloff", 1.0f);

	
	branchA.draw();
	branchB.draw();
	shader.end();
	ofSetColor(255, 255, 255);
	for (int i=0; i< limbs.size(); i++) {
		drawLimb(limbs[i]);
	}
}

void testApp::drawLimb(ofxLimb limb){
	
	glBegin(GL_LINES);
	glVertex3f(limb.begin.x, limb.begin.y, 0);
	glVertex3f(limb.end.x, limb.end.y, 0);
	glEnd();
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	found = false;
}


//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	
}

