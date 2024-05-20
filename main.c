
/*
        //����231������//
����ۺ���ϰ��Ŀ��1����
��֪�ڵ�ǰ·�������ı��ļ�data.txt���������£�
���     ����    ����     ����     ��ѧ   ����
1	    ����		20		88		92    76
2		����		26		82		92    76
3		����		23		84		65    76
4		����		20		66		82    50
5		����		30		72		92    76

1.	���һ������ʵ�ִӴ����ļ��������ݣ����������϶��������򡱵�������������ʾ
2.	��������������ļ�newdata.txt����ʽ��ԭ�ļ���ͬ����Ҫ�Զ������ֳܷɼ���

*/

////////////////////////////˼ ·//////////////////////////////////////
//                                                                  //
//�Ƚ�data.txt���������У���������в������ٽ������newdata.txt��// 
//                                                                 //
///////////////////////////˼ ·/////////////////////////////////////

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//�ɼ��Ľṹ��
typedef struct student_message{
	int order_number;
	char name[20];
	int age;
	int chinese;
	int math;
	int english;
	int score_sum;
}STU;


//�ɼ�������
struct Node{
	STU data;
	struct Node *next;
};


//�ַ����ȽϺ��������������Ķ�����������
int NameCompare(const char *name1,const char *name2) {
	return strcmp(name1,name2);
}


//��������ĺ���������������������,��������
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


//�����β�巨
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


//�����ֵܷĺ���
void ScoreSum(struct Node *head) {
	struct Node *p = head;
	while(p!=NULL) {
		p->data.score_sum = p->data.chinese+p->data.math+p->data.english;
		p = p->next;
	}
	return;
}


//��ӡ����ĺ���
void PrintLinkList(struct Node *head){
	struct Node *node = head;
	printf("-----------------------------------------\n");
    printf("���    ����    ����    ����    ��ѧ    ����\n");
    while (node != NULL) {
        printf("%d    ", node->data.order_number);
        printf("%s    ", node->data.name);
        printf("%d    ", node->data.age);
        printf("%d    ", node->data.chinese);
        printf("%d    ", node->data.math);
    	printf("%d    \n", node->data.english);
    	//
    	//printf("%d    \n", node->data.score_sum);    ������Ҫѡ���Ƿ��ӡ�ܳɼ�
		//

        node = node->next;
    }
    printf("-----------------------------------------\n");
    
} 


int main(){
	struct Node *head = NULL;
	
	//���ļ�data.txt������������� 
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


	//���������� 
	Sort(head);
	
	
	//�����ܳɼ� 
	ScoreSum(head);
	
	
	//��ӡ���� 
	PrintLinkList(head);
	

	//�����������ļ�newdata.txt�� 
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



    //�ͷŴ�������ʱ�������ڴ� 
    struct Node* t;
    while (head != NULL) {
        t = head;
        head = head->next;
        free(t);
    }
	
	
	
	return 0;
}
