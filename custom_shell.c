#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>

bool isLeapYear(int year) {
    	return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

int daysInMonth(int month, int year) {
    	int Months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    	if (isLeapYear(year) && month == 2) {
        	return 29;
    	}
    	return Months[month - 1];
}
int main ()
{
	char buff[100];
	char *username = getenv("USER");		
	char hostname[40]; 
	char path[100]="/home/";
	char default_path[100];
	char history_file [100] = "/home/";
	strcat(history_file,username);
	strcat(history_file,"/Project/history.txt");
	strcat(path,username);
	strcpy(default_path,path);
	gethostname(hostname,40);
	system("clear");
	while (1)
	{
		char str1[100]="./home/";
		strcat(str1,username);
		strcat(str1,"/Project/hello.sh \"");
		char str2[100]="./home/";
		strcat(str2,username);
		strcat(str2,"/Project/white.sh \"");
		gethostname(hostname,40);
		if (strcmp(path,"/")==0 || strcmp(path,"/home")==0)
		{
			char pr[100];
			strcpy(pr,str1);
			strcat(pr,username);
			strcat(pr,"@");
			strcat(pr,hostname);
			strcat(pr,"\"");
			system(pr);
			char ex[50]="./home/";
			strcat(ex,username);
			strcat(ex,"/Project/col.sh");
			system(ex);
			strcpy(pr,str2);
			strcat(pr,path);
			strcat(pr,"\"");
			system(pr);
			printf("$ ");
		}
		else if (strcmp(path,default_path)==0)
		{
			char pr[100];
			strcpy(pr,str1);
			strcat(pr,username);
			strcat(pr,"@");
			strcat(pr,hostname);
			strcat(pr,"\"");
			system(pr);
			char ex[50]="./home/";
			strcat(ex,username);
			strcat(ex,"/Project/col.sh");
			system(ex);
			strcpy(pr,str2);
			strcat(pr,"~\"");
			system(pr);
			printf("$ ");
		}
		else
		{
			int n=strlen(default_path);
			char currpath[100]="";
			int i=0;
			while(path[n]!='\0')
			{
				currpath[i]=path[n];
				n++;
				i++;
			}
			char pr[100];
			strcpy(pr,str1);
			strcat(pr,username);
			strcat(pr,"@");
			strcat(pr,hostname);
			strcat(pr,"\"");
			system(pr);
			char ex[50]="./home/";
			strcat(ex,username);
			strcat(ex,"/Project/col.sh");
			system(ex);
			strcpy(pr,str2);
			strcat(pr,currpath);
			strcat(pr,"\"");
			system(pr);
			printf("$ ");
		}
		fgets(buff,100, stdin);
		FILE *hist;
		hist = fopen(history_file,"a"); 
		fprintf(hist,"%s",buff);
		fclose(hist);
		buff[strcspn(buff, "\n")] = '\0';
		char *token;
   		token = strtok(buff, " ");
		if(strcmp(buff,"exit")==0)
		{
			exit(0);
		}
		if (strcmp(token,"cd")==0)
		{
			char save[100];
			if (buff[3] =='.')
			{
				int c=0,c1=0,i=3;
				while(buff[i]!='\0')
				{
					if(buff[i]=='.')
						c1++;
					if (c1==2)
					{
						c1=0;
						c++;
					}
					i++;
				}
				i=strlen(path)-1;
				for (int j=0;j<c;j++)
				{
					while(path[i]!='/' && i>0)
					{
						path[i]='\0';
						i--;
					}
					if (i!=0)
					{
						path[i]='\0';
						i--;
					}
					
				}
			}
			else
			{
				strcpy(save,path);
				int i=strlen(path);
				if (i!=1)
				{
					path[i]='/';
					i++;
				}
				int j=3;
				while(buff[j]!='\0')
				{
					path[i]=buff[j];
					i++;
					j++;
				}	
			}
			char exe[100];
			strcpy(exe,"cd ");
			strcat(exe,path);
			int ch=system(exe);
			if (ch!=0)
			{
				printf("No such directory.\n");
				memset(path,0,strlen(path));			
				strcpy(path,save);
			}
		}
		else if (strcmp(token,"ls")==0)
		{
			char exe[100];
			char save[100]="";
			int j=3,i=0;
			while(buff[j]!='\0')
			{
				save[i]=buff[j];
				i++;
				j++;
			}
			if (save[0]=='\0')
			{
				strcpy(exe,buff);
				strcat(exe," ");
				strcat(exe,path);
			}
			else 
			{
				i=strlen(save);
				i--;
				while(i>0 && save[i]!='/')
					i--;
				char st[100]="",s[100]="";
				int k=i;
				j=0;
				if (save[i]=='/')
					i++;
				while(save[i]!='\0')
				{
					st[j]=save[i];
					j++;
					i++;
				}
				j=0;
				while(j<k)
				{
					s[j]=save[j];
					j++;
				}
				strcpy(exe,"cd ");
				strcat(exe,path);
				strcat(exe,"/");
				strcat(exe,s);
				strcat(exe," && ls ");
				strcat(exe,st);
			}
			int ch = system(exe);
			if (ch!=0)
			{
				printf("No such directory.\n");
			}
		}
		else if (strcmp(token,"pwd")==0)
		{
			printf("%s\n",path);
		}
		else if (strcmp(token,"greetme")==0)
		{
			time_t curtime;
			time(&curtime);
			char *time=ctime(&curtime);
			char* tk = strtok(time, " ");
    			for (int i=0;i<3;i++) 
    			{
        			tk = strtok(NULL, " ");
   			}			
   			int t;
   			char tstr[2];
   			tstr[0]=tk[0];
   			tstr[1]=tk[1];
   			sscanf(tstr, "%d", &t);
   			if (t>=5 && t<12)
   				printf("Good Morning\n");
   			else if (t>=12 && t<16)
   				printf("Good Afternoon\n");
   			else if (t>=16 && t<19)
   				printf("Good Evening\n");
   			else 
   				printf("Good night\n");
		}
		else if (strcmp(token,"fileage")==0)
		{
			char exe[100];
			char fileloc[100]="/home/";
			strcat(fileloc,username);
			strcat(fileloc,"/Project/temp.txt");
			char filename[100]="";
			int j=8,i=0;
			//printf("%s\n",fileloc);
			while(buff[j]!='\0')
			{
				filename[i]=buff[j];
				i++;
				j++;
			}
			strcpy(exe,"stat --printf='%w' ");
			strcat(exe,path);
			strcat(exe,"/");
			strcat(exe,filename);
			strcat(exe," > ");
			strcat(exe,fileloc);
			system(exe);
			char str[100]="";
			FILE *fptr;
   			fptr = fopen(fileloc,"r");
   			fscanf(fptr,"%s",str);
   			fclose(fptr);
   			if (strcmp(str,"-")!=0)
   			{
   				char byear[5];
	   			char bmonth[3];
	   			char bday[3];
	   			bmonth[0]=str[5];bmonth[1]=str[6];
	   			byear[0]=str[0];byear[1]=str[1];byear[2]=str[2];byear[3]=str[3];
	   			bday[0]=str[8];bday[1]=str[9];
	   			int btday,btmonth,btyear;
	   			sscanf(bmonth, "%d", &btmonth);
	   			sscanf(byear, "%d", &btyear);
	   			sscanf(bday, "%d", &btday);
	   			//printf("%d %d %d\n",btday,btmonth,btyear);
	   			char cyear[5],cday[3];
	   			int ctday,ctmonth,ctyear;
	   			char months[12][10]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
	   			time_t curtime;
				time(&curtime);
				char *time=ctime(&curtime);
				char* tk1 = strtok(time, " ");
				tk1 = strtok(NULL, " ");
				char t[50];
				strcpy(t,tk1);
				//printf("%s\n",tk1);
				for (int i=0;i<12;i++)
				{
					if (strcmp(months[i],t)==0)
					{
						ctmonth=i+1;
						break;
					}		
				}
				tk1 = strtok(NULL, " ");
				strcpy(cday,tk1);
				tk1 = strtok(NULL, " ");
				tk1 = strtok(NULL, " ");
				strcpy(cyear,tk1);
				sscanf(cday,"%d",&ctday);
				sscanf(cyear,"%d",&ctyear);
				//printf("%d %d %d\n",ctday,ctmonth,ctyear);
				int *ageyears=(int*) malloc(sizeof(int)),*agemonths=(int*) malloc(sizeof(int)),*agedays=(int*) malloc(sizeof(int));			
				struct tm date1 = {.tm_year = btyear - 1900, .tm_mon = btmonth - 1, .tm_mday = btday};
	    			struct tm date2 = {.tm_year = ctyear - 1900, .tm_mon = ctmonth - 1, .tm_mday = ctday};
	    			
	    			mktime(&date1);
	    			mktime(&date2);
	    			*ageyears = date2.tm_year - date1.tm_year;
	    			*agemonths = date2.tm_mon - date1.tm_mon;
	    			*agedays = date2.tm_mday - date1.tm_mday;
	    			if (*agedays < 0) 
	    			{
					*agemonths -= 1;
					*agedays += daysInMonth(date1.tm_mon, date1.tm_year + 1900);
	    			}
	    			if (*agemonths < 0) 
	    			{
					*ageyears -= 1;
					*agemonths += 12;
	    			}
				printf("Age of file %s is : %d years %d months & %d days\n",filename,*ageyears,*agemonths,*agedays);
			}
			else 
				printf("Birth date doesnot exist of file %s\n",filename);
		}
		else if (strcmp(token,"cp")==0)
		{
			char file1[100]="";
			strcpy(file1,path);
			strcat(file1,"/");
			int i=0,j=3;
			char temp[50]="";
			while(buff[j]!=' ')
			{
				temp[i]=buff[j];
				i++;
				j++;
			}
			temp[i]='\0';
			strcat(file1,temp);
			j++;
			if (buff[j]=='/')
			{
				char file2[100]="";
				i=0;
				while(buff[j]!='\0')
				{
					file2[i]=buff[j];
					i++;
					j++;
				}
				i=strlen(file2)-1;
   				if (file2[i]=='/')
   				{
   					strcat(file2,temp);	
   				}
   				else 
   				{
   					strcat(file2,"/");
   					strcat(file2,temp);
   				}
   				printf("%s %s\n",file1,file2);
   				FILE *fptr1,*fptr2;
   				fptr1 = fopen(file2,"w");
   				fptr2 = fopen(file1,"r");
   				char ch;
   				while ((ch = fgetc(fptr2)) != EOF)
   				{
      					fputc(ch, fptr1);
      				}
      				fclose(fptr1);
      				fclose(fptr2);	
			}
			else 
			{
				char file2[100]="";
				strcpy(file2,path);
				strcat(file2,"/");
				i=0;
				char t[50]="";
				while(buff[j]!='\0')
				{
					t[i]=buff[j];
					i++;
					j++;
				}
				t[i]='\0';
				strcat(file2,t);
				//printf("%s %s\n",file1,file2);
				FILE *fptr1,*fptr2;
   				fptr1 = fopen(file2,"w");
   				if (fptr1==NULL)
   				{
   					i=strlen(file2)-1;
   					if (file2[i]=='/')
   					{
   						strcat(file2,temp);	
   					}
   					else 
   					{
   						strcat(file2,"/");
   						strcat(file2,temp);
   					}
   					//printf("%s %s\n",file1,file2);
   					fptr1 = fopen(file2,"w");
   				}
   				fptr2 = fopen(file1,"r");
   				char ch;
   				while ((ch = fgetc(fptr2)) != EOF)
   				{
      					fputc(ch, fptr1);
      				}
      				fclose(fptr1);
      				fclose(fptr2);	
			}
		}
		else if (strcmp(token,"mv")==0)
		{
			char file[100]="";
			char location[100]="";
			strcpy(file,path);
			strcat(file,"/");
			int i=0,j=3;
			char temp[50]="";
			while(buff[j]!=' ')
			{
				temp[i]=buff[j];
				i++;
				j++;
			}
			temp[i]='\0';
			strcat(file,temp);
			j++;
			if (buff[j]=='/')
			{
				i=0;
				while(buff[j]!='\0')
				{
					location[i]=buff[j];
					i++;
					j++;
				}
				i=strlen(location)-1;
   				if (location[i]=='/')
   				{
   					strcat(location,temp);	
   				}
   				else 
   				{
   					strcat(location,"/");
   					strcat(location,temp);
   				}
   				//printf("%s %s\n",file,location);
   				FILE *fptr1,*fptr2;
   				fptr1 = fopen(location,"w");
   				fptr2 = fopen(file,"r");
 				char ch;
   				while ((ch = fgetc(fptr2)) != EOF)
   				{
      					fputc(ch, fptr1);
      				}
      				fclose(fptr1);
      				fclose(fptr2);
      				remove(file);  				
			}
			else 
			{
				strcpy(location,path);
				strcat(location,"/");
				char t[50]="";
				i=0;
				while(buff[j]!='\0')
				{
					t[i]=buff[j];
					i++;
					j++;
				}
				strcat(location,t);
				i=strlen(location)-1;
   				if (location[i]=='/')
   				{
   					strcat(location,temp);	
   				}
   				else 
   				{
   					strcat(location,"/");
   					strcat(location,temp);
   				}
   				//printf("%s %s\n",file,location);
   				FILE *fptr1,*fptr2;
   				fptr1 = fopen(location,"w");
   				fptr2 = fopen(file,"r");
 				char ch;
   				while ((ch = fgetc(fptr2)) != EOF)
   				{
      					fputc(ch, fptr1);
      				}
      				fclose(fptr1);
      				fclose(fptr2);
      				remove(file);
			}			
		}
		else if (strcmp(token,"rename")==0)
		{
			char file1[100]="",file2[100]="";
			int i=7,j=0;
			strcpy(file1,path);
			strcpy(file2,path);
			char temp[50]="";
			while(buff[i]!=' ')
			{
				temp[j]=buff[i];
				j++;
				i++;
			}		
			i++;
			strcat(file1,"/");
			strcat(file1,temp);
			char t[50]="";
			j=0;
			while(buff[i]!='\0')
			{
				t[j]=buff[i];
				j++;
				i++;
			}
			strcat(file2,"/");
			strcat(file2,t);
			//printf("%s %s\n",file1,file2);
			FILE *fptr1,*fptr2;
   			fptr1 = fopen(file2,"w");
   			fptr2 = fopen(file1,"r");
 			char ch;
   			while ((ch = fgetc(fptr2)) != EOF)
   			{
      				fputc(ch, fptr1);
      			}
      			fclose(fptr1);
      			fclose(fptr2);
      			remove(file1);		
		}
		else if (strcmp(token,"clear")==0)
		{
			system("clear");
		}
		else if (strcmp(token,"history")==0)
		{
			FILE *h;
			h = fopen(history_file,"r");
			char String[100];
			while(fgets(String, 100, h)) 
			{
  				printf("%s", String);
			} 
			fclose(h);
		}
		else if (strcmp(token,"search_history")==0)
		{
			char cmd[100]="";
			int i=0,j=15;
			while(buff[j]!='\0')
			{
				cmd[i]=buff[j];
				i++;
				j++;
			}
			cmd[i]='\0';
			//printf("%s\n",cmd);
			FILE *h;
			h = fopen(history_file,"r");
			char String[100];
			while(fgets(String, 100, h)) 
			{
				char temp[100];
				strcpy(temp,String);
				char *tk;
   				tk = strtok(temp, " ");
   				//printf("%s\n",tk);
   				if (strcmp(tk,cmd)==0)
  					printf("%s", String);
			} 
			fclose(h);
		}
		else if (strcmp(token, "mkdir") == 0) 
		{
    			token = strtok(NULL, " ");
    			if (token == NULL) 
    			{
        			printf("mkdir: missing operand\n");
    			}		 
    			else 
    			{
        			char dir_name[100];
        			strcpy(dir_name, token);
        			char path_dir[100];
        			strcpy(path_dir, path);
        			strcat(path_dir, "/");
        			strcat(path_dir, dir_name);
        			int result = mkdir(path_dir, 0777);
        			if (result != 0) 
        			{
            				printf("mkdir: cannot create directory '%s': File exists\n", dir_name);
        			}
    			}
		}
		else if (strcmp(token, "rmdir") == 0) 
		{
    			token = strtok(NULL, " ");
    			if (token == NULL) 
    			{
        			printf("rmdir: missing operand\n");
   	 		}		 
    			else 
    			{
       				char dir_name[100];
        			strcpy(dir_name, token);
        			char path_dir[100];
        			strcpy(path_dir, path);
        			strcat(path_dir, "/");
        			strcat(path_dir, dir_name);
        			int result = rmdir(path_dir);
        			if (result != 0) 
        			{
        	    			printf("rmdir: failed to remove '%s': Directory not empty\n", dir_name);
        			} 
    			}
		}
		else if (strcmp(buff, "trash") == 0)
		{
   			 token = strtok(NULL, " ");
  			 if (token == NULL)
    			 {
        			printf("trash: missing operand\n");
    			 }
    			 else
    			 {
          			char file_name[100];
        			strcpy(file_name, token);
           			char trash_dir[100] = "/home/";
        			strcat(trash_dir, username);
        			strcat(trash_dir, "/.local/share/Trash/files");        
        			char original_path[100];
        			strcpy(original_path, path);
        			strcat(original_path, "/");
        			strcat(original_path, file_name);
        			char metadata_dir[1000];
        			sprintf(metadata_dir, "/home/%s/.local/share/Trash/info", username);
        			char metadata_file[2000];
        			sprintf(metadata_file, "%s/%s.trashinfo", metadata_dir, file_name);
        			FILE *f = fopen(metadata_file, "w");
        			fprintf(f, "[Trash Info]\nPath=%s\n", original_path);
        			fclose(f);
        			char command[1000];
        			sprintf(command, "mv %s/%s %s", path, file_name, trash_dir);
        			system(command);
    			 }
		 }
        	 else if (strcmp(buff, "restore") == 0)
		 {
    			token = strtok(NULL, " ");
    			if (token == NULL)
    			{
        			printf("restore: missing operand\n");
    			}
    			else
    			{
        			char file_name[100];
        			strcpy(file_name, token);
        			char trash_dir[100] = "/home/";
        			strcat(trash_dir, username);
        			strcat(trash_dir, "/.local/share/Trash/files");
        			char metadata_dir[1000];
        			sprintf(metadata_dir, "/home/%s/.local/share/Trash/info", username);
        			char metadata_file[2000];
        			sprintf(metadata_file, "%s/%s.trashinfo", metadata_dir, file_name);
        			FILE *f = fopen(metadata_file, "r");
        			if (f == NULL)
        			{
            				printf("restore: cannot restore file '%s': file not found in trash\n",file_name);
        			}
        			else
        			{
            				char original_path[100];
            				fscanf(f, "[Trash Info]\nPath=%s\n", original_path);
            				fclose(f);
            				char command[1000];
            				sprintf(command, "mv %s/%s %s", trash_dir, file_name, original_path);
            				system(command); 
            				remove(metadata_file);
        			}
    			}
		}
		else if (strcmp(token, "batchmove") == 0)
		{
    			token = strtok(NULL, " ");
    			if (token == NULL)
    			{
        			printf("batchmove: missing source directory\n");
    			}
    			else
    			{
        			char source_dir[100];
        			strcpy(source_dir, token);
        			token = strtok(NULL, " ");
        			if (token == NULL)
        			{
            				printf("batchmove: missing destination directory\n");
        			}
        			else
        			{
            				char dest_dir[100];
            				strcpy(dest_dir, token);
            				token = strtok(NULL, " ");
            				if (token == NULL)
            				{
                				printf("batchmove: missing extension\n");
            				}
            				else
            				{
                				char extension[10];
                				strcpy(extension, token);
                				char command[1000];
                				sprintf(command, "mv %s/*.%s %s", source_dir, extension, dest_dir);
                				system(command);
            				}
        			}
    			}
		}
		else if (strcmp(token, "rm") == 0)
		{
    			token = strtok(NULL, " ");
    			if (token == NULL)
    			{
        			printf("rm: missing operand\n");
    			}
    			else
    			{
        			char file_name[100];
        			strcpy(file_name, token);
        			char path_file[100];
        			strcpy(path_file, path);
        			strcat(path_file, "/");
        			strcat(path_file, file_name);
        			int result = remove(path_file);
        			if (result != 0)
        			{
        				printf("rm: failed to remove '%s': No such file or directory\n",file_name);   
 			        }
    			}
		}
		else if (strcmp(token, "shutdown") == 0) 
		{
    			token = strtok(NULL, " ");
    			if (token == NULL) 
    			{
        			system("sudo shutdown -h now");
    			}
    			else 
    			{
        			int time = atoi(token);
        			if (time > 0) 
        			{
            				printf("System will shutdown after %d seconds\n", time);
            				int pid = fork();
            				if (pid == 0) 
            				{
                				sleep(time);
                				system("sudo shutdown -h now");
            				}
            				else if (pid > 0) 
            				{
                				// parent process, continue taking commands
            				}
        			}
       				else 
        			{
            				printf("Invalid time value\n");
        			}
    			}	
		}	
        	else if (strcmp(token, "search") == 0)
        	{
           		token = strtok(NULL, " ");
            		if (token == NULL)
            		{
               			printf("search: missing operand\n");
               		}
            		else
            		{
            			char command[100];
                		strcpy(command, "find ");
                		strcat(command, path);
                		strcat(command, " -name ");
                		strcat(command, token);
                		system(command);
                	}
        	}
        	else if (strcmp(token, "uname") == 0)
		{
    			system("uname -a");
		}
		else if (strcmp(token, "print")==0)
		{
			token = strtok(NULL, " ");
			if (token == NULL)
			{
				printf("print: missing file operand\n");
			}
			else
			{
				char filename[100];
				strcpy(filename, token);
				char path_filename[200];
				sprintf(path_filename, "%s/%s", path, filename);
				FILE* file = fopen(path_filename, "r");
				if (file == NULL)
				{
					printf("print: %s: No such file or directory\n", filename);
				}
				else
				{
					char line[100];
					while (fgets(line, 100, file))
					{
						printf("%s", line);
					}
					fclose(file);
				}
			}
		}
		else if (strcmp(token, "create")==0)
		{
			token = strtok(NULL, " ");
			if (token == NULL)
			{
				printf("create: missing file operand\n");
			}
			else
			{
				char filename[100];
				strcpy(filename, token);
				char path_filename[200];
				sprintf(path_filename, "%s/%s", path, filename);
				FILE* file = fopen(path_filename, "w");
				fclose(file);
			}
		}
		else if (strcmp(token, "gedit") == 0) 
		{
    			token = strtok(NULL, " ");
    			if (token == NULL) 
    			{
        			system("gedit");
    			}		 
    			else 
    			{
        			char file_name[100];
        			strcpy(file_name, token);
        			char command[1000];
        			sprintf(command, "gedit -w %s/%s",path,file_name);
        			system(command);
    			}
		}		
		else
			printf("cammand not found\n");	
	}
}
