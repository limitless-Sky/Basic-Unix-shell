#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdlib.h>

int count=1;
char *org(char *name)
{
    char* tmp=name;
    while (*tmp!='\0')
    {
        if(*tmp=='@')
            *tmp=' ';
        tmp++;
    }
    return name;
}

int red_num(char *file)
{
    FILE *file_ptr;
    char c;
    file_ptr=fopen(file,"r");
    if(file_ptr == NULL)
    {
      printf("cat: %s: No such file or directory\n",file);   
      return(0);             
    }
    printf("   %d ",count);
    while (1)
    {
        c = fgetc(file_ptr);
        if(c==EOF)
            break;
        else
        {
            printf("%c", c);
            if(c=='\n')
            {
                count+=1;
                printf("   %d ",count);
            }

        }
    }
    fclose(file_ptr);    
}

int red(char *file)
{
    FILE *file_ptr;
    char c;
    file_ptr=fopen(file,"r");
    if(file_ptr == NULL)
    {
      printf("cat: %s: No such file or directory\n",file);   
      return(0);             
    }
    while (1)
    {
        c = fgetc(file_ptr);
        if(c==EOF)
            break;
        else
            printf("%c", c);
    }
    fclose(file_ptr);    
}

int red_dol(char *file)
{
    FILE *file_ptr;
    char c;
    file_ptr=fopen(file,"r");
    if(file_ptr == NULL)
    {
      printf("cat: %s: No such file or directory\n",file);   
      return(0);             
    }
    while (1)
    {
        c = fgetc(file_ptr);
        if(c==EOF)
            break;
        else
        {
            if(c=='\n')
                printf("$");
            printf("%c", c);
        }
    }
    fclose(file_ptr);    
}

int main(int argc,char **argv)
{   
    if(strcmp(argv[1],"-n")==0)
    {
        int i=2;
        int flag=0;
        while(argv[i]!=NULL)
        {
            flag=1;
            red_num(org(argv[i]));
            i+=1;
        }
        count=0;
        if(flag==0)
        {
            while(1)
            {
                char *st;
                fgets(st,10000,stdin);
                printf("%s",st);
            }
        }
        return(0);
    }

    if(strcmp(argv[1],"-E")==0)
    {
        int i=2;
        int flag=0;
        while(argv[i]!=NULL)
        {
            flag=1;
            red_dol(org(argv[i]));
            i+=1;
        }
        if(flag==0)
        {
            while(1)
            {
                char *st;
                fgets(st,10000,stdin);
                printf("%s",st);
            }
        }
        return(0);
    }


    else if(strcmp(argv[1],"--help")==0)
    {
        printf("Usage: cat [OPTION]... [FILE]...\n");
        printf("Concatenate FILE(s) to standard output.\n\n");
        printf("With no FILE, or when FILE is -, read standard input.\n\n");
        printf("  -n,             number all output lines\n\n");
        printf("  -E,             display $ at end of each line\n");
        printf("         --help     display this help and exit\n\n");
        printf("cat f - g  Output f's contents, then standard input, then g's contents.\n");
        printf("cat        Copy standard input to standard output.");
        return(0);
    }

    else
    {
        char* tmp=argv[1];
        if (*tmp=='-')
        {
            printf("cat: invalid option -- '%s'\n",argv[1]);
            printf("Try 'cat --help' for more information.\n");
            return(-1);
        }
        int i=1;
        int flag=0;
        while(argv[i]!=NULL)
        {
            flag=1;
            red(org(argv[i]));
            i+=1;
        }
        if(flag==0)
        {
            while(1){}
        }
        return(0);
    }
}