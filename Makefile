d = src/dataplane/src/dataplane.cc
cont = src/controlplane/src/controlplane.cc
user = src/user/src/userControlplane.cc
comp = src/simplep4/src/compile.cc
l = src/simplep4/src/compile.l
y = src/simplep4/src/compile.y

CCo = g++ -I include -o
CCc = g++ -c

DCCc = g++ -I src/dataplane/include -c $(d) -o 
CCCc = g++ -I src/controlplane/include -c $(cont) -o
UCCc = g++ -I src/user/include -c $(user) -o
PCCc = g++ -I src/simplep4/include -c $(comp) -o

LCCc = g++ -I src/simplep4/include -I build -c


WARNINGS = -Wno-deprecated
LEX = lex -l -o
YACC = yacc -d -o


all: main

main: clean directory src/dataplane/src/dataplane.cc src/controlplane/src/controlplane.cc src/main.cc dataplane controlplane userControlplane compile yacc lex
	$(CCo) bin/main src/main.cc bin/dataplane.o bin/controlplane.o bin/userControlplane.o bin/compile.o bin/yacc.o bin/lex.o 

dataplane: $(d)
	$(DCCc) bin/dataplane.o

controlplane: $(cont)
	$(CCCc) bin/controlplane.o

userControlplane: $(user)
	$(UCCc) bin/userControlplane.o

compile: $(comp)
	$(PCCc) bin/compile.o

lex: $(l)
	$(LEX) build/lex.yy.cc $(l)
	$(LCCc) build/lex.yy.cc -o bin/lex.o

yacc: $(y)
	$(YACC) build/y.tab.cc $(y)
	$(LCCc) build/y.tab.cc -o bin/yacc.o


directory:
	mkdir bin

clean:
	rm -r bin

