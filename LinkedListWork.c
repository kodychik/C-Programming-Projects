#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// You may NOT modify this struct in any way.
// This includes adding new variables.
typedef struct NumNode
{
    int val;
    struct NumNode *next;
} NumNode;

/**
 * Populates a NumNode linked list based on a given array of integer values.
 * Maintains the same order as the array.
 *
 * Returns the head of a new linked list.
 * If the array of values is negative or empty (count <= 0), return an empty list.
 */
NumNode *new_num_node(void)
{
    NumNode *new_node = NULL;
    new_node = (NumNode *)calloc(1, sizeof(NumNode));
    new_node->val = -1;
    new_node->next = NULL;
    return new_node;
}

void insertAtTail(NumNode *head, NumNode *new_node)
{
    NumNode *p = NULL;
    p = head;

    while (p->next != NULL)
    {
        p = p->next;
    }
    p->next = new_node;
}

NumNode *create_num_list(int *vals, int count)
{
    // TODO: Complete this function.
    NumNode *new_num_list = NULL;
    NumNode *q = NULL;
    //int *p = NULL;
    //p = vals;
    if (count <= 0)
    {
        return NULL;
    }

    new_num_list = new_num_node();
    new_num_list->val = *(vals);
    // pointer to head of list


    for (int i = 1; i < count; i++)
    {
        q = new_num_node();
        q->val = *(vals + i);
        insertAtTail(new_num_list, q);
    }

    return new_num_list;
}

/**
 * Sorts a NumNode linked list in increasing order.
 *
 * NOTE:
 *      [-10] -> [3] -> [5] -> [5] -> [30]
 *
 * NOTE:
 *      To sort, you can use any algorithm you wish as
 *      long as it runs in O(N^2) or faster.
 *
 * Returns the head of the new linked list.
 * Similaritily, if the given list is empty, return NULL.
 */
NumNode *sort_num_list(NumNode *list)
{
    // TODO: Complete this function.
    int temp;
    NumNode *pre = NULL;
    NumNode *tr = NULL;
    pre = list;

    while (pre != NULL)
    {
        tr = list;
        while (tr->next != NULL)
        {
            if (tr->val > tr->next->val)
            {
                temp = tr->next->val;
                tr->next->val = tr->val;
                tr->val = temp;
            }
            tr = tr->next;
        }
        pre = pre->next;
    }

    return list;


    /*
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
    */ // insertion sort for integers
}

void delete_num_list(NumNode *head)
{
    if (head == NULL)
    {
        return;
    }

    if (head->next != NULL)
    {
        delete_num_list(head->next);
    }

    free(head);
}

bool check_num_list_order(NumNode *list, int *vals, int count)
{
    int idx = 0;

    while (count > 0)
    {
        if (list == NULL) // reached end of list, but not end of array
        {
            printf("Reached end of list not end of array\n");
            return false;
            
        }

        if (list->val != vals[idx++]) // list and array vals do not match
        {
            printf("list and array vals do not match\n");
            return false;
        }

        list = list->next;
        count--;
    }

    if (list != NULL) // reached end of array, but not end of list
    {
        printf("Reached end of array but not end of list\n");
        return false;
    }
    return true;
}

// Don't touch the line below or the automarker will fail to compile your program.
#ifndef __testing__

// Feel free to modify any part of the main function!
int main()
{
    int nums[10] = {-7, 9, -1, 10, -5, 3, 3, 10, 5, -30};
    NumNode *list = create_num_list(nums, 10);
    if (!check_num_list_order(list, nums, 10))
    {
        printf("The list returned by create_num_list() is not correct\n");
        return 1;
    }
    
    int nums1[1] = {5};
    NumNode *list1 = create_num_list(nums1, 1);
    if (!check_num_list_order(list1, nums1, 1))
    {
        printf("The list returned by create_num_list() is not correct (1)\n");
        return 1;
    }

    int nums2[9] = {500, 1, 10, 2, 50, 40, 3, 1000, 700};
    NumNode *list2 = create_num_list(nums2, 9);
    if (!check_num_list_order(list2, nums2, 9))
    {
        printf("The list returned by create_num_list() is not correct (2)\n");
        return 1;
    }



    NumNode *sorted_list = sort_num_list(list);
    int expected_nums[10] = {-30, -7, -5, -1, 3, 3, 5, 9, 10, 10};
    if (!check_num_list_order(sorted_list, expected_nums, 10))
    {
        printf("The list returned by sort_num_list() is not correct\n");
        return 1;
    }

    NumNode *sorted_list1 = sort_num_list(list1);
    int expected_nums1[1] = {5};
    if(!check_num_list_order(sorted_list1, expected_nums1, 1))
    {
        printf("The list returned by sort_num_list() is not correct (1)\n");
    }

    NumNode *sorted_list2 = sort_num_list(list2);
    int expected_nums2[10] = {1, 2, 3, 10, 40, 50, 500, 700, 1000};
    if(!check_num_list_order(sorted_list2, expected_nums2, 9))
    {
        printf("The list returned by sort_num_list() is not correct (2)\n");
    }

    delete_num_list(sorted_list);
    delete_num_list(sorted_list1);
    delete_num_list(sorted_list2);
    printf("End reached :)\n");
    return 0;
}

// You know the drill, don't remove this
#endif