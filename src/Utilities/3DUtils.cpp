///************************************************************************
//     File:        3DUtils.cpp
//
//     Author:
//                  Michael Gleicher, gleicher@cs.wisc.edu
//     Modifier
//                  Yu-Chi Lai, yu-chi@cs.wisc.edu
//
//     Comment:     some useful routines for writing 3D interactive
//					   programs written for CS638 -
//						Michael Gleicher, November 1999
//                  re-written and expanded, October 2005
//
//						+ Routines to draw objects
//							- drawCube
//							- drawFloor
//						+	Drop shadow code
//						+	MousePole code
//						+ Quick and Dirty Quaternions
//
//	  Note:        The utilities in this file are meant to be
//						an example for	CS559 students to refer to. please
//						follow the course policy on
//						using example code!
//
//     Platform:    Visio Studio.Net 2003/2005
//
//*************************************************************************/
//#define _USE_MATH_DEFINES
//
//#include <math.h>
//
//#include <SFML/OpenGL.hpp>
//
//#include "3DUtils.H"
//
//#include <vector>
//using std::vector;
//
////*************************************************************************
////
//// * Convert from mouse coordinates to world coordinates
////   in a sense, this mimics the old fashioned gl's mapw
////   the only advantage is that we don't have to pick the near clipping
////   plane, so we can be a little more well-balanced
////   this code mimics page 147 of the OpenGL book
////===============================================================================
//int getMouseLine(double& x1, double& y1, double& z1,
//								 double& x2, double& y2, double& z2)
////===============================================================================
//{
////  int x = Fl::event_x();
////  int iy = Fl::event_y();
////
////  double mat1[16],mat2[16];		// we have to deal with the projection matrices
////  int viewport[4];
////
////  glGetIntegerv(GL_VIEWPORT, viewport);
////  glGetDoublev(GL_MODELVIEW_MATRIX,mat1);
////  glGetDoublev(GL_PROJECTION_MATRIX,mat2);
////
////  int y = viewport[3] - iy; // originally had an extra -1?
//
////  int i1 = gluUnProject((double) x, (double) y, .25, mat1, mat2, viewport, &x1, &y1, &z1);
////  int i2 = gluUnProject((double) x, (double) y, .75, mat1, mat2, viewport, &x2, &y2, &z2);
//    int i1;
//    int i2;
//
//
//  return i1 && i2;
//}
//
//
////*************************************************************************
////
//// More of an explanation in the header file.
//// The beginings of a mousepole handler, given a pair of points on the
//// mouse ray, and the point in question, find a new point. By default,
//// it assumes the plane parallel to the ground, unless the elevator
//// button is pushed, in which case it is the YZ plane
////===============================================================================
//inline double ABS(double x) { return (x<0) ? -x : x; };
////===============================================================================
//
////*************************************************************************
////
//// * When you have a mouse line, you want to pick a point where you think the user
////   wants to drag to
//// * Idea: given a plane parallel to the floor, pick a point on that
////         plane (where the line intersects it)
//// * Problem: what to do when the plane is parallel to the line?
//// * Problem: how to make things go vertically?
//// * Answer:
////   1. Have an "elevator mode" where we use a plane perpindicular to the floor
////   2. r1,r2 are two points on the line
////      a. l is the initial position of the point - we need this to know where
////         the plane is.
////      b. r is the resulting position. it will share 1 of its coordinates
////         with l, but will be on the line
////===============================================================================
//void mousePoleGo(double r1x, double r1y, double r1z,
//									double r2x, double r2y, double r2z,
//									double lx, double ly, double lz,
//									double &rx, double &ry, double &rz,
//									bool elevator)
////===============================================================================
//{
//  rx = lx; ry=ly; rz=lz;
//  if (elevator || (ABS(r1y - r2y) < .01)) {
//	if (ABS(r1z-r2z) > ABS(r1x-r2x)) {
//	  double zd = r1z-r2z;
//	  if (ABS(zd) > .01) {
//		double zp = (lz - r1z) / zd;
//		rx = r1x + (r1x - r2x) * zp;
//		ry = r1y + (r1y - r2y) * zp;
//	  }
//	} else {
//	  double xd = r1x-r2x;
//	  if (ABS(xd) > .01) {
//		double xp = (lx-r1x) / xd;
//		rz = r1z + (r1z - r2z) * xp;
//		ry = r1y + (r1y - r2y) * xp;
//	  }
//	}
//  } else {
//	double yd = r1y - r2y;
//	// we have already made sure that the elevator is not singular
//	double yp = (ly - r1y) / yd;
//	rx = r1x + (r1x - r2x) * yp;
//	rz = r1z + (r1z - r2z) * yp;
//  }
//}
//
////*******************************************************************************
////
//// * save the lighting state on the stack so it can be restored
////
////*******************************************************************************
//struct LightState {
//	bool lighting;
//	bool smooth;
//
//	LightState(bool l, bool s) : lighting(l), smooth(s) {};
//};
//static vector<LightState> lightStateStack;
//
////*******************************************************************************
////
//// *
////===============================================================================
//void setLighting(const LightOnOff lighting, const LightOnOff smoothi)
////===============================================================================
//{
//	int smooth;
//	bool lights = glIsEnabled(GL_LIGHTING) > 0;
//	glGetIntegerv(GL_SHADE_MODEL,&smooth);
//	lightStateStack.push_back(LightState( lights, (smooth == GL_SMOOTH) ));
//
//	if (lighting != keep) {
//		if (lighting == on) glEnable(GL_LIGHTING);
//		else glDisable(GL_LIGHTING);
//	}
//	if (smoothi != keep) {
//		if (smoothi == on) glShadeModel(GL_SMOOTH);
//		else glShadeModel(GL_FLAT);
//	}
//
//}
//
////*******************************************************************************
////
//// *
////===============================================================================
//void restoreLighting()
////===============================================================================
//{
//	if (!lightStateStack.empty()) {
//		if ((lightStateStack.end()-1)->lighting)
//			glEnable(GL_LIGHTING);
//		else
//			glDisable(GL_LIGHTING);
//
//		if ((lightStateStack.end()-1)->smooth)
//			glShadeModel(GL_SMOOTH);
//		else
//			glShadeModel(GL_FLAT);
//
//	}
//}