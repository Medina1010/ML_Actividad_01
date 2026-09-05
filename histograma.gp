
set terminal pngcairo size 1200,600 font "Arial,10"
set output "grafica_caracteres.png"

# Títulos y etiquetas
set title "Conteo de caracteres"
set xlabel "Caracter"
set ylabel "Número de repeticiones"

# Estilo de las barras (azul relleno)
set style fill solid 0.8 border -1
set boxwidth 0.6 absolute

# Opciones de cuadrícula y leyenda
set grid y
unset key

# Ajustar los rangos si es necesario
set yrange [0:*]

# Generar la gráfica usando la columna 1 para las etiquetas del eje X (xtic) y la columna 2 para la altura
plot "odyssey.txt.dat" using 2:xtic(1) with boxes lc rgb "#3366cc"

