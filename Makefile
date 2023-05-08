CCo = g++ -I include -o
DCCc = g++ -I src/dataplane/include -c
CCCc = g++ -I src/controlplane/include -c
WARNINGS = -Wno-deprecated


all: main

main: src/dataplane/src/dataplane.cc src/controlplane/src/controlplane.cc src/main.cc dataplane controlplane
	$(CCo) main src/main.cc dataplane.o controlplane.o

dataplane: src/dataplane/src/dataplane.cc
	$(DCCc) src/dataplane/src/dataplane.cc

controlplane: src/controlplane/src/controlplane.cc
	$(CCCc) src/controlplane/src/controlplane.cc

	
clean:
	rm -f main
	rm -f dataplane.o
	rm -f controlplane.o

