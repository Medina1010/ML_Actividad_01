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
		if (s[i] < 'a') continue;
		if (s[i] > 'z') continue;
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
	// Leer archivo y generar estadisticas
	chars cs = {0};
	chars_from_file(&cs, argv[1]);
	text_stats ts = get_text_stats_from_str(cs.data);

	// formatear mensaje para compartir a compartir con compañeros
	chars csm = {0};
	for (size_t i = 0; i < 1024*16; i++) {
		char v = cs.data[i];
		if(v > 255) continue;
		if(v >= 'a' && v <= 'z')
			chars_append(&csm, v);
	}

	chars_append(&csm, 0);
	str_to_file(csm.data, "mensaje.txt");

	free(cs.data);
	free(csm.data);

	// guardar estadisticas para graficar histograma y barra de chances

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

	// generar texto aleatorio
	
	char generated_text[512];
	for (int i = 0; i < 512 - 1; i++) {
		generated_text[i] = get_random_character(ts);
	}
	generated_text[512-1] = 0;
	str_to_file(generated_text, "generated_text.txt");

	// encriptar mensaje

	char suffle[] = "qwertyuiopasdfghjklzxcvbnm";
	chars mensaje_f = {0};
	chars_from_file(&mensaje_f, "mensaje.txt");
	char* mensaje = mensaje_f.data;
	char encripted_mensaje[strlen(mensaje) + 1];
	encripted_mensaje[strlen(mensaje)]=0;
	for (size_t i = 0; i < strlen(mensaje); i++)
		encripted_mensaje[i] = suffle[mensaje[i] - 'a'];
	str_to_file(encripted_mensaje, "mensaje_encriptado.txt");

	// generar estadisticas del mensaje de nuestros compeñeros

	chars mensaje_e_f = {0};
	chars_from_file(&mensaje_e_f, "mensaje_cuartas.txt");
	//chars_from_file(&mensaje_e_f, "mensaje_encriptado.txt");
	char* mensaje_cuartas = mensaje_e_f.data;
	text_stats tse = get_text_stats_from_str(mensaje_cuartas);

	int sortinge[256];
	sort(tse.frec, sortinge, 256);

	// comparar estadisticas para emparejar caracteres y desencriptar el mensaje y guardarlo

	char mensaje_cuartas_desencriptado[strlen(mensaje_cuartas)+1];
	mensaje_cuartas_desencriptado[strlen(mensaje_cuartas)] = 0;

	for (size_t i = 0; i < strlen(mensaje_cuartas); i++) {
		size_t j = 0;
		while ( mensaje_cuartas[i] != sortinge[j]) j++;
		mensaje_cuartas_desencriptado[i] = sorting[j];
	}

	str_to_file(mensaje_cuartas_desencriptado, "mensaje_desencriptado.txt");

	return 0;
}
