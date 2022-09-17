
#include <stdio.h>
#include <assert.h>

#include "headergen_writer.h"

int main(void) 
{
    headergen_dev_t dev = {
        .name = "IS31FL3237",
        .description = "36-channel LED driver"
    };

    headergen_reg_t reg = {
        .name = "Control",
        .description = "Power control register",
        .address = 0x00,
        .width = 8
    };

    headergen_fld_t fld = {
        .name = "SSD",
        .description = "Software Shutdown Enable",
        .position = 0,
        .width = 1
    };

    headergen_opt_t opt0 = {
        .name = "Shutdown",
        .description = "Shutdown mode enabled",
        .value = 0
    };

    headergen_opt_t opt1 = {
        .name = "Normal",
        .description = "Normal operation",
        .value = 1
    };

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