/*
 *  Vehicle.cpp
 *  pathFollowing3D
 *
 *  Created by Nikolas Psaroudakis on 3/30/11.
 *  Copyright 2011 Home. All rights reserved.
 *
 */

#include "ofMain.h"
#include "Vehicle.h"

Vehicle::Vehicle():pos(ofxVec3f()),maxspeed(3), maxforce(5)
{
	init();
}
Vehicle::Vehicle(ofxVec3f pos, float ms, float mf):pos(pos),maxspeed(ms), maxforce(mf)
{
	init();
}
void Vehicle::init()
{
	r = 12;
	acc = ofxVec3f();
	vel = ofxVec3f(maxspeed, 0, 0);
	debug = false;
}
void Vehicle::applyForces(vector<Vehicle> boids, Path path)
{
	ofxVec3f f = follow(path);
	ofxVec3f s = separate(boids);
	//Arbitrary weighting
	f*=3;
	s*=1;
	applyForce(f);
	applyForce(s);
}
void Vehicle::applyForce(ofxVec3f force)
{
	acc+=force;
}
void Vehicle::run()
{
	update();
	borders();
}
ofxVec3f Vehicle::follow(Path p)
{
	ofxVec3f predict = vel;
	predict.normalize();
	predict*=25; //25 is arbitrary
	ofxVec3f predictLoc = pos + predict;
	
	if (debug) {
		
		//debug code goes here
	}
	
	ofxVec3f target;
	ofxVec3f dir;
	float record = 1000000;
	
	for (int i =0; i< p.points.size(); i++){
		ofxVec3f a = p.points[i];
		ofxVec3f b = p.points[(i+1)%p.points.size()]; // wrap around
		
		//ofxVec3f b = p.points[(i+1)]; // wrap around
		
		ofxVec3f norm = getNormalPoint(predictLoc, a, b);
		ofxVec3f diffA = norm - a;
		ofxVec3f diffB  = norm - b;
		ofxVec3f line = b - a;
		
		float da = diffA.length();
		float db = diffB.length();
		if (da + db > line.length()+1) {
			norm = b;
			a = p.points[(i+1)%p.points.size()];
			b = p.points[(i+2)%p.points.size()];
			line = b - a;
		}
		float d  = (norm - predictLoc).length();
		
		if (d< record){
			record = d;
			target = norm;
			
			dir = line;
			dir.normalize();
			dir*=25;
		}
	}
	if (debug) {
		//draw debug stuff
	}
	if (record > p.radius || vel.length() < 0.1) {
		target+=dir;
		return seek(target);
	} else {
		return ofxVec3f();
	}
}
ofxVec3f Vehicle::getNormalPoint(ofxVec3f p, ofxVec3f a, ofxVec3f b)
{
	ofxVec3f ap = p - a;
	ofxVec3f ab = b - a;
	ab.normalize();
	ab*=ap.dot(ab);
	ofxVec3f norm = a + ab;
	return norm;
	
}
ofxVec3f Vehicle::separate(vector<Vehicle> boids)
{
	float desiredseparation = r*2;
	ofxVec3f steer = ofxVec3f();
	int count = 0;
	
	for (int i =0; i< boids.size(); i++) {
		Vehicle other = boids[i];
		float d = (pos - other.pos).length();
		if ((d>0)&&(d<desiredseparation) ) {
			ofxVec3f diff = pos - other.pos;
			diff.normalize();
			diff/=d;
			steer+=diff;
			count++;
		}
	}
	if (count > 0) {
		steer/=(float)count;
	}
	if (steer.length()>0) {
		steer.normalize();
		steer*=maxspeed;
		steer-=vel;
		steer.limit(maxforce);
	}
	return steer;
}
void Vehicle::update()
{
	vel += acc;
	vel.limit(maxspeed);
	pos+=vel;
	acc*=0;
}
ofxVec3f Vehicle::seek(ofxVec3f target)
{
	ofxVec3f desired = target - pos;
	
    // If the magnitude of desired equals 0, skip out of here
    // (We could optimize this to check if x and y are 0 to avoid mag() square root
    if (desired.length() == 0) return ofxVec3f();
	
    // Normalize desired and scale to maximum speed
    desired.normalize();
    desired*=maxspeed;
    // Steering = Desired minus Velocity
    ofxVec3f steer = desired - vel;
    steer.limit(maxforce);  // Limit to maximum steering force
    return steer;
}
void Vehicle::render()
{
	ofSetColor(200, 200, 200);
	ofPushMatrix();
	ofTranslate(pos.x, pos.y, pos.z);
	ofCircle(0, 0, r/5);
	ofPopMatrix();
	
}
void Vehicle::borders()
{
	if (pos.x < -r) pos.x = ofGetWidth()+r;
	if (pos.x > ofGetWidth()+r) pos.x = -r;
}