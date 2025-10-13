#include <stdio.h>
#include <stdlib.h>

int index_binary_search(int * vec, int start, int end, int el) {
  int middle = (start+end)/2;

  if (start > end) return -1;

  if (vec[middle] == el) return middle;
  else if (vec[middle] > el) {
    return index_binary_search(vec, start, middle-1, el);
  } else {
    return index_binary_search(vec, middle+1, end, el);
  }

}

int main() {
  int vec[] = {1, 1, 3, 7, 8, 9, 13, 90, 115};
  int size = sizeof(vec)/sizeof(vec[0]), el;
  scanf("%d", &el);

  int index = index_binary_search(vec, 0, size-1, el);
  if (index != -1) printf("ELEMENTO %d NA POS. %d", el, index);
  else printf("NAO ACHEI PARCA");

  return 0;
}