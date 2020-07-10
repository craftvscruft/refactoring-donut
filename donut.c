#include <stdio.h>
#include <math.h>
#include <string.h>

int main() {
  float A = 0;
  float B = 0;
  const size_t buffer_size = 1760;
  float z[buffer_size];
  char b[buffer_size];
  const float j_step = 0.07;
  const float i_step = 0.02;
  const int width = 80;
  const int height = 22;
  const char * shade_chars = ".,-~:;=!*#$@";
  const char * newline = '\n';
  printf("\x1b[2J");
  for (;;) {
    memset(b, ' ', buffer_size);
    memset(z, 0, buffer_size * sizeof(float));
    for (float j = 0; 6.28 > j; j += j_step) {
      for (float i = 0; 6.28 > i; i += i_step) {
        float c = sin(i);
        float d = cos(j);
        float e = sin(A);
        float f = sin(j);
        float g = cos(A);
        float h = d + 2;
        float D = 1 / (c * h * e + f * g + 5);
        float l = cos(i);
        float m = cos(B);
        float n = sin(B);
        float t = c * h * g - f * e;
        int x = (width / 2) + 30 * D * (l * h * m - t * n);
        int y = (height / 2 - 1) + 15 * D * (l * h * n + t * m); 
        int o = x + width * y;
        int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);
        if (height > y && y > 0 && x > 0 && width > x && D > z[o]) {
          z[o] = D;
          b[o] = shade_chars[N > 0 ? N : 0];
        }
      }
    }
    printf("\x1b[H");
    for (int k = 0; buffer_size >= k; k++)
      putchar(k % width ? b[k] : newline);
    A += 0.04;
    B += 0.02;
  }
}