#define _CRT_SECURE_NO_WARNINGS
#include"stdio.h"
#include"stdlib.h"
#include"string.h"
#include <conio.h> 
#include "windows.h"
#include<iostream>
using namespace std;
#include <iomanip>
using std::setw;
#define MAX 1000//最大学生人数
string HelloKey;

//学生结构体
typedef struct Student
{
	int  StuId;//学生学号
	char StuName[20];//学生姓名
	char StuGender[10];//学生性别
	int  StuAge;//学生年龄
	char StuClass[40];//学生所属班级
	int StuRoom;//学生房间号
}Student;

//查找指针
typedef struct Points
{
	int a;
	Points* points;
}Points;

char Revise[10] = "修改";
char Search[10] = "查询";
char Id[] = "学号";
char Name[] = "姓名";
char Gender[] = "性别";
char Age[] = "年龄";
char Class[] = "班级";
char Room[] = "宿舍";

//返回主菜单
void Pause()
{
	int i;
	cout << "\n按回车键返回主菜单!" << endl;
	_getch();
}

//输出
void Print(Student stu[], int point)
{
	cout << "\n\n学号:  " << stu[point].StuId << "姓名:  " << stu[point].StuName << "性别:  " << stu[point].StuGender
		<< "年龄:  " << stu[point].StuAge << "班级:  " << stu[point].StuClass << "宿舍号:  " << stu[point].StuRoom << endl;
}

//字体
void printRedText(const std::string& text) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// 设置文本颜色为红色
	WORD color = (FOREGROUND_RED | FOREGROUND_INTENSITY);
	SetConsoleTextAttribute(hConsole, color);
	std::cout << text;
	// 重置文本颜色为默认值
	SetConsoleTextAttribute(hConsole, 11);
}

//查找失败
void PrintNotFound()
{
	printRedText("查找失败！找不到该数据\n");
}

//输出查找结果
void PrintSearch(Student stu[], int i)
{
	cout << std::left << "      " << setw(12) << stu[i].StuId << setw(13) << stu[i].StuName << setw(12) << stu[i].StuGender <<
		setw(10) << stu[i].StuAge << setw(15) << stu[i].StuClass << setw(10) << stu[i].StuRoom << endl;
}

//输出表头
void PrintHead()
{
	cout << "*******************************************************************************" << endl;
	cout << "      学号：      姓名：      性别：      年龄：      班级：      宿舍号：" << endl;
	cout << "*******************************************************************************" << endl;
}

//继续操作或返回主菜单
int a = 1;//默认继续
//继续操作请按1,返回主菜单请按0
void SelectOperate()
{
button:

	cout << "继续操作请按1,返回主菜单请按0" << endl;
	cin >> a;
	if (!(a == 1 || a == 0))
	{
		printRedText("输入错误！请重新输入\n");
		//	_getch();
		goto button;
	}
}

// 读取文件，返回总个数
int ReadFile(Student stu[])
{
	FILE* fp;
	int point = 0;
	if ((fp = fopen("Student.txt", "r")) == NULL)
	{
		printRedText("\n学生宿舍文件不存在！请创建\n");
		return 0;
	}

	while (fscanf(fp, "%d %19s %9s %d %39s %d",
		&stu[point].StuId,
		stu[point].StuName,
		stu[point].StuGender,
		&stu[point].StuAge,
		stu[point].StuClass,
		&stu[point].StuRoom) == 6 && !feof(fp))
	{
		point++;
	}

	fclose(fp);
	return point;
}

// 存储数据到文件中
void SaveFile(Student stu[], int sum)
{
	FILE* fp;
	int i;

	if ((fp = fopen("Temp.txt", "w")) == NULL)
	{
		printRedText("写文件错误!\n");
		return;
	}

	for (i = 0; i < sum; i++)
	{
		fprintf(fp, "%d %19s %9s %d %39s %d\n",
			stu[i].StuId,
			stu[i].StuName,
			stu[i].StuGender,
			stu[i].StuAge,
			stu[i].StuClass,
			stu[i].StuRoom);
	}

	if (fclose(fp) != 0) { // 只需保留一次fclose，并在此处检查是否成功关闭文件
		printRedText("关闭文件错误!\n");
		return;
	}

	remove("Student.txt");
	rename("Temp.txt", "Student.txt");
}

//创建学生信息，返回的是总数
int InPut(Student stu[], int sum)
{
	int x;
	for (; sum < MAX; sum++)
	{
		int  Id;//学生学号
		char Name[20];//学生姓名
		char Gender[10];//学生性别
		int  Age;//学生年龄
		char Class[40];//学生所属班级
		int Room;//学生房间号
		system("cls");//清屏
		cout << "\t\t\t" << "********************************************" << endl;
		cout << "\t\t\t" << "*                                          *" << endl;
		cout << "\t\t\t" << "*             创建学生宿舍信息             *" << endl;
		cout << "\t\t\t" << "*                                          *" << endl;
		cout << "\t\t\t" << "********************************************" << endl;
		cout << endl << endl;
		cout << "           请录入第" << sum + 1 << "学生信息  (最多" << MAX << "个)" << endl;
		cout << "请输入学生的学号:";
		cin >> Id;
		int ee = 0;
		bool Isxh = false;
		for (ee = 0; ee < sum; ee++)
		{
			if (Id == stu[ee].StuId)
			{
				cout << "学生学号[" << Id << "]重复！请重新输入" << endl;
				Isxh = true;
			}
		}
		if (Isxh == true)
		{
			Sleep(2000);
			sum = sum - 1;
			continue;
		}
		cout << "请输入学生的姓名:";
		cin >> Name;
		cout << "请输入学生的性别:";
		cin >> Gender;
		if (strcmp("男", Gender) != 0 && strcmp("女", Gender) != 0)
		{
			printf("请输入正确的性别！\n");
			Sleep(2000);
			sum = sum - 1;
			continue;
		}
		cout << "请输入学生的年龄:";
		cin >> Age;
		cout << "请输入学生的班级:";
		cin >> Class;
		cout << "请输入学生的宿舍号:";
		cin >> Room;
		bool Isyes = false;
		int ff = 0;
		// 只需一个循环即可完成性别判断，无需区分Ishave的值
		for (ff = 0; ff < sum; ff++)
		{
			if (stu[ff].StuRoom == Room)
			{
				if (strcmp(stu[ff].StuGender, Gender) != 0)
				{
					cout << "男生与女士不能分配在一起" << endl;
					Isyes = true;
					break;
				}
			}
		}
		if (Isyes == true)
		{
			Sleep(2000);
			sum = sum - 1;
			continue;
		}
		stu[sum].StuId = Id;
		strcpy(stu[sum].StuName, Name);
		strcpy(stu[sum].StuGender, Gender);
		stu[sum].StuAge = Age;
		strcpy(stu[sum].StuClass, Class);
		stu[sum].StuRoom = Room;

		//选择操作
		SelectOperate();
		if (a == 0)
		{
			return sum + 1;
		}
	}
	return sum + 1;
}

//打印学生信息
void OutPut(Student stu[], int sum)
{
	int i;
	system("cls");
	cout << "\t\t\t" << "********************************************" << endl;
	cout << "\t\t\t" << "*                                          *" << endl;
	cout << "\t\t\t" << "*             打印学生宿舍信息             *" << endl;
	cout << "\t\t\t" << "*                                          *" << endl;
	cout << "\t\t\t" << "********************************************" << endl;
	PrintHead();
	for (i = 0; i < sum; i++)
	{
		PrintSearch(stu, i);
	}
	Pause();

}

//排序
//复制Student,排好的装在一个新的students数组里 ，不要存到文件中
void CopyStu(Student stu0[], Student stu[], int sum)
{
	int i;
	for (i = 0; i < sum; i++)
	{
		stu[i].StuId = stu0[i].StuId;
		strcpy(stu[i].StuName, stu0[i].StuName);
		strcpy(stu[i].StuGender, stu0[i].StuGender);
		stu[i].StuAge = stu0[i].StuAge;
		strcpy(stu[i].StuClass, stu0[i].StuClass);
		stu[i].StuRoom = stu0[i].StuRoom;
	}
}

//交换数据元素
void ExchangeData(Student* stu1, Student* stu2)
{
	stu1->StuId = stu2->StuId;
	stu1->StuRoom = stu2->StuRoom;
	stu1->StuAge = stu2->StuAge;
	strcpy(stu1->StuName, stu2->StuName);
	strcpy(stu1->StuGender, stu2->StuGender);
	strcpy(stu1->StuClass, stu2->StuClass);
}

//排序菜单
int SelectSort()
{
	int ch;
	cout << "\t\t\t" << "********************************************" << endl;
	cout << "\t\t\t" << "*           请您选择条件进行排序           *" << endl;
	cout << "\t\t\t" << "*                1. 学号                   *" << endl;
	cout << "\t\t\t" << "*                2. 班级                   *" << endl;
	cout << "\t\t\t" << "*                3. 宿舍号                 *" << endl;
	cout << "\t\t\t" << "*                4. 姓名                   *" << endl;
	cout << "\t\t\t" << "*                0. 返回主菜单             *" << endl;
	cout << "\t\t\t" << "********************************************" << endl;
	cin >> ch;
	return ch;
}

//根据宿舍号从小到大排序（冒泡）
void Sort_Room(Student stu0[], int sum, Student stup[])
{
	Student stu1;//交换中间值
	int i, j;
	CopyStu(stu0, stup, sum);
	for (i = 0; i < sum - 1; i++)
	{
		for (j = 0; j < sum - 1 - i; j++)
		{
			if (stup[j].StuRoom > stup[j + 1].StuRoom)
			{
				ExchangeData(&stu1, &stup[j]);
				ExchangeData(&stup[j], &stup[j + 1]);
				ExchangeData(&stup[j + 1], &stu1);
			}
		}
	}
}

//根据班级从小到大排序（选择）
void Sort_Class(Student stu0[], int sum, Student stup[])
{
	Student stu1;
	int i, j, k = 0;
	CopyStu(stu0, stup, sum);
	for (i = 0; i < sum - 1; i++)
	{
		k = i;
		for (j = i + 1; j < sum; j++)
		{
			if (strcmp(stup[k].StuClass, stup[j].StuClass) > 0)
			{
				k = j;
			}
		}
		if (i != k)
		{
			ExchangeData(&stu1, &stup[i]);
			ExchangeData(&stup[i], &stup[k]);
			ExchangeData(&stup[k], &stu1);
		}
	}
}

//根据姓名从大到小排序（折半插入排序）
//因为这里是从stu[1]开始操作的,所以得再创个中间变量
void Sort_Name(Student stu0[], int sum, Student stup[])
{
	Student stu1;//中间变量
	Student stu[1000];
	int i, j, low, high, mid;
	for (i = 0; i < sum; i++) {
		stu[i + 1].StuId = stu0[i].StuId;
		strcpy(stu[i + 1].StuName, stu0[i].StuName);
		strcpy(stu[i + 1].StuGender, stu0[i].StuGender);
		stu[i + 1].StuAge = stu0[i].StuAge;
		strcpy(stu[i + 1].StuClass, stu0[i].StuClass);
		stu[i + 1].StuRoom = stu0[i].StuRoom;
	}

	for (i = 2; i < sum + 1; i++) {
		ExchangeData(&stu1, &stu[i]);    //保存待插入元素到stu1
		low = 1; high = i - 1;
		while (low <= high)
		{
			mid = (low + high) / 2;
			if (strcmp(stu1.StuName, stu[mid].StuName) > 0)
				low = mid + 1;
			else
				high = mid - 1;
		}

		for (j = i - 1; j >= high + 1; j--)
			ExchangeData(&stu[j + 1], &stu[j]);//后移元素，留出插入空位 
		ExchangeData(&stu[high + 1], &stu1);
	}

	for (i = 0; i < sum; i++) {
		stup[i].StuId = stu[i + 1].StuId;
		strcpy(stup[i].StuName, stu[i + 1].StuName);
		strcpy(stup[i].StuGender, stu[i + 1].StuGender);
		stup[i].StuAge = stu[i + 1].StuAge;
		strcpy(stup[i].StuClass, stu[i + 1].StuClass);
		stup[i].StuRoom = stu[i + 1].StuRoom;
	}

}

//根据学号从小到大排序（插入希尔排序）
void ShellInsert(Student stup[], int sum, int dk)
{
	int i, j, k;
	Student stu1;//中间变量
	for (k = 0; k < dk; k++)
		for (i = dk + k; i < sum; i = i + dk)
			if (stup[i].StuId < stup[i - dk].StuId)
			{
				ExchangeData(&stu1, &stup[i]);
				for (j = i - dk; j >= 0 && stu1.StuId < stup[j].StuId; j = j - dk)//记录向后移    			
					ExchangeData(&stup[j + dk], &stup[j]);
				ExchangeData(&stup[j + dk], &stu1);
			}
}
void Sort_Id(Student stu[], int sum, Student stup[])
{
	int i, x;
	CopyStu(stu, stup, sum);
	int dlta[5] = { 5,4,3,2,1 };
	for (x = 0; x < 5; x++)
		ShellInsert(stup, sum, dlta[x]);
}

//排序主函数
void SortStudent(Student stu[], int sum)
{
	Student stup[1000];//把排好序的放在这里
	int ch, x, i;
	do {
		system("cls");//清屏
		cout << "\t\t\t" << "********************************************" << endl;
		cout << "\t\t\t" << "*                                          *" << endl;
		cout << "\t\t\t" << "*             学生宿舍信息排序             *" << endl;
		cout << "\t\t\t" << "*                                          *" << endl;
		cout << "\t\t\t" << "********************************************" << endl;
	select:
		ch = SelectSort();//排序菜单

		system("cls");
		cout << "\t\t\t" << "********************************************" << endl;
		cout << "\t\t\t" << "*                                          *" << endl;
		cout << "\t\t\t" << "*             学生宿舍信息排序             *" << endl;
		cout << "\t\t\t" << "*                                          *" << endl;
		cout << "\t\t\t" << "********************************************" << endl;

		switch (ch)
		{
		case 1:Sort_Id(stu, sum, stup); break;//按学号排序
		case 2:Sort_Class(stu, sum, stup); break;//按班级排序
		case 3:Sort_Room(stu, sum, stup); break;//按宿舍排序
		case 4:Sort_Name(stu, sum, stup); break;//按姓名排序
		case 0:return;
		default:printRedText("输入错误！请重新输入\n"); goto select;
		}
		//排序后打印输出
		PrintHead();
		for (i = 0; i < sum; i++)
		{
			PrintSearch(stup, i);
		}
		if (ch == 1 || ch == 2 || ch == 3 || ch == 4)
		{
			cout << endl << endl;
		button:
			cout << "继续排序请按1,返回主菜单请按0 " << endl;
			cin >> x;
			if (x == 1)
				x = 1;
			else if (x == 0)
				continue;
			else
			{
				printRedText("输入错误！请重新输入\n");
				goto button;
			}
		}
		else if (ch == 0)
			x = 0;
		else
		{
			printRedText("输入错误！请重新输入\n");
			goto select;
		}

	} while (x == 1);//x==1循环，x==0跳回主菜单
}

//查询或修改的选择菜单
int SelectChoice(char condition[20])
{
	int choice;
	cout << "\t\t\t" << "**************************************" << endl;
	cout << "\t\t\t" << "*        请您选择条件进行" << condition << "        *" << endl;
	cout << "\t\t\t" << "*             1. 学号                *" << endl;
	cout << "\t\t\t" << "*             2. 姓名                *" << endl;
	cout << "\t\t\t" << "*             3. 性别                *" << endl;
	cout << "\t\t\t" << "*             4. 年龄                *" << endl;
	cout << "\t\t\t" << "*             5. 班级                *" << endl;
	cout << "\t\t\t" << "*             6. 宿舍号              *" << endl;
	cout << "\t\t\t" << "*             0. 返回主菜单          *" << endl;
	cout << "\t\t\t" << "**************************************" << endl;
	cin >> choice;
	return choice;
}

Points* ConnectPoint(Points* r, Points* p, int i) {
	p = new Points;
	p->a = i;
	r->points = p;
	r = p;
	return r;
}

//choice为条件选择，condition为条件（学号，姓名，性别，年龄，班级，宿舍号）
Points* FindPoint(Student stu[], int sum, int choice, char condition[])
{
	int i, j = 0; Points* p, * q, * r; q = new Points; p = new Points; r = q;
	int StuId, StuAge, StuRoom; char StuClass[20], StuGender[5], StuName[20];
	cout << "请输入您要查找的学生的" << condition << "：";
	switch (choice)
	{
	case 1:
		cin >> StuId;
		for (i = 0; i < sum; i++)
		{
			if (StuId == stu[i].StuId)
			{
				r = ConnectPoint(r, p, i);
			}
		}
		break;

	case 2:
		cin >> StuName;
		for (i = 0; i < sum; i++)
		{
			if (strcmp(StuName, stu[i].StuName) == 0)
			{
				r = ConnectPoint(r, p, i);
			}
		}
		break;

	case 3:
		cin >> StuGender;
		for (i = 0; i < sum; i++)
		{
			if (strcmp(StuGender, stu[i].StuGender) == 0)
			{
				r = ConnectPoint(r, p, i);
			}
		}
		break;
	case 4:
		cin >> StuAge;
		for (i = 0; i < sum; i++)
		{
			if (StuAge == stu[i].StuAge)
			{
				r = ConnectPoint(r, p, i);
			}
		}
		break;
	case 5:
		cin >> StuClass;
		for (i = 0; i < sum; i++)
		{
			if (strcmp(StuClass, stu[i].StuClass) == 0)
			{
				r = ConnectPoint(r, p, i);
			}
		}
		break;
	case 6:
		cin >> StuRoom;
		for (i = 0; i < sum; i++)
		{
			if (StuRoom == stu[i].StuRoom)
			{
				r = ConnectPoint(r, p, i);
			}
		}
		break;
	}
	r->points = NULL;
	return q;
}

//查询学生信息
void Inquire(Student stu[], int sum)
{
	int choice;
	Points* p;
	do {
		system("cls");//清屏
		cout << "\t\t\t" << "********************************************" << endl;
		cout << "\t\t\t" << "*                                          *" << endl;
		cout << "\t\t\t" << "*             查询学生宿舍信息             *" << endl;
		cout << "\t\t\t" << "*                                          *" << endl;
		cout << "\t\t\t" << "********************************************" << endl;
	button:
		choice = SelectChoice(Search);
		system("cls");//清屏
		cout << "\t\t\t" << "********************************************" << endl;
		cout << "\t\t\t" << "*                                          *" << endl;
		cout << "\t\t\t" << "*              查询学生宿舍信息            *" << endl;
		cout << "\t\t\t" << "*                                          *" << endl;
		cout << "\t\t\t" << "********************************************" << endl;
		switch (choice)
		{
		case 1: p = FindPoint(stu, sum, choice, Id); break;
		case 2: p = FindPoint(stu, sum, choice, Name); break;
		case 3: p = FindPoint(stu, sum, choice, Gender); break;
		case 4: p = FindPoint(stu, sum, choice, Age); break;
		case 5: p = FindPoint(stu, sum, choice, Class); break;
		case 6: p = FindPoint(stu, sum, choice, Room); break;
		case 0: return;
		default:
			printRedText("输入错误！请输入正确的指令\n"); goto button;//查询循环
		}
		if (p->points != NULL)
		{
			p = p->points;
			PrintHead();
			while (p != NULL)
			{
				PrintSearch(stu, p->a);
				p = p->points;
			}
		}
		else
			PrintNotFound();
		SelectOperate();//继续操作或返回主菜单
	} while (a);//默认a==1循环，选择a==0,则返回主菜单
}

//二分查找
#include <vector>

Points* FindPoint2(Student stu[], int sum, int choice, char condition[])
{
	int i, j = 0;
	Points* p, * q, * r;
	q = new Points;
	p = new Points;
	r = q;
	int StuId, StuRoom;
	char StuName[20];
	cout << "请输入您要查找的学生的" << condition << "：";
	switch (choice)
	{
	case 1: cin >> StuId; break;
	case 2: cin >> StuName; break;
	case 3: cin >> StuRoom; break;
	}

	std::vector<int> matched_indices;

	if (choice == 3) // 只有查询寝室号时才进行查找
	{
		for (i = 0; i < sum; ++i)
		{
			if (stu[i].StuRoom == StuRoom)
			{
				matched_indices.push_back(i);
			}
		}
	}
	else // 其他条件直接遍历查找
	{
		for (i = 0; i < sum; ++i)
		{
			switch (choice)
			{
			case 1:
				if (StuId == stu[i].StuId)
					matched_indices.push_back(i);
				break;
			case 2:
				if (strcmp(StuName, stu[i].StuName) == 0)
					matched_indices.push_back(i);
				break;
			}
		}
	}

	// 将匹配到的学生索引添加到链表中
	for (int index : matched_indices)
	{
		r = ConnectPoint(r, p, index);
	}

	r->points = NULL;
	return q;
}

//二分法查询学生信息
void Inquire2(Student stu[], int sum)
{
	Student stup1[1000];//引用，把排好序的放在这里，不跟原来的混淆 
	Student stup2[1000];//引用，把排好序的放在这里，不跟原来的混淆 
	Student stup3[1000];//引用，把排好序的放在这里，不跟原来的混淆 
	//先排序再二分
	Sort_Id(stu, sum, stup1);
	Sort_Name(stu, sum, stup2);
	Sort_Room(stu, sum, stup3);
	int choice;
	Points* p; p = new Points;
	do
	{
		system("cls");//清屏
		cout << "\t\t\t" << "********************************************" << endl;
		cout << "\t\t\t" << "*                                          *" << endl;
		cout << "\t\t\t" << "*             查询学生宿舍信息             *" << endl;
		cout << "\t\t\t" << "*                                          *" << endl;
		cout << "\t\t\t" << "********************************************" << endl;
	botton:
		cout << "\t\t\t" << "********************************************" << endl;
		cout << "\t\t\t" << "*           请您选择条件进行查询           *" << endl;
		cout << "\t\t\t" << "*                1. 学号                   *" << endl;
		cout << "\t\t\t" << "*                2. 姓名                   *" << endl;
		cout << "\t\t\t" << "*                3. 宿舍号                 *" << endl;
		cout << "\t\t\t" << "*                0. 返回主菜单             *" << endl;
		cout << "\t\t\t" << "********************************************" << endl;
		cin >> choice;
		system("cls");//清屏
		cout << "\t\t\t" << "********************************************" << endl;
		cout << "\t\t\t" << "*                                          *" << endl;
		cout << "\t\t\t" << "*             查询学生宿舍信息             *" << endl;
		cout << "\t\t\t" << "*                                          *" << endl;
		cout << "\t\t\t" << "********************************************" << endl;
		switch (choice)
		{
		case 1:p = FindPoint2(stup1, sum, choice, Id); break;//二分法查询(学号) 
		case 2:p = FindPoint2(stup2, sum, choice, Name); break;//二分法查询(姓名)
		case 3:p = FindPoint2(stup3, sum, choice, Room); break;//二分法查询(房间号)
		case 0:return;
		default:printRedText("输入错误!请重新输入\n"); goto botton;//循环
		}
		if (p->points != NULL)
		{
			p = p->points;
			PrintHead();
			while (p != NULL)
			{
				if (choice == 1) {
					PrintSearch(stup1, p->a);
					p = p->points;
				}
				if (choice == 2) {
					PrintSearch(stup2, p->a);
					p = p->points;
				}
				if (choice == 3) {
					PrintSearch(stup3, p->a);
					p = p->points;
				}
			}
		}
		else
			PrintNotFound();
		//选择继续查询还是退回主菜单
		SelectOperate();
	} while (a);
}

//选择查找方法
void SelectInquire(Student stu[], int sum)
{
	int ch;
	system("cls");
button:

	cout << "\t\t\t" << "********************************************" << endl;
	cout << "\t\t\t" << "*           请您选择方法进行查询           *" << endl;
	cout << "\t\t\t" << "*                1. 顺序查找               *" << endl;
	cout << "\t\t\t" << "*                2. 二分查找               *" << endl;
	cout << "\t\t\t" << "*                0. 返回主菜单             *" << endl;
	cout << "\t\t\t" << "********************************************" << endl;
	cin >> ch;
	switch (ch)
	{
	case 1: Inquire(stu, sum); break;//顺序查找
	case 2: Inquire2(stu, sum); break;//二分查找
	case 0: return;
	default:printRedText("输入错误!请重新输入\n"); goto button;//循环
	}
}

//修改和删除判断输入学生个数 
int OperateNum(int sum)
{
	int n;
	cout << "请输入您要操作的学生个数" << endl;
	cin >> n;
	if (n > sum)
	{
		printRedText("操作失败!输入学生个数超过学生总量\n");
		SelectOperate();
		return 0;
	}
	else if (n <= 0)
	{
		printRedText("操作失败!输入学生个数不能小于或对于零\n");
		SelectOperate();
		return 0;
	}
	return n;
}

//根据学号删除学生信息
int Delete(Student stu[], int sum)
{
	a = 1;
	system("cls");//清屏
	int i, j = 0, n = 0, flag = 1;
	Points* p;
	cout << "\t\t\t" << "********************************************" << endl;
	cout << "\t\t\t" << "*                                          *" << endl;
	cout << "\t\t\t" << "*             删除学生宿舍信息             *" << endl;
	cout << "\t\t\t" << "*                                          *" << endl;
	cout << "\t\t\t" << "********************************************" << endl;
	while (n == 0)
	{
		n = OperateNum(sum);//输入正确返回个数，输入不正确返回0（n=0）,SelectOperate()里面选择a的取值（继续或返回主菜单）
		if (a == 0)
			return sum;
	}
	do {
		if (flag) {
			system("cls");
			Points* p;
			cout << "\t\t\t" << "********************************************" << endl;
			cout << "\t\t\t" << "*                                          *" << endl;
			cout << "\t\t\t" << "*             删除学生宿舍信息             *" << endl;
			cout << "\t\t\t" << "*                                          *" << endl;
			cout << "\t\t\t" << "********************************************" << endl;
		}
		//查一个删一个
		p = FindPoint(stu, sum, 1, Id);
		p = p->points;
		if (p != NULL)
		{
			i = p->a;
			//把后面的一次覆盖掉前面一个 
			for (; i < sum - 1; i++)
			{
				ExchangeData(&stu[i], &stu[i + 1]);
			}
			cout << "该条信息删除成功！" << endl;
			flag = 0;
			j++;
			if (j == n)
			{
				cout << "完成全部删除操作！" << endl;
				SelectOperate();//继续操作请按1,返回主菜单请按0
				if (a == 0)
					return sum - n;//剩余学生信息个数
				else
					Delete(stu, sum - n);
			}
		}
		else
		{
			printRedText("输入的学号不存在！\n");
			SelectOperate();
			if (a == 0)
				return sum - j;
		}
	} while (a == 1 && j < n);
}

//根据学号修改学生信息
void Change(Student stu[], int sum)
{
	int choice;
	Points* p;
	do
	{
		system("cls");
		cout << "\t\t\t" << "********************************************" << endl;
		cout << "\t\t\t" << "*                                          *" << endl;
		cout << "\t\t\t" << "*             修改学生宿舍信息             *" << endl;
		cout << "\t\t\t" << "*                                          *" << endl;
		cout << "\t\t\t" << "********************************************" << endl;
		p = FindPoint(stu, sum, 1, Id);//先查找再删除
		p = p->points;
		if (p != NULL)
		{
			system("cls");
			cout << "\t\t\t" << "********************************************" << endl;
			cout << "\t\t\t" << "*                                          *" << endl;
			cout << "\t\t\t" << "*             修改学生宿舍信息             *" << endl;
			cout << "\t\t\t" << "*                                          *" << endl;
			cout << "\t\t\t" << "********************************************" << endl;
			int i = p->a;
			Print(stu, i);
		button:
			int id;
			int room;
			char gender[10];
			int ee = 0, ff = 0, fe = 0;
			choice = SelectChoice(Revise);
			switch (choice)
			{
			case 1: cout << "请输入您要修改的新学号:";
				cin >> id;

				for (ee = 0; ee < sum; ee++)
				{
					if (id == stu[ee].StuId)
					{
						cout << "学生学号[" << id << "]重复！请重新输入" << endl;
						Sleep(2000);
						goto button;
					}
				}
				stu[i].StuId = id;
				break;
			case 2: cout << "请输入您要修改的新姓名:";
				cin >> stu[i].StuName;
				break;
			case 3: cout << "请输入您要修改的新性别:";
				cin >> gender;
				if (strcmp("男", gender) != 0 || strcmp("女", gender) != 0)
				{
					printRedText("请输入正确的性别！\n");
					Sleep(2000);
					goto button;
				}
				for (fe = 0; fe < sum; fe++)
				{
					if (stu[fe].StuRoom == stu[i].StuRoom)
					{
						if (strcmp(stu[fe].StuGender, gender) != 0)
						{
							cout << "男生与女士不能分配在同一个宿舍" << endl;
							Sleep(2000);
							goto button;
						}
					}
				}
				strcpy(stu[i].StuGender, gender);
				break;
			case 4: cout << "请输入您要修改的新年龄:";
				cin >> stu[i].StuAge;
				break;
			case 5: cout << "请输入您要修改的新班级:";
				cin >> stu[i].StuClass;
				break;
			case 6: cout << "请输入您要修改的新宿舍号:";
				cin >> room;
				for (ff = 0; ff < sum; ff++)
				{
					if (stu[ff].StuRoom == room)
					{
						if (strcmp(stu[ff].StuGender, stu[i].StuGender) != 0)
						{
							cout << "男生与女士不能分配在一起" << endl;
							Sleep(2000);
							goto button;
						}
					}
				}
				stu[i].StuRoom = room;
				break;
			case 0:
				return;
			default:
				printRedText("输入错误!请重新输入\n");
				goto button;
			}
			cout << "修改成功!" << endl;
			Print(stu, i);
		}
		else
			PrintNotFound();
		SelectOperate();
		if (a == 0)
		{
			return;
		}
	} while (a);
}

void SystemMain();
//欢迎界面密码输入错误
int HelloKey_Result()
{
	int n = 3;//最大输入次数
	for (int i = 1; i <= n; i++)
	{
		if (HelloKey == "admin")//默认系统密码
		{
			return 1;
		}
		else
		{
			if (i < n)
			{
				cout << "密码错误！请重新输入。"
					<< "您已经输入了" << i << "次," << "剩余" << n - i << "次机会" << endl;
				cin >> HelloKey;

			}
			if (i == n)
			{
				cout << "密码错误！您已经输入" << i << "次,自动退出宿舍管理系统。" << endl;
				exit(0);
			}

		}
	}

}

//退出界面
void Bye()
{
	cout << "成功退出!感谢您的使用" << endl;
	cout << "欢迎您下次使用宿舍管理系统！" << endl;
}

//欢迎界面
void Hello()
{
	cout << "\t\t\t" << "**********************************" << endl;
	cout << "\t\t\t" << "*        宿舍管理查询软件        *" << endl;
	cout << "\t\t\t" << "*             ^ _ ^              *" << endl;
	cout << "\t\t\t" << "*                                *" << endl;
	cout << "\t\t\t" << "*             ^ _ ^              *" << endl;
	cout << "\t\t\t" << "*                                *" << endl;
	cout << "\t\t\t" << "*         2024年03月20日         *" << endl;
	cout << "\t\t\t" << "**********************************" << endl;
	cout << endl;
	//printYellowText("请输入登录密码: (默认admin)\n");
	cout << "请输入登录密码: (默认admin)" << endl;
	cin >> HelloKey;
	HelloKey_Result();
}
void printStu(Student stu[], int sum)
{
	system("cls");//清屏
	system("color 0B");
	cout << "\t\t\t" << "********************************************" << endl;
	cout << "\t\t\t" << "*                                          *" << endl;
	cout << "\t\t\t" << "*            请选择您的打印方式            *" << endl;
	cout << "\t\t\t" << "*                 1、默认                  *" << endl;
	cout << "\t\t\t" << "*                 2、排序                  *" << endl;
	cout << "\t\t\t" << "*                 0、主菜单                *" << endl;
	cout << "\t\t\t" << "*                                          *" << endl;
	cout << "\t\t\t" << "********************************************" << endl;
	int op = 0;
	scanf_s("%d", &op);
	if (op == 1)
	{
		OutPut(stu, sum);//打印学生信息
	}
	else if (op == 2)
	{
		SortStudent(stu, sum);//排序学生信息
	}
	else if (op == 0)
	{

	}
	else {
		printRedText("您的输入有误！\n");
		cout << "2秒后自动进入主界面..." << endl;
		Sleep(2000);
	}
}
//宿舍管理系统主页面
void SystemMain()
{
	Student stu[20];
	int choice, sum;
	sum = ReadFile(stu);
	if (sum == 0)
	{
		cout << "3秒后自动进入信息录入系统..." << endl;
		Sleep(3000);
		sum = InPut(stu, sum);
	}
	system("cls");
	do
	{
		system("cls");//清屏
		system("color 0B");
	button:
		cout << "欢迎您进入宿舍管理系统" << endl;
		cout << "\t\t\t" << "********************************************" << endl;
		cout << "\t\t\t" << "*          请从主菜单中选择您的操作        *" << endl;
		cout << "\t\t\t" << "*              1.录入学生宿舍信息          *" << endl;
		cout << "\t\t\t" << "*              2.打印学生宿舍信息          *" << endl;
		cout << "\t\t\t" << "*              3.查询学生宿舍信息          *" << endl;
		cout << "\t\t\t" << "*              4.修改学生宿舍信息          *" << endl;
		cout << "\t\t\t" << "*              5.删除学生宿舍信息          *" << endl;
		cout << "\t\t\t" << "*              0.退出宿舍管理系统          *" << endl;
		cout << "\t\t\t" << "********************************************" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1: sum = InPut(stu, sum); break;//录入学生信息
		case 2: printStu(stu, sum); break;//打印学生信息
		case 3: SelectInquire(stu, sum); break;//查询学生信息
		case 4: Change(stu, sum); break;//修改学生信息
		case 5: sum = Delete(stu, sum); break;//删除学生信息
		case 0: Bye(); break;
		default:printRedText("输入错误!请重新输入\n"); //cout << "输入错误!请重新输入" << endl;
			goto button;
		}
		if (sum > 0) {
			SaveFile(stu, sum);
		}
	} while (choice != 0);
}

int main()
{
	//system("mode con cols=66 lines=22");
	system("color 8E");
	Hello();
	SystemMain();

}