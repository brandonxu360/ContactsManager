#include "header.h"

int main(void) {
	//creat new list
	Node* list = NULL;
	Node* alphList = NULL;

	Contact b = { "Brandon", "4256478607", "brandon.xu@wsu.edu", "student" };
	Contact c = { "Andy", "1234325345", "andy.ofallon@wsu.edu", "professor" };
	Contact e = { "Elijah", "1346453456", "elijah.lin@wsu.edu", "ta" };
	Contact t = { "Timmy", "2344355634", "timmy.yip@wsu.edu", "bafoon" };

	insertContactAtFront(&list, b);
	insertContactAtFront(&list, c);
	insertContactAtFront(&list, e);
	insertContactAtFront(&list, t);

	insertContactInOrder(&alphList, b);
	insertContactInOrder(&alphList, c);
	insertContactInOrder(&alphList, e);
	insertContactInOrder(&alphList, t);

	printList(list);
	printList(alphList);

	return 0;
}