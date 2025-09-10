import matplotlib.pyplot as plt
import numpy as np
from matplotlib.collections import LineCollection
import matplotlib.cm as cm

# Lê o arquivo da espiral
with open("output/espiral.out", "r") as f:
    linhas = [linha.strip() for linha in f if linha.strip()]

# Converte para matriz
matriz = np.array([list(map(int, linha.split())) for linha in linhas])
n, m = matriz.shape

# Cria dicionário número -> posição
posicoes = {}
for i in range(n):
    for j in range(m):
        posicoes[matriz[i, j]] = (j, n - 1 - i)  # inverter eixo y

# Extrai caminho na ordem
max_val = matriz.max()
xs = np.array([posicoes[i][0] for i in range(1, max_val + 1)])
ys = np.array([posicoes[i][1] for i in range(1, max_val + 1)])

# Cria segmentos para LineCollection
points = np.array([xs, ys]).T.reshape(-1, 1, 2)
segments = np.concatenate([points[:-1], points[1:]], axis=1)

# Normaliza cores de 0 a 1
colors = np.linspace(0, 1, len(segments))
lc = LineCollection(segments, cmap='plasma', norm=plt.Normalize(0, 1))
lc.set_array(colors)
lc.set_linewidth(2)

# Figura dinâmica baseada no tamanho da matriz
cell_size = 1
plt.figure(figsize=(cell_size*m, cell_size*n))
plt.gca().add_collection(lc)

# Adiciona círculos nos pontos (opcional)
plt.scatter(xs, ys, c='black', s=20, zorder=5)

# Adiciona números dentro das casas (opcional)
for i in range(1, max_val + 1):
    x, y = posicoes[i]
    plt.text(x, y, str(i), ha='center', va='center', fontsize=max(6, 12 - max(n, m)//2), color='white')

# Configurações do tabuleiro
plt.xlim(-0.5, m-0.5)
plt.ylim(-0.5, n-0.5)
plt.xticks(range(m))
plt.yticks(range(n))
plt.grid(True)
plt.gca().set_aspect('equal', adjustable='box')
plt.title("Espiral com gradiente de cores")
plt.colorbar(lc, label="Progresso da espiral")

plt.show()
