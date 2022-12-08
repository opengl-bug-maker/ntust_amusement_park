/************************************************************************
     File:        ArcBallCam.h

     Author:     
                  Michael Gleicher, gleicher@cs.wisc.edu
     Modifier
                  Yu-Chi Lai, yu-chi@cs.wisc.edu

     Comment:    
						This is a camera UI for FlTk OpenGL Applications.

	 
						An arcball is a user interface for rotating an object 
						around its very useful for looking around the world.

						The actual mathematics to implement it are elegant, 
						but beyond the scope of CS559. This example code is 
						provided for you to use
						without having to worry about the details of 
						how it works.

     Note:
						1.	A quickly hacked together implementation of ArcBall, 
							with lots of bits lifted from Ken Shoemake's original 
							source in Graphics Gems	made into a nice C++ thing
						2.	It is simplified a lot - the controller is always 
						   at the origin,
						3.	It has a fixed radius, it doesn't have constraints

						4.	Added the double right click and the mousewheel - 
							to make a much	better UI.

					   5. the "ball" also stores all of the other camera 
							parameters (position, FoV)

						6. We take over the right mouse button - pass us your 
							events, and we'll take the ones we want.
						7. the ALT button lets you do panning
							double right click resets the arcball if you get lost

						To use it:
						1) instantiate it in your Fl_Gl_Window class
						2) call setup in the constructor of your window class
						3) call its handle method inside of your handle method
						4) use its SetProjection method when you need to set the 
							camera (like when drawing)

     Platform:    Visio Studio.Net 2003 (converted to 2005)

*************************************************************************/
#include "ArcBallCam.H"

#include <glad/glad.h>

#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <math.h>
#include "../GameWindow.h"

using namespace std;

//**************************************************************************
//
// * Constructor
//==========================================================================
ArcBallCam::
ArcBallCam() 
	:   fieldOfView(40),
		eyeX(0), eyeY(0), eyeZ(20),
		initEyeZ(20), 
		mode(None), 
		panX(0), panY(0),
		isx(0), isy(0), isz(0)
//==========================================================================
{
}

//**************************************************************************
//
// * really do the setup stuff, once you have the window
//==========================================================================
void ArcBallCam::
setup(float _fieldOfView, float _eyeZ,
	   float _isx, float _isy, float _isz)
//==========================================================================
{
	// set up the basic information
	fieldOfView = _fieldOfView;
	eyeZ			= _eyeZ;
	initEyeZ		= _eyeZ;
	eyeX			= 0;
	eyeY			= 0;
	isx			= _isx;
	isy			= _isy;
	isz			= _isz;


	reset();
	spin(isx,isy,isz);
}

glm::mat4 ArcBallCam::getPerspectiveMatrix() const {
    double f = 1/tan(fieldOfView / 360.0 * 3.141519265358979);
    double aspect = ((double) GameWindow::magic->getSize().x) / ((double) GameWindow::magic->getSize().y);

    return glm::mat4(
            f / aspect, 0, 0, 0,
            0, f, 0, 0,
            0, 0, -1.00020002f, -1,
            0, 0, -0.200020002f, 0
    );
}

glm::mat4 ArcBallCam::getModelViewMatrix() const {
    glm::mat4 ModelView = glm::mat4(1);
    ModelView = glm::translate(ModelView, glm::vec3(-eyeX, -eyeY, -eyeZ));

    Quat qAll = now * start;
    qAll = qAll.conjugate();
    glm::mat4 q = qAll.toGLMMatrix();

    ModelView = ModelView * q;
    return ModelView;
}

//todo eyePosition
void ArcBallCam::getEyePosition(glm::vec4& eyePosition) const {
    Quat qAll = now * start;
    glm::mat4 m = qAll.toGLMMatrix();

    eyePosition = glm::vec4(eyeX, eyeY, eyeZ, 1.0);
    eyePosition = m * eyePosition;
}

//**************************************************************************
//
// * Handle the event happen to this camera
//==========================================================================
int ArcBallCam::
handle(sf::Event e)
//==========================================================================
{
    switch (e.type) {
        case sf::Event::MouseWheelMoved:
            if(abs(e.mouseWheel.delta) < 1) break;
            eyeZ *= (e.mouseWheel.delta < 0) ? 1.1f : 1/1.1f;
            return 1;
        case sf::Event::MouseButtonPressed:
            mode = None;
            // right mouse button down
            if (e.mouseButton.button == sf::Mouse::Right){
                float x, y;
                getMouseNDC(x,y);
                // Compute the mouse position
                down(x, y);
                // Set up the mode
                mode = sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) ? Pan : Rotate;
                return 1;
            }
            break;
        case sf::Event::MouseButtonReleased:
            if (mode != None) {
                mode = None;
                return 1;
            }
            break;
        case sf::Event::MouseMoved:
            if(mode != None) { // we're taking the drags
                float x,y;
                getMouseNDC(x,y);
                computeNow(x,y);
                return 1;
            }
            break;
        default:
            break;
    }
	return 0;
}

//**************************************************************************
//
// * Get the mouse in NDC
//==========================================================================
void ArcBallCam::
getMouseNDC(float& x, float& y)
//==========================================================================
{

	// notice, we put everything into doubles so we can do the math
	float mx = (float) sf::Mouse::getPosition(*((sf::Window*)GameWindow::magic)).x;	// remeber where the mouse went down
	float my = (float) sf::Mouse::getPosition(*((sf::Window*)GameWindow::magic)).y;

	// we will assume that the viewport is the same as the window size
    float wd = GameWindow::magic->getSize().x;
    float hd = GameWindow::magic->getSize().y;

	// remember that FlTk has Y going the wrong way!
	my = hd-my;

	x = (mx / wd) * 2.0f - 1.f;
	y = (my / hd) * 2.0f - 1.f;
}

//**************************************************************************
//
// * When the mouse goes down, remember where. also, clear out the now
//   position by putting it into start
//==========================================================================
void ArcBallCam::
down(const float x, const float y)
//==========================================================================
{
	start = now * start;
	now = Quat();		// identity

	downX = x;
	downY = y;

	panX = 0;
	panY = 0;
}

//**************************************************************************
//
// * Reset the camera's control related parameters
//==========================================================================
void ArcBallCam::
reset()
//==========================================================================
{
	start.x = start.y = start.z = 0; start.w = 1;

	now.x = now.y = now.z = 0; now.w = 1;
}

//**************************************************************************
//
// * 
//==========================================================================
void ArcBallCam::
spin(float x, float y, float z)
//==========================================================================
{
	// printf("\nstart was %g %g %g %g\n",start.x,start.y,start.z,start.w);
	// first, get rid of anything cached
	start = now * start;
	now = Quat();

	float iw = x*x + y*y + z*z;
	if (iw<1)
		iw = sqrt(1-iw);
	else
		iw = 0;
	Quat newq(x,y,z,iw);

	newq.renorm();
	start = newq * start;
	// printf(" (no norm) %g %g %g %g\n",start.x,start.y,start.z,start.w);

	start.renorm();
	// printf("start is %g %g %g %g\n",start.x,start.y,start.z,start.w);
}

//**************************************************************************
//
// * a helper - figure out where in XYZ a mouse down goes
// assumes sphere of unit radius
//==========================================================================
static void onUnitSphere(const float mx, const float my,
								float& x, float& y, float& z)
//==========================================================================
{
	x = mx;		// should divide radius
	y = my;
	float mag = x*x + y*y;
	if (mag > 1.0f) {
		float scale = 1.0f / ((float) sqrt(mag));
		x *= scale;
		y *= scale;
		z = 0;
	} else {
		z = (float) sqrt(1 - mag);
	}
}

//**************************************************************************
//
// * 
//==========================================================================
void ArcBallCam::
computeNow(const float nowX, const float nowY)
//==========================================================================
{
	if (mode==Rotate) {
		float dx,dy,dz;
		float mx,my,mz;
		onUnitSphere(downX, downY, dx, dy, dz);
		onUnitSphere(nowX, nowY, mx, my, mz);

		// here we compute the quaternion between these two points
		now.x = dy*mz - dz*my;
		now.y = dz*mx - dx*mz;
		now.z = dx*my - dy*mx;
		now.w = dx*mx + dy*my + dz*mz;

		now.renorm();		// just in case...
	}
	else if (mode==Pan) {
		float dx = (nowX-downX) * eyeZ;
		float dy = (nowY-downY) * eyeZ;

		eyeX += panX - dx;
		eyeY += panY - dy;
		panX = dx;
		panY = dy;
	}
}


//*****************************************************************************
//
// Minimal Quaternion Class - if you don't know what a quaternion is, don't
// worry. if you do know what a quaternion is, you probably want a more complete
// implementation
//
//*****************************************************************************

//**************************************************************************
//
// * Set up constructor
//==========================================================================
Quat::
Quat(float ix, float iy, float iz, float iw) 
	:  x(ix), y(iy), z(iz), w(iw)
//==========================================================================
{
}

//**************************************************************************
//
// * Default constructor
//==========================================================================
Quat::
Quat() 
	:  x(0), y(0), z(0), w(1)
//==========================================================================
{
}

//**************************************************************************
//
// * Copy constructor
//==========================================================================
Quat::
Quat(const Quat& q) 
	:  x(q.x), y(q.y), z(q.z), w(q.w)
//==========================================================================
{
}

//**************************************************************************
//
// * Renormalize, in case things got messed up
//==========================================================================
void Quat::
renorm()
//==========================================================================
{
	float Nq = 1.f / (float) sqrt(x*x + y*y + z*z + w*w);
	x *= Nq;
	y *= Nq;
	z *= Nq;
	w *= Nq;
}

glm::mat4 Quat::toGLMMatrix() const {
    float Nq = x*x + y*y + z*z + w*w;
    float s = (Nq > 0.f) ? (2.0f / Nq) : 0.f;
    float xs = x*s,	      ys = y*s,	  zs = z*s;
    float wx = w*xs,	  wy = w*ys,  wz = w*zs;
    float xx = x*xs,	  xy = x*ys,  xz = x*zs;
    float yy = y*ys,	  yz = y*zs,  zz = z*zs;

    return glm::mat4(
            1.0f - (yy + zz), xy - wz, xz + wy, 0.0f,
            xy + wz, 1.0f - (xx + zz), yz - wx, 0.0f,
            xz - wy, yz + wx, 1.0f - (xx + yy), 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
            );
}

//**************************************************************************
//
// * Find the conjugate of the quaternion
//==========================================================================
Quat Quat::
conjugate() const
//==========================================================================
{
  return Quat(-x,-y,-z,w);
}

//**************************************************************************
//
// * 
//==========================================================================
Quat Quat::
operator* (const Quat& qR) const
//==========================================================================
{
	Quat qq;
	qq.w = w*qR.w - x*qR.x - y*qR.y - z*qR.z;
	qq.x = w*qR.x + x*qR.w + y*qR.z - z*qR.y;
	qq.y = w*qR.y + y*qR.w + z*qR.x - x*qR.z;
	qq.z = w*qR.z + z*qR.w + x*qR.y - y*qR.x;
	return (qq);
}
