/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (NULL == q)
        return NULL;
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (NULL == q)
        return;
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    list_ele_t *e = q->head, *e_next;
    while (e) {
        e_next = e->next;
        if (e->value)
            free(e->value);
        free(e);
        e = e_next;
    }
    free(q);
}

static bool _ele_add_string(list_ele_t *e, char *s)
{
    size_t s_len = strlen(s);
    e->value = (char *) malloc(s_len + 1);
    if (NULL == e->value) {
        return false;
    }
    memcpy(e->value, s, s_len);
    e->value[s_len] = '\0';
    return true;
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    if (NULL == q || NULL == s)
        return false;
    newh = malloc(sizeof(list_ele_t));
    if (NULL == newh)
        return false;

    /* Don't forget to allocate space for the string and copy it */
    if (false == _ele_add_string(newh, s)) {
        free(newh);
        return false;
    }

    /* What if either call to malloc returns NULL? */
    newh->next = q->head;
    q->head = newh;
    if (++q->size == 1)
        q->tail = q->head;

    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    list_ele_t *newt;
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (NULL == q || NULL == s)
        return false;
    newt = malloc(sizeof(list_ele_t));
    if (NULL == newt)
        return false;

    if (false == _ele_add_string(newt, s)) {
        free(newt);
        return false;
    }
    if (q->tail)
        q->tail->next = newt;
    q->tail = newt;
    newt->next = NULL;
    if (++q->size == 1)
        q->head = q->tail;

    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    list_ele_t *e;
    size_t s_len;

    if (NULL == q || NULL == q->head)
        return false;
    e = q->head;
    if (sp && bufsize > 0) {
        s_len = strlen(e->value);
        s_len = (bufsize - 1) >= s_len ? s_len : (bufsize - 1);
        memcpy(sp, e->value, s_len);
        sp[s_len] = '\0';
    }
    q->head = q->head->next;
    if (--q->size == 0)
        q->tail = NULL;
    free(e->value);
    free(e);
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (NULL == q)
        return 0;
    return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    list_ele_t *new_head = NULL, *e;
    /* You need to write the code for this function */
    if (NULL == q || NULL == q->head)
        return;

    q->tail = q->head;
    while (q->head) {
        e = q->head;
        q->head = q->head->next;
        e->next = new_head;
        new_head = e;
    }
    q->head = new_head;
}
