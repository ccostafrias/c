import matplotlib.pyplot as plt
import numpy as np

# Lê a matriz do arquivo
with open("saida.out", "r") as f:
    linhas = [linha.strip() for linha in f if linha.strip()]

matriz = np.array([list(map(int, linha.split())) for linha in linhas])
n = matriz.shape[0]

# Cria dicionário número → posição
posicoes = {}
for i in range(n):
    for j in range(n):
        # inverter y para plotar como matriz
        posicoes[matriz[i, j]] = (j, n - 1 - i)

# Extrai o caminho na ordem
xs = [posicoes[i][0] for i in range(1, n*n + 1)]
ys = [posicoes[i][1] for i in range(1, n*n + 1)]

# Define tamanho da figura baseado no tabuleiro
cell_size = 1  # 1 unidade por célula
plt.figure(figsize=(cell_size * n, cell_size * n))

# Desenha o caminho do cavalo
plt.plot(xs, ys, marker='o', linewidth=2, markersize=8, color='blue')

# Adiciona os números dentro das casas
for i in range(1, n*n + 1):
    x, y = posicoes[i]
    plt.text(x, y, str(i), color='white', ha='center', va='center', fontsize=max(6, 12 - n//2))

# Configurações do tabuleiro
plt.xlim(-0.5, n-0.5)
plt.ylim(-0.5, n-0.5)
plt.xticks(range(n))
plt.yticks(range(n))
plt.grid(True)
plt.gca().set_aspect('equal', adjustable='box')

plt.title(f"Caminho do Cavalo {n}x{n}")
plt.show()
