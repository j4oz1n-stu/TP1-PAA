all:
	gcc main.c Labirinto/labirinto.c Caminhos/caminhos.c Cores/cores.c -o programa
run:
	./programa
