CREATING A LINKED LIST

typedef struct node
{
    string phrase;
    struct node *next;
}
node
}


node *list = NULL;

Create a new NODE and add the first piece of data

node *n = malloc(sizeof(node)); // Allocate memory
n->phrase = "Hi!"; // Assign data to the node (phrase)
n->next = NULL; // Assign data to the Node (next)
list = n; // Points the list to the node (n)

n = malloc(sizeof(node));
n->phrase = "Hey!";
n->next = list;     // make sure new node is pointing to the beginning of e the structure
                    //other wise it could take a long time to find the end of the list
list = n; //now include the orinal node


EXAMPLE


typedef struct node
{
    string phrase;
    struct node *next;
}
node;

#define LIST_SIZE 2

void unload(node *lsit);
void visualize(node *list);

int main(void)
{
    node *list = NULL;

    // Add items to list
    for (int i = 0; i < LIST_SIZE; i++)
    {
        string phrase = get_string("Enter a new Phrase: ");

        // TODO: add prase to a new node in list
        node *n = malloc(sizeof(node)); // Create a node pointer *n. Size of determines how much memory to allocate
        // check that the memory is actually given to us and has been allocated
        if (n == NULL)
        {
            printf("Coun't allocate memory for node\n");
            return 1;
        }
        n->phrase = phrase;
        n->next = list; // Next pointer must be the head of the list not NULL

        list = n; // Update the list to have the newest node at the beginning

// THE ABOVE CODE ALLOCATES MEMORY TO A NODE POINTER CALLED N
// CHECK IF THE MEMORY HAS BEEN ALLOCATED AND IS NOT NULL
// IT THEN PUTS THE PHASE FROM THE STRING ABOVE INTO THE NODE
// IT THEN POINTS THE NEXT NODE TO THE HEAD OF THE LIST (NOT THE TAIL)
// IT THEN MAKES THE LIST EQUAL TO THE NODE THAT WAS JUST CREATED

//NOT RECURRSION BUT IT IS A RECURSIVE FUNCTION


    unload(list);
}

void unload(node *list)
{
    // TODO: Free all allocated nodes
    //CANNOT JUST FREE THE LIST BECAUSE IT WILL LOSE ITS LINK TO THE NEXT NODES

    while (list != NULL) // Keep doing this until the list is NULL
    {
        node *ptr = list->next; // Creates a pointer to the next node
        free(list); // Can do this because we have a pointer to the next node
        list = ptr; //
    }
}



HASH TABLES - HOW TO MAKE THIS FASTER




node *table[26] ; // New array pointer with 26 places

int hash(string phrase)

int main(void)
{
    for (int i = 0; i < 3;, i++)
    {
        string phrase = get_string("Enter a new phrase: ");
        int index = hash(phrase);
        printf("%s hashes to %i\n", phrase, index);
    }
}


// TODO: return an index, 0-25 for a given phrase
int hash(string phrase)
{
    return toupper(phrase[0]) - 'A'; // Dont return 0, instead return an array index
    // Make uppercase to hash the same value otherwise a would return 39 which is outside of 0-25
    // BUT add - 'A' because A is equal to ASCII 65
    // A = 65
    // So for Hello: 72 - 65 = 7 which is H in the array index table
    // A - A = 0
    // B - A = 1
}



