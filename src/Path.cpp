/*
 *  Path.cpp
 *  pathFollowing3D
 *
 *  Created by Nikolas Psaroudakis on 3/30/11.
 *  Copyright 2011 Home. All rights reserved.
 *
 */

#include "Path.h"

Path::Path()
{
	radius = 20;	
}
void Path::addPoint(ofxVec3f p)
{
	points.push_back(p);
}
void Path::display()
{


}