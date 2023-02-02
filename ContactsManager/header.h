#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum boolean
{
	FALSE, TRUE
} Boolean;
typedef struct contact
{
	char name[50];
	char phone[12]; // 18005557577
	char email[50];
	char title[20];
} Contact;
typedef struct node
{
	Contact data;
	struct node* pNext;
	struct node* pPrev; // this lab is now using two links
} Node;

/*
* Description: Allocates space for a Node on the heap and initializes the Node with the
*			   information found in newData.
* Returns:	   The address of the start of the block of memory on the heap or NULL if no
*			   memory was allocated
*/
Node* makeNode(Contact newData);

/*
* Description: Uses makeNode() to allocate space for a new Nodeand inserts the new
*			   Node into the front of the list.
* Returns:	   TRUE if memory was allocated for a Node; FALSE otherwise
*/
Boolean insertContactAtFront(Node** pList, Contact newData);

/*
* Description: Uses makeNode() to allocate space for a new Nodeand inserts the new
*			   Node into the list in alphabetic order ('a' - 'z') based on the name field
* Returns:	   TRUE if memory was  allocated for a Node; FALSE otherwise
*/
Boolean insertContactInOrder(Node** pList, Contact newData);

/*
* Description: Deletes a Contact in the list based on the name field; deletes the first
*			   occurrence of the name
* Returns:	   TRUE if the Contact was found; FALSE otherwise
*/
Boolean deleteContact(Node** pList, Contact searchContact);

/*
* Description: Edits a Contact in the list based on the name field; edits the first
*			   occurrence of the name
* Returns:	   TRUE if the Contact was found; FALSE otherwise
*/
Boolean editContact(Node* pList, Contact searchContact);

/*
* Description: Loads all Contact information from the given file, in alphabetic order,
*			   based on the name, into the list
* Returns:	   TRUE if all Contacts were loaded; FALSE otherwise
*/
Boolean loadContacts(FILE* infile, Node** pList);

/*
* Description: Stores all Contact information from the list into the given file
* Returns: TRUE if all Contacts were stored; FALSE otherwise
*/
Boolean storeContacts(FILE* infile, Node* pList);

/*
* Description: Prints all contact information in the list
* Returns: Nothing
*/
void printList(Node* pList);