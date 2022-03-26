#include "headergen_writer.h"

int headergen_write_device_macros(headergen_dev_t *dev, FILE *fh)
{
    /*
    info->dev.name;
    info->dev.description;
    */

    return 0;
}

int headergen_write_register_macros(headergen_dev_t *dev, headergen_reg_t *reg, FILE *fh)
{
    /*
    info->dev.name;

    info->reg.name;
    info->reg.description;
    info->reg.address;
    info->reg.width;
    */

    return 0;
}

int headergen_write_field_macros(headergen_dev_t *dev, headergen_reg_t *reg, headergen_fld_t *fld, FILE *fh)
{
    char fld_prefix[128];
    char fld_comment[128];

    /* Field prefix */
    snprintf(fld_prefix, sizeof(fld_prefix), "%s%s%s%s%s",
                dev->name,
                HEADERGEN_SEPARATOR,
                reg->name,
                HEADERGEN_SEPARATOR,
                fld->name);

    /* Field comment */
    snprintf(fld_comment, sizeof(fld_comment), "%s%s%s",
                fld->name,
                fld->description ? " - " : "",
                fld->description);

    /* Field position */
    fprintf(fh, "#define %s%s%s %d ",
            fld_prefix,
            HEADERGEN_SEPARATOR,
            HEADERGEN_POSITION_SUFFIX,
            fld->position);

    /* Field position description*/
    fprintf(fh, "%s %s%s%s %s\n",
            HEADERGEN_DOXYGEN_INLINE_COMMENT_START,
            fld->name,
            fld->description ? " - " : "",
            fld->description,
            HEADERGEN_DOXYGEN_INLINE_COMMENT_END);

    /* Field mask */
    fprintf(fh, "#define %s%s%s (0x%X << %s%s%s)\n",
            fld_prefix,
            HEADERGEN_SEPARATOR,
            HEADERGEN_MASK_SUFFIX,
            (1 << fld->width) - 1,
            fld_prefix,
            HEADERGEN_SEPARATOR,
            HEADERGEN_POSITION_SUFFIX); 

    return 0;
}

int headergen_write_option_macros(headergen_dev_t *dev, headergen_reg_t *reg, headergen_fld_t *fld, headergen_opt_t *opt, FILE *fh)
{
    /*
    dev->name;

    reg->name;

    fld->name;
    fld->description;

    opt->name;
    opt->description;
    opt->value;
    */

    return 0;
}