#include "encoder.h"
#include <string.h>
#include <time.h>

#define FIRST_FILE_INPUT_TEXT "������� ���� � ��������� (����������) �����: "
#define SECOND_FILE_INPUT_TEXT "������� ���� ������ ������������ (������) �����: "
#define KEY_MODE_INPUT_TEXT "0 - ������ ���� ����, 1 - ������������ ����\n����: "
#define MASK_INPUT_TEXT "������� ����(�����) ����������: "
#define DEL_FILE_FLAG_INPUT_TEXT "������� ���� �� �������� ��������� �����(0: ��������, 1: �������): "
#define ENCODER_MODE_INPUT_TEXT "������� ����� ������ ���������(1: ���������, 0: �����������): "
#define FILE_DEL_ERROR "�� ������� ������� ����"

//��������� �������, ���������� ��������������� ����� � ����������� ��� �������������/������������� ����
static char * getpath(char* out_str, char* file_mode, char * out_message);
//��������� �������, ��������� ��������� ������ ������ �������� ����������� �� �����:
static char charencrypt(char ch, const char* key, bool mode);
//��������� ������� ��� ����� ����� ����������:
static char * inputkey(char * restrict storage, int size, char * out_message);
//��������� �������, ������������ ���� ����������:
static char * generatekey(char * restrict storage, int size);

//���������� �����(mode true - ����������, bool - ������������):
bool Encode(const ENCODE_INFO * restrict enc)
{
    FILE * fs, * ft;
    char ch;
    //�������� ������ � �������� ������:
    if(!(fs = fopen(enc->SourceFilePath, "rb")) && !ferror(fs))
    {
        perror(enc->SourceFilePath);
        return false;
    }
    if(!(ft = fopen(enc->TargetFilePath, "wb")) && !ferror(fs))
    {
        fclose(fs);
        perror(enc->TargetFilePath);
        return false;
    }

    //��������/�����������:
    while(!feof(fs))
    {
        fread(&ch, sizeof(ch), 1, fs);
        ch = charencrypt(ch, enc->Key, enc->Mode);
        fwrite(&ch, sizeof(ch), 1, ft);
    }
    fclose(fs);
    fclose(ft);

    //���� ����� ���� �������� ��������� �����
    if(enc->SourceFileDelFlag)
        if(remove(enc->SourceFilePath))
            perror(FILE_DEL_ERROR);
    return true;
}

//������� ��� ���������� ����� ���������:
void FillEncodeInfo(ENCODE_INFO * restrict enc)
{
    int encodeMode, keyMode;

    //��������� ���� ��������� �����:
    getpath(enc->SourceFilePath, "rb", FIRST_FILE_INPUT_TEXT);
    //��������� ���� ������ �����:
    getpath(enc->TargetFilePath, "wb", SECOND_FILE_INPUT_TEXT);

    //���� ������ ������ ���������:
    fputs(ENCODER_MODE_INPUT_TEXT, stdout);
    while(!scanf("%d", &encodeMode))
    {
        clear_buff();
        putchar('\n');
        fputs(ENCODER_MODE_INPUT_TEXT, stdout);
    }
    clear_buff();
    enc->Mode = encodeMode;

    if(enc->Mode)
    {
        fputs(KEY_MODE_INPUT_TEXT, stdout);
        while(!scanf("%d", &keyMode))
        {
            clear_buff();
            putchar('\n');
            fputs(KEY_MODE_INPUT_TEXT, stdout);
        }
        clear_buff();

        if(!keyMode)
            inputkey(enc->Key, KEY_LENGTH, MASK_INPUT_TEXT);
        else
            generatekey(enc->Key, KEY_LENGTH);
    }
    else
    {
        inputkey(enc->Key, KEY_LENGTH, MASK_INPUT_TEXT);
    }

    //���� ����� �� �������� ��������� �����:
    fputs(DEL_FILE_FLAG_INPUT_TEXT, stdout);
    while(!scanf("%d", &enc->SourceFileDelFlag))
    {
        clear_buff();
        putchar('\n');
        fputs(DEL_FILE_FLAG_INPUT_TEXT, stdout);
    }
    clear_buff();

    return;
}

//������� ��� ����������� �����(�����) ����������:
void ShowKey(ENCODE_INFO * restrict enc)
{
    fputs("��� ����(�����) ����������: ", stdout);
    puts(enc->Key);
    return;
}

//��������� ������� ��� ����� ���� �����:
static char * getpath(char* out_str, char* file_mode, char * out_message)
{
    FILE * fs = NULL;
    do
    {
        fputs(out_message, stdout);
        //������ ���� � ������� �� ������ ��� �������(del_spaces, s_gets � clearbuff ��������� ������� �� cstmio.h)
        del_spaces(s_gets(out_str, PATH_LENGTH));
        clear_buff();
        if(!(fs = fopen(out_str, file_mode)))
            perror(out_str);
    }
    while(!fs);
    //��������� �������� ���� ��� ����������� �������������:
    fclose(fs);

    //���� ��������������� ������ � ����, ������� ��������(���������) ����
    if(strcmp(file_mode, "wb") == 0)
        if(remove(out_str)) //���� ������� �� �������, ������� ������
            perror(FILE_DEL_ERROR);
    return out_str;
}

//true - ����������, false - ������������
//��������� �������, ��������� ��������� ������ ������ �������� ����������� �����:
static char charencrypt(char ch, const char* key, bool mode)
{
    int i;
    if(mode) //���� �������
        for(i = 0; i < strlen(key); ++i)
            ch ^= key[i];
    else //���� ��������������
        for(i = strlen(key) - 1; i >= 0; --i)
            ch ^= key[i];

    return ch;
}

static char * inputkey(char * restrict storage, int size, char * out_message)
{
    fputs(out_message, stdout);
    if(s_gets(storage, KEY_LENGTH) == NULL)
    {
        perror(NULL);
        exit(EXIT_FAILURE);
    }
    del_spaces(storage);
    clear_buff();

    return storage;
}

static char * generatekey(char * restrict storage, int size)
{
    int i;
    //������ ����� ���������� ��������� �����, ��� �� ������ ��� ��� ������� ��� ������ ����
    srand(time(NULL));
    for(i = 0; i < size; ++i)
        storage[i] = rand()%95 + 33; //�������� �������� � ASCII
    del_spaces(storage);
    storage[i - 1] = '\0';

    return storage;
}
