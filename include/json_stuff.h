#ifndef JSON_STUFF_H
#define JSON_STUFF_H

typedef struct SJList_S SJList;
typedef struct SJString_S SJString;
typedef struct SJson_S SJson;

void sj_empty(SJson *js);
/**
* @brief frees a previously loaded json struct
*/

SJson *sj_copy(SJson *json);
/**
* @brief make a duplicate of a json structure.
* @note the duplicate needs to be sj_free()'d separately
* @param json the json to be duplicated
* @return NULL on error, or a Duplicate json
*/

SJson *sj_load(const char *file);
/**
* @brief loads and parses a json file
* @param filename the file to parse
* @return NULL on error or an SJS pointer
*/

void sj_save(SJson *json, char *file);
/**
* @brief write a json value as a formatted json string to file
* @param json the struct to convert and write
* @param filename the file to overwrite
*/

SJson *sj_new_string(char *string);
/**
* @brief make a new json value that is a string
* @param str the string to base the json value on
* @return NULL on error or a new json that holds a string value
*/

const char *sj_string_value(SJson *json);
/**
* @brief get the JSON value as a string
* @param json the json value to get the string from
* @return NULL if the provided json was not a string or on error, the string otherwise
*/

int sj_integer_value(SJson *json, int i);
/**
* @brief get the json value as an integer
* Can be used to check for existence
* @param json the json value to get from
* @param i [optional] place to write the output to
* @return 0 if the json did not contain an integer or if there was an error, 1 otherwise
*/

#endif