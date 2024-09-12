#include <stdio.h>

void mystery(char* x) {
  while (*x) {
      if (*x > 96) *x -= 32;
      x++;
  }
}

int main() {
    int x = 200; 
    mystery(&x);
}