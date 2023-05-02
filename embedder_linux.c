#define __STDC_WANT_LIB_EXT1__ 1
#define MAX_FILENAME 64

#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char* code =
"const char *grab_file(const char *name, size_t *size) {\n"
"  const struct file_array *p;\n"
"  for (p = files; p->name != NULL; p++) {\n"
"    if (!strcmp(p->name, name)) {\n"
"      if (size != NULL) { *size = p->size; }\n"
"      return (const char *) p->data;\n"
"    }\n"
"  }\n"
"  return NULL;\n"
"}\n";

static const char* reconstruct = 
"//takes in a data buffer and size of the buffer and writes contents to\n"
"// a file with desired name\n"
"int rebuild_file(const char* d, size_t size, const char* desired_name) {\n"
"\n"
"    FILE* f = NULL;\n"
"   errno_t err;\n"
"    if (d == NULL || size <= 0 || desired_name == NULL) {\n"
"        printf(\"ERR: data array, the desired_name, or the size is uninitialized\\n\");\n"
"        printf(\"data: %s\\n\", d);\n"
"        printf(\"size: %l\\n\", size);\n"
"        printf(\"desired_name: %s\\n\", desired_name);\n"
"        return 1;\n"
"    }\n"
"\n"
"   err = fopen_s(&f, desired_name, \"wb\");\n"
"    if (!f) {\n"
"        perror(\"ERR: \");\n"
"        return 1;\n"
"    }\n"
"   size_t writtendata = fwrite(d, sizeof(char), size, f);\n"
"    fclose(f);\n"
"    if (writtendata != size) {\n"
"        printf(\"ERR: Failed to write full file contents.\\n\");\n"
"        return 1;\n"
"    }\n"
"    else return writtendata;\n"
"\n"
"}";

int main(int argc, char* argv[]) {

    if (argc < 2) {
        printf("\nUSAGE: embedder FILE1 [FILE2...] > outfile\n\n");
        return 1;
    }

    FILE* fp = NULL;
    int i, j, ch;

    for (i = 1; i < argc; i++) {
        fp = fopen(argv[i], "rb");
        if(fp == NULL) {
            exit(EXIT_FAILURE);
        }
        else {
            printf("static const unsigned char v%d[] = {", i);
            for (j = 0; (ch = fgetc(fp)) != EOF; j++) {
                if ((j % 12) == 0) {
                    printf("%s", "\n ");
                }
                printf(" %#04x,", ch);
            }

            printf("%s", " 0x00\n};\n");
            fclose(fp);
        }
    }

    printf("%s", "\nconst struct file_array {\n");
    printf("%s", "  const char *name;\n");
    printf("%s", "  const unsigned char *data;\n");
    printf("%s", "  size_t size;\n");
    printf("%s", "} files[] = {\n");

    for (i = 1; i < argc; i++) {
        char* tmp = argv[i] + 2;
        printf("  {\"%s\", v%d, sizeof(v%d) - 1},\n", tmp, i, i);
    }
    printf("%s", "  {NULL, NULL, 0}\n");
    printf("%s", "};\n\n");
    printf("%s", code);
    printf("\n");
    printf("%s", reconstruct);

    return EXIT_SUCCESS;
}
