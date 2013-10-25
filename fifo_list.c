/* 
 * fifo list
 * copywrit (C) 2013 ruisheng <ruishengleen@gmail.com>
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "fifo_list.h"

int fifo_in(struct fifo_node **head, void *data) {
	struct fifo_node *p = NULL;	
	if (!data)
		return -1;
	//make a node
	struct fifo_node *n = (struct fifo_node *)malloc(sizeof(struct fifo_node));
	if (!n) {
		perror("malloc");
		return -1;
	}
	n->next = NULL;
	n->data = data;

	//become header
	if (*head == NULL) {
		*head = n;
		return 0;
	}

	//add to end
	for (p = *head; p->next != NULL; p = p->next) {
		;
	}
	p->next = n;

	return 0;
}

void *fifo_out(struct fifo_node **head) {
	struct fifo_node *p = NULL;
	void *data = NULL;
	
	if (!*head)
		return NULL;

	p = *head;
	data = (*head)->data;
	*head = (*head)->next;
	free(p);
	return data;
}
