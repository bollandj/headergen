#include <stdio.h>
#include <yaml.h>

#include "headergen_parser.h"

int main(void) 
{
    FILE *fh = fopen("../../test.yaml", "r");
    yaml_parser_t parser;
    yaml_token_t token;
    headergen_parser_t headergen_parser;
    headergen_token_t headergen_token;

    /* Initialize parser */
    if (!yaml_parser_initialize(&parser))
        fputs("Failed to initialize parser!\n", stderr);
    if (fh == NULL)
        fputs("Failed to open file!\n", stderr);

    /* Set input file */
    yaml_parser_set_input_file(&parser, fh);

    headergen_parser_init(&headergen_parser);

    do 
    {
        yaml_parser_scan(&parser, &token);
        switch (token.type) 
        {
            /* Stream start/end */
            case YAML_STREAM_START_TOKEN:
            // puts("STREAM START");
            headergen_token.type = HEADERGEN_DOCUMENT_START;
            headergen_token.data = NULL;
            headergen_process_token(&headergen_parser, headergen_token);
            break;

            case YAML_STREAM_END_TOKEN:
            // puts("STREAM END");
            headergen_token.type = HEADERGEN_DOCUMENT_END;
            headergen_token.data = NULL;
            headergen_process_token(&headergen_parser, headergen_token);
            break;

            /* Key/value */
            case YAML_KEY_TOKEN:
            // printf("(Key token)   ");
            /* Set token type - no data to send to parser yet */
            headergen_token.type = HEADERGEN_KEY;
            headergen_token.data = NULL;  
            break;

            case YAML_VALUE_TOKEN:
            // printf("(Value token) ");
            /* Set token type - no data to send to parser yet */
            headergen_token.type = HEADERGEN_VALUE;
            headergen_token.data = NULL; 
            break;

            /* Block delimiters */
            case YAML_BLOCK_SEQUENCE_START_TOKEN:
            // puts("<b>Start Block (Sequence)</b>");
            break;

            case YAML_BLOCK_ENTRY_TOKEN:
            // puts("<b>Start Block (Entry)</b>");        
            break;

            case YAML_BLOCK_END_TOKEN:
            // puts("<b>End block</b>");
            headergen_token.type = HEADERGEN_BLOCK_END;
            headergen_token.data = NULL;
            headergen_process_token(&headergen_parser, headergen_token);
            break;

            /* Data */
            case YAML_BLOCK_MAPPING_START_TOKEN:
            // puts("[Block mapping]");
            headergen_token.type = HEADERGEN_BLOCK_START;
            headergen_token.data = NULL;
            headergen_process_token(&headergen_parser, headergen_token); 
            break;

            case YAML_SCALAR_TOKEN:
            // printf("Scalar %s \n", token.data.scalar.value);
            headergen_token.data = token.data.scalar.value;
            headergen_process_token(&headergen_parser, headergen_token);
            break;

            default:
            // printf("Got token of type %d\n", token.type);
            break;
        }

        if (token.type != YAML_STREAM_END_TOKEN)
            yaml_token_delete(&token);

    } while (token.type != YAML_STREAM_END_TOKEN);

    yaml_token_delete(&token); 
    yaml_parser_delete(&parser);
    fclose(fh);

    fh = fopen("test_output.c", "w");

    if (fh == NULL)
        fputs("Failed to open file!\n", stderr);
    else
        fputs("Opened file\n", stdout);

    headergen_write(fh, &headergen_parser);
    headergen_parser_delete(&headergen_parser);

    return 0;
}