#include "linked_list.h"

int main() {
    sll_node* head = sll_create_node(0);

    int       i    = 1;
    while (i <= 10) {
        sll_append(i, head);
        i++;
    }
    sll_print(head);

    // delete 8
    sll_delete_node(8, head);
    sll_print(head);

    // re-insert 8
    sll_insert_after(7, 8, head);
    sll_print(head);

    // delete 1
    sll_delete_first(head);
    sll_print(head);
    // re-insert 1;
    sll_insert_first(1, head);
    sll_print(head);

    // insert 10
    sll_append(10, head);
    sll_print(head);

    // I made findPrevioussll_node static so it is not visible outside
    // of this file insert 7 a 2nd time (after 6)
    /*sll_node* sevenPrev = findPrevioussingly_list_node(7, head);
    insertAftersll_node(sevenPrev, 7);
    sll_print(head);*/
}
