#ifndef BSP_H
#define BSP_H

extern int eMAX_NODE;
extern int eSeed;
extern int devideL;
extern int devideR;

#include <stdlib.h>
#include <stdio.h>

typedef struct space {
    int x;
    int y;
    int width;
    int height;
} spaceType;

typedef struct spaceTree {
    spaceType space;
    struct spaceTree* left;
    struct spaceTree* right;
} SpaceTree;
SpaceTree* initBSP(int seed, int maxNode, int width, int height, int devideL, int devideR) {
    eSeed = seed;
    eMAX_NODE = maxNode;
    srand(eSeed);
    SpaceTree* root = (SpaceTree*)malloc(sizeof(SpaceTree));
    root->space.x = 0;
    root->space.y = 0;
    root->space.width = width;
    root->space.height = height;
    return root;
}





SpaceTree* divideSpace(SpaceTree* node, int n) {
    if (n == eMAX_NODE)
        return;
    node->left = (SpaceTree*)malloc(sizeof(SpaceTree));
    node->right = (SpaceTree*)malloc(sizeof(SpaceTree));
    if (node->space.width > node->space.height) {
        int divide = (rand() % (devideR - devideL) + devideL + 1)/10;

        node->left->space.x = node->space.x;
        node->right->space.x = node->space.x + divide;
        node->left->space.y = node->space.y;
        node->right->space.y = node->space.y;
        node->left->space.width = divide;
        node->right->space.width = node->space.width - divide;
        node->left->space.height = node->space.height;
        node->right->space.height = node->space.height;

    }
    else {
        int divide = (rand() % (devideR - devideL) + devideL + 1)/10;
        node->left->space.x = node->space.x;
        node->left->space.y = node->space.y;
        node->right->space.x = node->space.x;
        node->right->space.y = node->space.y + divide;
        node->left->space.height = divide;
        node->right->space.height = node->space.height - divide;
        node->left->space.width = node->space.width;
        node->right->space.width = node->space.width;
    }

    divideSpace(node->left, n + 1);
    divideSpace(node->right, n + 1);
    if(n == 0)
        return node;
}

#endif // !BSP_H