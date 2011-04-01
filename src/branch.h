/*
 *  branch.h
 *  trees
 *
 *  Created by Nikolas Psaroudakis on 3/6/11.
 *  Copyright 2011 Addictive Labs. All rights reserved.
 *
 */


#pragma once
#include "branchNode.h"
#include "ofxVec3f.h"
#include <iostream>
#include <vector>
class branch {
public:
	branch();
	branch(ofxVec3f pos, ofxVec3f vel, ofxVec3f acc, float radiusStart, float decay);
	void init(ofxVec3f pos, ofxVec3f vel, ofxVec3f acc, float radiusStart, float decay);
	void update();
	void draw();
    //Branching
    bool timeToStem();
    void doStem();
	std::vector<branchNode> nodes;
	std::vector<branch>::iterator branchIter;
	std::vector<branchNode>::iterator nodeIter;
    
    std::vector<branch>::iterator childIter;
    std::vector<branch> children;
	ofxVec3f currentPos;
	ofxVec3f currentVel;
	ofxVec3f currentAcc;
	static float minRadius;
	static int nodeRes;
    static int depth;
    static int maxDepth;
	float branchDecay;
	float radius;
    int age;
    int ageBranched;
	
	// Vehicle stuff
	
	bool isMain;
	
	
	
};