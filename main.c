
/*
        //技科231姜永治//
编程综合练习题目（1）：
已知在当前路径下有文本文件data.txt，内容如下：
序号     姓名    年龄     语文     数学   外语
1	    张三		20		88		92    76
2		李四		26		82		92    76
3		王五		23		84		65    76
4		马六		20		66		82    50
5		赵七		30		72		92    76

1.	设计一个链表，实现从磁盘文件读入数据，产生按姓氏读音“升序”的有序链表，并显示
2.	将有序链表存入文件newdata.txt，格式与原文件相同，需要自动计算总分成绩。

*/

////////////////////////////思 路//////////////////////////////////////
//                                                                  //
//先将data.txt放入链表中，对链表进行操作后，再将其放入newdata.txt中// 
//                                                                 //
///////////////////////////思 路/////////////////////////////////////

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//成绩的结构体
typedef struct student_message{
	int order_number;
	char name[20];
	int age;
	int chinese;
	int math;
	int english;
	int score_sum;
}STU;


//成绩的链表
struct Node{
	STU data;
	struct Node *next;
};


//字符串比较函数，根据姓名的读音升序排列
int NameCompare(const char *name1,const char *name2) {
	return strcmp(name1,name2);
}


//处理链表的函数，根据姓氏升序排名,插入排序法
void Sort(struct Node *head) {
	if (head == NULL || head->next == NULL) {
		return;
	}

	struct Node *sortedHead = NULL;
	struct Node *current = head;

	while (current != NULL) {
		struct Node *nextNode = current->next;
		if (sortedHead == NULL || NameCompare(current->data.name, sortedHead->data.name) <= 0) {
			current->next = sortedHead;
			sortedHead = current;
		} else {
			struct Node *temp = sortedHead;
			while (temp->next != NULL && NameCompare(current->data.name, temp->next->data.name) > 0) {
				temp = temp->next;
			}
			current->next = temp->next;
			temp->next = current;
		}
		current = nextNode;
	}
	head = sortedHead;
}


//链表的尾插法
void InsertDataToList(struct Node **head, STU new_data){
	struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));
	if (new_node==NULL){
		printf("Malloc fail");
		return;
	}
	
	new_node->data.order_number = new_data.order_number;
    strcpy(new_node->data.name, new_data.name);
    new_node->data.age = new_data.age;
    new_node->data.chinese = new_data.chinese;
    new_node->data.math = new_data.math;
    new_node->data.english = new_data.english;
    
	new_node->next = NULL;
	
	if (*head == NULL) {
        *head = new_node;
        return;
    }

	struct Node *tail = *head;
	while (tail->next != NULL)
		tail = tail->next;
		
		
	tail->next = new_node;	
}


//计算总分的函数
void ScoreSum(struct Node *head) {
	struct Node *p = head;
	while(p!=NULL) {
		p->data.score_sum = p->data.chinese+p->data.math+p->data.english;
		p = p->next;
	}
	return;
}


//打印链表的函数
void PrintLinkList(struct Node *head){
	struct Node *node = head;
	printf("-----------------------------------------\n");
    printf("序号    姓名    年龄    语文    数学    外语\n");
    while (node != NULL) {
        printf("%d    ", node->data.order_number);
        printf("%s    ", node->data.name);
        printf("%d    ", node->data.age);
        printf("%d    ", node->data.chinese);
        printf("%d    ", node->data.math);
    	printf("%d    \n", node->data.english);
    	//
    	//printf("%d    \n", node->data.score_sum);    根据需要选择是否打印总成绩
		//

        node = node->next;
    }
    printf("-----------------------------------------\n");
    
} 


int main(){
	struct Node *head = NULL;
	
	//打开文件data.txt并存放在链表中 
	FILE *fp = fopen("data.txt","r");
	if (fp==NULL){
		printf("Open fail");
		return 1;
	}
	
	STU student;
    while (fscanf(fp, "%d %s %d %d %d %d", &student.order_number, student.name, &student.age,&student.chinese, &student.math, &student.english) == 6) {
    	InsertDataToList(&head, student);
    }
	fclose(fp);


	//对链表排序 
	Sort(head);
	
	
	//计算总成绩 
	ScoreSum(head);
	
	
	//打印链表 
	PrintLinkList(head);
	

	//将链表存放入文件newdata.txt中 
	FILE *newFile = fopen("newdata.txt", "w");
	if (newFile == NULL) {
		printf("open fail");
		exit(0);
	}

	struct Node *temp = head;
	while (temp != NULL) {
		fprintf(newFile, "%d\t%s\t%d\t%d\t%d\t%d\t%d\n", temp->data.order_number, temp->data.name, temp->data.age,
				temp->data.chinese, temp->data.math, temp->data.english, temp->data.score_sum);
		temp = temp->next;
	}

	fclose(newFile);



    //释放创建链表时创建的内存 
    struct Node* t;
    while (head != NULL) {
        t = head;
        head = head->next;
        free(t);
    }
	
	
	
	return 0;
}
