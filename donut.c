#include <stdio.h>
#include <math.h>
#include <string.h>

const char newline = '\n';
const float phi_step = 0.07;
const float theta_step = 0.02;
const char * shade_chars = ".,-~:;=!*#$@";

float TWO_PI = 6.28;

struct Canvas {
  char * buffer;
  size_t height;
  size_t width;
};

void display_buffer(struct Canvas canvas) {
  const size_t buffer_size = canvas.height * canvas.width;
  printf("\x1b[H");
  for (int k = 0; buffer_size >= k; k++)
    putchar(k % canvas.width ? canvas.buffer[k] : newline);
}

void iterate_buffer(struct Canvas canvas, float * z, float A, float B) {
  const size_t buffer_size = canvas.height * canvas.width;
  memset(canvas.buffer, ' ', buffer_size);
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
      int x = (canvas.width / 2) + 30 * D * (cos_theta * h * cos_B - t * sin_B);
      int y = (canvas.height / 2 - 1) + 15 * D * (cos_theta * h * sin_B + t * cos_B); 
      int o = x + canvas.width * y;
      int N = 8 * ((sin_phi * sin_A - sin_theta * cos_phi * cos_A) * cos_B - sin_theta * cos_phi * sin_A - sin_phi * cos_A - cos_theta * cos_phi * sin_B);
      if (canvas.height > y && y > 0 && x > 0 && canvas.width > x && D > z[o]) {
        z[o] = D;
        canvas.buffer[o] = shade_chars[N > 0 ? N : 0];
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
  struct Canvas canvas;
  canvas.width = width;
  canvas.height = height;
  float z[buffer_size];
  char buffer[buffer_size];
  canvas.buffer = buffer;
  printf("\x1b[2J");
  for (;;) {
    iterate_buffer(canvas, z, A, B);
    display_buffer(canvas);
    A += 0.04;
    B += 0.02;
  }
}