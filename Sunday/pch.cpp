// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"

// 当使用预编译的头时，需要使用此源文件，编译才能成功。

extern "C" __declspec(dllexport) int __stdcall FindByteArray_Sunday(unsigned char* Source, unsigned char* Destin, int start)
{
    if (Source == NULL)
    {
        return -1;
    }
    if (Destin == NULL)
    {
        return -1;
    }
    Source = (unsigned char*)*(int*)(Source);
    Destin = (unsigned char*)*(int*)(Destin);
    if (Source == NULL)
    {
        return -1;
    }
    if (Destin == NULL)
    {
        return -1;
    }
    Source += 4;
    Destin += 4;
    int slen = *(int*)(Source);
    int dlen = *(int*)(Destin);
    Source += 4;
    Destin += 4;
    if (start == NULL)
    {
        start++;
    }
    start--;
    if (start < 0 || slen < 1 || dlen < 1)
    {
        return -1;
    }
    int best = slen = dlen;
    if (start > best)
    {
        return -1;
    }
    int output = -1;
    int i = 0;
    int j = start;
    int k = 0;
    int hash[256];
    for (i = 0; i < 256; i++)
    {
        hash[i] = -1;
    }
    for (i = 0; i < dlen; i++)
    {
        hash[Destin[i]] = i;
    }
    while (j <= best)
    {
        for (k = 0; k < dlen; k++)
        {
            if (Source[j] != Destin[k])
            {
                i++;
                break;
            }
            j++;
        }
        if (k == dlen)
        {
            output = j - k + 1;
            break;
        }
        if (j >= best)
        {
            break;
        }
        //j += dlen - hash[Source[j + dlen]];
        k = hash[Source[j + dlen]];
        if (k == -1)
        {
            j += dlen + 1;
        }
        else
        {
            j += dlen - k;
        }
    }
    return output;
}
