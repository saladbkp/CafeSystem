#pragma once
#pragma warning(disable:4996)

#include<stdio.h>
#include<conio.h>		//_getch()
#include<stdlib.h>		//system()
#include<string.h>		//strlen()

#define MAXCHAR 50
char curr_user[MAXCHAR];
#pragma region struct
//1
struct student {
	char userid[MAXCHAR];
	char fullName[MAXCHAR];
	char password[MAXCHAR];
	char gender[MAXCHAR];
	struct student* pNext;

};

struct tutor {
	char tutorid[MAXCHAR];
	char password[MAXCHAR];
	char fullName[MAXCHAR];
	char courseName[MAXCHAR];
	struct tutor* pNext;

};

struct session {
	char sessionid[MAXCHAR];
	char title[MAXCHAR];
	char day[MAXCHAR];
	char startTime[MAXCHAR];
	char Location[MAXCHAR];
	char TutorCode[MAXCHAR];
	struct session* pNext;

};

struct enroll {
	char studentName[MAXCHAR];
	char sessionCode[MAXCHAR];
	char TutorCode[MAXCHAR];
	char Location[MAXCHAR];
	struct enroll* pNext;

};
struct user {
	char userName[MAXCHAR];
	char password[MAXCHAR];
	int role;
	struct user* pNext;

};

#pragma endregion

// linked list
#pragma region common function
char* trim(char* s) {
	char* ptr;
	if (!s)
		return NULL;   // handle NULL string
	if (!*s)
		return s;      // handle empty string
	for (ptr = s + strlen(s) - 1; (ptr >= s) && isspace(*ptr); --ptr);
	ptr[1] = '\0';
	return s;
}

int check_void_file(char path[])
{
	FILE* fp;
	fp = fopen(path, "r+");
	char ch;
	ch = fgetc(fp);
	fclose(fp);
	if (ch == EOF) return 0;
	return 1;
}

int checkuser(struct user* user)
{
	int exist = 0;

	char username[MAXCHAR];
	strcpy(username, user->userName);

	char username_f[MAXCHAR];

	FILE* fp;
	fp = fopen("user_pwd.txt", "r+");
	while (fscanf(fp,"%s",username_f)!=EOF) {
		username_f[strcspn(username_f, "\n")] = 0;
		if (strcmp(username, username_f) == 0) {
			exist = 1;
			break;
		}
	}
	fclose(fp);

	return exist;
}

int checksession(struct session* ss)
{
	int exist = 0;

	char session[MAXCHAR];
	strcpy(session, ss->sessionid);
	char tutor[MAXCHAR];
	strcpy(tutor, ss->TutorCode);

	char session_f[MAXCHAR];

	FILE* fp;
	fp = fopen("session.txt", "r+");
	while (fscanf(fp, "%s", session_f) != EOF) {
		session_f[strcspn(session_f, "\n")] = 0;
		if (strcmp(session, session_f) == 0 || strcmp(tutor,session_f) == 0 ) {
			exist = 1;
			break;
		}
	}
	fclose(fp);

	return exist;
}

int checktutor(struct tutor* tt)
{
	int exist = 0;

	char session[MAXCHAR];
	strcpy(session, tt->courseName);

	char tutor_f[MAXCHAR];

	FILE* fp;
	fp = fopen("acc.txt", "r+");
	while (fscanf(fp, "%s", tutor_f) != EOF) {
		tutor_f[strcspn(tutor_f, "\n")] = 0;
		if (strcmp(session, tutor_f) == 0){
			exist = 1;
			break;
		}
	}
	fclose(fp);

	return exist;
}

char* findTutorName(struct tutor* head ,char* id) {
	struct tutor* tt_p;
	tt_p = head->pNext;
	if (tt_p == NULL)
		return NULL;
	while (tt_p != NULL)
	{
		if (strcmp(id, trim(tt_p->tutorid)) == 0)
			return trim(tt_p->fullName);
		tt_p = tt_p->pNext;
	}
}

struct student* findStuName(struct student* head, char* id) {
	struct student* stu_p;
	stu_p = head->pNext;
	if (stu_p == NULL)
		return NULL;
	while (stu_p != NULL)
	{
		if (strcmp(id, trim(stu_p->userid)) == 0)
			return stu_p;
		stu_p = stu_p->pNext;
	}
}


#pragma endregion

#pragma region student
int override_Student(struct student* stu) {
	FILE* fp;
	fp = fopen("acc.txt", "w");

	struct student* p;
	p = stu;
	do{
		fprintf(fp, "\n-\n");
		fprintf(fp, "1 %s\n", p->userid);
		fprintf(fp, "%s\n", p->fullName);
		fprintf(fp, "%s\n", p->password);
		fprintf(fp, "%s", p->gender);

		p = p->pNext;
	} while (p->pNext != NULL);

	fclose(fp);

	FILE* fp_u;
	fp_u = fopen("user_pwd.txt", "w");

	struct student* p_acc;
	p_acc = stu;
	do{
		fprintf(fp_u, "\n1 %s %s", p_acc->userid, p_acc->password);
		p_acc = p_acc->pNext;
	} while (p_acc->pNext != NULL);
	fclose(fp_u);

	return 1;
}

int createStudent(struct student *stu) {
	FILE* fp;
	fp = fopen("acc.txt", "a");

	fprintf(fp, "\n-\n");
	fprintf(fp, "1 %s\n",stu->userid);
	fprintf(fp, "%s\n", stu->fullName);
	fprintf(fp, "%s\n", stu->password);
	fprintf(fp, "%s", stu->gender);

	fclose(fp);

	FILE* fp_u;
	fp_u = fopen("user_pwd.txt", "a");
	fprintf(fp_u, "\n1 %s %s", stu->userid, stu->password);
	fclose(fp_u);

	return 1;
}

struct student* make_linklist()   
{
	struct student* head;

	head = (struct student*)malloc(sizeof(struct student));
	head->pNext = NULL;
	
	FILE* fp;
	char path[] = "acc.txt";
	fp = fopen(path, "r+");

	if (check_void_file(path) == 0) {
		printf("Can't access account detail...\n");
		return head;
	}

	struct student* p;
	p = head;
	char ch;
	int role;
	char line[50];

	while (fgets(line, sizeof(line), fp) != NULL) {
		struct student* new_student_init;

		new_student_init = (struct student*)malloc(sizeof(struct student));
		fscanf(fp, "%d", &role);
		
		if (role == 1) {
			ch = fgetc(fp);
			fscanf(fp, "%[^\n]%*c", new_student_init->userid);
			fscanf(fp, "%[^\n]%*c", new_student_init->fullName);
			fscanf(fp, "%[^\n]%*c", new_student_init->password);
			fscanf(fp, "%[^\n]%*c", new_student_init->gender);
			ch = fgetc(fp);
			new_student_init->pNext = NULL;
			p->pNext = new_student_init;
			p = p->pNext;
			role = 0;
		}
		
	}
	fclose(fp);
	return head;
}

void printStudent() {
	system("cls");

	struct student* p;
	p = make_linklist()->pNext;

	printf("*********************************************************************************\n");
	printf("*\t\t\tWelcome to Apu Student Cafe System \t\t\t*\n");
	printf("*********************************************************************************\n");
	printf("*\tUser ID\t*\tFullName\t*\tGender\t*\n");
	printf("*********************************************************************************\n");

	while (p)
	{
		printf("*\t%s\t*\t%s\t*\t%s\t*\n",
			p->userid,
			p->fullName,
			p->gender
		);

		p = p->pNext;
	
	}
	printf("*********************************************************************************\n");

	system("pause");
	system("cls");
	
}

struct student* deleteStudent(struct student* stu, struct student* t) {

	struct student* p = NULL;
	struct student* front_p = NULL;
	p = stu;
	while (p != NULL) {
		if (p == t) {
			if (p == stu) {
				stu = p->pNext;
				free(p);
				return stu;
			}
			else {
				front_p->pNext = p->pNext;
				free(p);
				return stu;
			}
			
		}
		else {
			front_p = p;
			p = p->pNext;
		}
	}

}

#pragma endregion

#pragma region tutor
struct tutor* make_tutor_linklist()
{
	struct tutor* head;

	head = (struct tutor*)malloc(sizeof(struct tutor));
	head->pNext = NULL;

	FILE* fp;
	char path[] = "acc.txt";
	fp = fopen(path, "r+");

	if (check_void_file(path) == 0) {
		printf("Can't access account detail...");
		return head;
	}

	struct tutor* p;
	p = head;
	char ch;
	int role;
	char line[50];

	while (fgets(line, sizeof(line), fp) != NULL) {
		struct tutor* new_tutor_init;

		new_tutor_init = (struct tutor*)malloc(sizeof(struct tutor));
		fscanf(fp, "%d", &role);

		if (role == 2) {
			ch = fgetc(fp);
			fscanf(fp, "%[^\n]%*c", new_tutor_init->tutorid);
			fscanf(fp, "%[^\n]%*c", new_tutor_init->fullName);
			fscanf(fp, "%[^\n]%*c", new_tutor_init->password);
			fscanf(fp, "%[^\n]%*c", new_tutor_init->courseName);
			ch = fgetc(fp);
			new_tutor_init->pNext = NULL;
			p->pNext = new_tutor_init;
			p = p->pNext;
			role = 0;
		}

	}
	fclose(fp);
	return head;
}

int createTutor(struct tutor* tt) {
	FILE* fp;
	fp = fopen("acc.txt", "a");

	fprintf(fp, "\n-\n");
	fprintf(fp, "1 %s\n", tt->tutorid);
	fprintf(fp, "%s\n", tt->fullName);
	fprintf(fp, "%s\n", tt->password);
	fprintf(fp, "%s", tt->courseName);

	fclose(fp);

	FILE* fp_u;
	fp_u = fopen("user_pwd.txt", "a");
	fprintf(fp_u, "\n2 %s %s", tt->tutorid, tt->password);
	fclose(fp_u);

	return 1;
}

void printTutor() {
	system("cls");

	struct tutor* p;
	p = make_tutor_linklist()->pNext;

	printf("*********************************************************************************\n");
	printf("*\t\t\tWelcome to Apu Student Cafe System \t\t\t*\n");
	printf("*********************************************************************************\n");
	printf("*\tTutor ID\t*\tFullName\t*\tCourse\t\t\t*\n");
	printf("*********************************************************************************\n");

	while (p)
	{
		printf("*\t%s\t\t*\t%s\t\t*\t%s\t\t*\n",
			p->tutorid,
			p->fullName,
			p->courseName
		);

		p = p->pNext;

	}
	printf("*********************************************************************************\n");

	system("pause");
	system("cls");
}


#pragma endregion

#pragma region session
struct session* make_session_linklist()
{
	struct session* head;

	head = (struct session*)malloc(sizeof(struct session));
	head->pNext = NULL;

	FILE* fp;
	char path[] = "session.txt";
	fp = fopen(path, "r+");

	if (check_void_file(path) == 0) {
		printf("Can't access account detail...");
		return head;
	}

	struct session* p;
	p = head;
	char ch;
	char line[50];

	while (fgets(line, sizeof(line), fp) != NULL) {
		struct session* new_session_init;

		new_session_init = (struct session*)malloc(sizeof(struct session));

		fscanf(fp, "%[^\n]%*c", new_session_init->sessionid);
		fscanf(fp, "%[^\n]%*c", new_session_init->title);
		fscanf(fp, "%[^\n]%*c", new_session_init->day);
		fscanf(fp, "%[^\n]%*c", new_session_init->startTime);
		fscanf(fp, "%[^\n]%*c", new_session_init->Location);
		fscanf(fp, "%[^\n]%*c", new_session_init->TutorCode);

		ch = fgetc(fp);
		new_session_init->pNext = NULL;
		p->pNext = new_session_init;
		p = p->pNext;
		}

	
	fclose(fp);
	return head;
}

int createSession(struct session* ss) {
	FILE* fp;
	fp = fopen("session.txt", "a");

	fprintf(fp, "\n-\n");
	fprintf(fp, "%s\n", ss->sessionid);
	fprintf(fp, "%s\n", ss->title);
	fprintf(fp, "%s\n", ss->day);
	fprintf(fp, "%s\n", ss->startTime);
	fprintf(fp, "%s\n", ss->Location);
	fprintf(fp, "%s", ss->TutorCode);

	fclose(fp);
	return 1;
}


void printSession() {
	system("cls");

	struct session* p;
	p = make_session_linklist()->pNext;

	printf("*********************************************************************************\n");
	printf("*\t\t\tWelcome to Apu Student Cafe System \t\t\t*\n");
	printf("*********************************************************************************\n");
	printf("*\tSession ID\t*\tTitle\t\t\t*\t\tDay\t*\tStart Time\t*\tLocation\t*\tTutor Code\t*\n");
	printf("*********************************************************************************\n");

	while (p)
	{
		printf("*\t%s\t\t*\t%-20s\t*\t%-10s\t*\t%s\t*\t%s\t*\t%s\t*\n",
			p->sessionid,
			p->title,
			p->day,
			p->startTime,
			p->Location,
			p->TutorCode
		);

		p = p->pNext;

	}
	printf("*********************************************************************************\n");

	system("pause");
	system("cls");
}

#pragma endregion

#pragma region enroll

struct enroll* make_enroll_linklist()
{
	struct enroll* head;

	head = (struct enroll*)malloc(sizeof(struct enroll));
	head->pNext = NULL;

	FILE* fp;
	char path[] = "enroll.txt";
	fp = fopen(path, "r+");

	if (check_void_file(path) == 0) {
		printf("Can't access account detail...");
		return head;
	}

	struct enroll* p;
	p = head;
	char ch;
	char line[50];

	while (fgets(line, sizeof(line), fp) != NULL) {
		struct enroll* new_enroll_init;

		new_enroll_init = (struct enroll*)malloc(sizeof(struct enroll));

		fscanf(fp, "%[^\n]%*c", new_enroll_init->studentName);
		fscanf(fp, "%[^\n]%*c", new_enroll_init->sessionCode);
		fscanf(fp, "%[^\n]%*c", new_enroll_init->TutorCode);
		fscanf(fp, "%[^\n]%*c", new_enroll_init->Location);

		ch = fgetc(fp);
		new_enroll_init->pNext = NULL;
		p->pNext = new_enroll_init;
		p = p->pNext;
	}


	fclose(fp);
	return head;
}

struct enroll* assignEnroll(char*studentid,char* sessionid) {

	struct enroll* enr;

	enr = (struct enroll*)malloc(sizeof(struct enroll));


	struct student* stu_p;
	stu_p = make_linklist()->pNext;
	struct tutor* tt_p;
	tt_p = make_tutor_linklist()->pNext;
	struct session* ss_p;
	ss_p = make_session_linklist()->pNext;

	while (stu_p != NULL) {
		if (strcmp(trim(stu_p->userid), studentid) == 0) {
			strcpy(enr->studentName, trim(stu_p->fullName));
			printf("%s\n", enr->studentName);
		}
		stu_p = stu_p->pNext;
	}

	while (ss_p->pNext != NULL) {
		if (strcmp(trim(ss_p->sessionid), sessionid) == 0) {
			strcpy(enr->sessionCode, sessionid);
			strcpy(enr->Location, trim(ss_p->Location));
			printf("%s\n", enr->sessionCode); 
			printf("%s\n", enr->Location);
				
			while (tt_p->pNext != NULL) {
				if (strcmp(trim(tt_p->tutorid), ss_p->TutorCode) == 0) {
					strcpy(enr->TutorCode, trim(tt_p->fullName));
					printf("%s\n", enr->TutorCode);
				}
				tt_p = tt_p->pNext;
			}
		}
		ss_p = ss_p->pNext;

	}

	return enr;
}

int createEnroll(struct enroll * en) {
	
	FILE* fp;
	fp = fopen("enroll.txt", "a");
	
	fprintf(fp, "\n-\n");
	fprintf(fp, "%s\n", en->studentName);
	fprintf(fp, "%s\n", en->sessionCode);
	fprintf(fp, "%s\n", en->TutorCode);
	fprintf(fp, "%s", en->Location);

	fclose(fp);
	return 1;
}

void printEnroll() {
	system("cls");

	struct enroll* p;
	p = make_enroll_linklist()->pNext;

	printf("*********************************************************************************\n");
	printf("*\t\t\tWelcome to Apu Student Cafe System \t\t\t*\n");
	printf("*********************************************************************************\n");
	printf("*\tStudent Name\t*\tSession Code\t\t*\tTutor Code\t*\tLocation\t*\n");
	printf("*********************************************************************************\n");

	while (p)
	{
		printf("*\t%s\t*\t%s\t*\t%s\t*\t%s\t*\n",
			p->studentName,
			p->sessionCode,
			p->TutorCode,
			p->Location
		);

		p = p->pNext;

	}
	printf("*********************************************************************************\n");

	system("pause");
	system("cls");
}

void printTutorOnlyEnroll(struct tutor* head) {
	system("cls");
	struct enroll* p;
	char tutorName[MAXCHAR];
	strcpy(tutorName, findTutorName(head, curr_user));

	p = make_enroll_linklist()->pNext;

	printf("*********************************************************************************\n");
	printf("*\t\t\tWelcome to Apu Student Cafe System \t\t\t*\n");
	printf("*********************************************************************************\n");
	printf("*\tStudent Name\t*\tSession Code\t\t*\tTutor Code\t*\tLocation\t*\n");
	printf("*********************************************************************************\n");

	while (p)
	{
		if (strcmp(tutorName, trim(p->TutorCode))==0) {
			printf("*\t%s\t*\t%s\t*\t%s\t*\t%s\t*\n",
				p->studentName,
				p->sessionCode,
				p->TutorCode,
				p->Location
			);
		}

		p = p->pNext;

	}
	printf("*********************************************************************************\n");

	system("pause");
	system("cls");
}

void printStudentOnlyEnroll(struct student* head) {
	system("cls");
	struct enroll* p;
	char stuName[MAXCHAR];
	strcpy(stuName, trim(findStuName(head, curr_user)->fullName));

	p = make_enroll_linklist()->pNext;

	printf("*********************************************************************************\n");
	printf("*\t\t\tWelcome to Apu Student Cafe System \t\t\t*\n");
	printf("*********************************************************************************\n");
	printf("*\tStudent Name\t*\tSession Code\t\t*\tTutor Code\t*\tLocation\t*\n");
	printf("*********************************************************************************\n");

	while (p)
	{
		if (strcmp(stuName, trim(p->studentName)) == 0) {
			printf("*\t%s\t*\t%s\t*\t%s\t*\t%s\t*\n",
				p->studentName,
				p->sessionCode,
				p->TutorCode,
				p->Location
			);
		}

		p = p->pNext;

	}
	printf("*********************************************************************************\n");

	system("pause");
	system("cls");
}

#pragma endregion

#pragma region login
// not used
struct user* make_user_linklist()
{
	struct user* head;

	head = (struct user*)malloc(sizeof(struct user));
	head->pNext = NULL;

	FILE* fp;
	char path[] = "user_pwd.txt";
	fp = fopen(path, "r+");

	if (check_void_file(path) == 0) {
		printf("Can't access account detail...");
		return head;
	}

	struct user* p;
	p = head;
	char ch;
	char line[50];

	while (fgets(line, sizeof(line), fp) != NULL) {
		struct user* new_user_init;

		new_user_init = (struct user*)malloc(sizeof(struct user));

		fscanf(fp, "%d", new_user_init->role);
		ch = fgetc(fp);
		fscanf(fp, "%[^\n]%*c", new_user_init->userName);
		ch = fgetc(fp);
		fscanf(fp, "%[^\n]%*c", new_user_init->password);
		ch = fgetc(fp);
		new_user_init->pNext = NULL;
		p->pNext = new_user_init;
		p = p->pNext;
	}


	fclose(fp);
	return head;
}

int checkpwd(struct user *user)
{
	int status = 0;
	
	char rup[MAXCHAR];
	// concat 2geder
	itoa(user->role,rup,10);
	strcat(rup, " ");
	strcat(rup, user->userName);
	strcat(rup, " ");
	strcat(rup, user->password);

	char username_f[MAXCHAR];

	FILE* fp;
	fp = fopen("user_pwd.txt", "r+");
	while (feof(fp) == 0) {
		fgets(username_f, MAXCHAR, fp);
		username_f[strcspn(username_f, "\n")] = 0;
		if (strcmp(rup, username_f) == 0) {
			status = 1;
			break;
		}
	}
	fclose(fp);

	return status;
}

#pragma endregion


//declare function name
void Menu();
void TutorMenu();
void SubMenu();
int LoginMenu();
void CreateMenu();
void CreateTutorMenu();
void CreateSessionMenu();
void CreateEnrollMenu();
void CreateStudentEnrollMenu();
void DeleteMenu();