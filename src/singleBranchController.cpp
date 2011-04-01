/*
 *  singleBranchController.cpp
 *  treesWithPaths
 *
 *  Created by Nikolas Psaroudakis on 3/31/11.
 *  Copyright 2011 Home. All rights reserved.
 *
 */

#include "singleBranchController.h"
#include "ofMain.h"
#include <iostream>
singleBranchController::singleBranchController()
{
	init(1);
}
singleBranchController::singleBranchController(int numBranches)
{
	init(numBranches);
}
void singleBranchController::init(int numBranches)
{
	path = NULL;
	for (int i=0; i<numBranches; i++) {
		branches.push_back(branch());
		branches[i].isMain = true;
		vehicles.push_back(Vehicle(ofxVec3f(), ofRandom(2,4), 0.3));
	}
}
void singleBranchController::setPath(Path *p)
{
	path  = p;
	for (int i=0; i<branches.size(); i++) {
		//std::cout << path->points[0].x << "and" << path->points[0].y << std::endl;
//		branches[i].currentPos = path->points[0];
		vehicles[i].pos = path->points[0];
	}
}
void singleBranchController::update()
{
	if (path) {
		for (int i = 0; i< vehicles.size(); i++) {
			vehicles[i].applyForces(vehicles, *path);
			vehicles[i].run();
		}
		for (int i=0; i<branches.size(); i++) {
			
			branches[i].currentPos = vehicles[i].pos;
			branches[i].currentVel = vehicles[i].vel;
			branches[i].update();
		}
	}
}
void singleBranchController::draw()
{
	for (int i=0; i<branches.size(); i++) {
		branches[i].draw();
	}
}