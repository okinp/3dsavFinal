/*
 *  singleBranchController.h
 *  treesWithPaths
 *
 *  Created by Nikolas Psaroudakis on 3/31/11.
 *  Copyright 2011 Home. All rights reserved.
 *
 */

#pragma once
#include "branch.h"
#include "Path.h"
#include "Vehicle.h"
#include <vector> branches;
class singleBranchController {
public:
	singleBranchController();
	singleBranchController(int numBranches);
	void init(int numBranches);
	void setPath(Path* p);
	void update();
	void draw();
	Path *path;
	vector<branch> branches;
	vector<Vehicle> vehicles;
};