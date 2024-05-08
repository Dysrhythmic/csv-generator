/**
* @author Jacob Tucker
*
* For generating CSV files of a given size for testing.
* */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {
  char* filepath;
  size_t record_count = 0, field_count = 0, str_write_count = 0;
  
  if (argc == 4) {
    filepath = argv[1];
    field_count = atoi(argv[2]);
    record_count = atoi(argv[3]);
  }
  else {
    printf("[*]Usage is: %s <filepath> <num_of_columns> <num_of_rows>\n", argv[0]);
    return 1;
  }

  FILE* csv = fopen(filepath, "w");
  if (csv == NULL) {
    printf("[!]ERROR: Unable to open file %s for writing\n", filepath);
    return 1;
  }

  size_t field_size = sizeof(char) * field_count * 10;
  char buf[field_size * record_count];
  for (size_t records_written = 0; records_written != record_count; ++records_written) {
    for (size_t fields_written = 0; fields_written != field_count; ++fields_written) {
      str_write_count += snprintf(buf + str_write_count, field_size, "%lu", records_written + 1);
      if (fields_written + 1 != field_count) { buf[str_write_count++] = ','; }
    }
    buf[str_write_count++] = '\n';
  }

  size_t file_write_count = fwrite(buf, sizeof(char), str_write_count, csv);
  if (file_write_count != str_write_count) {
    printf("[!]ERROR: Failed to create write field\n");
    printf("[*]file_write_count: %lu\n", file_write_count);
    printf("[*]str_write_count: %lu\n", str_write_count);
    fclose(csv);
    return 1;
  }

  fclose(csv);
  return 0;
}