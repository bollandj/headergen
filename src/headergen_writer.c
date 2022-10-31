#include "headergen_writer.h"

#include "headergen_utils.h"

int headergen_write_device_macros(FILE *fh, struct headergen_node_info *node_info)
{
    printf("Writing device macros\n");
    return 0;
}

int headergen_write_register_macros(FILE *fh, struct headergen_node_info *node_info)
{
    printf("Writing register macros\n");
    return 0;
}

int headergen_write_field_macros(FILE *fh, struct headergen_node_info *node_info)
{
    char prefix[128];
    char comment[256];

    printf("Writing field macros\n");

    snprintf(prefix, sizeof(prefix), "%s%s%s%s%s",
                node_info->dev.name,
                HEADERGEN_SEPARATOR,
                node_info->reg.name,
                HEADERGEN_SEPARATOR,
                node_info->fld.name);

    snprintf(comment, sizeof(comment), "%s%s%s",
                node_info->fld.name,
                *node_info->fld.description ? " - " : "",
                *node_info->fld.description ? node_info->fld.description : "");

    strntouppersnakecase(prefix, prefix, sizeof(prefix));
    strntouppersnakecase(comment, comment, sizeof(comment));

    /* Field position */
    fprintf(fh, "#define %s%s%s %d ",
            prefix,
            HEADERGEN_SEPARATOR,
            HEADERGEN_POSITION_SUFFIX,

            node_info->fld.position);

    /* Field description */
    fprintf(fh, "%s %s%s%s %s\n",
            HEADERGEN_DOXYGEN_INLINE_COMMENT_START,
            node_info->fld.name,
            *node_info->fld.description ? " - " : "",
            *node_info->fld.description ? node_info->fld.description : "",
            HEADERGEN_DOXYGEN_INLINE_COMMENT_END);

    /* Field mask */
    fprintf(fh, "#define %s%s%s (0x%X << %s%s%s)\n",
            prefix,
            HEADERGEN_SEPARATOR,
            HEADERGEN_MASK_SUFFIX,

            (1 << node_info->fld.width) - 1,

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

int headergen_write_option_macros(FILE *fh, struct headergen_node_info *node_info)
{
    // TODO: make these non-arbitrary values
    char prefix_fld[128];
    char prefix_opt[192];
    char comment[256];

    printf("Writing option macros\n");

    snprintf(prefix_fld, sizeof(prefix_fld), "%s%s%s%s%s",
                node_info->dev.name,
                HEADERGEN_SEPARATOR,
                node_info->reg.name,
                HEADERGEN_SEPARATOR,
                node_info->fld.name);

    snprintf(prefix_opt, sizeof(prefix_opt), "%s%s%s",
                prefix_fld,
                HEADERGEN_SEPARATOR,
                node_info->opt.name);

    snprintf(comment, sizeof(comment), "%s%s%s",
                node_info->opt.name,
                *node_info->opt.description ? " - " : "",
                *node_info->opt.description ? node_info->opt.description : "");

    strntouppersnakecase(prefix_fld, prefix_fld, sizeof(prefix_fld));
    strntouppersnakecase(prefix_opt, prefix_opt, sizeof(prefix_opt));
    strntouppersnakecase(comment, comment, sizeof(comment));

    /* Option value */
    fprintf(fh, "#define %s%s%s 0x%X ",
            prefix_opt,
            HEADERGEN_SEPARATOR,
            HEADERGEN_VALUE_SUFFIX,
            
            node_info->opt.value); 

    /* Option description */
    fprintf(fh, "%s %s%s%s %s\n",
            HEADERGEN_DOXYGEN_INLINE_COMMENT_START,
            node_info->opt.name,
            *node_info->opt.description ? " - " : "",
            *node_info->opt.description ? node_info->opt.description : "",
            HEADERGEN_DOXYGEN_INLINE_COMMENT_END);

    /* Option value mask */
    fprintf(fh, "#define %s (%s%s%s << %s%s%s)\n",
            prefix_opt,

            prefix_opt,
            HEADERGEN_SEPARATOR,
            HEADERGEN_VALUE_SUFFIX,
            
            prefix_fld,
            HEADERGEN_SEPARATOR,
            HEADERGEN_VALUE_SUFFIX); 

    return 0;
}