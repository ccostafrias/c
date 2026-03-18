#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// #define DEBUG

//--------------------------------------
// -- Estruturas
//--------------------------------------

// VERMELHO mais grave, AZUL menos grave
typedef enum {
  VERMELHO,
  LARANJA,
  AMARELO,
  VERDE,
  AZUL,
} Priority;

// cada paciente apresenta:
// uma prioridade (vide Priority acima)
// categoria (PCD, Idoso, Pessoa Obesa, Grávida, Recem nascido, N/A)
// tempo de espera na fila (em minutos)
typedef struct {
  Priority priority;
  char category[16];
  int waitTime;
} Patient;

// Data guarda a estrutura principal e seu tamanho
typedef struct {
  int len;
  int max;
  Patient * patients;
} Data;

//--------------------------------------
// -- Funções Auxiliares
//--------------------------------------

Priority str_to_priority(char * str) {
    if (strcmp(str, "Vermelho") == 0) return VERMELHO;
    if (strcmp(str, "Laranja")  == 0) return LARANJA;
    if (strcmp(str, "Amarelo")  == 0) return AMARELO;
    if (strcmp(str, "Verde")    == 0) return VERDE;
    if (strcmp(str, "Azul")     == 0) return AZUL;

    return -1;
}

const char* priority_to_string(Priority p) {
  switch (p) {
    case VERMELHO: return "Vermelho";
    case LARANJA:  return "Laranja";
    case AMARELO:  return "Amarelo";
    case VERDE:    return "Verde";
    case AZUL:     return "Azul";
    default:       return "Morto";
  }
}

void print_patients(Patient * patients, int len) {
  for (int i = 0; i < len; i++) {
    printf("%s,%s,%d", priority_to_string(patients[i].priority), patients[i].category, patients[i].waitTime);

    if (i != len - 1)
      printf("\n");
  }
}

void reverse_patients(Patient * patients, int len) {
  for (int i = 0; i < len/2; i++) {
    Patient temp = patients[len-1-i];
    patients[len-1-i] = patients[i];
    patients[i] = temp;
  }
}

int counting_lines(FILE * f) {
  char c;
  int count = 0;

  // itera sobre cada caracter e conta cada vírgula
  // duas virgulas = uma linha
  do {
    c = fgetc(f);
    if (c == ',') count++;
  } while (c != EOF);

  if (count == 0) {
    printf("Arquivo vazio ou inválido!\n");
    exit(1);
  }

  // volta para o início do arquivo
  rewind(f);

  return count/2;
}

// reclassifica prioridades de acordo com as especificações
void review_priority(Patient * p) {
  if (p->priority == AZUL && p->waitTime > 240) {
    p->priority = VERDE;
    return;

  } else if (p->priority == VERDE && p->waitTime > 120) {
    p->priority = AMARELO;
    return;

  } else if (p->priority == AMARELO && p->waitTime > 60) {
    p->priority = LARANJA;
    return;

  } else if (p->priority == LARANJA && p->waitTime > 10) {
    p->priority = VERMELHO;    
    return;

  }
}

// lê o arquivo CSV (ignorando vírgulas e '\n')
void load_CSV(Data * d) {
  for (int i = 0; i < d->len; i++) {
    char tempPriority[16];

    scanf(" %[^,],%[^,],%d", tempPriority, d->patients[i].category, &d->patients[i].waitTime);
    
    if (d->patients[i].waitTime > d->max) 
      d->max = d->patients[i].waitTime;
    
    // converte a cor lida para o enum Priority (0 a 4)
    d->patients[i].priority = str_to_priority(tempPriority);
    review_priority(&d->patients[i]);
  }
}

void swap(Patient * patients, int iA, int iB) {
  if (iA == iB) return;
  
  Patient temp = patients[iB];
  patients[iB] = patients[iA];
  patients[iA] = temp;
}

//--------------------------------------
// -- Funções de Ordenação
//--------------------------------------
static long int TENZY = 1; // usado no RADIX sort

void counting_place(
    Data * d,
    int *countArray,
    int lenCoutArray,
    int (*getIndex)(Patient)
) {

  Patient * tempPatients = (Patient*) malloc(d->len * sizeof(Patient));
  for (int i = 0; i < d->len; i++) {
    tempPatients[i] = d->patients[i];
    countArray[getIndex(tempPatients[i])]++;
  }
  
  for (int i = 1; i < lenCoutArray; i++)
    countArray[i] += countArray[i-1];

  for (int i = d->len - 1; i >= 0; i--) {
      int index = getIndex(tempPatients[i]);
      int currCount = countArray[index] - 1;

      d->patients[currCount] = tempPatients[i];
      countArray[index]--;
  }

  free(tempPatients);
}

int index_category(Patient patient) {
  // se é vermelho ou laranja, jogamos para o final da ordenação
  if (patient.priority == VERMELHO || patient.priority == LARANJA)
    return 2;

  // se for categoria especial, fica na frente; se não, fica atrás dos especiais
  return (strcmp(patient.category, "N/A") == 0) ? 1 : 0;
}

int index_priority(Patient patient) {
  return patient.priority;
}

int index_time(Patient patient) {
  return patient.waitTime;
}

int index_digit(Patient patient) {
    return 9 - ((patient.waitTime / TENZY) % 10);
}

// contamos os pacientes por prioridade (cinco)
void counting_sort_priority(Data * d) {
  int priorityCount[5] = {0, 0, 0, 0, 0};

  counting_place(d, priorityCount, 5, index_priority);
}

// contamos por "categoria" (três)
// VERMELHO/LARANJA | N/A | ESPECIAL
void counting_sort_category(Data * d) {
  int categoryCount[3] = {0, 0, 0};

  counting_place(d, categoryCount, 3, index_category);
}

// contamos por tempo de espera (waitTime máximo)
void counting_sort_time(Data * d) {
  int * timeCount = calloc((d->max + 1), sizeof(int));

  counting_place(d, timeCount, (d->max + 1), index_time);
  reverse_patients(d->patients, d->len);

  free(timeCount);
}

void radix_sort(Data * d) {
  int * buckets = (int*) malloc(10 * sizeof(int));

  for (TENZY = 1; TENZY <= d->max; TENZY *= 10) {
    for (int i = 0; i < 10; i++) buckets[i] = 0;
    counting_place(d, buckets, 10, index_digit);
  }

  free(buckets);
}

// -------- MERGE ------------

void merge(Patient patients[], int start, int mid, int end) {
  int lenLeft = mid - start + 1, lenRight = end - mid;
  int iLeft = 0, iRight = 0, iFinal = start;

  Patient * left = (Patient*) malloc(lenLeft * sizeof(Patient));
  Patient * right = (Patient*) malloc(lenRight * sizeof(Patient));

  // copia os valores para os arrays left e right temporariamente
  for (int i = 0; i < lenLeft; i++)
    left[i] = patients[start + i];

  for (int i = 0; i < lenRight; i++)
    right[i] = patients[mid + 1 + i];

  //se iLeft e iRight não chegaram ao fim dos arrays, compara os valores e pega o maior
  while (iLeft < lenLeft && iRight < lenRight) {
    if (left[iLeft].waitTime > right[iRight].waitTime) {
      patients[iFinal++] = left[iLeft++];

    } else {
      patients[iFinal++] = right[iRight++];

    }
  }

  // se iRight chegou ao fim do array, copia o resto do left
  while (iLeft < lenLeft)
    patients[iFinal++] = left[iLeft++];

  // se iLeft chegou ao fim do array, copia o resto do right
  while (iRight < lenRight)
    patients[iFinal++] = right[iRight++];

  free(left);
  free(right);
}

void merge_sort(Patient patients[], int start, int end) {
  if (start >= end) {
    return;
  }

  int mid = (start + end) / 2;
  merge_sort(patients, start, mid);
  merge_sort(patients, mid+1, end);

  merge(patients, start, mid, end);
}

// -------- QUICK ------------

int randomN(int min, int max) {
  return rand() % (max - min + 1) + min;
}

void quick_sort(Patient * patients, int start, int end) {
  if (start >= end) return;

  int iPivot = randomN(start, end);
  int pivot = patients[iPivot].waitTime;
  swap(patients, iPivot, end);

  int iStart = start, iEnd = end - 1;

  while (iStart <= iEnd) {
    if (patients[iStart].waitTime > pivot) {
      iStart++;
    } else {
      while (iEnd >= iStart && patients[iEnd].waitTime <= pivot) {
        iEnd--;
      }
      if (iStart <= iEnd) {
        swap(patients, iStart, iEnd);
        iEnd--;
        iStart++;
      }
    }
  }

  swap(patients, end, iStart);

  quick_sort(patients, start, iStart - 1);
  quick_sort(patients, iStart + 1, end);

}

// -------- HEAP ------------

void heapify(Patient * patients, int last, int parent) {
  int left = 2*parent + 1;
  int right = left + 1;
  int max = parent;

  if (left <= last && patients[left].waitTime < patients[max].waitTime)
    max = left;
    
  if (right <= last && patients[right].waitTime < patients[max].waitTime)
    max = right;

  if (max != parent) {
    swap(patients, parent, max);
    heapify(patients, last, max);
  }

}

void build_max_heap(Patient * patients, int last) {
  for (int index = (last - 1)/2; index >= 0; index--) {
    heapify(patients, last, index);
  }
}

void heapsort(Patient * patients, int last) {
  build_max_heap(patients, last);

  for (int newLast = last; newLast > 0; newLast--) {
    swap(patients, 0, newLast);
    heapify(patients, newLast-1, 0);
  }
}

// -------- INSERTION ------------

void insert(Patient * patients, int actualIndex) {
  Patient actualPatient = patients[actualIndex];
  int prevIndex = actualIndex - 1;

  while (prevIndex >= 0 && patients[prevIndex].waitTime > actualPatient.waitTime) {
    patients[prevIndex + 1] = patients[prevIndex];
    prevIndex--;
  }

  patients[prevIndex + 1] = actualPatient;
}

void insertion_sort(Data * d) {
  for (int i = 1; i < d->len; i++) {
    insert(d->patients, i);
  }
}

// -------- BUBBLE ------------

void bubble_sort(Data * d) {
  int end = d->len - 1;
  int k, trocou;
  Patient * patients = d->patients;

  do {
    trocou = 0;
    for (k = 0; k < end; k++) {
      if (patients[k].waitTime > patients[k+1].waitTime) {
        swap(patients, k, k+1);

        trocou = 1;
      }
    }
    end--;

  } while (trocou);
}


//--------------------------------------
// -- Função Principal
//--------------------------------------
int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Insira o caminho do arquivo de entrada! (Ex: pacientes.csv)");
    return 1;
  }

  #ifdef DEBUG
    if (argc == 3) {
      char command[128];
      sprintf(command, "generate_patients.exe %d", atoi(argv[2]));
      system(command);
    }

    clock_t start = clock();
  #endif

  // gera seed aleatória para randomização (usado no quicksort)
  srand(time(NULL));  

  // redireciona stdin para um arquivo
  FILE *f = freopen(argv[1], "r", stdin);
  if (!f) {
    printf("Erro ao abrir o arquivo %s\n", argv[1]);
    return 1;
  }
  
  // cria e lê os dados do CSV
  Data d;
  d.max = 0;
  d.len = counting_lines(f);
  d.patients = (Patient*) malloc(d.len * sizeof(Patient));
  load_CSV(&d);
  fclose(f);
  
  // a estratégia de ordenação é:
  // 1. ordenar por tempo de espera (decrescente) - merge/quick/heap/insertion/couting sort
  // 2. ordenar por "categoria", separando em três gurpos: VL > N/A > outra categoria - counting sort
  // 3. ordenar por prioridade: V > L > Am > Vd > Az - counting sort

  merge_sort(d.patients, 0, d.len - 1);
  counting_sort_category(&d);
  counting_sort_priority(&d);
  
  // imprime o resultado final (já no arquivo .csv)
  f = freopen("OrdemDeAtendimentos.csv", "w", stdout);
  print_patients(d.patients, d.len);

  // libera memória e fecha arquivo
  free(d.patients);
  fclose(f);

  #ifdef DEBUG
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    fprintf(stderr, "Tempo de execução: %.6f segundos\n", time_spent);
  #endif

  return 0;
}