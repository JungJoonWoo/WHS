#include <stdio.h>
#include <string.h>
#include <memory.h>


int main(void)
{
	FILE *fp;
	char file_buff[100];
	fp = fopen("test_line.txt", "w");

	if (fp == NULL) printf("���Ͽ��� ����\n");
	else printf("���Ͽ��� ����\n");

	int i;

	for (i = 1; i <= 5; i++) {
		printf("%d���ο� �ۼ��� ������ �Է��ϼ���. \n", i);
		memset(file_buff, 0, sizeof(file_buff));
      //scanf("%s", &file_buff);
		 fgets(file_buff, sizeof(file_buff), stdin); //�����̽���
		file_buff[strlen(file_buff)] = '\n';

		fputs(file_buff, fp);
	}
	fclose(fp);

	fp = fopen("test_line.txt", "r");

	if (fp == NULL) printf("���Ͽ��� ����\n");
	else printf("���Ͽ��� ����\n");

	while(fgets(file_buff, sizeof(file_buff), fp) != NULL){
		printf("%s", file_buff);
		memset(file_buff, 0, sizeof(file_buff));
	}
	fclose(fp);

	return 0;
}