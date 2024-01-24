#include <stdio.h>
#include <string.h>
#include "json_c.c"

struct Data {
    char nodetype[30];
    char type[10];
    char name[30];
};

void find_IF(json_value v);

int num_if;

int main() {
    FILE *fp = fopen("json_sudoku.json", "r");
    if (fp == NULL) {
        printf("error\n");
    }
    // 파일의 크기를 얻기 위해 파일의 끝으로 이동하고 현재 위치(ftell)를 얻는다.
    fseek(fp, 0L, SEEK_END);
    long bufsize = ftell(fp);
    fseek(fp, 0L, SEEK_SET);  // 다시 파일의 시작으로 이동

    char *str = (char *) malloc(bufsize + 1);
    if (str == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }


    fread(str, 1, bufsize, fp);
    str[bufsize] = '\0';  // 문자열의 끝을 나타내기 위해 NULL 문자를 추가

    json_value json = json_create(str);

    json_value ext = json_get(json, "ext");
    int data_size = json_len(ext);

    struct Data data[100];

    int count = 0;
    int total = 0;

    for (int i = 0; i < data_size; i++) {

        json_value v = json_get(ext, i);

        char *nodetype = json_get_string(v, "_nodetype");
        num_if = 0;

        if (strcmp(nodetype, "FuncDef") == 0) {
            //함수 갯수 구하기
            count++;
            json_value decl = json_get(v, "decl");
            //함수 이름 구하기
            strcpy(data[count].nodetype, nodetype);
            strcpy(data[count].name, json_get_string(decl, "name"));
            printf("Data.nodetype[%d] : %s\n", count, data[count].nodetype);
            printf("Data.name[%d] : %s\n", count, data[count].name);

            //함수 리턴타입 구하기
            json_value out_type = json_get(decl, "type");
            json_value in_type = json_get(out_type, "type");
            json_value last_type = json_get(in_type, "type");

            char *coord = json_get_string(last_type, "coord");

            json_value type = json_get(last_type, "names");
            char *return_type = json_get_string(type, 0);
            strcpy(data[count].type, return_type);

            printf("Data.returnType[%d] : %s\n", count, data[count].type);

            //함수 파라미터 타입, 변수명 구하기
            json_value item = json_get_from_array((json_array *) ext.value, i);
            if (item.type == JSON_OBJECT) {
                json_value decl = json_get(item, "decl");
                if (decl.type == 0) {
                    printf("decl.type %d == 0\n\n\n\n", i);
                    continue;
                }
                if (decl.type == JSON_OBJECT) {
                    json_value type_1 = json_get(decl, "type");
                    if (type_1.type == JSON_OBJECT) {
                        json_value args = json_get(type_1, "args");
                        if (args.type == JSON_OBJECT) {
                            json_value params = json_get(args, "params");
                            if (params.type == JSON_ARRAY) {
                                for (int j = 0; j <= 1; j++) {
                                    json_value item2 = json_get_from_array((json_array *) params.value, j);
                                    if (item2.type == JSON_OBJECT) {
                                        json_value type_2 = json_get(item2, "type");
                                        if (type_2.type == JSON_OBJECT) {
                                            json_value type_3 = json_get(type_2, "type");
                                            if (type_3.type == JSON_OBJECT) {
                                                {
                                                    json_value names = json_get(type_3, "names");
                                                    if (names.type == JSON_ARRAY) {
                                                        json_value item3 = json_get_from_array(
                                                                (json_array *) names.value, 0);
                                                        if (item3.type == JSON_STRING)
                                                            printf("type : %s ,", json_get_string(item3));
                                                    }
                                                }
                                            }
                                        }
                                        json_value name = json_get(item2, "name");
                                        printf("parameter %d : %s\n", j, json_get_string(name));
                                    }
                                }
                            }
                        } else {
                            printf("No parameter\n");
                        }
                    }
                }
            }
            //함수 if문 갯수 구하기 (else는 count하지 않음)
            json_value body = json_get(v, "body");
            json_value items = json_get(body, "block_items");
            for (int j = 0; j < json_len(items); j++) {
                json_value item = json_get(items, j);
                find_IF(item);
            }
            total += num_if;
            if (num_if != 0)
                printf("num_if : %d\n\n", num_if);

            json_free(decl);
        }
    }
    printf("total if num : %d\n", total);

    printf("Function Number : %d\n", count);
    json_free(ext);
    json_free(ext);
    json_free(json);
    fclose(fp);

    return 0;
}

void find_IF(json_value v) {
    char *s = json_get_string(v, "_nodetype");
    if (strcmp(s, "Compound") == 0) {
        json_value j = json_get(v, "block_items");
        for (int i = 0; i < json_len(j); i++) {
            json_value js = json_get(j, i);
            find_IF(js);
        }
    } else if (strcmp(s, "For") == 0) {
        json_value j = json_get(v, "stmt");
        find_IF(j);
    } else if (strcmp(s, "If") == 0) {
        json_value js = json_get(v, "iffalse");
        json_value jso = json_get(v, "iftrue");
        if (js.value != NULL) {
            find_IF(js);
        }
        if (jso.value != NULL) {
            find_IF(jso);
        }
        num_if++;
    } else if (strcmp(s, "Switch") == 0) {
        json_value j = json_get(v, "stmt");
        find_IF(j);
    } else if (strcmp(s, "Case") == 0) {
        json_value j = json_get(v, "stmts");
        for (int i = 0; i < json_len(j); i++) {
            json_value js = json_get(j, i);
            find_IF(js);
        }
    } else if (strcmp(s, "Label") == 0) {
        json_value j = json_get(v, "stmt");
        find_IF(j);
    }
    return;
}