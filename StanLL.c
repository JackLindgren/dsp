#include <stdio.h>
#include <stdlib.h>

struct node {
	int value;
	struct node* next;
};

void PrintAll(struct node* head){
	while (head != NULL){
		printf("%d, ", head->value);
		head = head->next;
	}
	printf("\n");
}

void Push(struct node** headRef, int newData){
	struct node* newNode = malloc(sizeof(struct node));
	newNode->value = newData;
	newNode->next = *headRef;
	*headRef = newNode;
}

int Length(struct node* head){
	int len = 0;
	while(head != NULL){
		len++;
		head = head->next;
	}
	return len;
}

struct node* BuildOneTwoThree(){
	struct node* newList = NULL;
	Push(&newList, 3);
	Push(&newList, 2);
	Push(&newList, 1);
	return newList;
}

struct node* BuildGapList(){
	struct node* gapList = NULL;
	Push(&gapList, 7);
	Push(&gapList, 5);
	Push(&gapList, 4);
	return gapList;
}

struct node* BuildCrooked(){
	struct node* crooked = NULL;
	Push(&crooked, 8);
	Push(&crooked, 6);
	Push(&crooked, 7);
	Push(&crooked, 5);
	Push(&crooked, 3);
	Push(&crooked, 0);
	Push(&crooked, 9);
	return crooked;
}

int Count(struct node* head, int countMe){
	int count = 0;
	while(head != NULL){
		if(head->value == countMe){
			count++;
		}
		head = head->next;
	}
	return count;
}

int GetNth(struct node* head, int index){
	if(index >= Length(head)){
		return -1;
	} else {
		int curIndex = 0;
		while(head != NULL && curIndex < index){
			curIndex++;
			head = head->next;
		}
		return head->value;
	}
}

void DeleteList(struct node** headRef){
	struct node* current = *headRef;
	struct node* next;
	while(current != NULL){
		next = current->next;
		free(current);
		current = next;
	}
	*headRef = NULL;
}

int Pop(struct node** headRef){
	struct node* temp = *headRef;
	int first = temp->value;
	*headRef = temp->next;
	free(temp);
	return(first);
}

void InsertNth(struct node** headRef, int index, int data){
	struct node* head = *headRef;
	int curIndex = 0;

	struct node* newNode = malloc(sizeof(struct node));
	newNode->value = data;

	if(index == 0){
		Push(headRef, data);
//		newNode->next = head;
//		*headRef = newNode;
	} else {
		while(head != NULL){
			if(curIndex == index - 1){
				newNode->next = head->next;
				head->next = newNode;
			}
			head = head->next;
			curIndex++;
		}
	}
}

/*void InsertNth(struct node** headRef, int index, int data){
	if(index == 0){
		Push(headRef, data);
	}else{
		struct node* current = *headRef;
		int i = 0;
		//for(i=0; i<index-1; i++){
		while (i < index - 1){
			current = current->next;
			i++;
		}
		Push(&(current->next), data);
	}
}*/

void SortedInsert(struct node** headRef, struct node* newNode){
	//struct node* head = *headRef;
//	if(head->value >= newNode->value){
	if(*headRef == NULL || (*headRef)->value >= newNode->value){
		//newNode->next = head;
		newNode->next = *headRef;
		*headRef = newNode;
	} else {
		struct node* head = *headRef;
		while(head->next != NULL && head->next->value < newNode->value){
			head = head->next;
		}
		newNode->next = head->next;
		head->next = newNode;
	}
}
/*		while(head->next != NULL){
			if(head->value < newNode->value && head->next->value >= newNode->value){
			//if(head->next->value > newNode->value){
				newNode->next = head->next;
				head->next = newNode;
				return;
			}
			head = head->next;
		}
		head->next = newNode;
		newNode->next = NULL;*/
//	}
//}

void InsertSort(struct node** headRef){
	struct node* sortedList = NULL;
	struct node* head = *headRef;
	struct node* next; // need to use this separate "next" node again...
	while(head != NULL){
		next = head->next; // missed this
		SortedInsert(&sortedList, head);
		//head = head->next; // this is wrong
		head = next; // missed this
		// ^ we need to do it this way because SortedInsert alters the location of the node that is passed to it
		// so we need the "next" node to temporarily hold head->next
	}
	*headRef = sortedList;
}

void Append(struct node** aRef, struct node** bRef){
	if (*aRef == NULL) {
		*aRef = *bRef;
	} else {
		struct node* aHead = *aRef;
		while(aHead->next != NULL){
			aHead = aHead->next;
		}
		aHead->next = *bRef;
	}
	*bRef = NULL;
}

void FrontBackSplit(struct node* source, struct node** frontRef, struct node** backRef){
//	printf("The source list has %d items\n", Length(source));
	int half = Length(source) / 2;
//	if(Length(source) %2 == 0){
//		printf("it's even\n");
//	} else {
	if(Length(source) %2 != 0){
//		printf("it's odd\n");
		half++;
	}
//	printf("Our first segment will be %d long\n", half);

	int i = 0;
	*frontRef = source;

	// why do we need to do this? why can't we use source directly?
	struct node* current = source;

	while(i < half - 1){
	//	source = source->next;
		// ^working directly on the source
		// or working on the copy:
		current = current->next;
		i++;
	}
	// *backRef = source->next;
	// ^directly on the source or on copy:
	*backRef = current->next;
	current->next = NULL;
	// ^working on the copy or directly on source:
	//source->next = NULL;
}

// redo in a way that deletes the bad nodes in the current list
// instead of creating a new list using the good nodes
void RemoveDuplicates(struct node* head){
	struct node* deduped = NULL;
	struct node* next;
	while(head != NULL){
		next = head->next;
		if(Count(deduped, head->value) == 0){
			SortedInsert(&deduped, head);
			head = head->next;
		}
		head = next;
	}
}

// re-do so it's handled directly, without using existing Push and Pop methods
void MoveNode(struct node** destRef, struct node** sourceRef){
	int popped = Pop(sourceRef);
	Push(destRef, popped);
}

int main(){
/*	// test BuildOneTwoThree()
	struct node* first = BuildOneTwoThree();
	// test Push
	Push(&first, 0);
	// test PrintAll
	PrintAll(first);
	// test Length
	printf("The list is %d items long\n", Length(first));

	// make sure that Length works on an empty list
	struct node* empty;
	printf("The empty list is %d items long\n", Length(empty));
	// test Count
	Push(&first, 1);
	PrintAll(first);
	printf("There are %d 1s in our list\n", Count(first, 1));

	// test GetNth
	printf("The item at index 1 is: %d\n", GetNth(first, 1));
	// test GetNth with an index out of bounds
	printf("The item at index 8 is: %d\n", GetNth(first, 7));
	printf("The item at index 4 is: %d\n", GetNth(first, 4));
	printf("The item at index 5 is: %d\n", GetNth(first, 5));*/

/*	// test DeleteAll
	struct node* deleteMe = BuildOneTwoThree();
	PrintAll(deleteMe);
	DeleteList(&deleteMe);
	PrintAll(deleteMe);*/

	// test Pop
/*	struct node* popMe = BuildOneTwoThree();
	PrintAll(popMe);
	printf("first: %d\n", Pop(&popMe));
	PrintAll(popMe);
	printf("second: %d\n", Pop(&popMe));
	PrintAll(popMe);
	printf("third: %d\n", Pop(&popMe));
	PrintAll(popMe);*/

	// test InsertNth
/*	struct node* addToMe = BuildOneTwoThree();
	printf("Insert 44 at index 0:\n");
	InsertNth(&addToMe, 0, 44);
	PrintAll(addToMe);
	printf("Insert 55 at index 2:\n");
	InsertNth(&addToMe, 2, 55);
	PrintAll(addToMe);
	printf("Insert 66 at index 5:\n");
	InsertNth(&addToMe, 5, 66);
	PrintAll(addToMe);*/

	// test SortedInsert with a value at the beginning
/*	struct node* sortedList = BuildOneTwoThree();
	PrintAll(sortedList);
	printf("Insert 1 into my list:\n");
	struct node* one = malloc(sizeof(struct node));
	one->value = 1;
	one->next = NULL;
	SortedInsert(&sortedList, one);
	PrintAll(sortedList);
//	DeleteList(&sortedList);

	// test SortedInsert with a duplicate value in the middle
	printf("Insert 2 into my list:\n");
	struct node* two = malloc(sizeof(struct node));
	two->value = 2;
	two->next = NULL;
	SortedInsert(&sortedList, two);
	PrintAll(sortedList);

	// test SortedInsert with a value at the end
	printf("Insert 4 into my list:\n");
	struct node* four = malloc(sizeof(struct node));
	four->value = 4;
	four->next = NULL;
	SortedInsert(&sortedList, four);
	PrintAll(sortedList);

	// test SortedInsert with a new value in the middle
	struct node* gapList = BuildGapList();
	PrintAll(gapList);
	struct node* newtwo = malloc(sizeof(struct node));
	newtwo->value = 2;
	newtwo->next = NULL;
	SortedInsert(&gapList, newtwo);
	PrintAll(gapList);*/

	// test SortedInsert with an empty list
//	struct node* emptyList = malloc(sizeof(struct node));
//	emptyList = NULL;
/*	struct node* emptyList = NULL;
	printf("The empty list:\n");
	PrintAll(emptyList);
	struct node* fifty = malloc(sizeof(struct node));
	fifty->value = 50;
	fifty->next = NULL;
	SortedInsert(&emptyList, fifty);
	printf("Empty list with 50 added:\n");
	PrintAll(emptyList);
	struct node* forty = malloc(sizeof(struct node));
	forty->value = 40;
	forty->next = NULL;
	SortedInsert(&emptyList, forty);
	printf("Empty list with 40 added:\n");
	PrintAll(emptyList);*/

	// test InsertSort()
/*	struct node* crookedList = BuildCrooked();
	PrintAll(crookedList);
	InsertSort(&crookedList);
	PrintAll(crookedList); */

	// test Append
/*	struct node* aList = BuildOneTwoThree();
	// appending to a null list:
//	struct node* aList = malloc(sizeof(struct node));
//	aList = NULL;
	// appending to a non-null list:
	struct node* bList = BuildGapList();

	printf("List A:\n");
	PrintAll(aList);
	printf("List B:\n");
	PrintAll(bList);

	Append(&aList, &bList);
	printf("list A after appending B to it:\n");
	PrintAll(aList);
	//bList = NULL;
	printf("list B after the append operation:\n");
	PrintAll(bList); */

	// test FrontBackSplit
/*	struct node* splitList = BuildOneTwoThree();
	//struct node* splitList = NULL;
	Push(&splitList, 4);
	Push(&splitList, 5);
	Push(&splitList, 6);
	Push(&splitList, 7);
	PrintAll(splitList);
	struct node* frontList = NULL;
	struct node* backList = NULL;
	FrontBackSplit(splitList, &frontList, &backList);

	PrintAll(frontList);
	PrintAll(backList);
	PrintAll(splitList); */

	// test RemoveDuplicates
/*	struct node* dupList = BuildOneTwoThree();
	Push(&dupList, 3);
	Push(&dupList, 2);
	Push(&dupList, 1);
	printf("Our list before removing duplicates:\n");
	PrintAll(dupList);
	RemoveDuplicates(dupList);
	printf("Our list after removing duplicates:\n");
	PrintAll(dupList); */

	// test MoveNode()
	struct node* a = BuildOneTwoThree();
	struct node* b = BuildOneTwoThree();
	printf("list A: ");
	PrintAll(a);
	printf("list B: ");
	PrintAll(b);
	MoveNode(&a, &b);
	printf("list A: ");
	PrintAll(a);
	printf("list B: ");
	PrintAll(b);

}
