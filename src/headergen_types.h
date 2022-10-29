#pragma once

#define HEADERGEN_MAX_NAME_LENGTH 31
#define HEADERGEN_MAX_DESCRIPTION_LENGTH 127

enum headergen_token_type {
    HEADERGEN_DOCUMENT_START, 
    HEADERGEN_DOCUMENT_END,
    HEADERGEN_BLOCK_START,
    HEADERGEN_BLOCK_END,
    HEADERGEN_KEY,
    HEADERGEN_VALUE
};

struct headergen_token {

    /** Token type */
    enum headergen_token_type type;
    
    /** Token data */          
    void *data;    
};

struct headergen_option {

    /** Option name - will be used to name the macros corresponding to this option */
    char name[HEADERGEN_MAX_NAME_LENGTH + 1];

    /** Option description (optional) - will appear as a Doxygen inline comment */
    char description[HEADERGEN_MAX_DESCRIPTION_LENGTH + 1];

    /** Option value - field value which corresponds to this option */
    uint32_t value;
};

struct headergen_field {

    /** Field name - will be used to name the macros corresponding to this field */
    char name[HEADERGEN_MAX_NAME_LENGTH + 1];

    /** Field description (optional) - will appear as a Doxygen inline comment */
    char description[HEADERGEN_MAX_DESCRIPTION_LENGTH + 1];

    /** Field position - the index of the LSB of this field */
    uint8_t position;

    /** Field width - total width of field in bits */
    uint8_t width;
};

struct headergen_register {

    /** Register name - will be used to name the macros corresponding to this register */
    char name[HEADERGEN_MAX_NAME_LENGTH + 1];

    /** Register description (optional) - will appear as a Doxygen inline comment */           
    char description[HEADERGEN_MAX_DESCRIPTION_LENGTH + 1]; 

    /** Register address */   
    uint32_t address;

    /** Register width - total width of register in bits */
    uint8_t width;
};

struct headergen_device {

    /** Device name - will be used to name and title the resulting header file */
    char name[HEADERGEN_MAX_NAME_LENGTH + 1]; 

    /** Device description - a brief description of device function e.g. LED driver */          
    char description[HEADERGEN_MAX_DESCRIPTION_LENGTH + 1];  
};

struct headergen_node {

    struct headergen_device dev;
    
    struct headergen_register reg;
    
    struct headergen_field fld;
    
    struct headergen_option opt;  
};

