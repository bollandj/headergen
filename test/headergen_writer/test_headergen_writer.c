
#include <stdio.h>
#include <assert.h>

#include "headergen_writer.h"

int main(void) 
{
    FILE *fh = fopen("test_output.c", "w");

    if (fh == NULL)
        fputs("Failed to open file!\n", stderr);
    else
        fputs("Opened file\n", stdout);

    headergen_write_device_macros(fh, &dev);
    fprintf(fh, "\n");
    headergen_write_register_macros(fh, &dev, &reg);
    fprintf(fh, "\n");
    headergen_write_field_macros(fh, &dev, &reg, &fld);
    fprintf(fh, "\n");
    headergen_write_option_macros(fh, &dev, &reg, &fld, &opt0);
    headergen_write_option_macros(fh, &dev, &reg, &fld, &opt1);
    fprintf(fh, "\n");

    fclose(fh);
    fputs("Closed file\n", stdout);
    return 0;
}