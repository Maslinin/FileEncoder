#include "encoder.h"

int encode(const encodeStr * restrict enc)
{
    FILE * fs, * ft;
    char ch;
    //�������� ������ � �������� ������:
    if(!(fs = fopen(enc->sourceFilePath, "rb")) && !ferror(fs))
    {
        perror(enc->sourceFilePath);
        return EXIT_FAILURE;
    }
    if(!(ft = fopen(enc->targetFilePath, "wb")) && !ferror(fs))
    {
        perror(enc->targetFilePath);
        return EXIT_FAILURE;
    }

    //��������/�����������:
    while(!feof(fs))
    {
        fread(&ch, sizeof(ch), 1, fs);
        ch = XOR_TO_BYTE(ch, enc->mask);
        fwrite(&ch, sizeof(ch), 1, ft);
    }
    fclose(fs);
    fclose(ft);

    //���� ����� ���� �������� ��������� �����
    if(enc->srcFileDelFlag)
        if(remove(enc->sourceFilePath))
        {
            perror("�� ������� ������� ����");
        }
    return 0;
}

encodeStr * fill_struct(void)
{
    encodeStr * strct = malloc(sizeof(encodeStr));

    fputs("������� ���� � ��������� (����������) �����: ", stdout);
    s_gets(strct->sourceFilePath, PATH_LENGTH);

    fputs("������� ���� ������ �������������� �����: ", stdout);
    s_gets(strct->targetFilePath, PATH_LENGTH);

    //���� �����
    fputs("������� ����� ����������: ", stdout);
    while(!scanf("%c", &strct->mask))
    {
        clear_buff();
        putchar('\n');
        fputs("������� ����� ����������: ", stdout);
    }
    clear_buff();

    fputs("������� ���� �� �������� ��������� �����: ", stdout);
    //���� ����� �� ��������
    while(!scanf("%d", &strct->srcFileDelFlag))
    {
        clear_buff();
        putchar('\n');
        fputs("������� ���� �� �������� ��������� �����: ", stdout);
    }
    clear_buff();
    return strct;
}
