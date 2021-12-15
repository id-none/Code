#include <stdio.h>
#include <string.h>
#include <iostream>
int main()
{
    FILE *p = NULL;
    p = fopen("./ciphertext.txt", "r");
    char ch;
    char str[4760], letter[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    int i=0, k = 0, num[26] = {0}, sum=0;
    str[4760]='\0';
    while( (ch=fgetc(p))!=EOF )
    {
        if(ch>='a' && ch<='z')
        {
            if(ch=='n') putchar('e');
            if(ch=='y') putchar('t');
            if(ch=='v') putchar('a');
            if(ch=='x') putchar('o');
            if(ch=='u') putchar('n');
            if(ch=='q') putchar('s');
            if(ch=='m') putchar('i');
            if(ch=='h') putchar('r');
            if(ch=='t') putchar('h');
            if(ch=='i') putchar('l');
            if(ch=='p') putchar('d');
            if(ch=='a') putchar('c');
            if(ch=='c') putchar('m');
            if(ch=='z') putchar('u');
            if(ch=='l') putchar('w');
            if(ch=='b') putchar('f');
            if(ch=='g') putchar('b');
            if(ch=='r') putchar('g');
            if(ch=='e') putchar('p');
            if(ch=='d') putchar('y');
            if(ch=='f') putchar('v');
            if(ch=='s') putchar('k');
            if(ch=='k') putchar('x');
            if(ch=='j') putchar('q');
            if(ch=='o') putchar('j');
            if(ch=='w') putchar('z');
        }
        else
            putchar(ch);
    }
    fclose(p);
    p=NULL;
    system("pause");
    return 0;
} 
 //ports 半连接 全连接  scapy 扫描  
