//
// Created by happy on 2023-09-30.
//
#include <stdio.h>
#include "json_c.c"

typedef struct{
    char name[10];
    char age[4];
    int height;
    char h;
}student;

int main(void){
    const char *str = "{\"data\":[{\"name\": \"red\", \"age\": \"#f00\", \"height\" : 170}, {\"name\": \"green\", \"age\": \"#0f0\",\"height\" : 190}, {\"name\": \"blue\", \"age\": \"#00f\",\"height\" : 160}, {\"name\": \"cyan\", \"age\": \"#0ff\",\"height\" : 120}, {\"name\": \"magenta\", \"age\": \"#f0f\",\"height\" : 220}, {\"name\": \"yellow\", \"age\": \"#ff0\",\"height\" : 300}, {\"name\": \"black\", \"age\": \"#000\",\"height\" : 100}]}";
    int num;


    json_value json = json_create(str);
    json_value data = json_get(json, "data");
    int data_size = json_len(data);

    while(1) {
        printf("몇 명의 데이터를 저장할건지 입력하시오(0 ~ %d): ", data_size - 1);
        scanf("%d", &num);
        if (num < 0 || num >= data_size) {
            printf("범위 내의 값을 입력하시오.\n");
        }
        else
            break;
    }
    student *s = (student *) malloc(sizeof(student) * num);
    for(int i = 0; i<num; i++){
        printf("Data[%d] : ", i);
        json_value obj = json_get(data, i);

        strcpy(s[i].name,json_get_string(obj,"name"));
        strcpy(s[i].age, json_get_string(obj, "age"));
        s[i].height = json_get_int(obj, "height");

        printf("%s %s %d\n", s[i].name,s[i].age,s[i].height);
    }
    printf("\n");
    for(int i = 0; i <data_size - 1; i++){
        printf("Data[%d] : ", i);
        json_value obj = json_get(data, i);
        printf("%s %s %d\n", json_get_string(obj, "name"), json_get_string(obj, "age"), json_get_int(obj, "height"));

    }

    //이름, 나이도 비슷하게 구현 가능하므로 생략 ㅎㅎ
    int h;
    printf("\n제한 할 키를 입력하시오. ");
    scanf("%d", &h);
    for (int i = 0; i < data_size - 1; i++) {
        json_value obj = json_get(data, i);
        if(json_get_int(obj, "height")<=h) {
            printf("Data[%d] : ", i);
            printf("%s %s %d\n", json_get_string(obj, "name"), json_get_string(obj, "age"),
                   json_get_int(obj, "height"));
        }
    }
    free(s);
    FILE *fp;
    char file_buff[100];
    s = (student*)malloc(sizeof(student)*data_size);

    fp = fopen("practice.txt", "w");
    if (fp == NULL) printf("파일열기 실패\n");
    else printf("파일열기 성공\n");

    for(int i = 0; i<data_size; i++){
        json_value obj = json_get(data, i);

        strcpy(s[i].name, json_get_string(obj, "name"));
        strcpy(s[i].age, json_get_string(obj, "age"));
        s[i].height = json_get_int(obj, "height");
        fputs(s[i].name, fp);
        fputs(" ", fp);
        fputs(s[i].age, fp);
        fputs(" ", fp);
        fprintf(fp,"%d",s[i].height);
        fputs("\n",fp);

    }
    fclose(fp);

    fp = fopen("practice.txt", "r");

    //한문자씩 읽는 fgetc
    int c;
   int count = 0;
   while((c = fgetc(fp)) != EOF){
     putchar(c);
     count++;
   }
   fclose(fp);

    char d_s[10];
    char buff_size[sizeof(count)];

    printf("지우고 싶은 줄의 이름을 입력하시오: ");
    scanf("%s", d_s);
    fopen("practice.txt", "r+");

    while(fgets(buff_size,count,fp) != NULL){

    }
    return 0;

}