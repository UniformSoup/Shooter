#pragma once

#include <stack>
#include <exception>

#include "GameState.h"

/*Simple StateMachine Class*/
class StateMachine
{
	std::stack<GameState*> states;
	GameState* newState = nullptr;
	enum class Flag { CONTINUE, ADD, REMOVE, REPLACE } flag = Flag::CONTINUE;

public:
	~StateMachine();
	size_t size() const;
	GameState& getCurrentState() const;
	void addState(GameState* s);
	void replaceState(GameState* s);
	void removeState();
	void updateState();
};

