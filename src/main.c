#include <stdio.h>
#include <stdlib.h>

#include "list.h"

void List_PrintItems(List* list) {
    printf("List[%lu]:\n", list->length);
    for (int i = 0; i < list->length; i++) {
        Node* node;
        if (List_Get(list, i, &node) != LIST_OK) {
            break;
        }
        printf("[%d]: %d\n", i, *(int*)node->value);
    }
}

int main() {
    List* list = List_Construct();

    for (int i = 0; i < 10; i++) {
        List_PushBack(list, &i, sizeof(int));
    }
    List_PrintItems(list);

    printf("\nPushing to front 10\n");
    int x = 10;
    List_PushFront(list, &x, sizeof(int));
    List_PrintItems(list);

    printf("\nInserting 20 to 3 index\n");
    int y = 20;
    List_Insert(list, 3, &y, sizeof(int));
    List_PrintItems(list);

    printf("\nPopping node at 2 index\n");
    Node* node;
    List_Pop(list, 2, &node);
    printf("%d\n", *(int*)node->value);
    List_PrintItems(list);

    printf("\nFree 4 index\n");
    List_Free(list, 4);
    List_PrintItems(list);

    List_Clear(list);
    printf("\n");
    List_PrintItems(list);
    printf("%d\n", x);
    return 0;
}

