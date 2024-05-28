#ifndef _MD_HH_
#define _MD_HH_

#include "p.hh"

class Midfielder : public Player {
public:
	Midfielder(string n) : Player(n) { position = "md"; }
};

typedef shared_ptr<Midfielder> MidfielderPtr;

#endif