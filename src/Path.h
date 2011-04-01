/*
 *  Path.h
 *  pathFollowing3D
 *
 *  Created by Nikolas Psaroudakis on 3/30/11.
 *  Copyright 2011 Home. All rights reserved.
 *
 */

#pragma once

#include <vector>
#include "ofxVectorMath.h"
class Path {
public:
	Path();
	void addPoint(ofxVec3f p);
	void display();
	vector<ofxVec3f> points;
	float radius;
};