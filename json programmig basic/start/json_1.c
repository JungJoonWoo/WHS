#include <stdio.h>
#include "json_c.c"

void my_print_json(json_value j, int index, char *s){
    const char *s1 = json_get_string(j, index, s);
    printf("%s \n", s1);
    putchar('\n');
}

int main(void)
{   
    const char *str = "{\"data\":[{\"color\": \"red\", \"value\": \"#f00\"}, {\"color\": \"green\", \"value\": \"#0f0\"}, {\"color\": \"blue\", \"value\": \"#00f\"}, {\"color\": \"cyan\", \"value\": \"#0ff\"}, {\"color\": \"magenta\", \"value\": \"#f0f\"}, {\"color\": \"yellow\", \"value\": \"#ff0\"}, {\"color\": \"black\", \"value\": \"#000\"}]}";
	//Creation and assignment of a json_value
	//Dynamic allocation used
	json_value json = json_create(str);
    json_value data = json_get(json, "data");
    int data_size = json_len(json);

    //전체 출력
    json_print(json);
    putchar('\n');

    //오브젝트의 color만 출력
    json_value json2 = json_get(json,"data");
    for(int i = 0; i<json_len(json2); i++){
        printf("json2[%d]: ",i);
        json_value obj = json_get(json2,i);
        char *s = json_get_string(obj,"color");
        printf("%s \n",s);
    }
    putchar('\n');

    //오브젝트의 color와 value값 출력
    for (int i = 0; i < json_len(json2); i++) {
        printf("json2[%d]: ", i);
        json_value obj = json_get(json2, i);
        char *s1 = json_get_string(obj, "color");
        char *s2 = json_get_string(obj, "value");

        printf("%s %s\n", s1, s2);
    }
    putchar('\n');

    //오브젝트의 4번째 color값 출력
    const char *s = json_get_string(json2, 3, "color");
    printf("%s \n", s);
    putchar('\n');

    my_print_json(json2,2,"color");

    return 0;
}

