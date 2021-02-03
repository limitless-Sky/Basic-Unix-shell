#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
extern  int alphasort();
struct dirent **names;

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

int printls(char* s,int cc)
{
    struct dirent **names;
    int i;
    i=scandir(s,&names,NULL,alphasort);
    if(i<0)
    {
        printf("ls: cannot access '%s': No such file or directory\n",s);
        return(-1);
    }
    else
    {
        for(int k=0;k<i;k++)
        {
            if(cc==0)
                printf("%s      ",names[k]->d_name);
            else
                printf("%s\n",names[k]->d_name);
            free(names[k]);
        }
        if(cc!=1)
            printf("\n");
        free(names);
    }
}
int main(int argc,char **argv)
{   
    if(argc>=2 && strcmp(argv[1],"-1")==0)
    {
        if(argc==2)
        {
            printls(".",1);
            return(0);
        }
        if(argc>2)
        {
            int i=2;
            while (argv[i]!=NULL)
            {
                printf("%s:\n",org(argv[i]));
                printls(org(argv[i]),1);
                i++;
            }
            return(0);
        }
    }

    else if(argc!=1&&strcmp(argv[1],"--help")==0)
    {
        printf("Usage: ls [OPTION]... [FILE]...\n");
        printf("List information about the FILEs (the current directory by default).\n");
        printf("Sort entries alphabetically if none of -cftuvSUX nor --sort is specified.\n\n");
        printf("  -1,             list one file per line.\n");
        printf("  --help  display this help and exit\n\n");
        printf("Exit status:\n");
        printf("  0  if OK,\n");
        printf("  1  if minor problems (e.g., cannot access subdirectory),\n");
        printf("  2  if serious trouble (e.g., cannot access command-line argument).\n");
        return(0);
    }
    else
    {
        if (argc!=1)
        {
            char* tmp=argv[1];
            if (*tmp=='-')
            {
                printf("ls: invalid option -- '%s'\n",argv[1]);
                printf("Try 'ls --help' for more information.\n");
                return(-1);
            }
        }
        
        int i=1;
        if(argc==1)
            printls(".",0);
        else
        {
            char* tmp=argv[1];
            if (*tmp=='-')
            {
                printf("ls: invalid option -- '%s'\n",argv[1]);
                printf("Try 'ls --help' for more information.\n");
                return(-1);
            }
            else
            {
                while (argv[i]!=NULL)
                {
                    printf("%s:\n",org(argv[i]));
                    printls(org(argv[i]),0);
                    i++;
                }
            }
            
        }
        
        return(0);
    }
}