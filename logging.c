#include <stdio.h>
#include <stdlib.h>
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

void write_to_file(const char * filename, const char * header, const char * buffer, int buffer_size, int width) {
  FILE *file;
  file = fopen(filename, "a");

  int remaining = buffer_size;
  int i = 0;
  fprintf(file, header);
  while (remaining > 0) {
    int to_write = MIN(width, remaining);
    fwrite(&buffer[i], sizeof(char), to_write, file);
    fprintf(file, "\n");
    remaining -= to_write;
    i += to_write;
  }
  
  fclose(file); //Don't forget to close the file when finished
}

void log_step(int step, const char * buffer, int buffer_size, int width) {
  const char * filename = getenv("DONUT_STEP_LOG_FILE");
  if (!filename) {
    return;
  }

  if (step == 0) {
    remove(filename);
  }
  if (step < 32) {
    char header[80];
    sprintf(header, "## Step %d\n", step);
    write_to_file(filename, header, buffer, buffer_size, width);
  }
}
