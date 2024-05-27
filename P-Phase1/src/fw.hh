#ifndef _FW_HH_
#define _FW_HH_

#include "p.hh"

class Forward : public Player {
public:
	Forward(string n) : Player(n) { position = "fw"; }
};

typedef shared_ptr<Forward> ForwardPtr;

#endif