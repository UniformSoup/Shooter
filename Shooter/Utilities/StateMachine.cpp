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

/* can throw if you try to remove without checking stack size */
void StateMachine::updateState()
{
	switch (flag)
	{
	case Flag::REPLACE:
		states.pop(); // purposely bleed through here.
	case Flag::ADD:
		states.push(newState);
		newState = nullptr;
		// this is important,
		// so we are not holding on to something
		// that we are not using.
		break;

	case Flag::REMOVE:
		states.pop();
		break;

	default:
		break;
	}

	flag = Flag::CONTINUE;
}
