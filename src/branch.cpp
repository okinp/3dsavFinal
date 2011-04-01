/*
 *  branch.cpp
 *  trees
 *
 *  Created by Nikolas Psaroudakis on 3/6/11.
 *  Copyright 2011 Addictive Labs. All rights reserved.
 *
 */

#include "branch.h"
#include "ofMain.h"

float branch::minRadius = 1.0f;
int branch::nodeRes = 20;
int branch::depth = 0;
int branch::maxDepth = 4;
branch::branch(){
	init(ofxVec3f(),ofxVec3f(),ofxVec3f(), 10,  0.99); 
}
branch::branch(ofxVec3f pos, ofxVec3f vel, ofxVec3f acc, float radiusStart, float decay){
	init(pos, vel, acc, radiusStart, decay);
}
void branch::init(ofxVec3f pos, ofxVec3f vel, ofxVec3f acc, float radiusStart, float decay){
	radius =radiusStart;
	currentPos = pos;
	currentVel = vel;
	currentAcc = acc;
	branchDecay = decay;
	radius = radiusStart;
	age = 0;
	ageBranched = 0;
	isMain = false;
}
void branch::update(){
	if (radius>=minRadius) {
		
		if (!isMain) {
			radius*=branchDecay;
			float theta = ofNoise(currentPos.x, currentPos.y, currentPos.z);
			theta*=2*PI;
			if (nodes.size() >20) {
				currentAcc = cos(theta)*nodes.back().u+radius*sin(theta)*nodes.back().u;
			}
			currentVel+=0.1*currentAcc;
			currentVel*=branchDecay;
			currentVel.limit(5);
			currentPos+=currentVel;
			//branchNode b = branchNode(nodeRes,radius+1.0*sin(age*2*PI/20),currentPos+ofxVec3f(ofRandom(-0.1, 0.1),ofRandom(-0.1, 0.1),ofRandom(-0.1, 0.1)),currentVel);
		} else {
			radius*=0.99f;
		}
 
		branchNode b = branchNode(nodeRes,radius+0.4*radius*sin(age*2*PI/20),currentPos,currentVel);
		nodes.push_back(b);
		age++;
	}
    
    if (timeToStem()) {
		doStem();
    }
    
    
    //Update Children
    
    childIter = children.begin();
    while (childIter!=children.end()){
        childIter->update();
        ++childIter;
    }
}

bool branch::timeToStem(){
    if (depth<maxDepth && (age - ageBranched) > 30 ) {
        return true;
    }
	return false;
}
void branch::doStem(){
    ageBranched = age;
    ofxVec3f childVel  = currentVel.getRotated(ofRandom(0, 360),ofxVec3f(1,1,0));
    branch b = branch(currentPos, childVel, 0.1*currentAcc, radius*0.7, branchDecay);
    children.push_back(b);
}

void branch::draw(){
	//Draw Self
	glColor3f(0.0, 0.0, 1.0);
	if (nodes.size()>0) {
		ofxVec3f a, b, norm, normA, normB;
		int sz =nodes[0].points.size();
		for (int i=0; i<nodes.size()-1; i++) {
			glBegin(GL_TRIANGLE_STRIP);
			for (int j=0; j<sz; j++) {
				normA = nodes[i].points[j] - nodes[i].center;
				normA.normalize();
				normB = nodes[i+1].points[j] - nodes[i+1].center;
				normB.normalize();
				glNormal3f( normA.x, normA.y, normA.z);	
				glVertex3f(nodes[i].points[j].x, nodes[i].points[j].y, nodes[i].points[j].z);
				glNormal3f( normB.x, normB.y, normB.z);	
				glVertex3f(nodes[i+1].points[j].x, nodes[i+1].points[j].y, nodes[i+1].points[j].z);
			}
			glEnd();
		}
	}
    
    //Draw Children
    
    childIter = children.begin();
    while (childIter!=children.end()){
        childIter->draw();
        ++childIter;
    }
}