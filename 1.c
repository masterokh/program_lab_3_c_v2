#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale>
#define str_count = 1891715
int str = 1891715;
int errors = 0;
int error_num;
int time, time_temp = 0;
int time_start = 0; 
int a = 0;
int time_global = -100;


int main()
{
    setlocale( LC_ALL,"Russian" );
    FILE *input = fopen("access_log_Jul95.txt", "r");
    printf("Введите первую букву ошибки\n");
    scanf("%d",&error_num);
    printf("ошибки:\n");
    char temp[2000];
    int *times = (int *)malloc((str) * sizeof(int));
    for (int i = 0; i < str; i++)
    {
        fgets(temp, 2000, input);
        for (int j = 0; j < strlen(temp); j++)
        {
            if (j > 1 && temp[j - 2] == '"' && temp[j - 1] == ' ' && temp[j] - '0' == error_num)
            {
                errors++;
               // printf("%s\n", temp);
            }
        };
        for (int j = 0; j < strlen(temp); j++)
        {
            if (temp[j - 1] == '[' & j > 0)
            {
                time_temp = (((temp[j] - '0') * 10) + (temp[j + 1] - '0')) * 86400 + (((temp[j + 12] - '0') * 10) + (temp[j + 13] - '0')) * 3600;
                time_temp += (((temp[j + 15] - '0') * 10) + (temp[j + 16] - '0')) * 60 + (((temp[j + 18] - '0') * 10) + (temp[j + 19] - '0'));
                break;
            }
        }
        times[i] = time_temp;
    }
    printf("там %d ошибки\n",errors);
    printf("введите период времениБ в котором вы хотите посчитать запросы\n");
    scanf("%d", &time);
    int left, right, mid;
    for (int i = 0; i < str; i++)
    {
        if (abs(left - i) > a)
        {
            a = left - i + 1;
            time_global = times[i];
        }
        left = 0;
        right = str;
        while (left + 1 < right)
        {
            mid = (left + right) / 2;
            if (times[mid] <= (times[i] + time - 1))
            {
                left = mid;
            }
            else
            {
                right = mid;
            }
        }
    }
    printf("\nтам %d записи из\n", a);
    printf("%d Jul 1995 | %d:%d:%d\n", time_global / 86400, ((time_global % 86400)) / 3600, ((time_global % 3600)) / 60, time_global % 60);
    printf("to \n%d Jul 1995 | %d:%d:%d", (time_global + time) / 86400, (((time_global + time) % 86400)) / 3600, (((time_global + time) % 3600)) / 60, (time_global + time) % 60);
}