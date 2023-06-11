#include "Header.h"



int main() {
	char exit;
	int login;
	loop:
	system("cls");
		printf("*************************************************\n");
		printf("*\tWelcome to Apu Student Cafe System \t*\n");
		printf("*************************************************\n");
		printf("----------Press any key to login-------\n\n");
		printf("----------Press q to exit-------\n\n");

		exit = _getch();
		if (exit == 'q') return 0;
		while (1) {
			login = LoginMenu(); //1 admin 2 student 3 tutor
			switch (login) {
			case 1:
				goto admin_loop;
				break;
			case 2:
				goto student_loop;
				break;
			case 3:
				goto tutor_loop;
				break;
			default:
				printf("No this Role...\n\n");
				system("pause");  //暂停
				system("cls");    //清屏
				break;
			}
		}

	
	
	admin_loop:
		while (1)
	{
		system("cls");
		Menu();

		char ch = _getch();

		switch (ch)
		{
		case '1'://1.录入学生信息
			system("cls");

			SubMenu();
			char menu_sel = _getch();
			switch (menu_sel)
			{
			case '1':
				CreateMenu();
				break;
			case '2':
				CreateTutorMenu();
				break;
			case '3':
				CreateSessionMenu();
				break;
			case '4':
				CreateEnrollMenu();
				break;
			}
			break;

		case '2'://2.打印学生信息
			system("cls");

			SubMenu();
			char menu_sel2 = _getch();
			switch (menu_sel2)
			{
			case '1':
				printStudent();
				break;
			case '2':
				printTutor();
				break;
			case '3':
				printSession();
				break;
			case '4':
				printEnroll();
				break;
			}

			break;
		case '3':
			system("cls");

			SubMenu();
			char menu_sel3 = _getch();
			switch (menu_sel3)
			{
			case '1':
				DeleteMenu();
				break;
			case '2':
				DeleteTutorMenu();
				break;
			case '3':
				DeleteSessionMenu();
				break;
			case '4':
				DeleteEnrollMenu();
				break;
			default:
				printf("No this key...\n\n");
				system("pause");  //暂停
				system("cls");    //清屏
				break;
			}

			break;
		case '4':// update
			system("cls");

			SubMenu();
			char menu_sel4 = _getch();
			switch (menu_sel4)
			{
			case '1':
				UpdateMenu();
				break;
			case '2':
				UpdateTutorMenu();
				break;
			case '3':
				UpdateSessionMenu();
				break;
			case '4':
				UpdateEnrollMenu();
				break;
			}
			break;
		case '0'://0.退出系统
			goto loop;
			break;
		default:
			printf("No this key...\n\n");
			system("pause");  //暂停
			system("cls");    //清屏
			break;
		}

	}
	tutor_loop:
		while (1)
		{
			struct tutor* head;
			head = make_tutor_linklist();

			system("cls");
			TutorMenu();

			char ch = _getch();

			switch (ch)
			{
			case '1':
				
				printTutorOnlyEnroll(head,curr_user);
				break;
			
			case '0'://0.退出系统
				goto loop;
				break;
			default:
				printf("No this key...\n\n");
				system("pause");  //暂停
				system("cls");    //清屏
				break;
			}

		}
	student_loop:
		while (1)
		{
			struct student* head;
			head = make_linklist();

			system("cls");
			Menu();

			char ch = _getch();

			switch (ch)
			{
			case '1':
				CreateStudentEnrollMenu();
				break;

			case '2':
				printStudentOnlyEnroll(head, curr_user);
				break;
			case '3':
				DeleteOnlyStudentEnrollMenu();
				break;
			case '4':
				printf("You dont have this access...\n");
				system("pause");
				//UpdateStudentOnlyEnrollMenu();
				break;
			case '0'://0.退出系统
				goto loop;
				break;
			default:
				printf("No this key...\n\n");
				system("pause");  //暂停
				system("cls");    //清屏
				break;
			}

		}
	return 0;
}



void Menu() {
	printf("*************************************************\n");
	printf("*\tWelcome to Apu Student Cafe System \t*\n");
	printf("*************************************************\n");
	printf("*\t\t1.Register data\t\t\t*\n");
	printf("*\t\t2.Print data\t\t\t*\n");
	printf("*\t\t3.Delete data\t\t\t*\n");
	printf("*\t\t4.Update data\t\t\t*\n");
	printf("*\t\t0.Exit system\t\t\t*\n");
	printf("*************************************************\n");
};
void TutorMenu() {
	printf("*************************************************\n");
	printf("*\tWelcome to Apu Student Cafe System \t*\n");
	printf("*************************************************\n");
	printf("*\t\t1.Print data\t\t\t*\n");
	printf("*\t\t0.Exit system\t\t\t*\n");
	printf("*************************************************\n");
};
void SubMenu() {
	printf("*************************************************\n");
	printf("*\tPlease select a role \t\t\t*\n");
	printf("*************************************************\n");
	printf("*\t\t1.Student\t\t\t*\n");
	printf("*\t\t2.Tutor\t\t\t\t*\n");
	printf("*\t\t3.Session\t\t\t*\n");
	printf("*\t\t4.Enroll\t\t\t*\n");
	printf("*************************************************\n");
};

int LoginMenu() {
	strcpy(curr_user, "");
	int status = 0;
	struct user us = {0,"0","0"};
	system("cls");

	printf("*************************************************\n");
	printf("*\tWelcome to Apu Student Cafe System \t*\n");
	printf("*************************************************\n");

	printf("Please enter ur role: \n");
	printf("\t0.Admin\n");
	printf("\t1.Student\n");
	printf("\t2.Tutor\n");
	scanf("%d", &us.role);
	if (us.role > 2 || us.role < 0) {
		printf("Role Not Found\n");
		return status; 
	}

	printf("Please enter ur ID: ");
	scanf("%s", us.userName);
	
	if (checkuser(&us) == 1) {
		printf("User Exists\n");
	}
	else {
		printf("User Not Found\n");
		system("pause");
		return status;
	}
	
	printf("Please enter ur Password: ");
	scanf("%s", us.password);

	if (checkpwd(&us) == 1) {
		printf("\nLogin Successfully...\n");
		status = us.role+1;
		strcpy(curr_user, us.userName);
		system("pause");
 	}
	else 
	{
		printf("\nLogin Fail...\n");
		system("pause");
	}
	return status;
};

void CreateMenu() {
	struct student stu = { 0,"0","0","0"};
	system("cls");
	printf("*********************************************************************************\n");
	printf("*\t\t\tWelcome to Apu Student Cafe System \t\t\t*\n");
	printf("*********************************************************************************\n");
	printf("Please enter ur ID: ");
	scanf("%s", stu.userid);
	stu.userid[0] = toupper(stu.userid[0]);
	fflush(stdin);

	if (checkuser(&stu) != 1) {
		char temp;
		scanf("%c", &temp);
		printf("Please enter ur FullName: ");
		scanf("%[^\n]", stu.fullName);
		printf("Please enter ur gender(M/m or F/f): ");
		scanf("%s", stu.gender);

		switch (stu.gender[0])
		{
		case 'M':
		case 'm':
			printf("Male.");
			break;
		case 'F':
		case 'f':
			printf("Female.");
			break;
		default:
			printf("Unspecified Gender.\n");
			system("pause");
			return;
		}

		char password[MAXCHAR];
		strcpy(password, stu.userid);
		strcat(password, "_");
		strncat(password, stu.fullName, 7);

		printStudentNode(&stu);
		//createStudent(&stu);
		printf("\nStudent detail created...\n");
		system("pause");

	}
	else {
		printf("\nUser Exists\n");
		system("pause");

	}
}

void CreateTutorMenu() {
	struct tutor tt = { 0,"0","0","0" };
	system("cls");
	printf("*********************************************************************************\n");
	printf("*\t\t\tWelcome to Apu Student Cafe System \t\t\t*\n");
	printf("*********************************************************************************\n");
	printf("Please enter ur ID: ");
	scanf("%s", tt.tutorid);
	tt.tutorid[0] = toupper(tt.tutorid[0]);

	if (checkuser(&tt) != 1) {
		char temp;
		scanf("%c", &temp);
		printf("Please enter ur FullName: ");
		scanf("%[^\n]%*c", tt.fullName);
		printf("Please enter ur course: ");
		scanf("%[^\n]%*c", tt.courseName);

		if (checktutor(&tt) != 1) {
			char password[MAXCHAR];
			strcpy(password, tt.tutorid);
			strcat(password, "_");
			strncat(password, tt.fullName, 7);

			printTutorNode(&tt);
			//createTutor(&tt);
			printf("\nTutor detail created...\n");
			system("pause");
		}
		else {
			printf("\nSession Full\n");
			system("pause");
		}

	}
	else {
		printf("\nUser Exists\n");
		system("pause");

	}
}

void CreateSessionMenu() {
	struct user us = { 0 };
	struct session ss = { 0,"0","0","0" };
	char day[7][MAXCHAR] = { "Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday" };
	system("cls");
	printf("*********************************************************************************\n");
	printf("*\t\t\tWelcome to Apu Student Cafe System \t\t\t*\n");
	printf("*********************************************************************************\n");
	printf("Please enter session ID: ");
	scanf("%s", ss.sessionid);
	for (int i = 0; i < sizeof(ss.sessionid) / sizeof(ss.sessionid)[0]; i++) {
		ss.sessionid[i] = toupper(ss.sessionid[i]);
	}
	if (checksession(&ss) != 1) {
		char temp;
		scanf("%c", &temp);
		printf("Please enter the title: ");
		scanf("%[^\n]%*c", ss.title);
		printf("Please enter the day[1-7]: ");
		int index_day;
		scanf("%d", &index_day);
		if(&index_day>0 || &index_day<8)
			strcpy(ss.day, day[index_day]);
		else {
			printf("Input day invalid...\n");
			system("pause");
			return;
		}
		printf("Please enter the Start Time[00-23:00-59]: ");
		int hour, minute;
		scanf("%02d:%02d", &hour, &minute);
		if ((hour < 24 && hour >= 0) && (minute < 60 && hour >= 0)) {
			if (hour > 12) {
				sprintf(ss.startTime,"%02d:%02d pm", hour - 12, minute);

			}
			else if (hour == 12) {
				sprintf(ss.startTime, "12:%02d pm", minute);
			}
			else if (hour > 0) {
				sprintf(ss.startTime, "%02d:%02d am", hour, minute);
			}
			else {
				sprintf(ss.startTime, "12:%02d am", minute);
			}
			printf("%s\n", ss.startTime);
		}
		else {
			printf("Input time invalid...\n");
			system("pause");
			return;
		}
		printf("Please enter the location: ");
		scanf("%s", ss.Location);

		printf("Please enter the tutor code: ");

		scanf("%s", ss.TutorCode);
		strcpy(us.userName, ss.TutorCode);
		if (checkuser(&us) != 1) 
		{
			printf("\nTutorID Not Found...\n");
			system("pause");
			return;
		}
			
		if (checksession(&ss) != 1) {
			
			printSessionNode(&ss);
			//createSession(&ss);
			printf("\nSession detail created...\n");
			system("pause");
		}
		else
		{
			printf("\nTutor Full...\n");
			system("pause");
		}
	}
	else
	{
		printf("\nSession Exists...\n");
		system("pause");
	}
	
}

void CreateEnrollMenu() {
	struct student stu = { 0,"0","0"};
	struct enroll *en;
	struct session ss = { 0,"0","0","0" };
	system("cls");
	printf("*********************************************************************************\n");
	printf("*\t\t\tWelcome to Apu Student Cafe System \t\t\t*\n");
	printf("*********************************************************************************\n");
	printf("Please enter Student ID: ");
	scanf("%s", stu.userid);
	stu.userid[0] = toupper(stu.userid[0]);

	if (checkuser(&stu) == 1) {
		char temp;
		scanf("%c", &temp);
		printf("Please enter Session ID: ");
		scanf("%s", ss.sessionid);
		for (int i = 0; i < sizeof(ss.sessionid) / sizeof(ss.sessionid)[0]; i++) {
			ss.sessionid[i] = toupper(ss.sessionid[i]);
		}
		if (checksession(&ss) == 1) {

			en = assignEnroll(stu.userid, ss.sessionid);
			en->pNext = NULL;
			system("pause");

			printEnrollNode(en);
			//createEnroll(en);
			printf("\nEnroll detail created...\n");
			system("pause");
		}
		else {
			printf("\nSession Not Found...\n");
			system("pause");
		}
	}
	else {
		printf("\nStudent Not Found...\n");
		system("pause");
	}
}

void CreateStudentEnrollMenu() {
	struct enroll* en;
	struct session ss = { 0,"0","0","0" };
	system("cls");
	printf("*********************************************************************************\n");
	printf("*\t\t\tWelcome to Apu Student Cafe System \t\t\t*\n");
	printf("*********************************************************************************\n");
	printf("Ur Student ID: %s\n",curr_user);

	printf("Please enter Session ID: ");
	scanf("%s", ss.sessionid);
	for (int i = 0; i < sizeof(ss.sessionid) / sizeof(ss.sessionid)[0]; i++) {
		ss.sessionid[i] = toupper(ss.sessionid[i]);
	}
	if (checksession(&ss) == 1) {
		en = assignEnroll(curr_user, ss.sessionid);
		createEnroll(en);
		printf("\nEnroll detail created...\n");
		system("pause");
	}
	else {
		printf("\nSession Not Found...\n");
		system("pause");
	}

}

void DeleteMenu() {
	system("cls");

	printStudent();
	struct student* head = NULL;
	struct student* d_list = NULL;
	head = make_linklist();

	char student_name[MAXCHAR];
	printf("Please enter a student id: ");
	scanf("%s", student_name);

	d_list = findStuName(head, student_name);

	if (d_list != NULL) {
		head = deleteStudent(head, d_list);
		
		printStudentNode(head->pNext);
		//override_Student(head->pNext);
		printf("\nDelete Successfully...\n");
		system("pause");
	}
	else {
		printf("\nStudent ID Not Found...\n");
		system("pause");
	}
	

}

void DeleteTutorMenu() {
	system("cls");

	printTutor();
	struct tutor* head = NULL;
	struct tutor* d_list = NULL;
	head = make_tutor_linklist();

	char tutor_name[MAXCHAR];
	printf("Please enter a tutor id: ");
	scanf("%s", tutor_name);

	d_list = findTutorName(head, tutor_name);

	if (d_list != NULL) {
		head = deleteTutor(head, d_list);

		printTutorNode(head->pNext);
		//override_Student(head->pNext);
		printf("\nDelete Successfully...\n");
		system("pause");
	}
	else {
		printf("\nTutor ID Not Found...\n");
		system("pause");
	}


}

void DeleteSessionMenu() {
	system("cls");

	printSession();
	struct session* head = NULL;
	struct session* d_list = NULL;
	head = make_session_linklist();

	char session_name[MAXCHAR];
	printf("Please enter a session id: ");
	scanf("%s", session_name);

	d_list = findSessionName(head, session_name);

	if (d_list != NULL) {
		head = deleteSession(head, d_list);

		printSessionNode(head->pNext);
		//override_Student(head->pNext);
		printf("\nDelete Successfully...\n");
		system("pause");
	}
	else {
		printf("\nSession ID Not Found...\n");
		system("pause");
	}


}

void DeleteOnlyStudentEnrollMenu() {

	
	struct enroll* head = NULL;
	struct enroll* d_list = NULL;
	struct student* stu_head = NULL;
	head = make_enroll_linklist();
	stu_head = make_linklist();

	printStudentOnlyEnroll(stu_head);

	char enroll_name[MAXCHAR];
	printf("Please enter a session id: ");
	scanf("%s", enroll_name);

	d_list = findStudentOnlyEnrollName(head, stu_head, enroll_name);

	if (d_list != NULL) {
		head = deleteStudentOnlyEnroll(head, d_list,stu_head);
		printStudentOnlyEnrollNode(head->pNext, stu_head);

		//override_Student(head->pNext);
		printf("\nDelete Successfully...\n");
		system("pause");
	}
	else {
		printf("\nSession ID Not Found...\n");
		system("pause");
	}


}

void DeleteEnrollMenu() {
	system("cls");

	printEnroll();
	struct enroll* head = NULL;
	struct enroll* d_list = NULL;
	head = make_enroll_linklist();

	char enroll_name[MAXCHAR];
	printf("Please enter a session id: ");
	scanf("%s", enroll_name);

	d_list = findEnrollName(head, enroll_name);

	if (d_list != NULL) {
		head = deleteEnroll(head, d_list);

		printEnrollNode(head->pNext);
		//override_Student(head->pNext);
		printf("\nDelete Successfully...\n");
		system("pause");
	}
	else {
		printf("\nSession ID Not Found...\n");
		system("pause");
	}


}


void UpdateMenu() {
	system("cls");

	printStudent();
	struct student* head = NULL;
	struct student* up_list = NULL;

	head = make_linklist();
	char id[MAXCHAR];
	printf("Please enter a student id: ");
	scanf("%s", id);
	up_list = findStuName(head, id);

	if (up_list!=NULL) {
		system("cls");
		int modify_sel=0;
		
		printf("*************************************************\n");
		printf("*\tPlease select an item \t\t\t*\n");
		printf("*************************************************\n");
		printf("*\t\t1.Name\t\t\t\t*\n");
		printf("*\t\t2.Gender\t\t\t*\n");
		printf("*\t\t3.Password\t\t\t*\n");
		printf("*************************************************\n");
		scanf("%d", &modify_sel);
		if (modify_sel < 4 && modify_sel > 0) {
			char updateItem[MAXCHAR];
			char temp;
			scanf("%c", &temp);
			printf("Please enter update detail: ");
			scanf("%[^\n]", updateItem);
			
			head = modifyStu(head, up_list, modify_sel, updateItem);
			if (head != NULL) {
				printStudentNode(head->pNext);
				//override_Student(head->pNext);
				printf("\nUpdate Successfully...\n");
				system("pause");
			}
			else {
				printf("\nUpdate Fail...\n");
				system("pause");
			}
		}
		else {
			printf("Item Not Found...\n");
			system("pause");
		}
	}
	else {
		printf("User Not Found...\n");
		system("pause");
	}
	
}

void UpdateTutorMenu() {
	system("cls");

	printTutor();
	struct tutor* head = NULL;
	struct tutor* up_list = NULL;

	head = make_tutor_linklist();
	char id[MAXCHAR];
	printf("Please enter a tutor id: ");
	scanf("%s", id);
	up_list = findTutorName(head, id);

	if (up_list != NULL) {
		system("cls");
		int modify_sel = 0;

		printf("*************************************************\n");
		printf("*\tPlease select an item \t\t\t*\n");
		printf("*************************************************\n");
		printf("*\t\t1.Name\t\t\t\t*\n");
		printf("*\t\t2.Course\t\t\t*\n");
		printf("*\t\t3.Password\t\t\t*\n");
		printf("*************************************************\n");
		scanf("%d", &modify_sel);
		if (modify_sel < 4 && modify_sel > 0) {
			char updateItem[MAXCHAR];
			char temp;
			scanf("%c", &temp);
			printf("Please enter update detail: ");
			scanf("%[^\n]", updateItem);

			head = modifyTutor(head, up_list, modify_sel, updateItem);
			if (head != NULL) {
				printTutorNode(head->pNext);
				//override_Student(head->pNext);
				printf("\nUpdate Successfully...\n");
				system("pause");
			}
			else {
				printf("\nUpdate Fail...\n");
				system("pause");
			}
		}
		else {
			printf("Item Not Found...\n");
			system("pause");
		}
	}
	else {
		printf("User Not Found...\n");
		system("pause");
	}

}

void UpdateSessionMenu() {
	system("cls");

	printSession();
	struct session* head = NULL;
	struct session* up_list = NULL;

	head = make_session_linklist();
	char id[MAXCHAR];
	printf("Please enter a session id: ");
	scanf("%s", id);
	up_list = findSessionName(head, id);

	if (up_list != NULL) {
		system("cls");
		int modify_sel = 0;

		printf("*************************************************\n");
		printf("*\tPlease select an item \t\t\t*\n");
		printf("*************************************************\n");
		printf("*\t\t1.Title\t\t\t\t*\n");
		printf("*\t\t2.Day\t\t\t\t*\n");
		printf("*\t\t3.StartTime\t\t\t*\n");
		printf("*\t\t4.Location\t\t\t*\n");
		printf("*\t\t5.Tutor Code\t\t\t*\n");
		printf("*************************************************\n");
		scanf("%d", &modify_sel);
		if (modify_sel < 4 && modify_sel > 0) {
			char updateItem[MAXCHAR];
			char temp;
			scanf("%c", &temp);
			printf("Please enter update detail: ");
			scanf("%[^\n]", updateItem);

			head = modifySession(head, up_list, modify_sel, updateItem);
			if (head != NULL) {
				printSessionNode(head->pNext);
				//override_Student(head->pNext);
				printf("\nUpdate Successfully...\n");
				system("pause");
			}
			else {
				printf("\nUpdate Fail...\n");
				system("pause");
			}
		}
		else {
			printf("Item Not Found...\n");
			system("pause");
		}
	}
	else {
		printf("User Not Found...\n");
		system("pause");
	}

}

void UpdateEnrollMenu() {
	system("cls");

	printEnroll();
	struct enroll* head = NULL;
	struct enroll* up_list = NULL;

	head = make_enroll_linklist();
	char id[MAXCHAR];
	printf("Please enter a session id: ");
	scanf("%s", id);
	up_list = findEnrollName(head, id);

	if (up_list != NULL) {
		system("cls");
		int modify_sel = 0;

		printf("*************************************************\n");
		printf("*\tPlease select an item \t\t\t*\n");
		printf("*************************************************\n");
		printf("*\t\t1.Student Name\t\t\t*\n");
		printf("*\t\t2.Tutor Code\t\t\t*\n");
		printf("*\t\t3.Location\t\t\t*\n");
		printf("*************************************************\n");
		scanf("%d", &modify_sel);
		if (modify_sel < 4 && modify_sel > 0) {
			char updateItem[MAXCHAR];
			char temp;
			scanf("%c", &temp);
			printf("Please enter update detail: ");
			scanf("%[^\n]", updateItem);

			head = modifyEnroll(head, up_list, modify_sel, updateItem);
			if (head != NULL) {
				printEnrollNode(head->pNext);
				//override_Student(head->pNext);
				printf("\nUpdate Successfully...\n");
				system("pause");
			}
			else {
				printf("\nUpdate Fail...\n");
				system("pause");
			}
		}
		else {
			printf("Item Not Found...\n");
			system("pause");
		}
	}
	else {
		printf("User Not Found...\n");
		system("pause");
	}

}

void UpdateStudentOnlyEnrollMenu() {
	system("cls");

	struct enroll* head = NULL;
	struct enroll* up_list = NULL;
	struct student* stu_head = NULL;
	stu_head = make_linklist();
	head = make_enroll_linklist();
	printStudentOnlyEnroll(stu_head);
	char id[MAXCHAR];
	printf("Please enter a session id: ");
	scanf("%s", id);
	up_list = findStudentOnlyEnrollName(head,stu_head ,id);

	if (up_list != NULL) {
		system("cls");
		int modify_sel = 0;

		printf("*************************************************\n");
		printf("*\tPlease select an item \t\t\t*\n");
		printf("*************************************************\n");
		printf("*\t\t2.Tutor Code\t\t\t*\n");
		printf("*\t\t3.Location\t\t\t*\n");
		printf("*************************************************\n");
		scanf("%d", &modify_sel);
		if (modify_sel < 4 && modify_sel > 1) {
			char updateItem[MAXCHAR];
			char temp;
			scanf("%c", &temp);
			printf("Please enter update detail: ");
			scanf("%[^\n]", updateItem);

			head = modifyEnroll(head, up_list, modify_sel, updateItem);
			if (head != NULL) {
				printStudentOnlyEnrollNode(head->pNext, stu_head);
				//override_Student(head->pNext);
				printf("\nUpdate Successfully...\n");
				system("pause");
			}
			else {
				printf("\nUpdate Fail...\n");
				system("pause");
			}
		}
		else {
			printf("Item Not Found...\n");
			system("pause");
		}
	}
	else {
		printf("User Not Found...\n");
		system("pause");
	}

}
// scanf no \n