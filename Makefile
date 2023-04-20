CCo = g++ -I include -o
CCc = g++ -c
WARNINGS = -Wno-deprecated


all: controlplane dataplane 

dataplane: src/dataplane/src/dataplane.cc
	$(CCo) dataplane src/dataplane/src/dataplane.cc

controlplane: src/controlplane/src/controlplane.cc
	$(CCo) controlplane src/controlplane/src/controlplane.cc

	
clean:
	rm -f dataplane
	rm -f controlplane

