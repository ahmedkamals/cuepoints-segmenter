/**
 * @file
 * Linked list prototypes.
 *
 * Copyright © 2015, Ahmed Kamal. (https://github.com/ahmedkamals)
 *
 * This file is part of Ahmed Kamal's segmenter configurations.
 * ® Redistributions of files must retain the above copyright notice.
 *
 * @copyright     Ahmed Kamal (https://github.com/ahmedkamals)
 * @link          https://github.com/ahmedkamals/dev-environment
 * @package       AK
 * @subpackage    Segmenter
 * @version       1.0
 * @since         2015-01-25 Happy day :)
 * @license
 * @author        Ahmed Kamal <me.ahmed.kamal@gmail.com>
 * @modified      2015-01-25
 */

/**
 * Definition of a data node for holding student information
 */
typedef struct node {
  
    unsigned int id;

    // The data pointer is of type void *, so that it could point to any data
    void *data;
    /**
     * @var pointer to the next node.
     */
    struct node *next;
    /**
     * @var pointer to the previous node.
     */
    struct node *prev;
} NODE;

typedef struct list {
    char *name;

    /**
     * @var int isDoubly used to indicate if it is a double direction linked list.
     * @var int isCircular used to indicate if it is a circular linked list.
     * @var int length of the list.
     */
    unsigned int isDoubly,
                 isCircular,
                 length;

    /**
     * Initialize both to NULL, meaning no nodes in list yet
     *
     * @var NODE *head points to first node in list.
     * @var NODE *tail points to last node in list.
     */
    NODE *head,
            *tail;

} LIST;

enum Traverse_Direction {
    FORWARD,
    BACKWARD
};

enum Sorting {
    ASC,
    DESC
};

/**
 * @author Ahmed Kamal
 *  Function prototypes
 */
LIST *createList(void *, int, int);
LIST *cloneList(LIST *);

NODE *createNode(int, void *);
void printNode(NODE *);

NODE *append(LIST *, NODE *);
NODE *prepend(LIST *, NODE *);
NODE *insertBefore(LIST *, NODE *, NODE *);
NODE *insertAfter(LIST *, NODE *, NODE *);
NODE *insertAt(LIST *, NODE *, int);
NODE *getNth(LIST *, int);
NODE *listFind(LIST *, int(*func)(void*, void*), void *);
NODE *listFindById(LIST *, int);

void checkList(LIST *);

void traverse(LIST *, enum Traverse_Direction, void (*callback) (NODE *));

void sortById(LIST *, enum Sorting);

LIST *sortList (LIST *);

NODE *mergeSort(NODE *);

NODE *split (NODE *);

NODE *merge(NODE *, NODE *);

void removeNode(LIST *, NODE *);

void deleteList(LIST *);

void printNode(NODE *);

// vim:sw=4:tw=4:ts=4:ai:expandtab
