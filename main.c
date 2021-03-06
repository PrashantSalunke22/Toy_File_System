#include"structure.h"
#include"alloc.h"
#include"change_directory.h"
#include"datafree.h"
#include"Files_namei.h"
#include"inodealloc.h"
#include"inodefree.h"
#include"list.h"
#include"mountFS.h"
#include"myappend.h"
#include"mycreat.h"
#include"mymkdir.h"
#include"myopen.h"
#include"myread.h"
#include"myremove.h"
#include"myremovedir.h"
#include"mywrite.h"

int main()
{
	FILE *fp;	
	int size=40,blk=BLOCK_SIZE,i=0,n,cur_inode=1;
	char cmd[40],s1[20],s2[20];
	
	fp = fopen("devfs","r+");
  	if(!fp)
	{
	    printf("\nError: Unable to MOUNT ");
	    exit(1);
	}
	
	fread(&sb,sizeof(struct superblock),1,fp);
	
	mountFS(size,blk);
	strcpy(cmdprompt,"MY_PROMPT");
	printf("\nType 'help' for any help\n");
	while(1)
	{
		printf("\n\n%s :=",cmdprompt);
		gets(cmd);
		n=sscanf(cmd,"%s%s",s1,s2);
		switch(n)
		{
			case 1:{
					if(strcmp(s1,"ls")==0)
					{	list(cur_inode);
						break;
					}
					if(strcmp(s1,"exit")==0)
					{	
						exit(0);
					}
					if(strcmp(s1,"FORMAT")==0)
					{	
						printf("\nARE YOU SURE(y/n):-");
						if(getchar()=='y')
						{
							fp = fopen("devfs","w+");
							sb.fs_size=0;
							fwrite(&sb,sizeof(SuperBlock),1,fp);
							mountFS(size,blk);
							
						}
						break;
					}
					if(strcmp(s1,"help")==0)
					{	
						printf("\nls 			:= list all files in current directory");
						printf("\nmkdir <dir name> 	:= create new directory in current directory");
						printf("\nrmdir <dir name> 	:= remove directory from current directory");
						printf("\ncreat <filename> 	:= create new file in current directory");
						printf("\nrm <filename> 	        := remove file from current directory");
						printf("\ncd <path> 		:= set pointer in end file in path ");
						printf("\nFORMAT		 	:= format the whole file system");
						printf("\nexit		 	:= exit the shell");
					
						break;
					}
				
				}
			case 2:
				{
					if(strcmp(s1,"open")==0)
					{	
						
						printf("\nInode allocated= %d",myopen(s2,cur_inode));
						break;
					}

					if(strcmp(s1,"read")==0)
					{	
						printf("\n%d\n",atoi(s2));
						myread(atoi(s2));
						break;
					}
			
					if(strcmp(s1,"write")==0)
					{	
						
						mywrite(atoi(s2));
						break;
					}
					if(strcmp(s1,"append")==0)
					{	
						
						printf("\nInode allocated= %d",myappend(atoi(s2)));
						break;
					}


					if(strcmp(s1,"creat")==0)
					{	
						
						printf("\nInode allocated= %d",mycreat(s2,cur_inode));
						break;
					}

					if(strcmp(s1,"mkdir")==0)
					{
						printf("\nInode allocated=%d",mymkdir(s2,cur_inode));
						break;								
					}
					if(strcmp(s1,"rm")==0)
					{
						myremove(s2,cur_inode);
						break;

					}
					if(strcmp(s1,"rmdir")==0)
					{
						myremovedir(s2,cur_inode);
						break;						
					}
					if(strcmp(s1,"cd")==0)
					{	change_directory(s2,cur_inode);
						cur_inode=FileS_namei(s2,cur_inode);
						break;
					}		
				}
		}	
		strcpy(s1,"");
		strcpy(s2,"");
	}		
	return 0;
}
