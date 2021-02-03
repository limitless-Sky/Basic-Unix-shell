#include<stdio.h>
#include<sys/types.h>
#include<unistd.h> 
#include<sys/wait.h>
#include<string.h>
#include<stdlib.h>
char cur_path[1000];

#define clear() printf("\033[H\033[J")
size_t bufsize = 64;
char *command;
char **command_split;
char cur_his[100000];



char **split(char *command)
{
    char **args=malloc(bufsize*sizeof(char*));
    char *token;
    if (!args) {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
    }
    int i=0;
    token=strtok(command," ");
    do
    {
        args[i]=token;
        i+=1;
        if (i>=bufsize)
        {
            args=realloc(args,(2*bufsize)*sizeof(char*));
        }
        token = strtok(NULL, " ");
        
    } while (token!=NULL);
    args[i]=NULL;
    return args;
}

int command_size(char **command_split)
{
    int i=0;
    while (command_split[i]!=NULL)
        i++;
    return i;
}

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

int ext_date(char **command_split)
{
    char pp[1000];
    pp[0]='\0';
    strcat(pp,cur_path);
    strcat(pp,"/");
    strcat(pp,"./date");
    pid_t pid;
    pid=fork();
    int status;
    if(pid<0)
    {
        fprintf(stderr,"Fork Failed");
        return 1;
    }
    else if(pid==0)
        execvp(pp,command_split);
    else
        waitpid(pid,&status,0);
}

int remov(char **command_split)
{
    char pp[1000];
    pp[0]='\0';
    strcat(pp,cur_path);
    strcat(pp,"/");
    strcat(pp,"./rem");
    pid_t pid;
    pid=fork();
    int status;
    if(pid<0)
    {
        fprintf(stderr,"Fork Failed");
        return 1;
    }
    else if(pid==0)
        execvp(pp,command_split);
    else
        waitpid(pid,&status,0);
}

int mk(char **command_split)
{
    char pp[1000];
    pp[0]='\0';
    strcat(pp,cur_path);
    strcat(pp,"/");
    strcat(pp,"./mkdr");
    pid_t pid;
    pid=fork();
    int status;
    if(pid<0)
    {
        fprintf(stderr,"Fork Failed");
        return 1;
    }
    else if(pid==0)
        execvp(pp,command_split);
    else
        waitpid(pid,&status,0);
}

int ct(char **command_split)
{
    char pp[1000];
    pp[0]='\0';
    strcat(pp,cur_path);
    strcat(pp,"/");
    strcat(pp,"./cat");
    pid_t pid;
    pid=fork();
    int status;
    if(pid<0)
    {
        fprintf(stderr,"Fork Failed");
        return 1;
    }
    else if(pid==0)
        execvp(pp,command_split);
    else
        waitpid(pid,&status,0);
}

int ls(char **command_split)
{
    char pp[1000];
    pp[0]='\0';
    strcat(pp,cur_path);
    strcat(pp,"/");
    strcat(pp,"./ls");
    pid_t pid;
    pid=fork();
    int status;
    if(pid<0)
    {
        fprintf(stderr,"Fork Failed");
        return 1;
    }
    else if(pid==0)
        execvp(pp,command_split);
    else
        waitpid(pid,&status,0);
}

int imp_echo(char **command_split)
{
    int sl=command_size(command_split);
    if(sl==1)
    {
        printf("\n");
        return(0);
    }
    else if(sl==2)
    {
        printf("%s\n",org(command_split[1]));
        return(0);
    }
    else
    {
        if(strcmp(command_split[1],"-n")==0)
        {
            printf("%s",org(command_split[2]));
            return(0);
        }
        if(strcmp(command_split[1],"-E")==0)
        {
            printf("%s",org(command_split[2]));
            return(0);
        }
        else
        {
            int i=1;
            while (command_split[i]!=NULL)
            {
                printf("%s ",command_split[i]);
                i++;
            }
            printf("\n");
            return(0);
        }
        
    }
}

int imp_his(char **command_split)
{
    int sl=command_size(command_split);
    if(sl==1)
    {
        int count=1;
        printf("%d  ",count);
        for(int i=0;cur_his[i]!='\0';i++)
        {
            if(cur_his[i]=='-'&&cur_his[i+1]!='\0')
            {
                printf("\n");
                count+=1;
                printf("%d  ",count);
            }
            else
                printf("%c",cur_his[i]);
        }
        printf("\n");
        return(0);
    }
    if(sl>=2 && strcmp(command_split[1],"-w")==0)
    {
        FILE *file_ptr;
        file_ptr=fopen("history.txt","a");
        for(int i=0;cur_his[i]!='\0';i++)
        {
            if(cur_his[i]=='-'&&cur_his[i+1]!='\0')
                fputc('\n',file_ptr);
            else 
                fputc(cur_his[i],file_ptr);
        }
        return(0);
    }
    else if(sl>=2 && strcmp(command_split[1],"--help")==0) 
    {
        printf("  Display or manipulate the history list.\n\n");
        printf("  Display the history list with line numbers, prefixing each modified\n");
        printf("  entry with a `*'.  An argument of N lists only the last N entries.\n\n");
        printf("  Options:\n\n");
        printf("  -w        write the current history to the history file\n\n");
        printf("Exit Status:\n");
        printf("  Returns success unless an invalid option is given or an error occurs.\n");
        return(0);
    }
    else
    {
        printf("bash: history: '%s': numeric argument required\n",command_split[1]);
        return(-1);
    }
}

int imp_cd(char **command_split)
{
    int sl=command_size(command_split);
    if(sl==1)
    {
        chdir(getenv("HOME"));
        return(0);
    }
    if(sl==2)
    {
        if(chdir(org(command_split[1]))!=0)
            printf("bash: cd: '%s': No such file or directory\n",command_split[1]);
        return(0);
    }
    if(sl>2)
    {
        if(strcmp(org(command_split[1]),"-e")!=0 && strcmp(command_split[1],"--help")!=0)
        {
            printf("bash: cd: too many arguments\n");
            return(0);
        }
        else if(strcmp(command_split[1],"-e")==0)
        {
            if(chdir(org(command_split[1]))!=0)
            {
                printf("bash: cd: '%s': No such file or directory\n",command_split[1]);
                return(-1);
            }
            return(0);
        }
        else if(strcmp(command_split[1],"--help")==0)
        {
            printf("cd: cd [-P] [dir]\n");
            printf("Change the shell working directory.\n\n");
            printf("Change the current directory to DIR.  The default DIR is the value of the HOME shell variable.\n\n");
            printf("Options:\n");
            printf("-P        use the physical directory structure without following symbolic links: resolve symbolic links in DIR before processing instances of `..'\n");
            printf("--help    display this help and exit\n");
            return(0);
        }
    }
}

int imp_pwd(char **command_split)
{
    int sl=command_size(command_split);
    if(sl==1)
    {
        char s[1000];
        printf("%s\n",getcwd(s,1000));
        return(0);
    }
    if(sl>=1)
    {
        if(strcmp(command_split[1],"-L")==0)
        {
            char s[1000];
            printf("%s\n",getcwd(s,1000));
            return(0);
        }
        else if(strcmp(command_split[1],"--help")==0)
        {
            printf("pwd: pwd [-L]\n");
            printf("Print the name of the current working directory.\n\n");
            printf("Options:\n");
            printf("-P        print the physical directory, without any symbolic links\n");
            printf("--help    display this help and exit\n");
            return(0);
        }
        else
        {
            printf("bash: pwd: -%s: invalid option\n",command_split[1]);
            printf("pwd: usage: pwd [-L]\n");
            return(0);
        }
    }
}

int main()
{
    clear();
    getcwd(cur_path, 1000);
    while (1)   
    {
        char pp[100];
        int com_size;
        printf("[user@linux ~]:%s$ ",getcwd(pp,sizeof(pp)));
        command=(char *) malloc(bufsize*sizeof(char));
        if( command == NULL)
        {
            perror("Unable to allocate buffer");
            exit(1);
        }
        getline(&command,&bufsize,stdin);
        int i;
        for(i=0;*(command+i)!='\n';++i);
        *(command+i)='\0';
        command_split=split(command);
        if (strcmp(command,"exit")==0)
            exit(EXIT_SUCCESS);
        else if(strcmp(command_split[0],"date")==0)
            ext_date(command_split);
        else if(strcmp(command_split[0],"rm")==0)
            remov(command_split);
        else if(strcmp(command_split[0],"mkdir")==0)
            mk(command_split);
        else if(strcmp(command_split[0],"cat")==0)
            ct(command_split);
        else if(strcmp(command_split[0],"ls")==0)
            ls(command_split);
        else if(strcmp(command_split[0],"echo")==0)
            imp_echo(command_split);
        else if(strcmp(command_split[0],"history")==0)
            imp_his(command_split);
        else if(strcmp(command_split[0],"cd")==0)
            imp_cd(command_split);
        else if(strcmp(command_split[0],"pwd")==0)
            imp_pwd(command_split);
        else
            printf("bash: '%s': command not found\n",command_split[0]);

        strcat(command_split[0],"-");
        strcat(cur_his,command_split[0]);
        free(command);
        free(command_split);
    }
    strcpy(cur_his,"");
    return(0);
}
