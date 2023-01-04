#include <criterion/criterion.h>
#include "cboxes/bst.h"

Test(test_bst, BST_Construct) {
    BST* bst = BST_ConstructD();
    BST* bst2 = BST_Construct(NULL);

    cr_expect(bst != NULL);
    cr_expect(bst2 != NULL);

    cr_expect(bst->root == NULL);
    cr_expect(bst2->root == NULL);

    cr_expect(bst->count == 0);
    cr_expect(bst2->count == 0);

    BST_Free(bst);
    BST_Free(bst2);
}
