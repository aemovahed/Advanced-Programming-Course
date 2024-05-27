all: futballFantasy.out

futballFantasy.out: main.o master.o pp.o p.o t.o m.o totw.o w.o
	g++ --std=c++11 main.o master.o pp.o p.o t.o m.o totw.o w.o -o futballFantasy.out

main.o: main.cpp master.hh t.hh p.hh pp.hh w.hh m.hh df.hh gk.hh fw.hh md.hh
	g++ --std=c++11 -c main.cpp

master.o: master.cpp master.hh t.hh p.hh pp.hh w.hh m.hh df.hh gk.hh fw.hh md.hh
	g++ --std=c++11 -c master.cpp

pp.o: pp.cpp pp.hh
	g++ --std=c++11 -c pp.cpp

p.o: p.cpp p.hh pp.hh
	g++ --std=c++11 -c p.cpp

t.o: t.cpp t.hh p.hh pp.hh df.hh gk.hh fw.hh md.hh
	g++ --std=c++11 -c t.cpp

m.o: m.cpp m.hh t.hh p.hh pp.hh
	g++ --std=c++11 -c m.cpp

totw.o: totw.cpp totw.hh p.hh pp.hh
	g++ --std=c++11 -c totw.cpp

w.o: w.cpp w.hh m.hh t.hh p.hh pp.hh totw.hh df.hh gk.hh fw.hh md.hh
	g++ --std=c++11 -c w.cpp

clean:
	rm *.o futballFantasy.out