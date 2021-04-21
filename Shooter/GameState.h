#pragma once
#include "Timing.h"

struct Data; // Forward Declaration to avoid including Game.h circularly

class GameState
{
protected: // anything that all of the differenet states need (ie a single font, or options) can be shared here.
	Data * const pdata;
	GameState(Data* const data) : pdata(data) {};

public:
	virtual void update(const Timing::duration& elapsed) = 0;
	virtual void render() = 0;
};