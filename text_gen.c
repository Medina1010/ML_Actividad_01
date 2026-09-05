#define FORMATER_IMPL
#include "formater.h"
#include "stdlib.h"

typedef struct {
	int count;
	int frec[256];
} text_stats;

text_stats get_text_stats_from_str(char* s) {
	text_stats ts = {0}; ts.count = strlen(s);
	for (int i = 0; i < ts.count; i++) {
		if (s[i] >= 0x80) continue;
		ts.frec[(int)s[i]]++;
	}
	return ts;
}

void sort(int* values, int* indexes, int count) {
	int aux;
	for (int i = 0; i < count; i++) indexes[i] = i;
	for (int i = 0; i < count; i++)
		for(int j = 0; j < i; j++)
			if (values[indexes[j]] < values[indexes[j+1]]) {
				aux = indexes[j];
				indexes[j] = indexes[j + 1];
				indexes[j + 1] = aux;
			}
			
}

char get_random_character(text_stats ts) {
	int number = rand() % (ts.count);
	char i = 0;
	while (1) {
		if (ts.frec[i] >= number) return i;
		else number -= ts.frec[i++];
	}
}

int main (int argc, char** argv) {
	chars cs = {0};
	chars_from_file(&cs, argv[1]);
	text_stats ts = get_text_stats_from_str(cs.data);
	free(cs.data);

	char str[256];
	int sorting[256];
	sort(ts.frec, sorting, 256);
	sprintf(str, "%s.dat", argv[1]);
	FILE* f = fopen(str, "w");
	for (int i = 0; i < 256; i++) {
		switch (sorting[i]) {
			case 9: sprintf(str, "[tab]");break;
			case 32: sprintf(str, "[sp]");break;
			case 27: sprintf(str, "[esc]");break;
			case 10: sprintf(str, "[lf]");break;
			case 13: sprintf(str, "[cr]");break;
			default: sprintf(str, "%c", sorting[i]);
		}
		if (ts.frec[sorting[i]]) {
			fprintf(f, "%s %d\n",
				str,
				ts.frec[sorting[i]]);
		}
	}
	fclose(f);
	
	char generated_text[512];
	for (int i = 0; i < 512 - 1; i++) {
		generated_text[i] = get_random_character(ts);
	}
	generated_text[512-1] = 0;
	str_to_file(generated_text, "generated_text.md");

	return 0;
}
