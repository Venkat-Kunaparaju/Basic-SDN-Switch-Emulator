d = src/dataplane/src/dataplane.cc
cont = src/controlplane/src/controlplane.cc
user = src/user/src/userControlplane.cc
comp = src/simplep4/src/compile.cc

CCo = g++ -I include -o

DCCc = g++ -I src/dataplane/include -c $(d) -o 
CCCc = g++ -I src/controlplane/include -c $(cont) -o
UCCc = g++ -I src/user/include -c $(user) -o
PCCc = g++ -I src/simplep4/include -c $(comp) -o



WARNINGS = -Wno-deprecated
LEX = lex -l -o
YACC = yacc -d -o


all: main

main: clean directory src/dataplane/src/dataplane.cc src/controlplane/src/controlplane.cc src/main.cc dataplane controlplane userControlplane compile
	$(CCo) bin/main src/main.cc bin/dataplane.o bin/controlplane.o bin/userControlplane.o bin/compile.o

dataplane: $(d)
	$(DCCc) bin/dataplane.o

controlplane: $(cont)
	$(CCCc) bin/controlplane.o

userControlplane: $(user)
	$(UCCc) bin/userControlplane.o

compile: $(comp)
	$(PCCc) bin/compile.o

directory:
	mkdir bin

clean:
	rm -r bin

