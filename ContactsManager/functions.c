#include "header.h"

Node* makeNode(Contact newData) {
	//allocate space
	Node* newNode = malloc(sizeof(Node));

	//initialize node with newdata
	newNode->data = newData;
	newNode->pNext = NULL;
	newNode->pPrev = NULL;

	//return pointer to new node
	return newNode;
}

Boolean insertContactAtFront(Node** pList, Contact newData) {
	//create and initialize a new node with newData
	Node* newContact = makeNode(newData);

	if (newContact == NULL) { //space was not allocated
		return FALSE;
	}

	else { //space was allocated => now insert at front
		
		if (*pList != NULL) { //not empty list

			//set former head's prev to new head (newContact)
			Node* formerHead = *pList;
			formerHead->pPrev = newContact;

			//set new head's (newContact) next to former head
			newContact->pNext = *pList;
		}

		//indirectly return new head (newContact) as list head
		*pList = newContact;

		return TRUE;
	}
}

Boolean insertContactInOrder(Node** pList, Contact newData) {
	//create and initialize a new node with newData
	Node* newContact = makeNode(newData);

	if (newContact == NULL) { //space was not allocated
		return FALSE;
	}

	else { //space was allocated => now insert alphabetically
		
		if (*pList == NULL) { //empty list => no sorting needed
			*pList = newContact; 
		}

		else { //not empty list

			//create current for iterating through list - set it to the head
			Node* current = *pList;

			if (strcmp(newContact->data.name, current->data.name) < 0) { //special case for if newContact is before the head (should be inserted as the head)
				current->pPrev = newContact;
				newContact->pNext = current;
				*pList = newContact;
			}

			else { //newContact should be inserted after the head

				while ((strcmp(newContact->data.name, current->data.name) > 0) && current->pNext != NULL) { //keep iterating while newContact is earlier in the alphabet or reach end of list
					current = current->pNext;
				}

				//after exiting loop, newContact should be alphabetically after current; thus, insert newContact after current

				if (current->pNext != NULL) {//set pprev of next node to newContact if next node is not null
					Node* currentNext = current->pNext;
					currentNext->pPrev = newContact;
				}

				//set pnext of newContact to that next node
				newContact->pNext = current->pNext; // or currentNext

				//set pprev of newContact to current
				newContact->pPrev = current;

				//set pnext of current to newContact
				current->pNext = newContact;
			}
			

			return TRUE;
		}
	}
}

Boolean deleteContact(Node** pList, Contact searchContact) {

}

Boolean editContact(Node* pList, Contact searchContact) {

}

Boolean loadContacts(FILE* infile, Node** pList) {

}

Boolean storeContacts(FILE* infile, Node* pList) {

}

void printList(Node* pList) {
	// set current to head (start of list); current will be used to iterate through the list
	Node* current = pList;
	int count = 1;

	while (current != NULL) { //iterate until the end of the list

		//print contact
		printf("%d)   Name: %s\n", count, current->data.name);
		printf("     Phone: %s\n", current->data.phone);
		printf("     Email: %s\n", current->data.email);
		printf("     Title: %s\n\n", current->data.title);

		current = current->pNext; //move to next contact
		count++; //increment count
	}
}