#include <stdio.h>
#include <stdlib.h>

#define EMPTY 0
#define START 1
#define TARGET 4
#define BLOCKING_PATH 9
#define OBSTACLE_1 2
#define OBSTACLE_2 3
#define PATH 1
#define MOVES 4

typedef struct {
  int x, y;
} Coord;

typedef struct {
  int ** matrix;
  int row, col;
  Coord * path;
  int pathLen;
} Context;

Coord moves[] = {
  {1, 0},
  {0, 1},
  {-1, 0},
  {0, -1},
};

Coord find_element(Context * ctx, int el) {
  for (int i = 0; i < ctx->row; i++) {
    for (int j = 0; j < ctx->col; j++) {
      if (ctx->matrix[i][j] == el) {
        return (Coord){j, i};
      }
    }
  }

  return (Coord){-1, -1};
}

int inside_limits(Context *ctx, int x, int y) { return (x >= 0 && x < ctx->col && y >= 0 && y < ctx->row); }
int coord_to_index(Context * ctx, int x, int y) { return y * ctx->col + x; }
void fill_vector(int * vec, int size, int value) { for (int i = 0; i < size ; i++) vec[i] = value; }
void rebuild_path(Context * ctx, int * pred, int target_idx) {
    int count = 0;

    for (int cur = target_idx; cur != -1; cur = pred[cur]) count++;
    
    if (ctx->path) free(ctx->path);
    ctx->path = malloc(count * sizeof(Coord));
    ctx->pathLen = count;

    int cur = target_idx;
    for (int i = count - 1; i >= 0; --i) {
        int x = cur % ctx->col, y = cur / ctx->col;
        ctx->path[i] = (Coord){x, y};
        if (ctx->matrix[y][x] != TARGET && ctx->matrix[y][x] != START) ctx->matrix[y][x] = PATH;
        cur = pred[cur];
    }

}

int bfs_find_shortest(Context *ctx, Coord start) {
    int n = ctx->row * ctx->col;
    int *pred = malloc(n * sizeof(int));
    int *visited = calloc(n, sizeof(int));
    int *q = malloc(n * sizeof(int));

    fill_vector(pred, n, -1);

    int start_idx = coord_to_index(ctx, start.x, start.y);
    int head = 0, tail = 0;
    q[tail++] = start_idx;
    visited[start_idx] = 1;

    int target_idx = -1;

    while (head < tail) {
        int cur = q[head++];
        int cx = cur % ctx->col, cy = cur / ctx->col;

        if (ctx->matrix[cy][cx] == TARGET) { target_idx = cur; break; }

        for (int k = 0; k < MOVES; k++) {
            int nx = cx + moves[k].x, ny = cy + moves[k].y;

            if (!inside_limits(ctx, nx, ny)) continue;

            int idx = coord_to_index(ctx, nx, ny);
            if (visited[idx]) continue;

            int cell = ctx->matrix[ny][nx];
            if (cell != 0 && cell != TARGET) continue; // obstáculo

            visited[idx] = 1;
            pred[idx] = cur;
            q[tail++] = idx;
        }
    }

    if (target_idx != -1) {
      rebuild_path(ctx, pred, target_idx);
    }
    
    free(pred); free(visited); free(q);

    return target_idx != -1;
}

void print_matrix(Context * ctx) {
    for (int i = 0; i < ctx->row; i++) {
      for (int j = 0; j < ctx->col; j++) {
        printf("%d", ctx->matrix[i][j]);
        if (j != ctx->col-1) printf(" ");
      }
      if (i != ctx->row-1) printf("\n");
    }
}

void print_path(Context * ctx) {
  for (int i = 1; i < ctx->pathLen; i++) {
    if (ctx->path[i-1].x < ctx->path[i].x) printf("->");
    else if (ctx->path[i-1].x > ctx->path[i].x) printf("<-");
    else if (ctx->path[i-1].y < ctx->path[i].y) printf("↓");
    else if (ctx->path[i-1].y > ctx->path[i].y) printf("↑");

    if (i != ctx->pathLen-1) printf(" ");
  }
}

void read_matrix(Context * ctx) {
  for (int i = 0; i < ctx->row; i++) {
    for (int j = 0; j < ctx->col; j++) {
      scanf("%d", &ctx->matrix[i][j]);
    }
  }
}

void add_obstacles(Context * ctx) {
  for (int i = 0; i < ctx->row; i++) {
    for (int j = 0; j < ctx->col; j++) {
      if (ctx->matrix[i][j] == OBSTACLE_1 || ctx->matrix[i][j] == OBSTACLE_2) {
        int actualObstacle = ctx->matrix[i][j] == OBSTACLE_1 ? OBSTACLE_1 - 1:  OBSTACLE_2 - 1; 
        for (int k = 0; k < MOVES; k++) {
          for (int m = 1; m <= actualObstacle; m++) {
            int newI = i + m*moves[k].x;
            int newJ = j + m*moves[k].y;

            if (!inside_limits(ctx, newI, newJ)) continue;

            ctx->matrix[newI][newJ] = BLOCKING_PATH;
          }
        }
      }
    }
  }
}

void create_matrix(Context * ctx) {
  ctx->matrix = (int**) malloc(sizeof(int)*ctx->row);
  for (int i = 0; i < ctx->row; i++) ctx->matrix[i] = (int*) malloc(sizeof(int)*ctx->col);
  read_matrix(ctx);
  add_obstacles(ctx);
}

void free_context(Context * ctx) {
  for (int i = 0; i < ctx->row; i++) {
    free(ctx->matrix[i]);
  }
  free(ctx->matrix);
  free(ctx);
}

int main() {
  freopen("labirinto.in", "r", stdin);   // redireciona stdin para o arquivo
  freopen("labirinto.out", "w", stdout);

  int casos;
  scanf("%d", &casos);

  for (int c = 0; c < casos; c++) {
    Context *ctx = (Context*) malloc(sizeof(Context));

    int size; scanf("%d", &size);
    ctx->row = size; ctx->col = size;
    
    create_matrix(ctx);
    // print_matrix(ctx);
    
    Coord startCoord = find_element(ctx, START);

    ctx->path = malloc(ctx->row * ctx->col * sizeof(Coord));
    ctx->path[0] = startCoord;
    ctx->pathLen = 1;
    
    if (startCoord.x != -1 && startCoord.y != -1) {
      if (bfs_find_shortest(ctx, startCoord)) {
        print_matrix(ctx);
      }
    }
    printf("\nPATH LEN: %d\n", ctx->pathLen);
    print_path(ctx);

    free_context(ctx);
  }

  return 0;
}