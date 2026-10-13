all:
	gcc Main/main.c Labirinto/labirinto.c Caminhos/caminhos.c Cores/cores.c -o Main/main -g
run:
	./Main/main
