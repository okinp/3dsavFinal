/*
 *  Vehicle.h
 *  pathFollowing3D
 *
 *  Created by Nikolas Psaroudakis on 3/30/11.
 *  Copyright 2011 Home. All rights reserved.
 *
 */

#pragma once
#include <vector>
#include "Path.h"
class Vehicle  {
public:
	Vehicle();
	Vehicle(ofxVec3f pos, float ms, float mf);
	void applyForces(vector<Vehicle> boids, Path path);
	void applyForce(ofxVec3f force);
	void run();
	ofxVec3f follow(Path p);
	ofxVec3f getNormalPoint(ofxVec3f p, ofxVec3f a, ofxVec3f b);
	ofxVec3f separate(vector<Vehicle> boids);
	void update();
	ofxVec3f seek(ofxVec3f target);
	void render();
	void borders();
	
	ofxVec3f pos, vel, acc;
	float r;
	float maxforce , maxspeed;
	
	bool debug;
private:
	void init();
	
};