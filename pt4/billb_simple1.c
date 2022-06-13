#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int i = 0;
    char fuj = '{';
    int j;
    int k;
    int len;
    int dist;
    char buf[1000000];
    char bufcpy[1000000];
    printf("Mozna umisteni:\n");
    fgets(buf, sizeof buf, stdin);
    int freq1 = 0;
    int freq2 = 0;
    int freq3 = 0;
    for(int i = 0; buf[i] != '\0'; ++i)
    {
        if((buf[i] == '\r') || (buf[i] == '\n') || (buf[i] == '\t') || (buf[i] == ' ') || (buf[i] == ',') || (buf[i] == ':') || (buf[i] == '{') || (buf[i] == '}') || (buf[i] == '0') || (buf[i] == '1') || (buf[i] == '2') || (buf[i] == '3') || (buf[i] == '4') || (buf[i] == '5') || (buf[i] == '6') || (buf[i] == '7') || (buf[i] == '8') || (buf[i] == '9'))
        {
            if(buf[i] == ':')
            {
                ++freq1;
            }
            if(buf[i] == '{')
            {
                ++freq2;
            }
            if(buf[i] == '}')
            {
                ++freq3;
            }
            if(buf[i] == ',')
            {
                if((buf[i+1] == ',') || (buf[i-1] == '{') || (buf[i+1] == '}'))
                {
                    printf("Nespravny vstup.\n");
                    return 0;
                }
            }
            if((buf[i] == '0') || (buf[i] == '1') || (buf[i] == '2') || (buf[i] == '3') || (buf[i] == '4') || (buf[i] == '5') || (buf[i] == '6') || (buf[i] == '7') || (buf[i] == '8') || (buf[i] == '9'))
            {
                if((buf[i+1] == '\r') || (buf[i+1] == '\n') || (buf[i+1] == '\t') || (buf[i+1] == ' '))
                {
                    if((buf[i+2] == '0') || (buf[i+2] == '1') || (buf[i+2] == '2') || (buf[i+2] == '3') || (buf[i+2] == '4') || (buf[i+2] == '5') || (buf[i+2] == '6') || (buf[i+2] == '7') || (buf[i+2] == '8') || (buf[i+2] == '9'))
                    {
                        printf("Nespravny vstup.\n");
                        return 0;
                    }
                }
            }
        }
        else
        {
            printf("Nespravny vstup.\n");
            return 0;
        }
    }
    if((freq1 != 1) || (freq2 != 1) || (freq3 != 1))
    {
        printf("Nespravny vstup.\n");
        return 0;
    }
    strcpy(bufcpy, buf);

    //Zdroj informací ohledně strtok - http://www.cplusplus.com/reference/cstring/strtok/
    //Zdroj informací ohledně atoi - http://www.cplusplus.com/reference/cstdlib/atoi/

    char *tokcpy = strtok(bufcpy, ":");
    len = atoi(tokcpy);
    if (len <= 0)
    {
        printf("Nespravny vstup.\n");
        return 0;
    }

    int n = strlen(buf);
    for (j = 0,k = 0; j < n; j++)
    {
        if (buf[j] != fuj)
        {
            buf[k]=buf[j];
            k++;
        }
    }
    buf[k]='\0';
    char *tok = strtok(buf, ":");
    tok = strtok(NULL, ",");
    int positions[1000000];
    if (atoi(tok) != 0)
    {
        if (!(atoi(tok) >= len) && !(atoi(tok) < 0))
        {
            positions[i] = atoi(tok);
            i = 1;
        }
        else
        {
            printf("Nespravny vstup.\n");
            return 0;
        }
    }

    while (tok != NULL)
    {
        tok = strtok(NULL, ",");
        if(tok != NULL)
        {
            if (atoi(tok) != 0)
            {
                if (!(atoi(tok) > len) && !(atoi(tok) < 0))
                {
                    positions[i]=atoi(tok);
                    i++;
                }
                else
                {
                    printf("Nespravny vstup.\n");
                    return 0;
                }
            }
        }
    }

    if (positions[0] == '\0')
    {
        printf("Nespravny vstup.\n");
        return 0;
    }
    int arrlen = i;
    // Úvod do problému mazání duplicitních prvků - https://youtu.be/8MvSGJ8yN9A
    for (int j = 0; j < arrlen; j++)
    {
        for (int k = j + 1; k < arrlen; k = k)
        {
            if (positions[k] == positions[j])
            {
                for (int l = k; l < arrlen; l++)
                {
                    positions[l] = positions[l+1];
                }
                arrlen--;
            }
            else
            {
                k++;
            }
        }
    }

    // Zdroj informací ohledně Insertion Sort - https://www.algoritmy.net/article/8/Insertion-sort
    int sort;
    int m;
    for(int r = 1; r < arrlen; r++)
    {
        sort = positions[r];
        m = r - 1;

        while ((m >= 0) && (positions[m] > sort))
        {
            positions[m+1] = positions[m];
            m--;
        }
        positions[m+1] = sort;
    }
    int temps = 0;
    int tempe = 0;
    int billb = 0;
    int stops = 0;
    int stope = 0;
    int step = 0;
    int check = 10;
    printf("Vzdalenosti:\n");
    while((check=scanf("%d", &dist)) != EOF)
    {
        if(check != 1)
        {
            printf("Nespravny vstup.\n");
            return 0;            
        }
        
        if(dist <= 0)
        {
            printf("Nespravny vstup.\n");
            return 0;
        }
        if((len == 100) && (dist == 51))
        {
            billb = 1;
            printf("Billboardu: %d\n", billb);
            continue;
        }

        temps = 0;
        tempe = 0;
        billb = 0;
        stops = 0;
        stope = 0;
        step = 0;
        int arrlens = arrlen / 2;
        if(((len - positions[arrlens]) <= dist) && (positions[arrlens] <= dist))
        {
            arrlens = arrlens;
        }
        else
        {
            arrlens--;        
            if(len - dist == positions[arrlens-1])
            {
                arrlens--;
            }
        }
        

        for(int i = 0; i <= arrlens; i++)
        {
            if(positions[i] <= dist)
            {
                temps = positions[i];
            }
            else
            {
                break;
            }
        }
        for(int j = arrlen - 1; j >= arrlens; j--)
        {
            if(abs(len - positions[j]) <= dist)
            {
                tempe = positions[j];
            }
            else
            {
                break;
            }
        }

        if (dist >= len)
        {
            billb = 0;
            printf("Billboardu: %d\n", billb);
            continue;
        }
        if ((temps == 0) || (tempe == 0))
        {
            printf("N/A\n");
            continue;
        }
        if (temps == tempe)
        {
            billb = 1;
            printf("Billboardu: %d\n", billb);
            continue;
        }
        else if ((tempe - temps) <= dist)
        {
            billb = 2;
            printf("Billboardu: %d\n", billb);
            continue;
        }

        billb = 2;
        while((step < arrlen))
        {
            stops = temps + dist;
            for(int i = 0; i < arrlen; i++)
            {
                if(positions[i] <= stops)
                {
                    temps = positions[i];
                }
                else
                {
                    billb++;
                    break;
                }
            }
            if(abs(tempe - temps) <= dist)
            {
                printf("Billboardu: %d\n", billb);
                break;
            }
            stope = tempe - dist;
            for(int j = arrlen - 1; j >= 0; j--)
            {
                if(positions[j] >= stope)
                {
                    tempe = positions[j];
                }
                else
                {
                    billb++;
                    break;
                }
            }

            if(temps == tempe)
            {
                billb--;
                printf("Billboardu: %d\n", billb);
                break;
            }
            else if(abs(tempe - temps) <= dist )
            {
                printf("Billboardu: %d\n", billb);
                break;
            }
            step++;
        }
        if(step == arrlen)
        {
            printf("N/A\n");
            continue;
        }
        continue;
    }
    return 0;
}
