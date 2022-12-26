#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// stockX representation

typedef struct sneakers_node
{
    char model[1024];
    char colour[1024];
    float price;
} sneaker;

typedef struct sneaker_BST_node
{
    sneaker *shoe;
    struct sneaker_BST_node *left;
    struct sneaker_BST_node *right;
} sneaker_BST;

sneaker_BST *create_BST_node()
{
    sneaker_BST *new_node = NULL;
    new_node = (sneaker_BST *)calloc(1, sizeof(sneaker_BST));
    sneaker *new_sneaker = NULL;
    new_sneaker = (sneaker *)calloc(1, sizeof(sneaker));
    new_node->shoe = new_sneaker;
    strcpy(new_node->shoe->colour, "");
    strcpy(new_node->shoe->model, "");
    new_node->shoe->price = 0.0;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

sneaker_BST *insert_into_BST(sneaker_BST *root, sneaker_BST *new_node) // in price lowest to highest sorted by price
{
    if (root == NULL) return new_node;
    if (new_node == NULL) return root;
    // setting key as price
    if (root->shoe->price >= new_node->shoe->price) root->left = insert_into_BST(root->left, new_node);

    else if (root->shoe->price < new_node->shoe->price) root->right = insert_into_BST(root->right, new_node);

    return root;
}

sneaker_BST *insertBST_ASCII(sneaker_BST *root, sneaker_BST *new_node)
{
    if (root == NULL) return new_node;
    if (new_node == NULL) return root;
    if (new_node == NULL && root == NULL) return NULL;

    if (strcmp(root->shoe->model, new_node->shoe->model) >= 0) root->left = insertBST_ASCII(root->left, new_node);
    else if (strcmp(root->shoe->model, new_node->shoe->model) < 0) root->right = insertBST_ASCII(root->right, new_node);

    return root;
}

sneaker_BST *search_for_shoe(sneaker_BST *root, char model[], float price)
{
    if (root == NULL) return root;

    if (root->shoe->price == price)
    {
        sneaker_BST *p = NULL;
        p = root;
        while (p != NULL)
        {
            if (strcmp(p->shoe->model, model) == 0 && p->shoe->price == price) return p;
            p = p->left;
        }
    }

    else if (root->shoe->price > price) return search_for_shoe(root->left, model, price);

    else if (root->shoe->price < price) return search_for_shoe(root->right, model, price);

    return root;
}

sneaker_BST *searchByASCII(sneaker_BST *root, char model[])
{
    if (root == NULL) return NULL;

    if (strcmp(root->shoe->model, model) == 0) return root;

    else if (strcmp(root->shoe->model, model) > 0) return searchByASCII(root->left, model);
    else if (strcmp(root->shoe->model, model) < 0) return searchByASCII(root->right, model);

    return NULL; // if returns NULL, model not found
}

sneaker_BST *delete_by_model(sneaker_BST *root, char model[])
{
    if (root == NULL) return NULL;

    if (strcmp(root->shoe->model, model) == 0)
    {
        sneaker_BST *p = NULL;
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }
        else if (root->left == NULL)
        {
            p = root->right;
            free(root);
            return p;
        }
        else if (root->right == NULL)
        {
            p = root->left;
            free(root);
            return p;
        }
        else // case c -> 2 children nodes on node we want to delete
        {
            p = root->right;
            while (p->left != NULL)
            {
                p = p->left;
            }
            strcpy(root->shoe->model, p->shoe->model);
            strcpy(root->shoe->colour, p->shoe->colour);
            root->shoe->price = p->shoe->price;
            //root->shoe->remaining = p->shoe->remaining;
            root->right = delete_by_model(root->right, p->shoe->model);
            return root;
        }
    }

    // traversing to actually find node first
    if (strcmp(root->shoe->model, model) > 0) root->left = delete_by_model(root->left, model);

    else if (strcmp(root->shoe->model, model) < 0) root->right = delete_by_model(root->right, model);

    return root;
}

void cleanUp(sneaker_BST *root)
{
    if (root == NULL) return;

    cleanUp(root->left);
    cleanUp(root->right);
    free(root);

    return;
}

void printInOrder(sneaker_BST *root)
{
    if (root == NULL) return;

    printInOrder(root->left);
    printf("Sneaker Model: %s\n", root->shoe->model);
    printInOrder(root->right);

    return;
}

void printSpecificSneaker(sneaker_BST *root, char model[])
{
    if (root == NULL) return;

    if (strcmp(root->shoe->model, model) == 0)
    {
        printf("Colour: %s\n", root->shoe->colour);
        printf("Price : %f\n", root->shoe->price);
        return;
    }
    else if (strcmp(root->shoe->model, model) > 0) printSpecificSneaker(root->left, model);

    else if (strcmp(root->shoe->model, model) > 0) printSpecificSneaker(root->right, model);

    return;
}



int main()
{
    int choice = 0;
    //int remaining;
    float price;
    char model[1024];
    char colour[1024];
    sneaker_BST *sneaker_node = NULL;
    sneaker_BST *root = NULL;

    while (choice != 5)
    {
        printf("Choose an option between 1-5\n");
        printf("(1) Insert Sneaker into list\n (2) Search for Shoe\n (3) Delete Specific Model\n (4) Print all shoes in database\n (5) Delete Data and Exit\n");
        scanf("%d", &choice);
        getchar();

        while (choice > 5 || choice < 1)
        {
            printf("Choose an option between 1-5\n");
            printf("(1) Insert Sneaker into list\n (2) Search for Shoe\n (3) Delete Specific Model\n (4) Print all shoes in database\n (5) Delete Data and Exit\n");
            scanf("%d", &choice);
            getchar();
        }
        
        if (choice == 1)
        {
            sneaker_node = create_BST_node();
            printf("Enter Price of Shoe\n");
            scanf("%f", &price);
            getchar();
            printf("Enter Shoe Model\n");
            fgets(model, 1024, stdin);
            printf("Enter Shoe Colour\n");
            fgets(colour, 1024, stdin);
            sneaker_node->shoe->price = price;
            strcpy(sneaker_node->shoe->model, model);
            strcpy(sneaker_node->shoe->colour, colour);
            root = insertBST_ASCII(root, sneaker_node);
        }
        else if (choice == 2)
        {
            printf("Enter Shoe Model\n");
            fgets(model, 1024, stdin);
            sneaker_node = searchByASCII(root, model);
            printf("Model: %s\n Price: %f\n, Colour: %s\n", sneaker_node->shoe->model, sneaker_node->shoe->price, sneaker_node->shoe->colour);
        }
        else if (choice == 3)
        {
            printf("Enter Shoe Model\n");
            fgets(model, 1024, stdin);
            root = delete_by_model(root, model);
        }
        else if (choice == 4)
        {
            printInOrder(root);
        }
        else
        {
            cleanUp(root);
            return 0;
        }
    }
    return 0;

}