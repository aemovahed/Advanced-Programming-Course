all: main

main: main.o system.o cm.o d.o dim.o dp.o drm.o m.o t.o tm.o
	g++ --std=c++11 main.o system.o cm.o d.o dim.o dp.o drm.o m.o t.o tm.o -o main

main.o: main.cpp system.hh m.hh d.hh drm.hh dp.hh t.hh tm.hh dim.hh cm.hh
	g++ --std=c++11 -c main.cpp

system.o: system.cpp system.hh m.hh d.hh drm.hh dp.hh t.hh tm.hh dim.hh cm.hh
	g++ --std=c++11 -c system.cpp

cm.o: cm.cpp cm.hh m.hh dp.hh
	g++ --std=c++11 -c cm.cpp

d.o: d.cpp d.hh m.hh drm.hh t.hh dp.hh 
	g++ --std=c++11 -c d.cpp

dim.o: dim.cpp dim.hh m.hh dp.hh
	g++ --std=c++11 -c dim.cpp

dp.o: dp.cpp dp.hh
	g++ --std=c++11 -c dp.cpp

drm.o: drm.cpp drm.hh m.hh dp.hh
	g++ --std=c++11 -c drm.cpp

m.o: m.cpp m.hh dp.hh
	g++ --std=c++11 -c m.cpp

t.o: t.cpp t.hh
	g++ --std=c++11 -c t.cpp

tm.o: tm.cpp tm.hh m.hh dp.hh
	g++ --std=c++11 -c tm.cpp

clean:
	rm *.o main