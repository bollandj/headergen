#pragma once

#include <stdint.h>
#include <stdio.h>

#include "headergen_types.h"
#include "headergen_tree.h"

enum headergen_level
{
    HEADERGEN_LEVEL_UNDERRUN=0,
    HEADERGEN_LEVEL_DEVICE,
    HEADERGEN_LEVEL_REGISTER,
    HEADERGEN_LEVEL_FIELD,
    HEADERGEN_LEVEL_OPTION,
    HEADERGEN_LEVEL_OVERRUN
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

typedef struct {
    enum headergen_level level;
    enum headergen_member member;

    headergen_node_t *root;

    headergen_node_t *current_dev_node;
    headergen_node_t *current_reg_node;
    headergen_node_t *current_fld_node;
    headergen_node_t *current_opt_node;
} headergen_parser_t;

void headergen_parser_init(headergen_parser_t *parser);
void headergen_parser_delete(headergen_parser_t *parser);

int headergen_process_token(headergen_parser_t *parser, headergen_token_t token);

