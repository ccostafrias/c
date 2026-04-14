#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

// Fila

typedef struct {
	int * a;
	int ini;
	int fim;
	int capacidade;
} Fila;

const int V = 5;

typedef struct s {
	int adj; // vértice adjacente
	struct s * prox; // próximo vértice adjacente
	int cia; // companhia aérea
	int id;

	// para Dijkstra:
	int peso; // peso da aresta
} No; // ADJACENCIA

typedef struct {
	No * inicio;
  int tipo;
  int flag; // 0 = não visitado, 1 = visitando, 2 = visitado
	int dist;

	// para Dijkstra
	int p; // 0 = não processado, 1 = processado
	int custo; // custo do caminho mais curto encontrado até agora
	int via; // vértice anterior no caminho mais curto encontrado até agora
} Vertice;

typedef enum { false, true } bool;
typedef enum { INDEF, AZUL, GOL, LATAM } cia;
typedef enum { primeiro, segundo, terceiro } tipo;
typedef enum { spam, mensagem, oferta } email;

// =======================
// == Fila
// =======================

Fila * inicializarFila(int cap) {
	Fila * fila = (Fila*) malloc(sizeof(Fila));

	fila-> a = (int*) malloc(cap * sizeof(int));
	fila->capacidade = cap;
	fila->ini = 0;
	fila->fim = 0;

	return fila;
}

int tamanhoFila(Fila * fila) {
	return fila->fim - fila->ini;
}

void inserirFila(Fila * fila, int value) {
	if (tamanhoFila(fila) >= fila->capacidade) return;

	int idx = fila->fim % fila->capacidade;
	fila->a[idx] = value;
	fila->fim++;
}

void removeFila(Fila * fila, int * elemento) {
	if (tamanhoFila(fila) <= 0) return;

	int idx = fila->ini % fila->capacidade;
	*elemento = fila->a[idx];
	fila->ini++;
}

void deletarFila(Fila * fila) {
	free(fila->a);
	free(fila);
}

// ========================
// == Lista
// ========================

void exibirLista(No * p) {
	bool first = true;

	while(p) {
		if (first) {
			first = false;
		} else {
			printf(" -> ");
		}
		printf("%d", p->adj);
		p = p->prox;
	}
	printf("\n");
}

void liberaLista(No * p) {
	if (!p) return;

	liberaLista(p->prox);
	free(p);
}

// ========================
// == Funções básicas
// ========================

void inicializar(Vertice * g, int v) {
	int i;
	for (i = 1; i <= v; i++) {
		g[i].inicio = NULL;
    g[i].flag = 0;
	}
}

void inicializarMatriz(int m[V][V]) {
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			m[i][j] = 0;
		}	
	}
}

void inicializarMatrizAerea(cia m[V][V]) {
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			m[i][j] = INDEF;
		}	
	}
}

bool existeAresta(Vertice * g, int v1, int v2) {
	No * p = g[v1].inicio;
	
	while (p) {
		if (p->adj == v2) return true;
		p = p->prox;
	}
	
	return false;
}

bool existeArestaMatriz(int m[V][V], int i, int j) {
	return m[i][j];
}

bool existeArestaMatrizAerea(cia m[V][V], int i, int j) {
	return m[i][j];
}

bool inserirAresta(Vertice * g, int v1, int v2, int peso, cia companhia) {
	if (existeAresta(g, v1,v2)) return false;
	
	No * novo = (No*) malloc(sizeof(No));
	novo->adj = v2;
	novo->peso = peso;
	novo->prox = g[v1].inicio;
	novo->cia = companhia;
	g[v1].inicio = novo;
	
	return true;
}

bool inserirArestaEmail(Vertice * g, int v1, int v2, email m) {
	if (existeAresta(g, v1,v2)) return false;
	
	No * novo = (No*) malloc(sizeof(No));
	novo->adj = v2;
	novo->prox = g[v1].inicio;
	novo->id = m;
	g[v1].inicio = novo;
	
	return true;
}

void inserirArestaMatriz(int m[V][V], int i, int j) {
	m[i][j] = 1;
}

void inserirArestaMatrizAerea(cia m[V][V], int i, int j, cia c) {
	m[i][j] = c;
}

bool deletaAresta(Vertice * g, int v1, int v2) {
	No * ant = NULL;
	No * p = g[v1].inicio;
	
	while (p) {
		if (p->adj == v2) break;
		ant = p;
		p = p->prox;
	}
	
	// não achamos v2
	if (!p) return false;
	
	if (ant) ant->prox = p->prox;
	else g[v1].inicio = p->prox;
	
	free(p);
	
	return true;
}

void deletaArestaMatriz(int m[V][V], int i, int j) {
	m[i][j] = 0;
}

void exibir(Vertice * g, char * nomeArquivo, int v) {
	char caminho[256];
	sprintf(caminho, "./build/dots/%s", nomeArquivo);
	sprintf(caminho, "%s.dot", caminho);

	FILE* f = fopen(caminho, "w");
	fprintf(f, "digraph G {\n");

	int i;
	for (i = 1; i <= v; i++) {
		printf("%d: ", i);
		No * p = g[i].inicio;

		if (p == NULL) {
			fprintf(f, "    %d;\n", i);
		}

		while (p) {
			printf("%d ", p->adj);
			fprintf(f, "    %d -> %d;\n", i, p->adj);
			p = p->prox;
		}

		printf("\n");
	}

	fprintf(f, "}\n");
	fclose(f);
}

void exibirMatriz(int m[V][V]) {
	for (int i = 0; i < V; i++) {
		int achou = false;
		for (int j = 0; j < V; j++) {
			int atual = m[i][j];

			if (atual) {
				if (!achou) {
					printf("%d: ", i);
					achou = true;
				}

				printf("%d ", j);
			}
		}	

		if (i != V-1 && achou) {
			printf("\n");
		}
		achou = false;
	}
	printf("\n");
}

void exibirMatrizAerea(cia m[V][V], char * nomeArquivo) {
	char caminho[256];
	sprintf(caminho, "./build/dots/%s", nomeArquivo);
	sprintf(caminho, "%s.dot", caminho);

	FILE* f = fopen(caminho, "w");
	fprintf(f, "digraph G {\n");

	for (int i = 0; i < V; i++) {
		int achou = false;
		for (int j = 0; j < V; j++) {
			int atual = m[i][j];

			if (atual != INDEF) {
				if (!achou) {
					printf("%d: ", i);
					achou = true;
				}

				printf("%d ", j);
				fprintf(f, "    %d -> %d;\n", i, j);
			}
		}	
		
		if (!achou) {
			printf("%d: ", i);
			fprintf(f, "    %d;\n", i);
		}

		if (i != V-1) {
			printf("\n");
		}

		achou = false;
	}

	printf("\n");
	fprintf(f, "}\n");
	fclose(f);
}


void zerarFlags(Vertice * g) {
  int i;
  for (i = 1; i <= V; i++) {
    g[i].flag = 0;
  }
}

void zerarFlagsMatriz(int flags[V]) {
	for (int i = 0; i < V; i++) {
		flags[i] = 0;
	}
}

void definirTipo(Vertice * g, int i, tipo t) {
  g[i].tipo = t;
}

// =========================
// == Operações com matrizes
// =========================

int grauSaida(int m[V][V], int linha) {
	int j; int grau = 0;
	
	// percorremos a linha, pulando de coluna em coluna
	for (j = 0; j < V; j++) {
		grau = grau + m[linha][j];
	}
	
	return grau;
}

int grauEntrada(int m[V][V], int coluna) {
	int i; int grau = 0;
	
	for (i = 0; i < V; i++) {
		grau = grau + m[i][coluna];
	}
	
	return grau;
}

// ==========================
// == Operações com grafos
// ==========================

bool subgrafo(Vertice * g1, Vertice * g2) {
	int i;
	for (i=1; i <= V; i++) {
		No * p = g2[i].inicio;
		while (p) {
			if (!existeAresta(g1, i, p->adj)) return false;
			p = p->prox;
		}
	}
	
	return true;
}

Vertice * CopiaTransposta(Vertice * g) {
	Vertice * r = (Vertice*) malloc((V+1) * sizeof(Vertice));
	inicializar(r, V);
	
	int i;
	for (i = 1; i <= V; i++) {
		No * p = g[i].inicio;
		while (p) {
			No * novo = (No*) malloc(sizeof(No));
			novo->adj = i;
			novo->prox = r[p->adj].inicio;
			r[p->adj].inicio = novo;
			p = p->prox;
		}
	}

	return r;
}

// ==========================
// == Busca em Profundidade
// ==========================


void soBuscaProfundamente(Vertice * g, int i) {
  // 1 = visitando
	g[i].flag = 1;
	No * p = g[i].inicio;
	
  // passa por cada adjacente de i
  // e chama recursivamente a busca para cada adjacente do adjacente
	while (p) {
    if (g[p->adj].flag == 0) {
			soBuscaProfundamente(g, p->adj);
		}
		
		p = p->prox;
	}
	
  // 2 = visitado
	g[i].flag = 2;
}

void buscaProfundidade(Vertice * g, int i, int j, bool * achou) {
	if (i == j) {
		*achou = true;
		return;
	}

  // 1 = visitando
	g[i].flag = 1;
	No * p = g[i].inicio;
	
  // passa por cada adjacente de i
  // e chama recursivamente a busca para cada adjacente do adjacente
	while (p) {
    if (g[p->adj].flag == 0) {
			buscaProfundidade(g, p->adj, j, achou);
			if (*achou) return;
		}
		
		p = p->prox;
	}
	
  // 2 = visitado
	g[i].flag = 2;
}

void buscaProfundidadeMatriz(int m[V][V], int i, int flag[V]) {
	flag[i] = 1;
	int j;

	for (j = 0; j < V; j++) {
		if (m[i][j] == 1 && flag[j] == 0) {
			buscaProfundidadeMatriz(m, j, flag);
		}
	}

	flag[i] = 2;
}

void passa_e_conta(Vertice * g, int i, int * count) {
  // 1 = visitando
	g[i].flag = 1;
	No * p = g[i].inicio;
	
  // passa por cada adjacente de i
  // e chama recursivamente a busca para cada adjacente do adjacente
	while (p) {
    if (g[p->adj].flag == 0) {
			passa_e_conta(g, p->adj, count);
		}
		
		p = p->prox;
	}
	
  // 2 = visitado
	g[i].flag = 2;
  *count = *count + 1;
}

// verifica se é conexo
bool ehConexo(Vertice *g) {
	zerarFlags(g);
	
	int count = 0;
	passa_e_conta(g, 1, &count);
	
	if (count != V) return false;

	count = 0;
	Vertice * gt = CopiaTransposta(g);
	passa_e_conta(gt, 1, &count);

	return count == V;
}

// Deteca ciclos e os printa
void achaCiclos(Vertice * g, int i) {
  // 1 = visitando
	g[i].flag = 1;
	No * p = g[i].inicio;
	
  // passa por cada adjacente de i
  // e chama recursivamente a busca para cada adjacente do adjacente
	while (p) {
    if (g[p->adj].flag == 1) {
			printf("Ciclo encontrado: %d->%d\n", i, p->adj);

		} else if (g[p->adj].flag == 0) {
			achaCiclos(g, p->adj);
		}
		
		p = p->prox;
	}
	
  // 2 = visitado
	g[i].flag = 2;  
}

// Conta quantos vértices do tipo 'tipox' estão conectados ao vértice 'i' (direta ou indiretamente)
void contaTipos(Vertice * g, int i, int tipox, int * count) {
	g[i].flag = 1; 
  if (g[i].tipo == tipox) *count = *count + 1;
	No * p = g[i].inicio;
	
	while(p) {
		if (g[p->adj].flag == 0) contaTipos(g, p->adj, tipox, count);
		p = p->prox;
	}
	
	g[i].flag = 2;
}

// retorna o vértice que pertence ao maior GRUPO, sendo um grupo um conjunto de vertices interligados
int maiorGrupo(Vertice * g, int * quant) {
	int maior = -1;
	int maiorQuant = 0;
	
	zerarFlags(g);
	
	int i;
	for (i = 1; i <= V; i++) {
		if (g[i].flag == 0) {
			int count = 0;
			passa_e_conta(g, i, &count);
			if (count > maiorQuant) {
				maiorQuant = count;
				*quant = count;
				maior = i;
			}
		}
	}
	
	return maior;
}

Vertice * matrizlista(int m[V][V]){
	Vertice * resp = (Vertice*) malloc(V * sizeof(Vertice));
	inicializar(resp, V);

	int i, j;
	for (i = 0; i < V; i++) {
		for (j = 0; j < V; j++) {
			if (m[i][j] == 1) {
				No * novo = (No*) malloc(sizeof(No));
				novo->adj = j;
				novo->prox = resp[i].inicio;
				resp[i].inicio = novo;
			}
		}
	}
}

void achaCaminho(Vertice * g, int v1, int v2, cia x, bool * achou) {
	if (*achou) return;

	if (v1 == v2) {
		*achou = true;
		return;
	}
	
	g[v1].flag = 1;
	No * p = g[v1].inicio;

	while(p) {
		if (g[p->adj].flag == 0 && p->cia == x) {
			achaCaminho(g, p->adj, v2, x, achou);

			if (*achou) return;
		}
		p = p->prox;
	}
	
	g[v1].flag = 2;
}

bool deAateBporC(Vertice * g, int a, int b, int c) {
	// primeiro, vê se tem caminho de a até c
	bool achou = false;
	zerarFlags(g);
	buscaProfundidade(g, a, c, &achou);
	if (!achou) {
		return false;
	}

	// se achou de a até c, vai tentar achar de c até b
	achou = false;
	zerarFlags(g);
	buscaProfundidade(g, c, b, &achou);
	if (!achou) {
		return false;
	}

	return true;
}

// cria uma aresta de i com todos os vértices não alcançáveis por ele
void botaSeNaoAlcanca(Vertice * g, int i) {
	zerarFlags(g);
	soBuscaProfundamente(g, i);

	int j;
	for (j = 1; j <= V; j++) {
		if (g[j].flag == 0) {
			No * novo = (No*) malloc(sizeof(No));

			novo->adj  = j;
			novo->peso = 0;
			novo->cia  = AZUL;
			novo->prox = g[i].inicio;
			g[i].inicio = novo;
		}
	}
}

// --------------------------
// -- Busca em Largura
// --------------------------

void buscaLargura(Vertice * g, int i) {
	zerarFlags(g);
	g[i].flag = 1;

	Fila * fila = inicializarFila(100);
	inserirFila(fila, i);

	while (tamanhoFila(fila) > 0) {
		removeFila(fila, &i);
		No * p = g[i].inicio;

		while(p) {
			if (g[p->adj].flag == 0) {
				g[p->adj].flag = 1;
				inserirFila(fila, p->adj);
			}
			p = p->prox;
		}
		
		g[i].flag = 2;
	}

	deletarFila(fila);
}

int tipoXmaisProximo(Vertice * g, int i, tipo tipoX) {
	zerarFlags(g);
	g[i].flag = 1;

	Fila * f = inicializarFila(100);
	inserirFila(f, i);

	while (tamanhoFila(f) > 0) {
		removeFila(f, &i);

		if (g[i].tipo == tipoX) {
			deletarFila(f);
			return i;
		}
		
		No * p = g[i].inicio;

		while(p) {
			if (g[p->adj].flag == 0) {
				g[p->adj].flag = 1;
				inserirFila(f, p->adj);
			}
			p = p->prox;
		}
		
		g[i].flag = 2;
	}

	deletarFila(f);
	return -1;
}

int comprimentoAtoB(Vertice * g, int a, int b) {
	zerarFlags(g);
	g[a].flag = 1;

	Fila * f = inicializarFila(100);
	inserirFila(f, a);

	// zera as distancias
	for (int j = 1; j <= V; j++) {
		if (j == a) {
			g[j].dist = 0;
		} else {
			g[j].dist = INT_MAX;
		}
	}

	int elemento;

	while (tamanhoFila(f) > 0) {
		removeFila(f, &elemento);

		if (elemento == b) {
			deletarFila(f);
			return g[elemento].dist;
		}
		
		No * p = g[elemento].inicio;

		while(p) {
			if (g[p->adj].flag == 0) {
				g[p->adj].flag = 1;
				g[p->adj].dist = g[elemento].dist + 1;
				inserirFila(f, p->adj);
			}

			p = p->prox;
		}
		
		g[elemento].flag = 2;
	}

	deletarFila(f);
	return -1;
}

// retorna uma lista com todos os elementos em um raio N a partir de i
No * verticesNoRaio(Vertice *g, int i, int N) {
	No *resp = NULL;
	zerarFlags(g);

	// zera as distancias
	for (int j = 1; j <= V; j++) {
		if (j == i) g[j].dist = 0;
		else g[j].dist = INT_MAX;
	}

	Fila * f = inicializarFila(100);
	inserirFila(f, i);
	g[i].flag = 1;

	int elemento;

	while (tamanhoFila(f) > 0) {
		removeFila(f, &elemento);

		if (g[elemento].dist > N) {
			break;
		}

		// adiciona vértice
		No * novo = (No*) malloc(sizeof(No));
		novo->adj = elemento;
		novo->prox = resp;
		resp = novo;

		if (g[elemento].dist < N) {
			No * p = g[elemento].inicio;
			while (p) {
				if (g[p->adj].flag == 0) {
					g[p->adj].dist = g[elemento].dist + 1;

					if (g[p->adj].dist <= N) {
						g[p->adj].flag = 1;
						inserirFila(f, p->adj);
					}
				}

				p = p->prox;
			}
		}

		g[elemento].flag = 2;
	}

	deletarFila(f);
	return resp;
}

// --------------------------
// -- Dijkstra
// --------------------------

void dijkstra (Vertice * g, int i) {
	int j;
	
	// inicializa 
	for (j = 1; j <= V; j++) {
		g[j].p = 0;
		g[j].custo = INT_MAX;
		g[j].via = -1;
	}
	
	g[i].custo = 0;
	
	// -------
	
	while (true) {
		int s = -1;
		int cs = INT_MAX;
		for (j = 1; j <= V; j++) {
			// se não foi finalizado e o custo é menos que o menor custo:
			if (g[j].p == 0 && g[j].custo < cs) {
				s = j;
				cs = g[j].custo;
			}
		}
		if (s == -1) return;
		g[s].p = 1; // concluido
		
		No * p = g[s].inicio;
		
		while (p) {
			int temp = g[s].custo + p->peso;
			if (temp < g[p->adj].custo) {
				g[p->adj].custo = temp;
				g[p->adj].via = s;
			}
			p = p->prox;
		}
	}
}

// --------------------------
// -- Exercícios
// --------------------------

int contaLacos(Vertice * g) {
	int count = 0;

	for (int i = 1; i <= V; i++) {
		No * atual = g[i].inicio;
		No * antes = NULL;

		while(atual) {
			if (atual->adj == i) {
				count ++;

				if (!antes) {
					g[i].inicio = g[i].inicio->prox;
				} else {
					antes->prox = atual->prox;
				}
				
				free(atual);
				break;
			}
			antes = atual;
			atual = atual->prox;
		}
	}

	return count;
}

void removeArestas(No * p) {
	if (!p) return;

	removeArestas(p->prox);
	free(p);
}

void destroiGrafo(Vertice * g) {
	for (int i = 1; i <= V; i++) {
		removeArestas(g[i].inicio);
		g[i].inicio = NULL;
	}
}

Vertice * Complemento(Vertice * g) {
	int * existeAresta = malloc((V+1)*sizeof(int));
	
	Vertice * complemento = (Vertice*) malloc((V + 1) * sizeof(Vertice));
	inicializar(complemento, V);
	
	int i, j;
	
	for (i = 1; i <= V; i++) {
		for (j = 1; j <= V; j++) {
			existeAresta[j] = 0;
		}

		No * p = g[i].inicio;

		while(p) {
			existeAresta[p->adj] = 1;

			p = p->prox;
		}

		for (j = 1; j <= V; j++) {
			if (!existeAresta[j] && i != j) {
				No * novo = (No*) malloc(sizeof(No));
				novo->adj = j;
				novo->prox = complemento[i].inicio;
				complemento[i].inicio = novo;
			}
		}

	}

	free(existeAresta);
	return complemento;
}

bool ehArvoreEnraizada(Vertice * g, int v) {
	int * grausEntrada = malloc((v+1) * sizeof(int));
	int i;
	
	for (i = 1; i <= v; i ++) {
		grausEntrada[i] = 0;
	}

	for (i = 1; i <= v; i ++) {
		No * p = g[i].inicio;

		while(p) {
			grausEntrada[p->adj]++;

			p = p->prox;
		}
	}

	int idxFonte = -1;
	for (i = 1; i <= v; i ++) {
		if (grausEntrada[i] == 0) {
			if (idxFonte != -1) {
        free(grausEntrada);
        return false;
    	}

			idxFonte = i;
			continue;
		}

		if (grausEntrada[i] != 1) {
			free(grausEntrada);
			return false;
		}
	}

	if (idxFonte == -1) {
		free(grausEntrada);
		return false;
	}

	int contagem = 0;
	passa_e_conta(g, idxFonte, &contagem);

	free(grausEntrada);

	return contagem == v;
}

Vertice * CustoMinimo(Vertice * g, int v, int custo) {
	Vertice * novo = (Vertice*) malloc((v+1) * sizeof(Vertice));
	inicializar(novo, v);

	int i;
	for (i = 1; i <= v; i++) {
		No * p = g[i].inicio;

		while(p) {
			if (p->peso > custo) {
				inserirAresta(novo, i, p->adj, p->peso, p->cia);
			}

			p = p->prox;
		}
	}

	return novo;
}

Vertice * TemNoANaoTemNoB(Vertice * a, Vertice * b, int v) {
	Vertice * novo = (Vertice*) malloc((v+1) * sizeof(Vertice));
	inicializar(novo, v);
	
	int * arestasAnaoB = malloc((v+1) * sizeof(int));
	int	i;
	int k = 1;
	
	for (i = 1; i <= v; i++) {
		arestasAnaoB[i] = 0;
	}

	for (i = 1; i <= v; i++) {
		// marca aresta que existem no A
		No * p = a[i].inicio;
		while(p) {
			arestasAnaoB[p->adj] = k;
			p = p->prox;
		}
		
		// remove as que estão em B
		p = b[i].inicio;
		while(p) {
			arestasAnaoB[p->adj] = 0;
			p = p->prox;
		}

		// adiciona no grafo novo
		p = a[i].inicio;
		while(p) {
			if (arestasAnaoB[p->adj] == k) {
				inserirAresta(novo, i, p->adj, 10, AZUL);
			}

			p = p->prox;
		}

		k++;
	}

	free(arestasAnaoB);
	return novo;
}

void suspeitosSpam(Vertice * g, int v) {
	int * recebeuSpam = malloc((v+1) * sizeof(int));
	int * participou = malloc((v+1) * sizeof(int));
	int i;

	for (i = 1; i <= v; i++) {
		recebeuSpam[i] = 0;
		participou[i] = 0;
	}

	for (i = 1; i <= v; i++) {
		No * p = g[i].inicio;

		while (p) {
			if (p->id == spam) {
				recebeuSpam[p->adj]++;
				participou[p->adj] = 1;;
				participou[i] = 1;
			}

			p = p->prox;
		}
	}

	for (i = 1; i <= v; i++) {
		if (participou[i] && recebeuSpam[i] == 0) {
			printf("Usuário %d é suspeito de enviar SPAM!!!\n", i);
		}
	}

	free(recebeuSpam);
	free(participou);
}

bool temCaminhoDeAateB(Vertice * g, int v, int a, int b, int * count, No ** caminho) {
	zerarFlags(g);
	Fila * f = inicializarFila(100);
	int * pai = malloc((v+1) * sizeof(int));

	// zera as distancias
	int i;
	for (i = 1; i <= v; i++) {
		if (i == a) g[i].dist = 0;
		else g[i].dist = INT_MAX;

		pai[i] = -1;
	}

	g[a].flag = 1;
	inserirFila(f, a);

	int elemento;
	bool achouCaminho = false;

	while (tamanhoFila(f) > 0) {
		removeFila(f, &elemento);

		if (elemento == b) {
			*count = g[elemento].dist + 1;
			achouCaminho = true;
			break;
		}

		No * p = g[elemento].inicio;
		while (p) {
			if (g[p->adj].flag == 0) {
				g[p->adj].flag = 1;
				g[p->adj].dist = g[elemento].dist + 1;
				pai[p->adj] = elemento;
				inserirFila(f, p->adj);
			}

			p = p->prox;
		}

		g[elemento].flag = 2;
	}

	if (!achouCaminho) {
		deletarFila(f);
		free(pai);
		return false;
	}

	int idxPai = b;
	while (idxPai != -1) {
		No * novo = (No*) malloc(sizeof(No));
		novo->adj = idxPai;

		novo->prox = *caminho;
		*caminho = novo;

		idxPai = pai[idxPai];
	}

	free(pai);
	deletarFila(f);
	return true;
}

bool buscaProfundidadeMatriz_v2(int m[V][V], int flags[V], int a, int b) {
	if (a == b)
		return true;

	flags[a] = 1;
	int i;

	for (i = 0; i < V; i++) {
		if (m[a][i] == 1 && flags[i] == 0 && buscaProfundidadeMatriz_v2(m, flags, i, b))
			return true;
	}

	flags[a] = 2;
	return false;
}

bool temCaminhoDeAateB_prof_matriz(int m[V][V], int a, int b) {
	int flags[V];
	int i;

	for (i = 0; i < V; i++) {
		flags[i] = 0;
	}

	return buscaProfundidadeMatriz_v2(m, flags, a, b);
}

No * voou_de_A_ate_B_cia_C_matriz(cia m[V][V], int a, int b, cia c) {
	Fila * f = inicializarFila(100);
	int pai[V], flags[V];
	No * inicio = NULL;

	int i;
	for (i = 0; i < V; i++) {
		flags[i] = 0;
		pai[i] = -1;
	}

	inserirFila(f, a);
	flags[a] = 1;

	int elemento;
	bool achou = false;

	while (tamanhoFila(f) > 0) {
		removeFila(f, &elemento);

		if (elemento == b) {
			flags[elemento] = 2;
			achou = true;
			break;
		}
		
		for (i = 0; i < V; i++) {
			if (m[elemento][i] != INDEF && m[elemento][i] == c && flags[i] == 0) {
				flags[i] = 1;
				pai[i] = elemento;
				inserirFila(f, i);
			}
		}

		flags[elemento] = 2;
	}

	if (!achou) {
		deletarFila(f);
		return NULL;
	}

	while (elemento != -1) {
		No * novo = (No*) malloc(sizeof(No));
		novo->adj = elemento;
		novo->prox = inicio;
		inicio = novo;

		elemento = pai[elemento];
	}

	deletarFila(f);
	return inicio;
}

bool temCicloNaoDirigido(Vertice * g) {
	zerarFlags(g);

	int i;
	for (i = 1; i <= V; i++) {
		if (g[i].flag == 0 && temCicloNaoDirigidoRec(g, i, -1)) {
			return true;
		}
	}

	return false;
}

bool temCicloNaoDirigidoRec(Vertice * g, int i, int pai) {
	g[i].flag = 1;
	No * p = g[i].inicio;

	while (p) {
		if (g[p->adj].flag == 1 && p->adj != pai) {
			return true;
		}

		if (g[p->adj].flag == 0) {
			if (temCicloNaoDirigidoRec(g, p->adj, i)) {
				return true;
			}
		}

		p = p->prox;
	}

	g[i].flag = 2;
	return false;
}

void removeArestaNaoDirigido(Vertice * g, int i, int j) {
	No * p = g[i].inicio;
	No * ant = NULL;

	while (p) {
		if (p->adj == j) {
			if (ant == NULL) {
				g[i].inicio = p->prox;
			} else {
				ant->prox = p->prox;
			}
			free(p);
			break;
		}
		
		p = p->prox;
	}

	p = g[j].inicio;
	ant = NULL;
	while (p) {
		if (p->adj == i) {
			if (ant == NULL) {
				g[j].inicio = p->prox;
			} else {
				ant->prox = p->prox;
			}
			free(p);
			break;
		}
		
		p = p->prox;
	}
}

void removeCicloNaoDirigido(Vertice * g) {
	zerarFlags(g);

	int i;
	for (i = 1; i <= V; i++) {
		if (g[i].flag == 0) {
			temCicloNaoDirigidoRec(g, i, -1);
		}
	}
}

void removeCicloNaoDirigidoRec(Vertice * g, int i, int pai) {
	g[i].flag = 1;
	No * p = g[i].inicio;

	while (p) {
		No * prox = p->prox;
		if (g[p->adj].flag == 1 && p->adj != pai) {
			removeArestaNaoDirigido(g, i, p->adj);
		} else if (g[p->adj].flag == 0) {
			removeCicloNaoDirigidoRec(g, p->adj, i);
		}

		p = prox;
	}

	g[i].flag = 2;
}

int main() {

  // Grafo 01
  Vertice * g = (Vertice*) malloc((V + 1) * sizeof(Vertice));
  inicializar(g, V);

  inserirAresta(g, 1, 2, 10, GOL);
  inserirAresta(g, 2, 1, 10, LATAM);
  inserirAresta(g, 2, 3, 5, GOL);
  inserirAresta(g, 3, 1, 5, AZUL);
  inserirAresta(g, 3, 2, 5, LATAM);
  inserirAresta(g, 3, 4, 8, GOL);
  inserirAresta(g, 4, 3, 8, LATAM);
  inserirAresta(g, 4, 1, 15, AZUL);
  inserirAresta(g, 5, 1, 20, GOL);
  inserirAresta(g, 5, 5, 0, LATAM);
  definirTipo(g, 1, primeiro);
  definirTipo(g, 2, segundo);
  definirTipo(g, 3, terceiro);
  definirTipo(g, 4, primeiro);
  definirTipo(g, 5, segundo);

  printf("Exibindo G:\n");
  exibir(g, "G", V);
  printf("=========================\n");

  // Grafo 02
  Vertice * g2 = (Vertice*) malloc((V + 1) * sizeof(Vertice));
  inicializar(g2, V);

	for (int v1 = 1; v1 <= V; v1++) {
		for (int v2 = 1; v2 < V; v2++) {
			if (v1 == v2) continue;

			inserirAresta(g2, v1, v2, 1, GOL);
		}
	}

  printf("Exibindo G2:\n");
  exibir(g2, "G2", V);
  printf("=========================\n");

  // Subgrafo
  printf("g2 %s subgrafo de g\n", subgrafo(g, g2) ? "é" : "não é");
  printf("=========================\n");

  // Transposta
  Vertice * gt = CopiaTransposta(g);
  printf("Exibindo transposta de G:\n");
  exibir(gt, "GT", V);
  printf("=========================\n");

  // Busca
  printf("Buscando em G:\n");

  zerarFlags(g);
  bool achou = false;
  int entrada = 1, saida = 2;
  buscaProfundidade(g, entrada, saida, &achou);
  printf("Aresta %d->%d encontrada: %s\n", entrada, saida, achou ? "Sim" : "Não");

  zerarFlags(g);
  achou = false;
  entrada = 3; saida = 1;
  buscaProfundidade(g, entrada, saida, &achou);
  printf("Aresta %d->%d encontrada: %s\n", entrada, saida, achou ? "Sim" : "Não");
  printf("=========================\n");

  // Ciclos
  zerarFlags(g);
  achaCiclos(g, 1);
  printf("=========================\n");

  // Conta tipos
  zerarFlags(g);
  int count = 0;
  contaTipos(g, 1, primeiro, &count);
  printf("Número de vértices do tipo 'primeiro': %d\n", count);
  printf("=========================\n");

  // Maior grupo
	int quant = 0;
  int maior = maiorGrupo(g, &quant);
  printf("Vértice com maior grupo: %d\n", maior);
  printf("Quantidade de vértices no maior grupo: %d\n", quant);
  printf("=========================\n");

	// Dijkstra
	dijkstra(g, 1);
	printf("Caminho mais curto de 1 para 1: %d\n", g[1].custo);
	printf("Caminho mais curto de 1 para 2: %d\n", g[2].custo);
	printf("Caminho mais curto de 1 para 3: %d\n", g[3].custo);
	printf("Caminho mais curto de 1 para 4: %d\n", g[4].custo);
	printf("Caminho mais curto de 1 para 5: %d\n", g[5].custo);
  printf("=========================\n");

	// Conexo
	printf("G é conexo? %s\n", ehConexo(g) ? "SIM!" : "NÃO!");
	printf("G2 é conexo? %s\n", ehConexo(g2) ? "SIM!" : "NÃO!");
	printf("GT é conexo? %s\n", ehConexo(gt) ? "SIM!" : "NÃO!");
  printf("=========================\n");

	// Matriz
	int matriz[V][V];
	inicializarMatriz(matriz);
	inserirArestaMatriz(matriz, 1, 2);
	inserirArestaMatriz(matriz, 2, 3);
	inserirArestaMatriz(matriz, 2, 1);
	inserirArestaMatriz(matriz, 3, 1);
	inserirArestaMatriz(matriz, 3, 2);
	inserirArestaMatriz(matriz, 3, 4);
	inserirArestaMatriz(matriz, 4, 1);
	inserirArestaMatriz(matriz, 4, 3);

	printf("Exibindo matriz: \n");
	exibirMatriz(matriz);
  printf("=========================\n");

	// Graus de entrada e saída

	printf("Grau de entrada de V1: %d\n", grauEntrada(matriz, 1));
	printf("Grau de entrada de V2: %d\n", grauEntrada(matriz, 2));
	printf("Grau de entrada de V3: %d\n", grauEntrada(matriz, 3));
	printf("Grau de saída de V1: %d\n", grauSaida(matriz, 1));
	printf("Grau de saída de V2: %d\n", grauSaida(matriz, 2));
	printf("Grau de saída de V3: %d\n", grauSaida(matriz, 3));
  printf("=========================\n");

	// Acha caminho (cia)
	printf("Testando achaCaminho:\n");

	zerarFlags(g);
	achou = false;
	achaCaminho(g, 1, 4, GOL, &achou);
	printf("Caminho de 1 para 4 via GOL: %s\n", achou ? "SIM" : "NAO");

	zerarFlags(g);
	achou = false;
	achaCaminho(g, 5, 1, GOL, &achou);
	printf("Caminho de 5 para 1 via GOL: %s\n", achou ? "SIM" : "NAO");

	zerarFlags(g);
	achou = false;
	achaCaminho(g, 2, 1, GOL, &achou);
	printf("Caminho de 4 para 1 via GOL: %s\n", achou ? "SIM" : "NAO");

	zerarFlags(g);
	achou = false;
	achaCaminho(g, 5, 4, LATAM, &achou);
	printf("Caminho de 5 para 4 via LATAM: %s\n", achou ? "SIM" : "NAO");
	printf("=========================\n");

	// Acha caminhos (passando por C)
	printf("Testando deAateBporC (passando por C):\n");
	printf("De 1 a 4 passando por 3: %s\n", deAateBporC(g, 1, 4, 3) ? "SIM" : "NAO");
	printf("De 1 a 3 passando por 2: %s\n", deAateBporC(g, 1, 3, 2) ? "SIM" : "NAO");
	printf("De 5 a 4 passando por 1: %s\n", deAateBporC(g, 5, 4, 1) ? "SIM" : "NAO");
	printf("De 4 a 5 passando por 1: %s\n", deAateBporC(g, 4, 5, 1) ? "SIM" : "NAO");
	printf("De 2 a 5 passando por 3: %s\n", deAateBporC(g, 2, 5, 3) ? "SIM" : "NAO");
	printf("=========================\n");

	// Bota se nao alcança

	Vertice * gc = CopiaTransposta(CopiaTransposta(g));
	printf("Bota aresta em V5 se ele não alcança: \n");
	botaSeNaoAlcanca(gc, 5);
	exibir(gc, "G_Bota", V);
	printf("=========================\n");

	// Acha tipo mais proximo
	printf("Testando tipoXmaisProximo (grafo G):\n");

	int resposta;

	resposta = tipoXmaisProximo(g, 1, segundo);
	printf("Mais proximo de tipo 'segundo' a partir de 1: %d\n", resposta);

	resposta = tipoXmaisProximo(g, 3, primeiro);
	printf("Mais proximo de tipo 'primeiro' a partir de 3: %d\n", resposta);

	resposta = tipoXmaisProximo(g, 3, segundo);
	printf("Mais proximo de tipo 'segundo' a partir de 3: %d\n", resposta);

	resposta = tipoXmaisProximo(g, 5, terceiro);
	printf("Mais proximo de tipo 'terceiro' a partir de 5: %d\n", resposta);

	printf("=========================\n");

	// Comprimentos entre vértices
	printf("Testando comprimentoAtoB (grafo G):\n");

	int dist;

	dist = comprimentoAtoB(g, 1, 1);
	printf("Distancia 1->1: %d\n", dist);
	dist = comprimentoAtoB(g, 1, 2);
	printf("Distancia 1->2: %d\n", dist);
	dist = comprimentoAtoB(g, 1, 3);
	printf("Distancia 1->3: %d\n", dist);
	dist = comprimentoAtoB(g, 1, 4);
	printf("Distancia 1->4: %d\n", dist);
	dist = comprimentoAtoB(g, 1, 5);
	printf("Distancia 1->5: %d\n", dist);

	dist = comprimentoAtoB(g, 5, 3);
	printf("Distancia 5->3: %d\n", dist);
	dist = comprimentoAtoB(g, 2, 4);
	printf("Distancia 2->4: %d\n", dist);
	dist = comprimentoAtoB(g, 4, 2);
	printf("Distancia 4->2: %d\n", dist);
	dist = comprimentoAtoB(g, 5, 2);
	printf("Distancia 5->2: %d\n", dist);

	printf("=========================\n");

	// Próximos

	No * p = verticesNoRaio(g, 1, 2);
	printf("Vértices pertos de V1 em um raio de 2: \n");
	exibirLista(p);
	liberaLista(p);

	p = verticesNoRaio(g, 2, 1);
	printf("Vértices pertos de V2 em um raio de 1: \n");
	exibirLista(p);
	liberaLista(p);
	printf("=========================\n");

	// Conta laços
	// printf("Laços em G: %d\n", contaLacos(g));
	// exibir(g);
	// printf("=========================\n");

	// printf("Laços em G2: %d\n", contaLacos(g2));
	// exibir(g2);
	// printf("=========================\n");

	// printf("Laços em Gt: %d\n", contaLacos(gt));
	// exibir(gt);
	// printf("=========================\n");


	// Destroi grafo

	Vertice * g3 = CopiaTransposta(CopiaTransposta(g));
	destroiGrafo(g3);
	printf("Cópia de G DESTRUIDA OBLITERADA: \n");
	exibir(g3, "G_DESTRUIDO", V);
	printf("=========================\n");

	// Complemento

	Vertice * gx = Complemento(g);
	printf("Exibindo complemento de G: \n");
	exibir(gx, "G_Complemento", V);
	printf("=========================\n");

	// Verifica árvore

	int Varvre = 8;
	Vertice * arvore = (Vertice*) malloc((Varvre + 1) * sizeof(Vertice));
	inicializar(arvore, Varvre);
	inserirAresta(arvore, 1, 2, 1, AZUL);
	inserirAresta(arvore, 1, 3, 1, AZUL);
	inserirAresta(arvore, 1, 4, 1, AZUL);
	inserirAresta(arvore, 2, 5, 1, AZUL);
	inserirAresta(arvore, 3, 6, 1, AZUL);
	inserirAresta(arvore, 5, 8, 1, AZUL);
	inserirAresta(arvore, 7, 8, 1, AZUL);
	inserirAresta(arvore, 8, 2, 1, AZUL);

	exibir(arvore, "ARVORE", Varvre);
	printf("ESSE MANO É ARVORE ENRAIZADA?: %s\n", ehArvoreEnraizada(arvore, Varvre) ? "SIM" : "NÃO");
	printf("=========================\n");

	// Custo minimo
	Vertice * gmin = CustoMinimo(g, V, 5);
	exibir(gmin, "G_MIN", V);
	printf("=========================\n");

	// Tem no A mas nao tem no B

	Vertice * g4 = TemNoANaoTemNoB(g, g2, V);
	printf("Arestas que tem em G1 mas nao tem em G2: \n");
	exibir(g4, "G4", V);
	printf("=========================\n");

	Vertice * g5 = TemNoANaoTemNoB(g, gt, V);
	printf("Arestas que tem em G mas nao tem em Gt: \n");
	exibir(g5, "G5", V);
	printf("=========================\n");

	// EMAILS com SPAM

	int V_Emails = 6;
	Vertice * emails = (Vertice*) malloc((V_Emails + 1) * sizeof(Vertice));
	inicializar(emails, V_Emails);
	inserirArestaEmail(emails, 1, 2, mensagem);
	inserirArestaEmail(emails, 1, 3, spam);
	inserirArestaEmail(emails, 1, 4, spam);
	inserirArestaEmail(emails, 2, 1, mensagem);
	inserirArestaEmail(emails, 2, 3, oferta);
	inserirArestaEmail(emails, 3, 4, mensagem);
	inserirArestaEmail(emails, 4, 5, spam);
	inserirArestaEmail(emails, 5, 4, oferta);
	inserirArestaEmail(emails, 6, 2, mensagem);
	printf("EMAILS: \n");
	exibir(emails, "EMAILS", V_Emails);
	suspeitosSpam(emails, V_Emails);
	printf("=========================\n");

	// Caminhos

	int tamanhoAateB = 0;
	No * caminho = NULL;
	bool temCaminho = temCaminhoDeAateB(g, V, 1, 5, &count, &caminho);

	if (temCaminho) {
		printf("Tem caminho!\n");
		exibirLista(caminho);
	} else {
		printf("Não tem caminho :(\n");
	}

	temCaminho = temCaminhoDeAateB(emails, V_Emails, 1, 5, &count, &caminho);
	
	if (temCaminho) {
		printf("Tem caminho!\n");
		exibirLista(caminho);
	} else {
		printf("Não tem caminho :(\n");
	}

	printf("=========================\n");

	// Matrizes

	int grafoMatriz[V][V];
	inicializarMatriz(grafoMatriz);
	inserirArestaMatriz(grafoMatriz, 0, 1);
	inserirArestaMatriz(grafoMatriz, 0, 2);
	inserirArestaMatriz(grafoMatriz, 1, 0);
	inserirArestaMatriz(grafoMatriz, 1, 2);
	inserirArestaMatriz(grafoMatriz, 2, 2);
	printf("Tem caminho de 0 até 2?: %s\n", temCaminhoDeAateB_prof_matriz(grafoMatriz, 0, 2) ? "SIM" : "NÃO");

	printf("=========================\n");

	// Viagem aérea em Matriz

	printf("VIAGEM ÁEREA: \n");
	cia matrizAerea[V][V];
	inicializarMatrizAerea(matrizAerea);
	inserirArestaMatrizAerea(matrizAerea, 0, 1, GOL);
	inserirArestaMatrizAerea(matrizAerea, 0, 3, AZUL);
	inserirArestaMatrizAerea(matrizAerea, 1, 3, LATAM);
	inserirArestaMatrizAerea(matrizAerea, 1, 2, GOL);
	inserirArestaMatrizAerea(matrizAerea, 1, 4, AZUL);
	inserirArestaMatrizAerea(matrizAerea, 2, 1, LATAM);
	inserirArestaMatrizAerea(matrizAerea, 2, 3, GOL);
	inserirArestaMatrizAerea(matrizAerea, 3, 3, AZUL);
	inserirArestaMatrizAerea(matrizAerea, 3, 4, GOL);
	inserirArestaMatrizAerea(matrizAerea, 4, 1, LATAM);
	inserirArestaMatrizAerea(matrizAerea, 4, 2, AZUL);
	exibirMatrizAerea(matrizAerea, "VOO");

	No * caminhoAereo = voou_de_A_ate_B_cia_C_matriz(matrizAerea, 0, 4, GOL);
	if (caminhoAereo) {
		exibirLista(caminhoAereo);
	} else {
		printf("Não tem caminho aéreo :(\n");
	}

	printf("=========================\n");

	return 0;
}