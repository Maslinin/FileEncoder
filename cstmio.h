#ifndef _CSTMIO_H
    #define _CSTMIO_H
        #include <stdio.h>
        #include <string.h>
        #include <ctype.h>

        //��������� ������������� �����
        //������� ����� ������. �������� ������ ����� ������ ������� ��������.
        char* s_gets(char* str, int value);
        //������� ������� ������ ����� stdin
        void clear_buff(void);
        //������� ��� ���������� ������� �� ������
        void del_spaces(char str[]);
#endif // _CSTMIO_H
