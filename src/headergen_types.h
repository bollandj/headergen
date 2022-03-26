#pragma once

#define HEADERGEN_MAX_NAME_LENGTH 31
#define HEADERGEN_MAX_DESCRIPTION_LENGTH 127

typedef enum {
    HEADERGEN_DOCUMENT_START, 
    HEADERGEN_DOCUMENT_END,
    HEADERGEN_BLOCK_START,
    HEADERGEN_BLOCK_END,
    HEADERGEN_KEY,
    HEADERGEN_VALUE
} headergen_token_type_t;

typedef struct {

    /** Token type */
    headergen_token_type_t type;
    
    /** Token data */          
    void *data;    

} headergen_token_t;

typedef struct {

    /** Option name - will be used to name the macros corresponding to this option */
    char name[HEADERGEN_MAX_NAME_LENGTH + 1];

    /** Option description (optional) - will appear as a Doxygen inline comment */
    char description[HEADERGEN_MAX_DESCRIPTION_LENGTH + 1];

    /** Option value - field value which corresponds to this option */
    uint32_t value;

} headergen_opt_t;

typedef struct {

    /** Field name - will be used to name the macros corresponding to this field */
    char name[HEADERGEN_MAX_NAME_LENGTH + 1];

    /** Field description (optional) - will appear as a Doxygen inline comment */
    char description[HEADERGEN_MAX_DESCRIPTION_LENGTH + 1];

    /** Field position - the index of the LSB of this field */
    uint8_t position;

    /** Field width - total width of field in bits */
    uint8_t width;

} headergen_fld_t;

typedef struct {

    /** Register name - will be used to name the macros corresponding to this register */
    char name[HEADERGEN_MAX_NAME_LENGTH + 1];

    /** Register description (optional) - will appear as a Doxygen inline comment */           
    char description[HEADERGEN_MAX_DESCRIPTION_LENGTH + 1]; 

    /** Register address */   
    uint32_t address;

    /** Register width - total width of register in bits */
    uint8_t width;

} headergen_reg_t;

typedef struct {

    /** Device name - will be used to name and title the resulting header file */
    char name[HEADERGEN_MAX_NAME_LENGTH + 1]; 

    /** Device description - a brief description of device function e.g. LED driver */          
    char description[HEADERGEN_MAX_DESCRIPTION_LENGTH + 1];  

} headergen_dev_t;

typedef struct {
    headergen_dev_t *devices;
} headergen_root_t;

