#include <stdio.h>
#include <math.h>
#include <string.h>

const char newline = '\n';
const float phi_step = 0.07;
const float theta_step = 0.02;
const char * shade_chars = ".,-~:;=!*#$@";

float TWO_PI = 6.28;


void display_buffer(char * buffer, size_t height, size_t width) {
  const size_t buffer_size = height * width;
  printf("\x1b[H");
  for (int k = 0; buffer_size >= k; k++)
    putchar(k % width ? buffer[k] : newline);
}

void iterate_buffer(char * buffer, float * z, size_t height, size_t width, float A, float B) {
  const size_t buffer_size = height * width;
  memset(buffer, ' ', buffer_size);
  memset(z, 0, buffer_size * sizeof(float));
  for (float phi = 0; phi < TWO_PI; phi += phi_step) {
    for (float theta = 0; theta < TWO_PI; theta += theta_step) {
      float sin_theta = sin(theta);
      float cos_phi = cos(phi);
      float sin_A = sin(A);
      float sin_phi = sin(phi);
      float cos_A = cos(A);
      float h = cos_phi + 2;
      float D = 1 / (sin_theta * h * sin_A + sin_phi * cos_A + 5);
      float cos_theta = cos(theta);
      float cos_B = cos(B);
      float sin_B = sin(B);
      float t = sin_theta * h * cos_A - sin_phi * sin_A;
      int x = (width / 2) + 30 * D * (cos_theta * h * cos_B - t * sin_B);
      int y = (height / 2 - 1) + 15 * D * (cos_theta * h * sin_B + t * cos_B); 
      int o = x + width * y;
      int N = 8 * ((sin_phi * sin_A - sin_theta * cos_phi * cos_A) * cos_B - sin_theta * cos_phi * sin_A - sin_phi * cos_A - cos_theta * cos_phi * sin_B);
      if (height > y && y > 0 && x > 0 && width > x && D > z[o]) {
        z[o] = D;
        buffer[o] = shade_chars[N > 0 ? N : 0];
      }
    }
  }
}

int main() {
  float A = 0;
  float B = 0;
  const size_t width = 80;
  const size_t height = 22;
  const size_t buffer_size = height * width;
  float z[buffer_size];
  char buffer[buffer_size];

  printf("\x1b[2J");
  for (;;) {
    iterate_buffer(buffer, z, height, width, A, B);
    display_buffer(buffer, height, width);
    A += 0.04;
    B += 0.02;
  }
}