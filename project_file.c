

							    		// STUDENT DATA MANAGEMENT SYSTEM {C,SQLITE3,CMD}

#include<sqlite3.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int x=0;		//global

void printLine(char g,int size)
{
int i;
for(i=1;i<=size;i++) printf("%c",g);
printf("\n");
}
void addStudent();
void display();
int rowHandler();
void update();
void delete();
int check();
void search();


int check(void *ptr,int columnCount,char **dataPtr,char **columnNamePtr)					//Check_For_Empty_OR_Not
{
printf("Working\n");
int e=0;
if(dataPtr[e]==NULL)
{
}
else
{
x=*(dataPtr[e]);				
}
printLine('-',100);
return 0;				 
} 



int main()														//MAIN FUNTION
{
int ch;
while(1)
{
printf("1. Add Student\n"); 
printf("2. Display List Of Student\n");
printf("3. Update Student\n");
printf("4. Search Student\n");
printf("5. Delete Student\n");
printf("6. Exit\n");
printf("Enter Your Choice : ");
scanf("%d",&ch);
fflush(stdin);
if(ch==1) addStudent();
else if(ch==2) display();
else if(ch==3) update();
else if(ch==4) search();
else if(ch==5) delete();
else if(ch==6) 
{
printLine('-',100);
char d=2,h=3;
printf("%50s %c%c%c\n","Welcome",h,d,h);
printLine('-',100);
break;
}
else printf("Invalid Input\n");
}
return 0;
}





void addStudent()														// add
{
printLine('-',100);
printf("%50s\n","Add Module");
printLine('-',100);
sqlite3 *db;
char *errorMessage;
int result;
int resultCode;
char rollNumber[10];
char sql[1001];
char name[32],gender;
printf("Enter Roll Number : ");
scanf("%s",&rollNumber);
fflush(stdin);

resultCode=sqlite3_open("p1.db",&db);
if(resultCode!=SQLITE_OK)
{
printf("Unable to connect to p1.db, reason %s\n",sqlite3_errmsg(db));
sqlite3_close(db);
return;
}
int checker=0;
char *a=rollNumber;
while(*a)
{
if(*a>=0 && *a<=47 || *a>=58 && *a<=255 ) checker=1;
a++;
}
if(checker==1)
{
printf("Invalid roll no.!\n");
return;
}
int rollNumber2=atoi(rollNumber);
if(rollNumber2<=0)
{
printf("Invalid Roll Number\n");
return;
}


sprintf(sql,"select exists(select * from student as s where s.roll_number=%d);",rollNumber2);
resultCode=sqlite3_exec(db,sql,check,"Student Information",&errorMessage);
if(resultCode!=SQLITE_OK)
{
printf("Unable to fetch Student data, reason %s\n",errorMessage);
sqlite3_free(errorMessage);
sqlite3_close(db);
return;
}

if(x==49)				
{	
printf("This Roll Number is already alloted!\n");
sprintf(sql,"select * from student where roll_number=%d;",rollNumber2);
resultCode=sqlite3_exec(db,sql,rowHandler,"Student Information :",&errorMessage);
if(resultCode!=SQLITE_OK)
{
printf("Unable to fetch Student data, reason %s\n",errorMessage);
sqlite3_free(errorMessage);
sqlite3_close(db);
return;
}
printf("Unable to Add Student!\n");
printLine('-',100);
sqlite3_close(db);
return;
}//if ends


printf("Enter Name of Student: ");
fgets(name,32,stdin);
fflush(stdin);
name[strlen(name)-1]='\0';
checker=0;
char *b=name;
while(*b)
{
if(*b>=48 && *b<=57) checker=2;
b++;
}
if(checker==2)
{
printf("Invalid Name!\n(name does not contain numbers)\n");
return;
}
printLine('-',100);
printf("Enter Gender (M/F) : ");
gender=getchar();
fflush(stdin);
if(gender!='f'&&gender!='F'&&gender!='m'&&gender!='M')
{
printf("Invalid Gender\n");
printLine('-',100);
return;
}
if(gender=='f') gender='F';
if(gender=='m') gender='M';
sprintf(sql,"insert into Student values(%d,'%s','%c');",rollNumber2,name,gender);
result=sqlite3_exec(db,sql,0,0,&errorMessage);
if(result!=SQLITE_OK)
{
printf("Unable to insert Student, reason %s\n",errorMessage);
sqlite3_free(errorMessage);
sqlite3_close(db);
return;
}
printLine('-',100);
printf("Student inserted in Student table\n"); 
printLine('-',100);
sqlite3_close(db);
return;
}									// add end





void display()											//DISPLAY
{
char sql[1001];
printLine('*',100);
printf("%50s\n","Display Module");
printLine('*',100);
sqlite3 *db;
char *errorMessage=NULL;
int resultCode;
resultCode=sqlite3_open("p1.db",&db);
if(resultCode!=SQLITE_OK)
{
printf("Unable to connect to p1.db\n");
sqlite3_close(db);
return;
}
sprintf(sql,"select exists(select * from student);");
resultCode=sqlite3_exec(db,sql,check,"Student Information",&errorMessage);
if(resultCode!=SQLITE_OK)
{
printf("Unable to fetch Student data, reason %s\n",errorMessage);
sqlite3_free(errorMessage);
sqlite3_close(db);
return;
}

if(x==49) 
{
resultCode=sqlite3_exec(db,"select * from student order by roll_number ASC",rowHandler,"Student Data",&errorMessage);
if(resultCode!=SQLITE_OK)
{
printf("Unable to fetch the data, reason %s\n",errorMessage);
sqlite3_free(errorMessage);
sqlite3_close(db);
return;
}
sqlite3_close(db);
return;
}
else //if absent means 0
{
printf("There No Student Present in DataBase!\n");
printLine('-',100);
sqlite3_close(db);
return;
}
}							// DISPLAY ENDS





void update()																	// UPDATE
{
char sql[1001];
sqlite3 *db;
char *errorMessage;
int resultCode;
resultCode=sqlite3_open("p1.db",&db);
if(resultCode!=SQLITE_OK)
{
printf("Unable to connect to p1.db\n");
sqlite3_close(db);
return;
}
sprintf(sql,"select exists(select * from student);");
resultCode=sqlite3_exec(db,sql,check,"Student Information : ",&errorMessage);
if(resultCode!=SQLITE_OK)
{
printf("Unable to fetch Student data, reason %s\n",errorMessage);
sqlite3_free(errorMessage);
sqlite3_close(db);
return;
}
if(x==49)       
{

char m;
int rollNumber;
printf("%50s\n","Update Module");							
printLine('-',100);
printf("Enter Roll no. of Student to Update : ");
scanf("%d",&rollNumber);
fflush(stdin);
if(rollNumber<0)
{
printf("Invalid roll Number\n");
return;
}
sprintf(sql,"select exists(select * from student as s where s.roll_number=%d);",rollNumber);
resultCode=sqlite3_exec(db,sql,check,"Student Information",&errorMessage);
if(resultCode!=SQLITE_OK)
{
printf("Unable to fetch Student data, reason %s\n",errorMessage);
sqlite3_free(errorMessage);
sqlite3_close(db);
return;
}

if(x==49)	
{
sprintf(sql,"select * from student where roll_number=%d;",rollNumber);
resultCode=sqlite3_exec(db,sql,rowHandler,"Student Information :",&errorMessage);
if(resultCode!=SQLITE_OK)
{
printf("Unable to fetch Student data, reason %s\n",errorMessage);
sqlite3_free(errorMessage);
sqlite3_close(db);
return;
}

}//if ends
else
{
printf("Student not found\n");
printLine('-',100);
return;
}

printf("Wanna Update (Y/N) : ");
m=getchar();
fflush(stdin);
if(m!='y' && m!='Y')
{
printf("Student Not Updated\n");
sqlite3_close(db);
return;
}                        
char name[32],gender;
printf("Enter New Name of student : ");
fgets(name,32,stdin);
fflush(stdin);
name[strlen(name)-1]='\0';
int checker=0;
char *a=name;
while(*a)
{
if(*a>=48 && *a<=57) checker=2;
a++;
}
if(checker==2)
{
printf("Invalid Name!\n(name does not contain numbers)\n");
return;
}
printf("Enter Gender (M/F) : ");
gender=getchar();
fflush(stdin);
if(gender!='f'&&gender!='F'&&gender!='m'&&gender!='M')
{
printf("Invalid Gender\n");
sqlite3_close(db);
return;
}
if(gender=='f') gender='F';
if(gender=='m') gender='M';
printf("Wanna Save (Y/N) : ");
m=getchar();
fflush(stdin);
if(m!='y' && m!='Y')
{
printf("Student Not Updated\n");
sqlite3_close(db);
return;
}


sprintf(sql,"update student set name='%s', gender='%c' where roll_number=%d;",name,gender,rollNumber);  
resultCode=sqlite3_exec(db,sql,0,0,&errorMessage);
if(resultCode!=SQLITE_OK)
{
printf("Unable to update Student, reason %s\n",errorMessage);
sqlite3_free(errorMessage);
sqlite3_close(db);
return;
}
printf("Student Updated in Student table\n"); 
sqlite3_close(db);
return;

} // if ends

else 
{
printf("There No Student Present in DataBase to Update\n");
printLine('-',100);
sqlite3_close(db);
return;
}

}//UPDATE END

void search()																// Search
{
printLine('-',100);
printf("%50s\n","Search Module");
printLine('-',100);
sqlite3 *db;
char *errorMessage;
char sql[1001];
int resultCode;
resultCode=sqlite3_open("p1.db",&db);
if(resultCode!=SQLITE_OK)
{
printf("Unable to connect to p1.db, reason %s\n",sqlite3_errmsg(db));
sqlite3_close(db);
return;
}
sprintf(sql,"select exists(select * from student);");
resultCode=sqlite3_exec(db,sql,check,"Student Information : ",&errorMessage);
if(resultCode!=SQLITE_OK)
{
printf("Unable to fetch Student data, reason %s\n",errorMessage);
sqlite3_free(errorMessage);
sqlite3_close(db);
return;
}
if(x==49) 
{
x=0;
char m;
int rollNumber;
printf("Enter Roll no. of Student to Search : ");
scanf("%d",&rollNumber);
fflush(stdin);
if(rollNumber<0)
{
printf("Invalid roll Number\n");
return;
}

sprintf(sql,"select exists(select * from student as s where s.roll_number=%d);",rollNumber);
resultCode=sqlite3_exec(db,sql,check,"Student Information",&errorMessage);
if(resultCode!=SQLITE_OK)
{
printf("Unable to fetch Student data, reason %s\n",errorMessage);
sqlite3_free(errorMessage);
sqlite3_close(db);
return;
}

if(x==49)
{
sprintf(sql,"select * from student where roll_number=%d;",rollNumber);
resultCode=sqlite3_exec(db,sql,rowHandler,"Student Information :",&errorMessage);
if(resultCode!=SQLITE_OK)
{
printf("Unable to fetch Student data, reason %s\n",errorMessage);
sqlite3_free(errorMessage);
sqlite3_close(db);
return;
}

}
else printf("Student not found\n");
printLine('-',100);
sqlite3_close(db);



} // if ends

else //if student absent means 0
{
printf("There No Student Present in DataBase to Search!\n");
printLine('-',100);
sqlite3_close(db);
return;
}

}// search ends

void delete()													//DELETE
{
printLine('-',100);
printf("%50s\n","Delete Module");
printLine('-',100);
sqlite3 *db;
char *errorMessage;
char sql[1001];
int resultCode;
resultCode=sqlite3_open("p1.db",&db);
if(resultCode!=SQLITE_OK)
{
printf("Unable to connect to p1.db, reason %s\n",sqlite3_errmsg(db));
sqlite3_close(db);
return;
}

sprintf(sql,"select exists(select * from student);");
resultCode=sqlite3_exec(db,sql,check,"Student Information : ",&errorMessage);
if(resultCode!=SQLITE_OK)
{
printf("Unable to fetch Student data, reason %s\n",errorMessage);
sqlite3_free(errorMessage);
sqlite3_close(db);
return;
}
if(x==49)       
{
char m;
int rollNumber;
printf("Enter Roll no. of Student to Delete : ");
scanf("%d",&rollNumber);
fflush(stdin);
if(rollNumber<0)
{
printf("Invalid roll Number\n");
return;
}

sprintf(sql,"select exists(select * from student as s where s.roll_number=%d);",rollNumber);
resultCode=sqlite3_exec(db,sql,check,"Student Information",&errorMessage);
if(resultCode!=SQLITE_OK)
{
printf("Unable to fetch Student data, reason %s\n",errorMessage);
sqlite3_free(errorMessage);
sqlite3_close(db);
return;
}

if(x==49)				
{

sprintf(sql,"select * from student where roll_number=%d;",rollNumber);
resultCode=sqlite3_exec(db,sql,rowHandler,"Student Information :",&errorMessage);
if(resultCode!=SQLITE_OK)
{
printf("Unable to fetch Student data, reason %s\n",errorMessage);
sqlite3_free(errorMessage);
sqlite3_close(db);
return;
}

}//if ends
else
{
printf("Student not found\n");
printLine('-',100);
return;
}

printf("Wanna Delete (Y/N) : ");
m=getchar();
fflush(stdin);
if(m!='y' && m!='Y')
{
printLine('-',100);
printf("Student Not Deleted\n");
printLine('-',100);
sqlite3_close(db);
return;
}                        
sprintf(sql,"delete from student where roll_number=%d;",rollNumber);
resultCode=sqlite3_exec(db,sql,0,0,&errorMessage);
if(resultCode!=SQLITE_OK)
{
printf("Unable to Delete Student, reason %s\n",errorMessage);
sqlite3_free(errorMessage);
sqlite3_close(db);
return;
}
printLine('-',100);

printf("Student Deleted\n"); 
printLine('-',100);
sqlite3_close(db);

} // if ends

else //if absent means 0
{
printf("There No Student Present in DataBase to Delete!\n");
printLine('-',100);
sqlite3_close(db);
return;
}



}// delete end



int rowHandler(void *ptr,int columnCount,char **dataPtr,char **columnNamePtr)					//rawHandler
{
int e;
if(ptr!=NULL)
{
printf("%s\n",(char*)ptr);
printLine('-',100);
}
for(e=0;e<columnCount;e++)
{
if(dataPtr[e]==NULL)
{
printf("%s : null\n",columnNamePtr[e]);
}
else
{
printf("%s : %s\n",columnNamePtr[e],dataPtr[e]);
}
}
printLine('-',100);
return 0; 
}





