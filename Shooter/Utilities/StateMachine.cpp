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
	newState = std::shared_ptr<GameState>(s);
	flag = Flag::ADD;
}
void StateMachine::replaceState(GameState* s)
{
	newState = std::shared_ptr<GameState>(s);
	flag = Flag::REPLACE;
}
void StateMachine::removeState() { flag = Flag::REMOVE; }
void StateMachine::updateState()
{
	switch (flag)
	{
	case Flag::ADD:
		states.push(newState);
		break;

	case Flag::REMOVE:
		states.pop();
		break;

	case Flag::REPLACE:
		states.pop();
		states.push(newState);
		break;

	default:
		break;
	}

	flag = Flag::CONTINUE;
}
