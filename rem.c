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
    if(strcmp(argv[1],"-d")==0)
    {
        int i=2;
        int flag=0;
        while(argv[i]!=NULL)
        {
            flag=1;
            if(rmdir(org(argv[i]))!=0)
                printf("rm: cannot remove directory ‘%s’: No such file or directory\n",org(argv[i]));
            i+=1;
        }
        if(flag==0)
        {
            printf("rm: missing operand\n");
            printf("Try 'rm --help' for more information.\n");
        }
        return(0);
    }

    else if(strcmp(argv[1],"--help")==0)
    {
        printf("Usage: rm [OPTION]... [FILE]...\n");
        printf("Remove (unlink) the FILE(s).\n\n");
        printf("Create the DIRECTORY(ies), if they do not already exist.\n\n");
        printf("  -d,             remove empty directories\n");
        printf("--help        display this help and exit\n\n");
        printf("By default, rm does not remove directories.\n");
        return(0);
    }

    else
    {
        char* tmp=argv[1];
        if (*tmp=='-')
        {
            printf("rm: invalid option -- '%s'\n",argv[1]);
            printf("Try 'rm --help' for more information.\n");
            return(-1);
        }
        
        
        int i=1;
        int flag=0;
        while(argv[i]!=NULL)
        {
            flag=1;
            if(remove(org(argv[i]))!=0)
                printf("rm: cannot remove '%s': No such file or directory\n",org(argv[i]));
            i+=1;
        }
        if(flag==0)
        {
            printf("rm: missing operand\n");
            printf("Try 'rm --help' for more information.\n");
        }
        return(0);
    }
}