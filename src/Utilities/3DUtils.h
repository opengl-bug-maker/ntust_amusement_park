/************************************************************************
     File:        3DUtils.H

     Author:     
                  Michael Gleicher, gleicher@cs.wisc.edu
     Modifier
                  Yu-Chi Lai, yu-chi@cs.wisc.edu
     
     Comment:     some useful routines for writing 3D interactive 
					   programs written for CS638 - 
						Michael Gleicher, November 1999
                  re-written and expanded, October 2005

						+ Routines to draw objects
							- drawCube
							- drawFloor
						+	Drop shadow code
						+	MousePole code
						+ Quick and Dirty Quaternions
   
	  Note:        The utilities in this file are meant to be 
						an example for	CS559 students to refer to. please 
						follow the course policy on
						using example code!

     Platform:    Visio Studio.Net 2003/2005

*************************************************************************/
#pragma once

//************************************************************************
// handy utility for turning lights on and off - it remembers what the
// state of the lighting was (on or off) and smooth shading (on or off)
typedef enum { 
	on		=  1, 
	off	= -1, 
	keep	=  0 
} LightOnOff;

void setLighting(const LightOnOff lighting=keep, const LightOnOff smooth=keep);
void restoreLighting();		// pop last state off the stack

//************************************************************************
// stuff for mouse handling
//************************************************************************
// 
// Given the position of the mouse in 2D, we need to figure out where
// it is in 3D. of course, its not in one place, its a line
// this function gets that ray for you (well, it gets 2 points on the line)
int getMouseLine(double& p1x, double& p1y, double& p1z,
								 double& p2x, double& p2y, double& p2z);
			  
//************************************************************************
//
// * When you have a mouse line, you want to pick a point where you think the user 
//   wants to drag to
// * Idea: given a plane parallel to the floor, pick a point on that
//         plane (where the line intersects it)
// * Problem: what to do when the plane is parallel to the line?
// * Problem: how to make things go vertically?
// * Answer:
//   1. Have an "elevator mode" where we use a plane perpindicular to the floor
//   2. r1,r2 are two points on the line
//      a. l is the initial position of the point - we need this to know where
//         the plane is. 
//      b. r is the resulting position. it will share 1 of its coordinates
//         with l, but will be on the line
//************************************************************************
void mousePoleGo( double r1x, double r1y, double r1z,
									double r2x, double r2y, double r2z,
									double lx, double ly, double lz, 
									double &rx, double &ry, double &rz,
									bool elevator);