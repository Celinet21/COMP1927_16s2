#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "BST.h"


/* --------------- README --------------
 * These are the BST solutions!
 * Only look here once you've given up on the question.
 * That's the point where you're convinced that your fists or
 * face would probably write better code than your hands, no sooner
 */


// Tree struct you have to play with
struct tree {
  Tree right, left;
  int val;
};

/* 
 * Easy Questions 
 */
// Check if a value is in the tree
// Should return 1 if it finds it, otherwise 0
int findValue(Tree t, int v) {
  // Our base case, where t our tree is empty (NULL)
  if (t == NULL) return 0;

  // If we have our value in the current root we're looking at,
  // return 1
  if (t->val == v) {
    return 1;
  }

  // Otherwise, continue to look down the left and right children
  // Remember that an || in this case will yield 1 if either value
  // is 1, so if the left tree found the value, then we'd get:
  // (1 || 0) == 1
  return findValue(t->left, v) || findValue(t->right, v);
}


/*
 * Medium Questions
 */
/* 
   You are given a Tree (t), and two pointers.
   k is a pointer to the 'kth' smallest value you should go to
    E.g. for *k == 0, it should return the smallest value
         for *k == 4, it should return the 5th smallest value
   v is a pointer to an int pointer, the function should finish by pointing to the value
    E.g. You found the kth smallest value, there should be some code which says
         *v = &(t->val)
    Initially, v is set to point to NULL
  
    You can assume the tree is a BST with at least one element and no duplicates 
    and that 0 <= k < n where n is the number of nodes in the tree
*/
void getKthSmallest(Tree t, int* k, int** v) {
  // If the tree is empty, or we've found our value, return
  if (t == NULL || *v != NULL) {
    return;
  }

  // First, go down as far left as we can
  getKthSmallest(t->left, k, v);

  // The return will place us as far left as we can go
  // We use 'k' as a countdown to see if we've hit the kth smallest
  // value
  // In here we check if k == 0, if it is, we set our v
  if (*k <= 0 && *v == NULL) {
    *v = &(t->val);
  }
  // Next time we will meet the next smallest value, so decrement
  *k = *k - 1;

  // We have traversed down as far left as we can, go one step right,
  // then go down as far left as we can again (we start at the top of this
  // function)
  getKthSmallest(t->right, k, v);


  // Notice that this is just an infix operation
}

/* Find the lowest common ancestor between the noes with values v1 and v2.
   You are guaranteed that both these values exist in your BST
   The lowest common ancestor is defined as the first node which each of
   v1 and v2 share, as they go up the tree. I.e. the root of the whole tree is
   the highest common ancestor. For the following tree:
           
            4
          /   \
         2     7
        / \   /
       1   3 6
      /
     0 
   If v1 == 3, and v2 == 7, then their lowest common ancestor is 4
   If v1 == 3, and v2 == 0, then their lowest common ancestor is 2
*/
Tree lowestCommonAnc(Tree t, int v1, int v2) {
  // Keep in mind what information you have; the key here is that you have
  // a BST, and you are guaranteed that the nodes exist
  // There is no need to find the actual nodes

  // Base case
  if (t == NULL) return NULL;

  // Check to see where v1 and v2 lie relative to the current tree
  // We recurse down until they diverge
  if (t->val < v1 && t->val < v2) {
    return lowestCommonAnc(t->right, v1, v2);
  } else if (t->val > v1 && t->val > v2) {
    return lowestCommonAnc(t->left, v1, v2);
  }

  // If it failed both the above conditions, that means that v1 and v2
  // diverge down different branches, and we have found their lowest common
  // ancestor
  return t;
}


/*
 * Hard Questions
 */
// Check to see if the given tree is actually a BST
// The rule is that from some arbitrary root, the left child's value must be
// smaller than the root, and the right child bigger
// return 0 if it isn't a BST, 1 if it is
// You are guaranteed no duplicates

/*
 * This Question is going to require a helper function. Checking that all values
 * to the right and left of the current root is smaller is easy, but remembering
 * that ALL values under the left of the root must be smaller (converse for right)
 * is a bit more tricky. E.g.
 *        5
 *      /   \
 *     0     X
 *    / \
 *   X   6
 *
 *  Is an INVALID BST; somehow 6 is to the left of 5
 */

// What we do is keep track of our running min and max under each subtree
// For the above example, when exploring the 0 subtree, 5 is now our new 'max'
int isBSTHelper(Tree t, int* min, int* max) {
  // ez base case
  if (t == NULL) return 1;

  // We know t exists, we need to check that our current value is in between our min
  // and max, and NOT equal to either of them
  if (min != NULL && t->val <= *min) return 0;
  if (max != NULL && t->val >= *max) return 0;

  return isBSTHelper(t->left, min, &(t->val)) && isBSTHelper(t->right, &(t->val), max);
}

int isBST(Tree t) {
  // Pass it to the method, we use NULL/pointer things as checks, because we have no way
  // of knowing what range our values hold until we actually inspect them
  // I.e. we cannot pass -1 for example because the root might be == -1 straight off
  return isBSTHelper(t, NULL, NULL);
}


/*

   You can ignore these methods below, unless you want examples of using the tree

*/
Tree createTree() {
  return NULL;
}

Tree createNode(int v) {
  Tree t = malloc(sizeof(struct tree));
  t->val = v;
  t->right = NULL;
  t->left = NULL;

  return t;
}

void destroyTree(Tree t) {
  if (t == NULL) return;
  destroyTree(t->right);
  destroyTree(t->left);
  free(t);
}

Tree insert(Tree t, int v) {
  if (t == NULL) {
    t = createNode(v);
  } else {
    if (t->val < v) {
      t->right = insert(t->right, v);
    } else if (t->val > v) {
      t->left = insert(t->left, v);
    }
  }
  return t;
}

Tree randInsert(Tree t, int v) {
  if (t == NULL) {
    t = createNode(v);
  } else {
    if (rand() % 2) {
      t->right = randInsert(t->right, v);
    } else {
      t->left = randInsert(t->left, v);
    }
  }
  return t;
}

// Insert in shorted path possible place
Tree inOrderInsert(Tree t, int v) {

  // Base cases
  if (t == NULL) {
    return createNode(v);
  }

  // Max possible height we'll deal with is 6
  Tree Q[64] = {};
  Tree temp[64] = {};

  // Current depth in Q
  int p = 0;
  int walk = 0;


  Q[0] = t;

  // For each level
  for (p = 0; p < 6; ++p) {

    // Walk over each node in the current level
    for (walk = 0; walk < (1 << p); ++walk) {

      // If we found a node with an empty child
      if (Q[walk]->left == NULL) {
        Q[walk]->left = createNode(v);
        return t;
      }
      if (Q[walk]->right == NULL) {
        Q[walk]->right = createNode(v);
        return t;
      }

      temp[walk * 2] = Q[walk]->left;
      temp[walk * 2 + 1] = Q[walk]->right;
    }
    memcpy(Q, temp, sizeof(Tree) * 64);
  }

  // We never found an empty position
  return t;
}

int getRootVal(Tree t) {
  assert(t != NULL);
  return t->val;
}

Tree buildTree(Tree t, int* vals, int n, Tree (*insertF)(Tree, int)) {
  int i = 0;
  for (i = 0; i < n; ++i) {
    t = insertF(t, vals[i]);
  }
  return t;
}

