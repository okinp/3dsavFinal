/*
 *  branchNode.h
 *  trees
 *
 *  Created by Nikolas Psaroudakis on 3/6/11.
 *  Copyright 2011 Addictive Labs. All rights reserved.
 *
 */

#pragma once
#include "ofxVectorMath.h"
#include <vector>

class branchNode {
public:
	branchNode();
	branchNode(int nodeResolution, float radius, ofxVec3f pos, ofxVec3f dir);
	void draw();
	ofxVec3f center;
	ofxVec3f u, v;
	std::vector<ofxVec3f> points;
};