#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ini.h"

#define MAX_LINE 256
#define MAX_SECTION 56
#define MAX_NAME 56

struct ini_t {
    char *data;
    size_t size;
};

static char* strstrip(char *s) {
    size_t len;
    char *end;

    while (*s && *s <= ' ') s++;
    len = strlen(s);
    if (!len) return s;
    end = s + len - 1;
    while (end >= s && *end <= ' ') end--;
    *(end + 1) = '\0';
    return s;
}

ini_t* ini_load(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return NULL;
    
    ini_t *ini = malloc(sizeof(ini_t));
    if (!ini) {
        fclose(file);
        return NULL;
    }
    
    fseek(file, 0, SEEK_END);
    ini->size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    ini->data = malloc(ini->size + 1);
    if (!ini->data) {
        fclose(file);
        free(ini);
        return NULL;
    }
    
    fread(ini->data, 1, ini->size, file);
    fclose(file);
    ini->data[ini->size] = '\0';
    
    return ini;
}

void ini_free(ini_t *ini) {
    if (ini) {
        free(ini->data);
        free(ini);
    }
}

const char* ini_get(ini_t *ini, const char *section, const char *key) {
    char current_section[MAX_SECTION] = "";
    char line[MAX_LINE];
    const char *ptr = ini->data;
    const char *end = ini->data + ini->size;
    
    while (ptr < end) {
        const char *eol = strchr(ptr, '\n');
        if (!eol) eol = end;
        
        size_t len = eol - ptr;
        if (len >= MAX_LINE) len = MAX_LINE - 1;
        memcpy(line, ptr, len);
        line[len] = '\0';
        ptr = eol + 1;
        
        char *stripped = strstrip(line);
        if (*stripped == ';' || *stripped == '#') continue;
        
        if (*stripped == '[') {
            char *close = strchr(stripped, ']');
            if (!close) continue;
            *close = '\0';
            strncpy(current_section, stripped + 1, MAX_SECTION);
        } else if (*stripped) {
            char *eq = strchr(stripped, '=');
            if (!eq) continue;
            *eq = '\0';
            char *k = strstrip(stripped);
            char *v = strstrip(eq + 1);
            
            if (strcmp(current_section, section) == 0 && strcmp(k, key) == 0) {
                return v;
            }
        }
    }
    
    return NULL;
}

int ini_sget(ini_t *ini, const char *section, const char *key, const char *scanfmt, void *dst) {
    const char *val = ini_get(ini, section, key);
    if (!val) return 0;
    return sscanf(val, scanfmt, dst) == 1;
}
