CCo = g++ -I include -o
DCCc = g++ -I src/dataplane/include -c
CCCc = g++ -I src/controlplane/include -c
UCCc = g++ -I src/user/include -c
PCCc = g++ -I src/simplep4/include -c
WARNINGS = -Wno-deprecated
LEX = lex -l -o
YACC = yacc -d -o


all: main

main: src/dataplane/src/dataplane.cc src/controlplane/src/controlplane.cc src/main.cc dataplane controlplane userControlplane compile
	$(CCo) bin/main src/main.cc dataplane.o controlplane.o userControlplane.o compile.o

dataplane: src/dataplane/src/dataplane.cc
	$(DCCc) src/dataplane/src/dataplane.cc

controlplane: src/controlplane/src/controlplane.cc
	$(CCCc) src/controlplane/src/controlplane.cc 

userControlplane: src/user/src/userControlplane.cc 
	$(UCCc) src/user/src/userControlplane.cc 

compile: src/simplep4/src/compile.cc
	$(PCCc) src/simplep4/src/compile.cc


	
clean:
	rm -f main
	rm -f dataplane.o
	rm -f controlplane.o
	rm -f userControlplane.o
	rm -f compile.o

