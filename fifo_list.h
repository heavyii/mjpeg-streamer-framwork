/*
 * fifo list
 * copywrit (C) 2013 ruisheng <ruishengleen@gmail.com>
 */

#ifndef FIFO_LIST_H_
#define FIFO_LIST_H_

struct fifo_node {
	void *data;
	struct fifo_node *next;
};

/**
 * put data into fifo
 * 0 on success, -1 on malloc error
 */
int fifo_in(struct fifo_node **head, void *data);

/**
 * get data from fifo
 * returns data pointer, NULL for empty fifo
 */
void *fifo_out(struct fifo_node **head);

#endif //FIFO_LIST_H_
