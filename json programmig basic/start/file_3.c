#include <stdio.h>

int main(void)
{
  FILE *fp;
  int c;

  // w와 a
  fp = fopen("test.txt", "w");

  if(fp == NULL){
    printf("파일열기 실패\n");
  } else {
    printf("파일열기 성공\n");
  }
  
  fputc('a', fp);
  fputc('b', fp);
  fputc('x', fp);


  fclose(fp);
  return 0;
}




