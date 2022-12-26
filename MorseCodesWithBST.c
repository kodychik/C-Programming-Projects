#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 1024

/**
 * Let's define a Morse Node which will contain a letter
 * and a right and a left pointer to another Node
 */
typedef struct morse_node_struct
{
  char letter;
  struct morse_node_struct *left;
  struct morse_node_struct *right;
} MorseNode;

/**
 * This function will initialize a Morse Node given a letter.
 *
 * ----------------------------------------------------------------------------
 * --- This function is already implemented for you. Nothing to change here ---
 * ----------------------------------------------------------------------------
 */
MorseNode *new_morse_node(char letter)
{

  // Create the pointer to a new node and allocate memory
  MorseNode *new_node = NULL;
  new_node = (MorseNode *)calloc(1, sizeof(MorseNode));

  // Initialize the node
  new_node->letter = letter;
  new_node->left = NULL;
  new_node->right = NULL;

  return new_node;
}

/**
 * This function will take the root of the Morse tree, a letter
 * and the morse code related to that letter.
 *
 * Insert the letter on the Morse tree based on its morse code.
 * Remember that the root node is empty (doesn't have any letter),
 * and that a dot indicates left and a dash indicates right.
 *
 * Note: All nodes may not have an associated character (for eg: the root).
 *       for these, set the associated character to '\0'.
 *
 * Note: Inserting a node for a letter may require you to create multiple
 *       other nodes or not create any and just update an existing one. Make
 *       sure you don't break any existing nodes for other letters!
 */
void insert_node(MorseNode *root, char *morse, char letter)
{
  /*
  if (root == NULL && *(morse) != '\0')
  {
    root = new_morse_node(0);
    return;
  }
  else if (root == NULL && *(morse) == '\0')
  {
    root = new_morse_node(letter);
    return;
  }
  else if (*(morse) == '\0')
  {
    root->letter = letter;
    return;
  }
  // iterate through binary tree and move left and right according to morse
  // ASCII '-' = 45, '.' = 46, '/' = 47, '0' = 48
  

  else if (*(morse) == '.')
  {
    insert_node(root->left, morse + 1, letter);
  }
  else if (*(morse) == '-')
  {
    insert_node(root->right, morse + 1, letter);
  }*/
  int i = 0;
  MorseNode *temp = NULL;
  temp = root;
  if (root == NULL)
  {
    root = new_morse_node(0);
  }
  while (*(morse + i) != '\0')
  {
    if (*(morse + i) == '.')
    {
      if (temp->left == NULL)
      {
        temp->left = new_morse_node(0);
      }
      temp = temp->left;
    }
    else if (*(morse + i) == '-')
    {
      if (temp->right == NULL)
      {
        temp->right = new_morse_node(0);
      }
      temp = temp->right;
    }
    i++;
  }
  temp->letter = letter;
 // TODO: insert (or update) the corresponding node for the letter.
}

void postOrderPrint(MorseNode *root)
{
  if (root == NULL) return;

  printf("%c\n", root->letter);
  postOrderPrint(root->left);
  postOrderPrint(root->right);
  
  return;
}

/**
 * This function will create a tree given an array of an alphabet and the
 * morse code relative to the alphabet.
 *
 * Use the insertNode function to create the Morse Tree and return the root.
 *
 * ----------------------------------------------------------------------------
 * --- This function is already implemented for you. Nothing to change here ---
 * ----------------------------------------------------------------------------
 */
MorseNode *make_tree(char **morse_code, char *abc)
{

  // Create a node that stores the char 0, which is an empty char
  MorseNode *root = new_morse_node(0);

  // The alphabet has 26 letters so we need to loop this many times
  // and insert each letter in the Morse Tree
  for (int i = 0; i < 26; i++)
  {
    insert_node(root, morse_code[i], abc[i]);
  }

  return root;
}

/**
 * This function will decode the morse code and store it in the text variable.
 *
 * Remember than the morse code can only include dots, dashes, spaces (' ') and
 * slashes ('/'). Spaces indicate the separation of letters and the slashes
 * indicate the separation of words.
 */
/*
char decodeTraversal(MorseNode *root, char *morse)
{
  if (*(morse) == '\0' || *(morse) == ' ') return root->letter;
  // text = root->letter; // text++ // return
  
  if (*(morse) == '.')
  {
    return decodeTraversal(root->left, morse + 1);
    // decodeTraversal not return (root->left, morse + 1, text)
  }
  else if (*(morse) == '-')
  {

    return decodeTraversal(root->right, morse + 1);
    // decode traversal not return (root->right, morse + 1, text)
  }
  else if (*(morse) == '/')
  {
    return ' ';
  }
  return NULL;
}
*/
void decode(MorseNode *root, char *morse, char *text)
{
  /*
  if (root == NULL) return;
  if (morse == '\0')
  {
    text = root->letter;
    return;
  }

  if (morse == '.')
  {
    decode(root->left, morse + 1, text);
  }
  else if (morse == '-')
  {
    decode(root->right, morse + 1, text);
  }
  else if (morse == ' ')
  {
    text = root->letter;
    decode(root, morse + 1, text + 1);
  }
  else if (morse == '/')
  {
    text = ' ';
    decode(root, morse + 1, text + 1);
  }
  int count = 0;

  *(text) = decodeTraversal(root, morse);
  count++;
  for (int i = 0; i < strlen(morse); i++)
  {
    if (*(morse + i) == ' ' || *(morse + i) == '\0')
    {
      *(text + count) = decodeTraversal(root, morse + i + 1);
      count++;
    }
  }*/
  MorseNode *temp = NULL;
  temp = root;
  int count = 0;
  int i = 0;

  while (*(morse + i) != '\0')
  {
    if (*(morse + i) == '.')
    {
      temp = temp->left;
    }
    else if (*(morse + i) == '-')
    {
      temp = temp->right;
    }
    else if (*(morse + i) == '/')
    {
      *(text + count) = ' ';
      count++;
      i++;
    }
    else if (*(morse + i) == ' ')
    {
      *(text + count) = temp->letter;
      count++;
      temp = root;
    }
    i++;
  }
  *(text + count) = temp->letter;
  *(text + count + 1) = '\0';

  // TODO: update `text` to have the decoded string
}

/**
 * This function will encode the text and store it in the morse variable.
 * This function also takes the morse_code array where you can get the morse
 * code related to each alphabet letter.
 *
 * Remember than the morse code can only include dots, dashes, spaces (' ')
 * and slashes ('/'). Spaces indicate the separation of letters and the
 * slashes indicate the separation of words.
 *
 * Note that it is easier here to just use the array containing the morse
 * code values, since we can get the correct code for every letter very fast
 * (figure out how!). The binary tree that was constructed is useful in
 * decoding the text!
 */
void encode(char **morse_code, char *text, char *morse)
{
  int i = 0;
  char ASCII;
  int j = 0;
  while (*(text + i) != '\0')
  {
    ASCII = *(text + i);
    if (*(text+i) == ' ')
    {
      *(morse + j) = '/';
      j++;
      *(morse + j) = ' ';
      j++;
      i++;
    }
    ASCII = *(text + i);
    ASCII = ASCII - 65;
    
    int count = 0;
    /*
    for (int j = 0; j < strlen(*(morse_code + ASCII)); j++)
    {
      morse + j = (morse_code + ASCII) + j;
      *(morse + j + 1) = '\0';
    }*/
    //strcat(morse, *(morse_code + ASCII));
    /*
    while (*(morse_code + ASCII) != '\0')
    {
      morse + j = *(morse_code + 1

      j++;
    }*/
    while (*(*(morse_code + (int)ASCII) + count) != '\0')
    {/*
      if (ASCII = ' ')
      {
        *(morse + j) = '/';
        j++;
        break;
      }*/
      (*(morse + j)) = (*(*(morse_code + (int)ASCII) + count));
      j++;
      count++;
    }
    *(morse + j) = ' ';
    j++;
    i++;
  }
  j--;
  *(morse + j) = '\0';
   // TODO: update `morse` to have the encoded string.
}

/*****************************************************************************/

#ifndef __testing__ // You know the drill, don't remove this

int main()
{
  // Create some space to store the morse and text
  char morse[MAX_STRING_LENGTH];
  char text[MAX_STRING_LENGTH];

  // Set up the alphabet, char array with null terminator at the end
  char abc[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  // Set up the morse code relative to the alphabet
  char *morse_code[26] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.",
                          "....", "..", ".---", "-.-", ".-..", "--", "-.",
                          "---", ".--.", "--.-", ".-.", "...", "-", "..-",
                          "...-", ".--", "-..-", "-.--", "--.."};

  // Create the Morse Tree
  MorseNode *tree = make_tree(morse_code, abc);


  // Encode "HELLO WORLD"
  encode(morse_code, "HELLO WORLD", morse);
  if (strcmp(morse, ".... . .-.. .-.. --- / .-- --- .-. .-.. -..") != 0)
  {
    printf("- encode() function result not correct:\n");
    printf("  expected: \".... . .-.. .-.. --- / .-- --- .-. .-.. -..\"\n");
    printf("     yours: \"%s\"\n", morse);
  }
  else
  {
    printf("- encode() passed the test.\n");
  }

  // Decode ".... . .-.. .-.. --- / .-- --- .-. .-.. -.."
  decode(tree, ".... . .-.. .-.. --- / .-- --- .-. .-.. -..", text);
  if (strcmp(text, "HELLO WORLD") != 0)
  {
    printf("- decode() function result not correct:\n");
    printf("  expected: \"HELLO WORLD\"\n");
    printf("     yours: \"%s\"\n", text);
  }
  else
  {
    printf("- decode() passed the test.\n");
  }

  char test_text[MAX_STRING_LENGTH];

  decode(tree, "/ / / / / .-", test_text);
  if (strcmp(test_text, "     A") == 0)
  {
    printf("decode() passed\n");
  }
  else printf("decode() failed\n");




  // TODO: Add tests to make sure your tree has the correct structure, we will
  //       test this when automarking, not just your encode() and decode().

  return 0;
}

#endif