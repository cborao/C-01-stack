
// JULIO 2020. CÉSAR BORAO MORATINOS: stack.c

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <err.h>

enum{
	Maxstr = 32
};

typedef struct Node Node;
typedef struct Node *Stack;

struct Node
{
	char Data[Maxstr];
	struct Node *Next;
};

Node *
createnode(char *data) {
	Node *new;
	if ((new = malloc(sizeof(Node))) == NULL)
		errx(EXIT_FAILURE,"error: malloc failed");

	strncpy(new->Data,data,strlen(data)+1);
	new->Next = NULL;
	return new;
}

void
freenode(Node *node) {
	node->Next = NULL;
	free(node);
}

void
push(char *str, Stack *s) {
	if (*s == NULL) {
		*s = createnode(str);
	}else{
		Node *aux = createnode(str);
		aux->Next = *s;
		*s = aux;
	}
}

char *
pop(Stack *s) {

	Node *aux = *s;
	char *value;
	if (*s == NULL)
		return NULL;

	if ((value = malloc(strlen(aux->Data)+1)) == NULL)
		errx(EXIT_FAILURE,"error: malloc failed");

	strncpy(value,aux->Data,strlen(aux->Data)+1);
	*s = aux->Next;
	freenode(aux);
	return value;
}

int
main(int argc, char *argv[]) {

	Stack list = NULL;
	char word[Maxstr];
	char i,j = 'a';

	for (i='a';i<='z'; i++) {
		word[0] = i;
		for (j = 'a'; j <= 'z'; j++) {
			word[1]= j;
			word[2]='\0';
			push(word, &list);
		}
	}

	char *output = pop(&list);

	while (output != NULL) {
		printf("%s\n",output);
		free(output);
		output = pop(&list);
	}
	free(output);
	
	if (output == NULL)
		errx(EXIT_FAILURE,"Stack empty");

	exit(EXIT_SUCCESS);
}
