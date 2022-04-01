#pragma once

#include <stdio.h>
#include <stdint.h>

#include "headergen_types.h"

#define HEADERGEN_POSITION_SUFFIX "Pos"
#define HEADERGEN_MASK_SUFFIX "Msk"
#define HEADERGEN_VALUE_SUFFIX "Val"
#define HEADERGEN_SEPARATOR "_"

#define HEADERGEN_DOXYGEN_BLOCK_COMMENT_START "/**"
#define HEADERGEN_DOXYGEN_BLOCK_COMMENT_END "*/"

#define HEADERGEN_DOXYGEN_INLINE_COMMENT_START "/**<"
#define HEADERGEN_DOXYGEN_INLINE_COMMENT_END "*/"

int headergen_write_device_macros(FILE *fh, headergen_dev_t *dev);
int headergen_write_register_macros(FILE *fh, headergen_dev_t *dev, headergen_reg_t *reg);
int headergen_write_field_macros(FILE *fh, headergen_dev_t *dev, headergen_reg_t *reg, headergen_fld_t *fld);
int headergen_write_option_macros(FILE *fh, headergen_dev_t *dev, headergen_reg_t *reg, headergen_fld_t *fld, headergen_opt_t *opt);