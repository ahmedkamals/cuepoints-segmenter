/**
 * @file
 * Linked list implementation.
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

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "helpers.h"
#include "linked_list.h"

/**
 * Used to create a list.
 *
 * @param char *name the name of the list
 * @param int isDoubly indicating whether the linked list is doubly or not.
 * @parm int isCircluar indicating whether the linked list is circular or not.
 * @return LIST *list
 */
LIST *createList(void *name, int isDoubly, int isCircular) {
    LIST *list;

    // Initialize node and make type casting to it.
    if (!(list = (LIST *) calloc(1, sizeof (LIST)))) return (LIST *) NULL; /* error allocating node? then return NULL */

    list->name = name;

    list->isDoubly = isDoubly;
    list->isCircular = isCircular;

    list->head = list->tail = NULL;
    list->length = 0;

    return list;
}

/**
 * Used to clone a list.
 *
 * @param LIST *source pointer to the source list.
 * @return LIST *destination pointer to the destination list.
 */
LIST *cloneList(LIST *source) {
    if(source == NULL || source->length == 0){
        return NULL;
    }

    LIST *destination;
    NODE *link, *tempNode;

    // Initialize node and make type casting to it.
    if (!(destination = (LIST *) calloc(1, sizeof (LIST)))) return (LIST *) NULL; /* error allocating node? then return NULL */

    destination->name = source->name;

    destination->isDoubly = source->isDoubly;
    destination->isCircular = source->isCircular;

    for (link = source->head; link; link = link->next) {
        tempNode = createNode(link->id, link->data);
        append(destination, tempNode);
    }

    return destination;
}

/**
 * This initializes a node, allocates memory for the node, and returns
 * a pointer to the new node. Must pass it the node details, name and id
 *
 * @param int id of the list.
 * @param void * data
 * @return node
 */
NODE *createNode(int id, void *data) {
    NODE *node;

    // Initialize node and make type casting to it.
    if (!(node = (NODE *) calloc(1, sizeof (NODE)))) return (NODE *) NULL; /* error allocating node? then return NULL */

    /* allocated node successfully */
    node->id = id; // Copy id details.
    node->data = data; // Copy data details.

    node->next = node->prev = NULL;

    return node; // Return pointer to new node.
}

/**
 * Adding a node to the end of the list. You must allocate a node and
 * then pass its address to this function
 *
 * @param LIST *list pointer to the list.
 * @param NODE **node pointer to the node.
 * @return NODE
 */
NODE *append(LIST * list, NODE *node) /* adding to end of list */ {

    if (list == NULL || node == NULL) return (NODE *) NULL;

    if (list->tail != NULL) /* if there are no nodes in list, then  */ {
        list->tail->next = node; // Modify the current list tail's next to point to the new node.
    }

    if (list->head == NULL) {
        list->head = node;
    }

    //node->id = list->length;

    // Modify pointer to point to the list head.
    node->next = (list->isCircular ? list->head : NULL); // Set next field to signify the end of list.
    node->prev = list->tail; // Set prev field to signify the current tail of list.

    list->tail = node; // Adjust end to point to the last node.

    ++list->length;
    return node;
}

/**
 * Adding a node to the head of the list. You must allocate a node and
 * then pass its address to this function
 *
 * @param LIST *list pointer to the list.
 * @param NODE *node pointer to the node.
 * @return NODE
 */
NODE *prepend(LIST *list, NODE *node) /* adding to end of list */ {

    if (list == NULL || node == NULL) return (NODE *) NULL;

    if (list->head != NULL) /* if there are no nodes in list, then  */ {
        list->head->prev = node; // Modify the current list head's prev to point to the new node.
    }

    if (list->tail == NULL) {
        list->tail = node;
    }

    //node->id = list->length + 1;

    node->next = list->head; // Set next field to signify the head of list.
    node->prev = NULL; // Set prev field to signify the current head of list.

    list->head = node; // Adjust head to point to the last node.

    // Modify pointer to point to the new head.
    if (list->isCircular) {
        list->tail->next = list->head;
    }

    ++list->length;
    return node;
}

/**
 * Inserting a node before a certain node.
 *
 * @param LIST *list pointer to the list.
 * @param NODE *node pointer to the node that we want to insert before.
 * @param NODE *insertedNode pointer to the inserted node.
 * @return NODE
 */
NODE *insertBefore(LIST *list, NODE *node, NODE *insertedNode) {

    if (list == NULL || node == NULL) return (NODE *) NULL;

    //insertedNode->id = node->id;
    //++node->id;

    insertedNode->prev = node->prev; // Set prev field to signify the current node's previous.
    insertedNode->next = node; // Set next field to signify the current node.

    if (node->prev == NULL) {
        list->head = insertedNode;

    } else { // The current node's prev pointer is pointing to an existing node, then we should modify its next attribute.
        node->prev->next = insertedNode;
    }

    node->prev = insertedNode; // Set prev field of the current node to signify the new node.

    ++list->length;
    return insertedNode;
}

/**
 * Inserting a node after a certain node.
 *
 * @param LIST list pointer to the list.
 * @param node pointer to the node that we want to insert after.
 * @param NODE *insertedNode pointer to the inserted node.
 * @return NODE
 */
NODE *insertAfter(LIST *list, NODE *node, NODE *insertedNode) {

    if (list == NULL || node == NULL) return (NODE *) NULL;

    //insertedNode->id = node->id;
    //--node->id;

    insertedNode->next = node->next; // Set next field to signify the current node's next.
    insertedNode->prev = node; // Set prev field to signify the current node.

    if (node->next == NULL) {
        list->tail = insertedNode;
    } else { // The current node's next is pointing to an existing node, then we should modify its prev attribute.
        node->next->prev = insertedNode;
    }

    node->next = insertedNode; // Set next field of the current node to signify the new node.

    ++list->length;
    return insertedNode;
}

/**
 * Used to insert a node at specific position
 *
 * @param LIST *list pointer to the list.
 * @param NODE *node pointer to the inserted node.
 * @param int position (0 Based) in which the node will be inserted.
 *
 * @return pointer to the node
 */
NODE *insertAt(LIST *list, NODE *node, int position) {

    if (list == NULL || node == NULL || abs(position) > list->length + 1) {
        return (NODE *) NULL;
    }

    enum Traverse_Direction direction = position >= 0 ? FORWARD : BACKWARD;

    NODE *tempNode;
    int c = -1;

    switch (direction) {
        case FORWARD:
            // Previous check to gain performance.
            if(position > list->length){
                return append(list, node);
            }

            tempNode = list->head;

            while (tempNode != NULL) {
                if (++c == position) {
                    return insertBefore(list, tempNode, node);
                }

                tempNode = tempNode->next;
            }

            break;

        case BACKWARD:
            if (!list->isDoubly){
                fprintf(stderr, "{\"error\":\"The list is not doubly, you can't traverse backward\"}");
                exit(1);
            }
            // Previous check to gain performance.
            if(position > list->length){
                return prepend(list, node);
            }

            tempNode = list->tail;
            c = 0;

            while (tempNode != NULL) {
                if (--c == position) {
                    return insertAfter(list, tempNode, node);
                }

                tempNode = tempNode->prev;
            }

            break;
    }

    return node;
}

/**
 * Used to get the element at n position.
 * @param LIST *list pointer to the list.
 * @param int position of the node to be inserted in.
 * @return NODE * pointer to the node.
 */
NODE *getNth(LIST *list, int position){
    if (list == NULL  || abs(position) >= list->length) {
        return (NODE *) NULL;
    }

    enum Traverse_Direction direction = position >= 0 ? FORWARD : BACKWARD;

    NODE *tempNode;
    int c = -1;

    switch (direction) {
        case FORWARD:
            tempNode = list->head;

            while (tempNode != NULL) {
                if (++c == position) {
                    return tempNode;
                }

                tempNode = tempNode->next;
            }
            break;

        case BACKWARD:
            if (!list->isDoubly){
                fprintf(stderr, "{\"error\":\"The list is not doubly, you can't traverse backward\"}");
                exit(1);
            }

            tempNode = list->tail;
            c = 0;

            while (tempNode != NULL) {
                if (--c == position) {
                    return tempNode;
                }

                tempNode = tempNode->prev;
            }
            break;
    }
    return NULL;
}

/**
 * Used to find a data in a node, using a passed in function to apply comparison logic.
 *
 * @param LIST *list pointer to the list.
 * @param callback.
 * @param data.
 * @return NODE.
 */
NODE *listFind(LIST *list, int(*callback)(void*, void*), void *data) {
    NODE *node = list->head;

    while (node) {
        if (callback(node->data, data) > 0) return node;
        node = node->next;
    }
    return NULL;
}

/**
 * Used to find a a node, by a given id.
 *
 * @param LIST *list pointer to the list.
 * @param int id the node id.
 * @return NODE.
 */
NODE *listFindById(LIST *list, int id) {
    NODE *node = list->head;

    while (node) {
        if (node->id == id) return node;
        node = node->next;
    }
    return NULL;
}

/**
 * Used to update list data, usually, used after sorting operations.
 *
 * @param LIST *list pointer to the list.
 */
void checkList(LIST *list){
    NODE *link;
    for (link = list->head; link->next; link = link->next) {
        // Keep looping while the end of the list.
    }

    list->tail = link;

    if(list->tail->id == list->head->id){
        list->isCircular = 1;
    }
}

/**
 * Used to remove a specific node from a list.
 *
 * @param LIST *list pointer to the list.
 * @param NODE *node pointer to the node.
 */
void removeNode(LIST *list, NODE *node) {
    if (node->prev == NULL) {
        list->head = node->next;
    } else {
        node->prev->next = node->next;
    }

    if (node->next == NULL) {
        list->tail = node->prev;
    } else {
        node->next->prev = node->prev;
    }
    free(node);
}

/**
 * Used to traverse on the nodes, and execute a callback.
 *
 * @param LIST *list pointer to the list.
 * @param enum Traverse_Direction direction the direction
 * @param callback
 */
void traverse(LIST *list, enum Traverse_Direction direction, void (*callback) (NODE *)) {
    NODE *link;
    switch (direction) {
        case FORWARD:

            for (link = list->head; link; link = link->next) {
                callback(link);
            }

            break;

        case BACKWARD:
            if (!list->isDoubly){
                fprintf(stderr, "{\"error\":\"The list is not doubly, you can't traverse backward\"}");
                exit(1);
            }

            for (link = list->tail; link; link = link->prev) {
                callback(link);
            }
            break;
    }
    free(link);
}

/**
 * Used to sort nodes based on id value.
 * @param LIST *list pointer to the list.
 * @param enum Sorting direction Ascending or Descending.
 */
void sortById(LIST *list, enum Sorting direction) {
    NODE * link, *temp;
    int rep;
    switch (direction) {
        case ASC:
            if(list->length > 1){
                sortList(list);
            }
            break;

        case DESC:

            for (link = list->tail; link; link = link->prev) {

                for (temp = link->prev; temp != NULL; temp = temp->prev) {
                    if (link->id > temp->id) {
                        rep = link->id;
                        link->id = temp->id;
                        temp->id = rep;
                    }
                }
            }
            break;
    }
}

/**
 * Used to sort a linked list using merge sort Algorithm.
 *
 * @param LIST *list pointer to the list.
 * @return LIST * pointer to the sorted list.
 */
LIST *sortList(LIST *list) {
    list->head = mergeSort(list->head);
    checkList(list);
    return list;
}

/**
 * Used to apply merge sort functionality.
 *
 * @param NODE *headOriginal pointer to the list head.
 * @return
 */
NODE *mergeSort(NODE *headOriginal) {

    if (headOriginal == NULL || headOriginal->next == NULL)
        return headOriginal;

    NODE *splittedList = split(headOriginal);

    headOriginal = mergeSort(headOriginal);
    splittedList = mergeSort(splittedList);

    return merge(headOriginal, splittedList);
}

/**
 * Used to split the list into two lists.
 *
 * @param LIST *list pointer to the list.
 * @param NODE *splitRefrence pointer to the split reference node.
 * @return NODE * pointer to the splitting node.
 */
NODE *split(NODE *splitRefrence) {
    if (splitRefrence == NULL || splitRefrence->next == NULL) return NULL;

    // Assign splittedList to split location
    NODE *splittedList = splitRefrence->next;

    // Move double steps
    splitRefrence->next = splitRefrence->next->next;

    // Keep splitting the nodes
    splittedList->next = split(splittedList->next);

    return splittedList;
}

/**
 * Used to merge two sorted lists.
 *
 * @param NODE *list1 pointer to the first node at list1.
 * @param NODE *list2 pointer the first node at list2.
 * @return NODE * pointer to the first node at merged list.
 */
NODE *merge(NODE *list1, NODE *list2) {
    if (list1 == NULL) return list2;
    if (list2 == NULL) return list1;

    // 'id' is the variable we're sorting on
    if (list1->id < list2->id) {
        list2->prev = list1;
        list1->next = merge(list1->next, list2);

        return list1;
    }// end if
    else {
        list1->prev = list2;
        list2->next = merge(list1, list2->next);
        return list2;
    } // end else
}

/**
 * Deleting all nodes from the place specified by ptr
 * if you pass it head, it will free up entire list.
 *
 * @param LIST *list pointer to the list.
 */
void deleteList(LIST *list) {
    NODE *traverseNode = list->head,
            *next;
    while (traverseNode != NULL) { // While there are still nodes to delete.
        next = traverseNode->next; // Record address of next node.
        free(traverseNode); // Free this node.
        traverseNode = next; // Point to next node to be deleted.
    }
    list->length = 0;
    list->head = list->tail = NULL;
}

/**
 *  Printing the details of a node, eg, the name and id
 *  must pass it the address of the node you want to print out
 *
 *  @param node pointer to the node.
 */
void printNode(NODE *node) {
    printf("\t%i- %s\n", node->id, (char *) node->data);
}

// vim:sw=4:tw=4:ts=4:ai:expandtab
