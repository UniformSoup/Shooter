#pragma once
#include "Timing.h"
#include "Camera.h"
#include "Shader.h"
#include "Window.h"
#include "ResourceManager.h"
#include "StateMachine.h"

struct Data
{
	Window win;
	Camera cam;
	ResourceManager<Shader> shaders;
};

class GameState
{
protected: // anything that all of the differenet states need (ie a single font, or options) can be shared here.
	StateMachine<GameState>* const stateMachine;
	Data * const pdata;

	GameState(Data* const data, StateMachine<GameState>* const machine) : pdata(data), stateMachine(machine) {};
	GameState(GameState* last) : GameState(last->pdata, last->stateMachine) {};

public:
	virtual void update(const Timing::duration& elapsed) = 0;
	virtual void render() = 0;
};