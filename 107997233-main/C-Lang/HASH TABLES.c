// Hash tables

combine an array with a linked list

allowing us to go straight to a value

Only use hash tables if we dont care about data being sorted

hash table is a combination of a:

HASH FUCNTION:
return a non-negative interger value called a hash code


ARRAY:
Storing data of the type we want to place in the data structure


Take data, put it through the hash function then store it in the array location

int x = hash("John");
x is now 4
hashtable[x] = "John";
so if we ask for 4 it will return "John"

int x = hash("Paul");
x is now 6
hashtable[x] = "John";
so if we ask for 6 it will return "Paul"


DEFINE A HASH FUNCTION:
Use only the data being hashed
Use ALL of the data being hashed
Deterministic - every time we passt he same data in, we always get the same result (4)
Uniformly distribute data - Dont want everythign to return (0)


EXAMPLE OF A HASH FUNCTION:

unsigned int hash(char* str)
{
    int sum = 0; // declare int
    for (int j = 0; str[j] != '\0'; j++) // not equal to \0
    {
        sum += str[j]; // keep adding str[j] to sum
    }
    return sum % HASH_MAX // return some modulus of hash_max
}

USE THE INTERNET TO FIND GOOD HASH FUNCTIONS
just site your sources so people are attributed correctly

COLLISION -
two pieces of data run through the same hash function give the same hash code

how to preserve

LINEAR PROBING (Clustering):
Puts data in the next space after where the hash code was originally

hash("Bart"); returns 6;
hash("Lisa"); returns 6, BUT 6 is full so we move it to 7
hash("Homer"); returns 6, BUT 6 is full so we move it to 8

THIS loses the speed of a hash table making it as bad as a linear search


CHAINING:
What if every element of an array can hold multiple pieces of data
What if every element was a pointer to the head of a linked list!!!

This eliminates clustering.


string hashtable{10]; OLD METHOD

instead we use

node* hashtable[10];

so now

hash("Joey"); returns 6;

BUT a pointer points to the head of a linked list with a *next node pointer
