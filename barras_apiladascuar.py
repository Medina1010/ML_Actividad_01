import pandas as pd
import matplotlib.pyplot as plt

# 1. Cargar el archivo .dat separado por espacios
df = pd.read_csv('mensaje_cuartas.txt.dat', sep=r'\s+', header=None, names=['valor', 'frecuencia'], quoting=3)

# 2. Configurar la figura
fig, ax = plt.subplots(figsize=(12, 4))

# 3. Dibujar las barras apiladas horizontalmente
left = 0
for idx, row in df.iterrows():
    ax.barh(y=0, width=row['frecuencia'], left=left, label=str(row['valor']))
    left += row['frecuencia']

# 4. Personalizar el estilo
ax.set_title("Barra de chances", fontsize=12, pad=50)
ax.set_yticks([])
ax.set_xlim(0, left)
ax.grid(axis='x', linestyle=':', alpha=0.6)

# Leyenda superior en múltiples columnas
ax.legend(ncols=22, loc='lower center', bbox_to_anchor=(0.5, 1.02), frameon=False, fontsize=7)

#plt.tight_layout()

# 5. Guardar la imagen en formato PNG
plt.savefig('grafico_chances_cuar.png', dpi=300, bbox_inches='tight')
