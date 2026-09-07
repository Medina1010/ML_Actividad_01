#include <stdio.h>
#include <stdlib.h>

#define PWD "ANALYSIS"

void cmd (char *prompt) {
	printf(PWD" > %s\n", prompt);
	if (system(prompt)) exit(1);
}

int main (int argc, char** argv) {
	// recompile
	if (argc == 1) {
		cmd("gcc -o bld bld.c");
		cmd("./bld R");
		exit(0);
	}
	// ---------
	cmd("gcc -Wall -Wextra -lm -o text_gen text_gen.c");
	cmd("./text_gen mensaje_cuartas.txt");
	cmd("./text_gen odyssey.txt");
	cmd("gnuplot histograma.gp");
	cmd("python barras_apiladas.py");
	cmd("gnuplot histogramacuar.gp");
	cmd("python barras_apiladascuar.py");
	return 0;
}
