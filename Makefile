all:
	gcc Main/main.c Labirinto/labirinto.c ModoHistoria/historia.h GeradorDeLabirintos/gerador.c ListaCaminhos/listaCaminhos.c Cores/cores.c -o Main/main -g
run:
	./Main/main
