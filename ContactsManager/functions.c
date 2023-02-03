#include "header.h"

int handleMainMenu(void) {
	int choice = 0;

	//print menu
	printf("MENU\n");
	printf("-------------------\n");
	printf("(1)   load\n");
	printf("(2)   store\n");
	printf("(3)   display\n");
	printf("(4)   insert\n");
	printf("(5)   delete\n");
	printf("(6)   edit\n");
	printf("(7)   exit\n\n");

	//prompt user input
	printf("Input: ");

	//get user input
	scanf("%d", &choice);

	//invalid input catch
	while (choice < 1 || choice > 8) {
		printf("\n\nInvalid input detected. Try again.\n");
		printf("Input: ");

		scanf("%d", &choice);
	}

	return choice;
}

Contact newContact(void) {
	Contact newContact;

	//get name field
	printf("\nEnter new name (49 char max): ");
	scanf("%s", newContact.name);

	//phone
	printf("\nEnter new phone (11 char max): ");
	scanf("%s", newContact.phone);

	//email
	printf("\nEnter new email (49 char max): ");
	scanf("%s", newContact.email);

	//title
	printf("\nEnter new title (19 char max): ");
	scanf("%s", newContact.title);

	return newContact;

}

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

			else { //newContact will be inserted after the head
				Node* prev = NULL;

				while ((strcmp(newContact->data.name, current->data.name) > 0) && current->pNext != NULL) { //keep iterating while newContact is earlier in the alphabet or reach end of list
					current = current->pNext;
				}

				//after exiting loop, newContact should be alphabetically before current (or special case end of list and newContact should be last)
				//thus, insert newContact before current, or insert newContact at end if current is the last node


				if (strcmp(newContact->data.name, current->data.name) > 0) { //case that we reached the end of the list and have not found data after new data; insert as end
					current->pNext = newContact;
					newContact->pPrev = current;
				}
				
				else { //insert before current
					prev = current->pPrev;

					current->pPrev = newContact;
					if (prev != NULL) prev->pNext = newContact;

					newContact->pPrev = prev;
					newContact->pNext = current;
				}
			}


			return TRUE;
		}
	}
}

Boolean deleteContact(Node** pList) {
	Node* current = *pList; //set current to head of list for iterator
	char name[64];

	//prompt name input
	printf("Enter the name of the contact to delete\n\n");
	printf("Input: ");
	
	//get name input
	scanf("%s", &name);

	//keep iterating until reach the end or contact is found
	while (current != NULL && strcmp(current->data.name, name) != 0) { 

		//set current to next node
		current = current->pNext;
	}

	if (current != NULL) { //contact was found (is current) => delete contact

		if (current->pPrev == NULL) { //special case - node being deleted is head

			//new head is the next node after current (current head)
			Node* newHead = current->pNext;

			//new head should not have a node before it (pprev = NULL)
			newHead->pPrev = NULL;

			//indirectly return new head as head of list
			*pList = newHead;
		}

		else if (current->pNext == NULL) { //special case - node being deleted is last node

			//only need to set last node (node before current) pnext to NULL
			current->pPrev->pNext = NULL;
		}

		else { //node being deleted is not the head

			//"close the gaps" - set pnext of the previous node to the node after current and pprev of the next node to the node before prev
			current->pPrev->pNext = current->pNext;
			current->pNext->pPrev = current->pPrev;
		}

		//free the space of node being deleted
		free(current);

		return TRUE;

	}

	else { //end of list was reached
		printf("\nSorry, the contact was not found\n\n");

		system("pause");

		return FALSE;
	}
}

Boolean editContact(Node* pList) {
	Node* current = pList; //set current to head of list for iterator
	char name[64];

	//prompt name input
	printf("Enter the name of the contact to edit\n\n");
	printf("Input: ");

	//get name input
	scanf("%s", &name);

	//keep iterating until contact is found or end of list is reached
	while (current != NULL && strcmp(current->data.name, name) != 0) {

		//set current to next node
		current = current->pNext;
	}

	if (current != NULL) { //contact was found
		int choice = 0;

		system("cls");

		//display contact being edited
		printf("Contact being modified: (1) %s\n", current->data.name);
		printf("                        (2) %s\n", current->data.phone);
		printf("                        (3) %s\n", current->data.email);
		printf("                        (4) %s\n", current->data.title);

		//prompt for selection of field to be edited
		printf("\nEnter the number corresponding with the field you would like to edit\n\n");
		printf("Input: ");

		scanf("%d", &choice);

		//edit field based on selection
		switch (choice) {
			case 1: //name
				printf("\n\nEnter new name (49 char max): ");
				scanf("%s", current->data.name);
				break;

			case 2: //phone
				printf("\n\nEnter new phone (11 char max): ");
				scanf("%s", current->data.phone);
				break;

			case 3: //email
				printf("\n\nEnter new email (49 char max): ");
				scanf("%s", current->data.email);
				break;

			case 4: //title
				printf("\n\nEnter new title (19 char max): ");
				scanf("%s", current->data.title);
				break;
		}

		//display contact after modification
		printf("Contact after changes:  (1) %s\n", current->data.name);
		printf("                        (2) %s\n", current->data.phone);
		printf("                        (3) %s\n", current->data.email);
		printf("                        (4) %s\n", current->data.title);

		return TRUE;
	}

	else { //contact was not found
		printf("\nSorry, contact was not found");

		return FALSE;
	}
}

Boolean loadContacts(FILE* infile, Node** pList) {
	char* token, line[128];
	Contact data;

	while (fgets(line, 127, infile) != NULL) { //while not at EOF

		//remove trailing newline added by fgets
		line[strcspn(line, "\n")] = 0;

		//name
		token = strtok(line, ",");
		strcpy(data.name, token);

		//phone
		token = strtok(NULL, ",");
		strcpy(data.phone, token);

		//email
		token = strtok(NULL, ",");
		strcpy(data.email, token);

		//title
		token = strtok(NULL, ",");
		strcpy(data.title, token);

		//insert contact into list
		insertContactInOrder(pList, data);
	}

	return TRUE;
}

Boolean storeContacts(FILE* infile, Node* pList) {
	//create iterator and set it to head node
	Node* current = pList;

	while (current != NULL) { //iterate until end of list

		fprintf(infile, "%s,%s,%s,%s\n", current->data.name, current->data.phone,
			current->data.email, current->data.title);

		current = current->pNext;
	}

	return TRUE;
}

void printList(Node* pList) {
	// set current to head (start of list); current will be used to iterate through the list
	Node* current = pList;
	int count = 1;

	while (current != NULL) { //iterate until the end of the list

		//print contact
		printf("%d)   Name:  %s\n", count, current->data.name);
		printf("     Phone: %s\n", current->data.phone);
		printf("     Email: %s\n", current->data.email);
		printf("     Title: %s\n\n", current->data.title);

		current = current->pNext; //move to next contact
		count++; //increment count
	}
}
