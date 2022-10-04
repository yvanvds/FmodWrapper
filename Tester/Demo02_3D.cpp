

#include "Demo02_3D.h"
#include <iostream>
#include <iomanip>

/* 3D:

This demo is about 3D positioning. It's a bit clumsy to do in a
little console demo. Most important is the member function setPosition,
and the helper object YSE::Pos which holds xyz coordinates.

*/


Demo3D::Demo3D()
{
	// load a sound in memory and get a pointer to it
	sound1 = FW::Sounds().create("../testResources/drone.ogg", true, 1, false);
	sound2 = FW::Sounds().create("../testResources/kick.ogg", true, 1, false);

	sound1->doppler(1.0f);
	sound2->doppler(1.0f);
	
	sound1->play();
	sound2->play();

	selectedObject = 1;
	Reset();

	SetTitle("3D Sound Movement");

	AddAction('1', "Select Drone Sound", std::bind(&Demo3D::SelectSound1, this));
	AddAction('2', "Select Kick Sound", std::bind(&Demo3D::SelectSound2, this));
	AddAction('3', "Select Listener", std::bind(&Demo3D::SelectListener, this));
	AddAction('a', "Move Selected Left", std::bind(&Demo3D::MoveObjectLeft, this));
	AddAction('s', "Move Selected Back", std::bind(&Demo3D::MoveObjectBack, this));
	AddAction('d', "Move Selected Right", std::bind(&Demo3D::MoveObjectRight, this));
	AddAction('w', "Move Selected Forward", std::bind(&Demo3D::MoveObjectForward, this));
	AddAction('r', "Reset All Positions", std::bind(&Demo3D::Reset, this));
}

void Demo3D::ExplainDemo()
{
	std::cout << "This demonstrates how sounds and the listener can be moved in 3D." << std::endl;
	std::cout << "Initial positions (xyz) are:" << std::endl;
	std::cout << "Listener:  0 / 0 / 0" << std::endl;
	std::cout << "Sound 1 : -3 / 0 / 3" << std::endl;
	std::cout << "Sound 2 :  3 / 0 / 3" << std::endl;
	std::cout << std::endl;
}

void Demo3D::ShowStatus() {
	const FW::Vector & listenerPos = FW::Listener().pos();
	const FW::Vector& sound1Pos = sound1->pos();
	const FW::Vector& sound2Pos = sound2 -> pos();
	std::cout << std::endl;
	std::cout << std::fixed << std::setw(11) << std::setprecision(1) << std::setfill('0');
	std::cout << "Listener:\t" << listenerPos.x << "/\t" << listenerPos.y << "/\t" << listenerPos.z << std::endl;
	std::cout << "Sound 1 :\t" << sound1Pos.x << "/\t" << sound1Pos.y << "/\t" << sound1Pos.z << std::endl;
	std::cout << "Sound 2 :\t" << sound2Pos.x << "/\t" << sound2Pos.y << "/\t" << sound2Pos.z << std::endl;
}

void Demo3D::SelectSound1()
{
	selectedObject = 1;
}

void Demo3D::SelectSound2()
{
	selectedObject = 2;
}

void Demo3D::SelectListener()
{
	selectedObject = 3;
}

void Demo3D::MoveObjectLeft()
{
	moveObject(LEFT);
}

void Demo3D::MoveObjectRight()
{
	moveObject(RIGHT);
}

void Demo3D::MoveObjectForward()
{
	moveObject(FORWARD);
}

void Demo3D::MoveObjectBack()
{
	moveObject(BACKWARD);
}

void Demo3D::Reset()
{
	// FW has a very flexible vector class built in
	FW::Vector pos(0.f, 0.f, 0.f);
	FW::Vector forward(0.f, 0.f, 1.f); 
	FW::Vector up(0.f, 1.f, 0.f);
	FW::Listener().move(pos, forward, up);
	
	sound1->pos(FW::Vector(-3.f,0.f,3.f));
	sound2->pos(FW::Vector(3.f,0.f,3.f));
}

void Demo3D::moveObject(direction d) {
	if (selectedObject < 3) {
		FW::sound * s;
		if (selectedObject == 1) s = sound1;
		else s = sound2;

		FW::Vector pos = s->pos();
		switch (d) {
			case FORWARD: pos.z += 0.5f; s->pos(pos); break;
			case BACKWARD: pos.z -= 0.5f; s->pos(pos); break;
			case LEFT: pos.x -= 0.5f; s->pos(pos); break;
			case RIGHT: pos.x += 0.5f; s->pos(pos); break;
		}
	}
	else {
		// you do not have to create the listener object, it's already there
		FW::Vector pos = FW::Listener().pos();
		FW::Vector forward(0.f, 0.f, 1.f); // must have unit length of 1
		FW::Vector up(0.f, 1.f, 0.f); // must have unit length of 1
		switch (d) {
			case FORWARD: pos.z += 0.5f; FW::Listener().move(pos, forward, up); break;
			case BACKWARD: pos.z -= 0.5f; FW::Listener().move(pos, forward, up); break;
			case LEFT: pos.x -= 0.5f; FW::Listener().move(pos, forward, up); break;
			case RIGHT: pos.x += 0.5f; FW::Listener().move(pos, forward, up); break;
		}
	}
}
