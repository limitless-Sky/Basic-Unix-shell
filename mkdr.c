#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>

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
int main(int argc,char **argv)
{   
    if(argv[1]==NULL)
    {
        printf("mkdir: missing operand\n");
        printf("Try 'mkdir --help' for more information.\n");
        return(0);
    }
    if(strcmp(argv[1],"-v")==0)
    {
        int i=2;
        int flag=0;
        while(argv[i]!=NULL)
        {
            flag=1;
            if(mkdir(org(argv[i]),S_IRWXU|S_IRWXG|S_IRWXO)!=0)
                printf("mkdir: cannot create directory ‘%s’: File exists\n",org(argv[i]));
            else
                printf("mkdir: created directory '%s'\n",org(argv[i]));
            i+=1;
        }
        if(flag==0)
        {
            printf("rm: missing operand\n");
            printf("Try 'mkdir --help' for more information.\n");
        }
        return(0);
    }

    else if(strcmp(argv[1],"--help")==0)
    {
        printf("Usage: mkdir [OPTION]... DIRECTORY...\n");
        printf("Create the DIRECTORY(ies), if they do not already exist.\n\n");
        printf("  -v,             print a message for each created directory\n\n");
        printf("         --help     display this help and exit\n");
        return(0);
    }

    else
    {
        char* tmp=argv[1];
        if (*tmp=='-')
        {
            printf("mkdir: invalid option -- '%s'\n",argv[1]);
            printf("Try 'mkdir --help' for more information.\n");
            return(-1);
        }
        int i=1;
        int flag=0;
        while(argv[i]!=NULL)
        {
            flag=1;
            if(mkdir(org(argv[i]),S_IRWXU|S_IRWXG|S_IRWXO)!=0)
                printf("mkdir: cannot create directory ‘%s’: File exists\n",org(argv[i]));
            i+=1;
        }
        if(flag==0)
        {
            printf("rm: missing operand\n");
            printf("Try 'mkdir --help' for more information.\n");
        }
        return(0);
    }
}