#ifndef _ENCODER_H
    #define _ENCODER_H
        #include <stdio.h>
        #include <errno.h>
        #include "cstmio.h"

        #define PATH_LENGTH 255
        #define FIRST_FILE_INPUT_TEXT "������� ���� � ��������� (����������) �����: "
        #define SECOND_FILE_INPUT_TEXT "������� ���� ������ �������������� �����: "
        #define MASK_INPUT_TEXT "������� ����� ����������: "
        #define DEL_FILE_FLAG_INPUT_TEXT "������� ���� �� �������� ��������� �����: "
        //#define FILE_OPEN_ERROR " - �� ������� ����� ��� ����� ����"
        #define FILE_DEL_ERROR "�� ������� ������� ����"

        #define XOR_TO_BYTE(X, MASK) ((X) ^ (MASK))
        #define MEM_FREE(X) free(X)

        typedef struct
        {
            char sourceFilePath[PATH_LENGTH];
            char targetFilePath[PATH_LENGTH];
            char mask;
            int srcFileDelFlag;
        } encodeStr;

        int encode(const encodeStr * restrict enc);
        void fill_struct(encodeStr * restrict enc);
        void free_mem(const encodeStr *);
#endif // _ENCODER_H
