#include<stdio.h>
#include<time.h>
#include<string.h>

int main(int argc,char **argv)
{
    int i=0;
    if( argc >= 2 )
    {
      while(argv[i]!=NULL)
        i+=1;
    }
    int hr,min,sec,dat,mon,yr;
    char* month;
    time_t now;
    time(&now);
    struct tm *tt;
    if(i==2 && strcmp(argv[1],"-R")!=0)
        tt=gmtime(&now);
    else
        tt=localtime(&now);
    hr = tt->tm_hour;	  	
	min = tt->tm_min;
	sec = tt->tm_sec;	
	dat = tt->tm_mday;
    mon = tt->tm_mon + 1; 	  	
	yr = tt->tm_year + 1900;


    char* day=strtok(ctime(&now)," ");
    char* nday;
    char* nmon;
    if (strcmp(day,"Mon")==0)
        nday="Monday";
    else if(strcmp(day,"Tue")==0)
        nday="Tuesday";
    else if(strcmp(day,"Wed")==0)
        nday="Wednesday";
    else if(strcmp(day,"Thu")==0)
        nday="Thursday";
    else if(strcmp(day,"Fri")==0)
        nday="Friday";
    else if(strcmp(day,"Sat")==0)
        nday="Saturday";
    else
        nday="Sunday"; 


    if(mon==1)
    {
        month="January";
        nmon="Jan";
    }
    else if(mon==2)
    {
        month="Febraury";
        nmon="Feb";
    }
    else if(mon==3)
    {
        nmon="Mar";
        month="March";
    }
    else if(mon==4)
    {
        nmon="Apr";
        month="April";
    }
    else if(mon==5)
    {
        nmon="May";
        month="May";
    }
    else if(mon==6)
    {
        nmon="Jun";
        month="June";
    }
    else if(mon==7)
    {
        nmon="Jul";
        month="July";
    }
    else if(mon==8)
    {
        month="August";
        nmon="Aug";
    }
    else if(mon==9)
    {
        nmon="Sep";
        month="September";
    }
    else if(mon==10)
    {
        nmon="Oct";
        month="October";
    }
    else if(mon==11)
    {
        nmon="Nov";
        month="November";
    }
    else
    {   
        nmon="Dec";
        month="December";
    }
    
    
    if(i>=2)
    {
        if(i>2)
        {
            printf("date: extra operand's\n");
            return(-1);
        }
        if(strcmp(argv[1],"-R")==0)
        {
            printf("%s, %d %s %d %02d:%02d:%02d +0530\n",day,dat,nmon,yr,hr,min,sec);
            return(0);
        }
        else if(strcmp(argv[1],"-u")==0)
        {
            if(hr<=12)
                printf("%s %d %s %d %02d:%02d:%02d AM UTC\n",nday,dat,month,yr,hr,min,sec);
            else
                printf("%s %d %s %d %02d:%02d:%02d PM UTC\n",nday,dat,month,yr,hr-12,min,sec);
            return(0);
        }
        else
        {
            printf("date: invalid date\n");
            return(-1);
        }
    }
    else
    {   
        if(hr<=12)
            printf("%s %d %s %d %02d:%02d:%02d AM IST\n",nday,dat,month,yr,hr,min,sec);
        else
            printf("%s %d %s %d %02d:%02d:%02d PM IST\n",nday,dat,month,yr,hr-12,min,sec);
        return(0);
    }
}