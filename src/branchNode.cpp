/*
 *  branchNode.cpp
 *  trees
 *
 *  Created by Nikolas Psaroudakis on 3/6/11.
 *  Copyright 2011 Addictive Labs. All rights reserved.
 *
 */

#include "branchNode.h"

branchNode::branchNode(){




}
branchNode::branchNode(int nodeResolution, float radius, ofxVec3f pos, ofxVec3f dir){
	ofxVec3f i = ofxVec3f(1,0,0);
	//ToDo: if moving horizontal;y, we will need to use j instead
	u = dir.getCrossed(i);
	v =dir.getCrossed(u);
	u.normalize();
	v.normalize();
	center = pos;
	for (int i=0; i<nodeResolution; i++) {
		float theta = 2*PI*i/(nodeResolution-1);
		ofxVec3f point = center+ radius*cos(theta)*u +radius*sin(theta)*v;
		points.push_back(point);
	}


}
void branchNode::draw(){
	glPointSize(3);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_LOOP);
	for (int i=0; i< points.size(); i++) {
		glVertex3f(points[i].x, points[i].y, points[i].z);
	}
	glEnd();
}