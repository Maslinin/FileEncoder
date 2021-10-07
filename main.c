#include <stdio.h>
#include <locale.h>
#include "encoder.h"
#define EXIT_SYMBOL 'q'

int main(void)
{
    encodeStr * enc;
    setlocale(LC_ALL, "Rus");
    do
    {
        getchar();
        putchar('\n');
        enc = fill_struct();
        if(encode(enc))
        {//���� ��������� ������ � �������
            putchar('\n');
            continue;
        }
        puts("���������� ���������. ������� \'q\', ��� �� ������� ���������, ��� ������ ������, ��� �� ����������.");
    }
    while(getchar() != EXIT_SYMBOL);
    FREE_MEM(enc);
    puts("��������� ������� ��������� ���� ����������");
    return 0;
}
