#include "headergen_writer.h"

#include <ctype.h>

#if 0

static void strtoupper(char *dst, const char *src)
{
    while (*src)
    {
        *dst++ = (char)toupper(*src++);
    }
    
    *dst = '\0';
}

#endif

static void strntoupper(char *dst, const char *src, size_t n)
{
    size_t i = 0;

    while (*src && i < n)
    {
        *dst++ = (char)toupper(*src++);
        i++;
    }
    
    *dst = '\0';
}

int headergen_write_device_macros(FILE *fh, headergen_dev_t *dev)
{
    printf("Writing device macros\n");
    return 0;
}

int headergen_write_register_macros(FILE *fh, headergen_dev_t *dev, headergen_reg_t *reg)
{
    printf("Writing register macros\n");
    return 0;
}

int headergen_write_field_macros(FILE *fh, headergen_dev_t *dev, headergen_reg_t *reg, headergen_fld_t *fld)
{
    char prefix[128];
    char comment[256];

    printf("Writing field macros\n");

    snprintf(prefix, sizeof(prefix), "%s%s%s%s%s",
                dev->name,
                HEADERGEN_SEPARATOR,
                reg->name,
                HEADERGEN_SEPARATOR,
                fld->name);

    snprintf(comment, sizeof(comment), "%s%s%s",
                fld->name,
                *fld->description ? " - " : "",
                *fld->description ? fld->description : "");

    strntoupper(prefix, prefix, sizeof(prefix));
    strntoupper(comment, comment, sizeof(comment));

    /* Field position */
    fprintf(fh, "#define %s%s%s %d ",
            prefix,
            HEADERGEN_SEPARATOR,
            HEADERGEN_POSITION_SUFFIX,

            fld->position);

    /* Field description */
    fprintf(fh, "%s %s%s%s %s\n",
            HEADERGEN_DOXYGEN_INLINE_COMMENT_START,
            fld->name,
            *fld->description ? " - " : "",
            *fld->description ? fld->description : "",
            HEADERGEN_DOXYGEN_INLINE_COMMENT_END);

    /* Field mask */
    fprintf(fh, "#define %s%s%s (0x%X << %s%s%s)\n",
            prefix,
            HEADERGEN_SEPARATOR,
            HEADERGEN_MASK_SUFFIX,

            (1 << fld->width) - 1,

            prefix,
            HEADERGEN_SEPARATOR,
            HEADERGEN_POSITION_SUFFIX); 

    /* Field value macro */
    fprintf(fh, "#define %s(value) (%s%s%s & ((value) << %s%s%s))\n",
            prefix,

            prefix,
            HEADERGEN_SEPARATOR,
            HEADERGEN_MASK_SUFFIX,

            prefix,
            HEADERGEN_SEPARATOR,
            HEADERGEN_POSITION_SUFFIX); 

    return 0;
}

int headergen_write_option_macros(FILE *fh, headergen_dev_t *dev, headergen_reg_t *reg, headergen_fld_t *fld, headergen_opt_t *opt)
{
    // TODO: make these non-arbitrary values
    char prefix_fld[128];
    char prefix_opt[192];
    char comment[256];

    printf("Writing option macros\n");

    snprintf(prefix_fld, sizeof(prefix_fld), "%s%s%s%s%s",
                dev->name,
                HEADERGEN_SEPARATOR,
                reg->name,
                HEADERGEN_SEPARATOR,
                fld->name);

    snprintf(prefix_opt, sizeof(prefix_opt), "%s%s%s",
                prefix_fld,
                HEADERGEN_SEPARATOR,
                opt->name);

    snprintf(comment, sizeof(comment), "%s%s%s",
                opt->name,
                *opt->description ? " - " : "",
                *opt->description ? opt->description : "");

    strntoupper(prefix_fld, prefix_fld, sizeof(prefix_fld));
    strntoupper(prefix_opt, prefix_opt, sizeof(prefix_opt));
    strntoupper(comment, comment, sizeof(comment));

    /* Option value */
    fprintf(fh, "#define %s%s%s 0x%X ",
            prefix_opt,
            HEADERGEN_SEPARATOR,
            HEADERGEN_VALUE_SUFFIX,
            
            opt->value); 

    /* Option description */
    fprintf(fh, "%s %s%s%s %s\n",
            HEADERGEN_DOXYGEN_INLINE_COMMENT_START,
            opt->name,
            *opt->description ? " - " : "",
            *opt->description ? opt->description : "",
            HEADERGEN_DOXYGEN_INLINE_COMMENT_END);

    /* Option value mask */
    fprintf(fh, "#define %s (%s%s%s << %s%s%s))\n",
            prefix_opt,

            prefix_opt,
            HEADERGEN_SEPARATOR,
            HEADERGEN_VALUE_SUFFIX,
            
            prefix_fld,
            HEADERGEN_SEPARATOR,
            HEADERGEN_VALUE_SUFFIX); 

    return 0;
}