#pragma once

#include <stdint.h>
#include <stdio.h>

#include "headergen_types.h"

enum headergen_level
{
    HEADERGEN_LEVEL_ROOT=0,
    HEADERGEN_LEVEL_DEVICE,
    HEADERGEN_LEVEL_REGISTER,
    HEADERGEN_LEVEL_FIELD,
    HEADERGEN_LEVEL_OPTION
};

enum headergen_member
{
    HEADERGEN_MEMBER_INVALID=-1,
    HEADERGEN_MEMBER_NAME=0,
    HEADERGEN_MEMBER_DESCRIPTION,
    HEADERGEN_MEMBER_ADDRESS,
    HEADERGEN_MEMBER_POSITION,
    HEADERGEN_MEMBER_WIDTH,
    HEADERGEN_MEMBER_VALUE
};

struct headergen_parser {
    enum headergen_level level;
    enum headergen_member member;

    headergen_node_t *root;

    headergen_node_t *current_dev_node;
    headergen_node_t *current_reg_node;
    headergen_node_t *current_fld_node;
    headergen_node_t *current_opt_node;
};

void headergen_parser_init(struct headergen_parser *parser);
void headergen_parser_delete(struct headergen_parser *parser);

int headergen_process_token(struct headergen_parser *parser, headergen_token_t token);

void headergen_write(FILE *fh, struct headergen_parser *parser);

