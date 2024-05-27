#ifndef _GK_HH_
#define _GK_HH_

#include "p.hh"

class Goalkeeper : public Player {
public:
	Goalkeeper(string n) : Player(n) { position = "gk"; }
};

typedef shared_ptr<Goalkeeper> GoalkeeperPtr;

#endif