#ifndef _DF_HH_
#define _DF_HH_

#include "p.hh"

class Defender : public Player {
public:
	Defender(string n) : Player(n) { position = "df"; }
};

typedef shared_ptr<Defender> DefenderPtr;

#endif