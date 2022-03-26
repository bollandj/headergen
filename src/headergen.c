#include "headergen.h"

#include <ctype.h>
#include <string.h>

/*

static void strtoupper(char *dst, const char *src)
{
    while (*src)
    {
        *dst++ = (char)toupper(*src++);
    }
    
    *dst = '\0';
}

*/

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



#define HEADERGEN_KEY(key_in, key_str, key_enum)    \
do {                                                \
    if (strcmp((key_in), (key_str)) == 0)           \
        return (key_enum);                          \
} while (0)

static int headergen_parse_key(const char *key)
{
    HEADERGEN_KEY(key, "name",          HEADERGEN_MEMBER_NAME);
    HEADERGEN_KEY(key, "description",   HEADERGEN_MEMBER_DESCRIPTION);
    HEADERGEN_KEY(key, "address",       HEADERGEN_MEMBER_ADDRESS);
    HEADERGEN_KEY(key, "position",      HEADERGEN_MEMBER_POSITION);
    HEADERGEN_KEY(key, "width",         HEADERGEN_MEMBER_WIDTH);
    HEADERGEN_KEY(key, "value",         HEADERGEN_MEMBER_VALUE);

    // add device/register/field/option here as well?
        
    return HEADERGEN_MEMBER_INVALID;
}

/** Populate the correct struct field, making conversions (e.g. str to int) where necessary and pre-formatting */ // NOTE: could always use strings for everything?
static int headergen_populate_info(headergen_parser_t *parser, const char *data)
{
    switch (parser->level)
    {
    case HEADERGEN_DEVICE:

        switch (parser->member)
        {
        case HEADERGEN_MEMBER_NAME:
            strntoupper(parser->current_dev->name, data, HEADERGEN_MAX_NAME_LENGTH);
            break;

        case HEADERGEN_MEMBER_DESCRIPTION:
            strncpy(parser->current_dev->description, HEADERGEN_MAX_DESCRIPTION_LENGTH);
            break;

        default:
            break;
        }

        break;

    case HEADERGEN_REGISTER:

        switch (parser->member)
        {
        case HEADERGEN_MEMBER_NAME:
            strntoupper(parser->current_reg->name, data, HEADERGEN_MAX_NAME_LENGTH);
            break;

        case HEADERGEN_MEMBER_DESCRIPTION:
            strncpy(parser->current_reg->description, data, HEADERGEN_MAX_DESCRIPTION_LENGTH);
            break;

        case HEADERGEN_MEMBER_ADDRESS:
            break;

        case HEADERGEN_MEMBER_WIDTH:
            break;

        default:
            break;
        }

        break;

    case HEADERGEN_FIELD:

        switch (parser->member)
        {
        case HEADERGEN_MEMBER_NAME:
            strntoupper(parser->current_fld->name, data, HEADERGEN_MAX_NAME_LENGTH);
            break;

        case HEADERGEN_MEMBER_DESCRIPTION:
            strncpy(parser->current_fld->description, data, HEADERGEN_MAX_DESCRIPTION_LENGTH);
            break;

        case HEADERGEN_MEMBER_POSITION:
            break;

        case HEADERGEN_MEMBER_WIDTH:
            break;

        default:
            break;
        }

        break;

    case HEADERGEN_OPTION:

        switch (parser->member)
        {
        case HEADERGEN_MEMBER_NAME:
            strntoupper(parser->current_opt->name, data, HEADERGEN_MAX_NAME_LENGTH);
            break;

        case HEADERGEN_MEMBER_DESCRIPTION:
            strncpy(parser->current_opt->description, data, HEADERGEN_MAX_DESCRIPTION_LENGTH);
            break;

        case HEADERGEN_MEMBER_VALUE:
            break;

        default:
            break;
        }

        break;

    default:
        break;
    }

    return 0;
}

void headergen_parser_init(headergen_parser_t *parser)
{
    parser->level = HEADERGEN_DEVICE;
    parser->member = HEADERGEN_MEMBER_NAME;
    parser->root = malloc(sizeof(headergen_node_t));
}

void headergen_parser_delete(headergen_parser_t *parser)
{
    free(parser->root);
}

/** Consume a token from the language parser */
int headergen_process_token(headergen_parser_t *parser, headergen_token_t token)
{
    switch ((int)token.type)
    {        
    case HEADERGEN_DOCUMENT_START:
        break;
        
    case HEADERGEN_DOCUMENT_END:
        break;
        
    case HEADERGEN_BLOCK_START:
        parser->level++;  

        if (parser->level == HEADERGEN_DEVICE) 
        {
            parser->current_dev = headergen_tree_add_child(parser->root);    
        }
        else if (parser->level == HEADERGEN_REGISTER)
        {
            parser->current_reg = headergen_tree_add_child(parser->current_dev);    
        }
        else if (parser->level == HEADERGEN_FIELD)
        {
            parser->current_fld = headergen_tree_add_child(parser->current_reg);     
        }
        else if (parser->level == HEADERGEN_OPTION)
        {
            parser->current_opt = headergen_tree_add_child(parser->current_fld);    
        }
        break;
        
    case HEADERGEN_BLOCK_END:
        if (parser->level == HEADERGEN_DEVICE) 
        {
            //printf("device: name: %s description: %s\n", info.dev.name, info.dev.description);
            
        }
        else if (parser->level == HEADERGEN_REGISTER)
        {
            //printf("register: name: %s description: %s\n", info.reg.name, info.reg.description);
            
        }
        else if (parser->level == HEADERGEN_FIELD)
        {
            //printf("field: name: %s description: %s\n", info.fld.name, info.fld.description);
            
        }
        else if (parser->level == HEADERGEN_OPTION)
        {
            //printf("option: name: %s description: %s\n", info.opt.name, info.opt.description);
            
        }
        parser->level--;
        
        break;
        
    case HEADERGEN_KEY:
        parser->member = headergen_parse_key(token.data);
        break;
        
    case HEADERGEN_VALUE:
        headergen_populate_info(parser, (const char *)token.data);
        break;
        
    default:
        break;
        
    }

    // printf("headergen: Current level: %d Current member: %d \n", level, member);

    return 0;
}

