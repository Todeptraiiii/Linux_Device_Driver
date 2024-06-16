#include <bits/stdc++.h>

using namespace std;

struct node{
   int data;
   struct node* next;
};

node* makeNode(int x){
   //node *newNode = (node*)malloc(sizeof(node));
   node *newNode = new node();
   newNode->data = x;
   newNode->next = NULL;
   return newNode;
}

int size(node *head){
   int cnt = 0;
   while(head != NULL){
      ++cnt;
      head = head->next;
   }
   return cnt;
}

void duyet(node *head){
   while(head != NULL){
      cout << head->data << ' ';
      head = head->next;
   }
}

void pushFront(node **head, int x){
   node* newNode = makeNode(x);
   newNode->next = (*head);
   (*head) = newNode;
}

void pushBack(node **head, int x){
   node* newNode = makeNode(x);
   if(*head == NULL){
      *head = newNode; return;
   }
   node* tmp = *head;
   while(tmp->next != NULL){
       tmp = tmp->next;
   }
   tmp->next = newNode;
}

void insert(node **head, int k, int x){
	int n = size(*head);
	if(k < 1 || k > n + 1) return;
	if(k == 1){
		pushFront(head, x); return;
	}
	node *temp = *head;
	for(int i = 1; i <= k - 2; i++){
		temp = temp->next;
	}
	//temp : k - 1
	node *newNode = makeNode(x);
	newNode->next = temp->next;
	temp->next = newNode;
}

void popFront(node **head){
	if(*head == NULL) return;
	node *temp = *head; // giai phong
	*head = (*head)->next;
	//free(temp)
	delete temp;
}

void popFront2(node *&head){
	if(head == NULL) return;
	node *temp = head;
	head = head->next;
	delete temp;
}

void popBack(node **head){
	if(*head == NULL) return;
	node *temp = *head;
	if(temp->next == NULL){
		*head = NULL; delete temp;
		return;
	}
	while(temp->next->next != NULL){
		temp = temp->next;
	}
	node *last = temp->next; // node cuoi
	temp->next = NULL;
	delete last;
}

void popBack2(node *&head){
	if(head == NULL) return;
	node *temp = head;
	if(temp->next == NULL){
		head = NULL; delete temp;
		return;
	}
	while(temp->next->next != NULL){
		temp = temp->next;
	}
	node *last = temp->next; // node cuoi
	temp->next = NULL;
	delete last;
}

int main(){
	node *head = NULL;
	while(1){
		cout << "------------------------------------\n";
		cout << "1. Them vao dau\n";
		cout << "2. Them vao cuoi\n";
		cout << "3. Them vao giua\n";
		cout << "4. Xoa node khoi dau DSLK\n";
		cout << "5. Xoa node khoi cuoi DSLK\n";
		cout << "6. Duyet\n";
		cout << "0. Thoat !\n";
		cout << "------------------------------------\n";
		cout << "Nhap lua chon :";
		int lc; cin >> lc;
		if(lc == 1){
			int x; cout << "Nhap x :"; cin >> x;
			pushFront(&head, x);
		}
		else if(lc == 2){
			int x; cout << "Nhap x :"; cin >> x;
			pushBack(&head, x);
		}
		else if(lc == 3){
			int x; cout << "Nhap x :"; cin >> x;
			int k; cout << "Nhap k :"; cin >> k;
			insert(&head, k, x);
		}
		else if(lc == 4){
			popFront2(head);
		}
		else if(lc == 5){
			popBack2(head);
		}
		else if(lc == 6){
			duyet(head);
			cout << endl;
		}
		else{
			break;
		}
	}
	return 0;
}