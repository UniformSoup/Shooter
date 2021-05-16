#pragma once

#include <stack>

/* Simple StateMachine Class */
template <typename T>
class StateMachine
{
	std::stack<std::shared_ptr<T>> states;
	std::shared_ptr<T> newState = nullptr;
	enum class Flag { CONTINUE, ADD, REMOVE, REPLACE } flag = Flag::CONTINUE;

public:
	size_t size() const { return states.size(); }
	T& getCurrentState() const { return *states.top(); }
	void updateState();
	void removeState() { flag = Flag::REMOVE; };
	void addState(T* s)
	{
		newState = std::shared_ptr<T>(s);
		flag = Flag::ADD;
	}
	void replaceState(T* s)
	{
		newState = std::shared_ptr<T>(s);
		flag = Flag::REPLACE;
	}
};

/* can throw if you try to remove without checking stack size */
template <typename T>
void StateMachine<T>::updateState()
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
	default: break;
	}

	flag = Flag::CONTINUE;
}
