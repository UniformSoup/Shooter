#include "StateMachine.h"

size_t StateMachine::size() const
{
	return states.size();
}
GameState& StateMachine::getCurrentState() const 
{
	return *states.top();
}
void StateMachine::addState(GameState* s)
{
	newState = s;
	flag = Flag::ADD;
}
void StateMachine::replaceState(GameState* s)
{
	newState = s;
	flag = Flag::REPLACE;
}
void StateMachine::removeState() { flag = Flag::REMOVE; }
void StateMachine::updateState()
{
	if (flag == Flag::ADD)
		states.push(newState);
	else if (flag == Flag::REMOVE)
	{
		delete states.top();
		states.pop();
	}
	else if (flag == Flag::REPLACE)
	{
		delete states.top();
		states.pop(); states.push(newState);
	}

	flag = Flag::CONTINUE;
	newState = nullptr;
}

StateMachine::~StateMachine()
{
	while (!states.empty())
	{
		delete states.top();
		states.pop();
	}
}
