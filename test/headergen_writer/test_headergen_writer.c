
#include <stdio.h>
#include <assert.h>

#include "headergen_writer.h"
#include "headergen_types.h"

int main(void) 
{
    FILE *fh = fopen("test_output.h", "w");

    if (fh == NULL)
        fputs("Failed to open file!\n", stderr);
    else
        fputs("Opened file\n", stdout);

    struct headergen_node_info node_info = {
        .dev = {
            .name = "IS31FL3237",
            .description = "36-channel LED driver with 16-bit PWM"
        },
        .reg = {
            .name = "Temperature Sensor",
            .description = "Temperature sensor register",
            .address = 0x00,
            .width = 8
        },
        .fld = {
            .name = "TROF",
            .description = "Thermal roll off percentage of output current",
            .position = 6,
            .width = 2
        },
        .opt = {
            .name = "75 percent",
            .description = "75 percent",
            .value = 0x01
        }
    };

    headergen_write_device_macros(fh, &node_info);
    fprintf(fh, "\n");
    headergen_write_register_macros(fh, &node_info);
    fprintf(fh, "\n");
    headergen_write_field_macros(fh, &node_info);
    fprintf(fh, "\n");
    headergen_write_option_macros(fh, &node_info);
    fprintf(fh, "\n");

    fclose(fh);
    fputs("Closed file\n", stdout);
    return 0;
}