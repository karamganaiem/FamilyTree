#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define VALIDAGE 18

typedef struct Node {
    struct Humanbeing *person;
    struct Node *next;
} Node;

typedef struct Allhumans {
    Node *data;
    unsigned int humansAmount;
} Allhumans;

typedef struct Humanbeing {
    char *name;
    unsigned int age;
    int flagForVisit;
    struct Humanbeing *dad;
    struct Humanbeing *mom;
    struct Humanbeing *partner;
    Node *sons;
} Humanbeing;


void print_menu();

char *scan_string();

void do_option1(Allhumans *humansData);

void do_option2(Allhumans *humansData);

void do_option3(Allhumans *humansData);

void do_option4(Allhumans *humansData);

void do_option5(Allhumans *humansData);

void do_option6(Allhumans *humansData);

void do_option7(Allhumans *humansData);

Allhumans *compile_structs();

void clear_data(Allhumans *humansData);

int if_name_exists(Allhumans *humansData, char *headName);

void add_human(Allhumans *humansData, char *headName, unsigned int
headAge);

void connect_couple(Allhumans *humansData, char *firstParent, char *
secondParent);

int check_marraige(Allhumans *humansData, char *humanName);

int check_age_validation(Allhumans *humansData, char *humanName);

Node *find_person_node(Allhumans *humansData, char *humanName);

Humanbeing *find_person_struct(Allhumans *humansData, char *humanName);

int check_couple_marrige(Allhumans *humansData, char *firstParent, char *
secondParent);

int check_common_dad(Allhumans *humansData, char *firstParent,
                     char *secondParent);

void add_child(Allhumans *humansData, char *childName, char *firstParent, char
*secondParent);

void connect_parent_child(Allhumans *humansData, char *currentParent, char *
childName);

void print_family(Allhumans *humansData, char *humanName, unsigned int
tabCounter);

void reset_flags(Allhumans *humansData);

void pass_the_time(Allhumans *humansData, unsigned int amountOfyears);

Node *link_lists(Node *list1, Node *list2);

Node *create_node(Humanbeing *humanStruct);

Node *find_degree_parents(Humanbeing *humanStruct, int degreeLevel);

Node *find_degree_sons(Humanbeing *humanStruct, int degreeLevel);

void sort_names(Node *allSonsList);

void free_list(Node* sonsList);

void print_cousins(Allhumans *humansData, char *humanName, int degreeLevel);

int main() {
    Allhumans *HumansData = compile_structs();
    char MenuInput;
    do {
        // printTheTestNumberDeleteMe();
        print_menu();
        //we scan the input from the user
        scanf(" %c", &MenuInput);
        //we switch to options
        switch (MenuInput) {
            case '0':
                //user inputs zero,clean data structures and terminate
                clear_data(HumansData);
                return 0;
                // does the supposed function for the given input
            case '1':
                do_option1(HumansData);
                break;
            case '2':
                do_option2(HumansData);
                break;
            case '3':
                do_option3(HumansData);
                break;
            case '4':
                do_option4(HumansData);
                break;
            case '5':
                do_option5(HumansData);
                break;
            case '6':
                do_option6(HumansData);
                break;
            case '7':
                do_option7(HumansData);
                break;
            default:
                //if the user inputs invalid option we print:
                printf("Invalid option\n");
                break;
        }
    } while (MenuInput != '0');
    return 0;
}

/**
 * this function prints out the main menu
 * */
void print_menu() {
    //We print the main menu
    printf("Choose an option:\n"
           "0. Exit\n"
           "1. Add a head\n"
           "2. Marry two people\n"
           "3. New offspring\n"
           "4. Print family top-down\n"
           "5. Years pass\n"
           "6. Count people\n"
           "7. Print cousins\n");
}

/**
 * @brief Scan a string input from the user.
 *
 * reads a string input from the user until a newline character is encountered.
 *
 * @return A dynamically allocated string containing the user's input.
 */
char *scan_string() {
    // Allocate initial memory
    char *fullName = (char *) malloc(sizeof(char));
    int index = 0;
    char input;
    scanf(" %c", &input);

    // Read characters until newline is encountered
    while (input != '\n') {
        fullName[index] = input;
        // Reallocate memory to accommodate the new character
        fullName = (char *) realloc(fullName, index + 2);
        // Read the next character
        scanf("%c", &input);
        index++;
    }
    // Add null terminator at the end of the string
    fullName[index] = '\0';
    return fullName;
}

/**
 * @brief Creates and initializes an Allhumans structure.
 *
 * @return A pointer to the newly created Allhumans structure.
 */
Allhumans *compile_structs() {
    // Allocate memory for the Allhumans structure
    Allhumans *humansData = (Allhumans *) malloc(sizeof(Allhumans));

    // Initialize the data and humansAmount fields
    humansData->data = NULL;
    humansData->humansAmount = 0;

    // Return the pointer to the created Allhumans structure
    return humansData;
}

/**
 * @brief Clears the data in the Allhumans structure.
 *
 * This function cleans up the nodes in the linked list of the Allhumans
 * structure and resets the humansAmount to 0.
 *
 * @param humansData Pointer to the Allhumans structure.
 */
void clear_data(Allhumans *humansData) {
    // Clean up nodes in the linked list
    Node *current = humansData->data;
    while (current != NULL) {
        Node *next = current->next;
        free(current->person->name);
        free(current->person);
        free(current);
        current = next;
    }
    // Set the linked list data to NULL and humansAmount to 0
    humansData->data = NULL;
    humansData->humansAmount = 0;
}

/**
 * @brief Performs option 1: Adding a new human to the Allhumans structure.
 *
 * This function prompts the user to enter a name and age for the new human.
 * It checks if the entered name already exists Otherwise, it adds a new human
 * structure using the add_human function.
 *
 * @param humansData Pointer to the Allhumans structure.
 */
void do_option1(Allhumans *humansData) {
    printf("Enter a name:\n");
    // Prompts the user to enter a name and scans it as a string
    char *headName = scan_string();

    printf("Enter age:\n");
    unsigned int headAge;
    // Prompts the user to enter an age and scans it as an unsigned integer
    scanf(" %u", &headAge);

    //Checks if the entered name already exists in the Allhumans structure
    if (if_name_exists(humansData, headName) == 1) {
        printf("The name is already taken\n");
        // Exits the function if the name is already taken
        return;
    } else {
        // Adds a new human with the entered name and age to the Allhumans
        // structure using the add_human function
        add_human(humansData, headName, headAge);
    }
}

/**
 * @brief option 2: Marriage between two persons in the Allhumans structure.
 *
 * This function prompts the user to enter the names of the first and second
 * person for marriage, If any of the conditions for a valid marriage is not
 * satisfied, it prints an appropriate error message and returns. If all the
 * conditions are met,it connects the couple with the function connect_couple
 *
 * @param humansData Pointer to the Allhumans structure.
 */
void do_option2(Allhumans *humansData) {
    printf("Enter the name of the first person:\n");
    char *firstHuman = scan_string();

    printf("Enter the name of the second person:\n");
    char *secondHuman = scan_string();

    // Check if people exist in the Allhumans structure
    if ((if_name_exists(humansData, firstHuman) == 0) ||
        (if_name_exists(humansData, secondHuman) == 0)) {
        printf("One of the persons does not exist\n");
        return;
    }

    // Check if one already married
    if ((check_marraige(humansData, firstHuman) == 1) ||
        (check_marraige(humansData, secondHuman) == 1)) {
        printf("Invalid marriage\n");
        return;
    }

    // Check if the ages are valid
    if ((check_age_validation(humansData, firstHuman) == 0) ||
        (check_age_validation(humansData, secondHuman) == 0)) {
        printf("Invalid marriage\n");
        return;
    }

    // Check if they have the same old father
    if (check_common_dad(humansData, firstHuman, secondHuman) == 1) {
        printf("Invalid marriage\n");
        return;
    }

    // Add them to the data struct
    connect_couple(humansData, firstHuman, secondHuman);
    printf("%s and %s are now married\n", firstHuman, secondHuman);
}

/**
 * @brief Performs option 3:Adding a child to parents in the Allhumans structure
 *
 * This function prompts the user to enter the names of the first parent,second
 * parent, and the child. If any of the conditions is not satisfied, it returns.
 * If all the conditions are satisfied, it adds the child to the data structure
 * using the add_child function and connects the child to the parents using
 * the connect_parent_child function.
 *
 * @param humansData Pointer to the Allhumans structure.
 */
void do_option3(Allhumans *humansData) {
    printf("Enter the name of the first parent:\n");
    // Prompts the name of the first parent from the user.
    char *firstParent = scan_string();

    printf("Enter the name of the second parent:\n");
    // Prompts the name of the second parent from the user.
    char *secondParent = scan_string();

    printf("Enter offspring's name:\n");
    // Prompts the name of the child from the user.
    char *childName = scan_string();

    // Check if one of the parents does not exist
    if ((if_name_exists(humansData, firstParent) == 0) ||
        (if_name_exists(humansData, secondParent) == 0)) {
        printf("One of the parents does not exist\n");
        return;
    }

    // Check if the parents are already married
    if (check_couple_marrige(humansData, firstParent, secondParent) == 0) {
        printf("The parents are not married\n");
        return;
    }

    // Check if the child's name is already taken
    if (if_name_exists(humansData, childName) == 1) {
        printf("The name is already taken\n");
        return;
    }
    // Add the child to the data structure
    add_child(humansData, childName, firstParent, secondParent);

    // Connect the child to the parents
    connect_parent_child(humansData, firstParent, childName);
    connect_parent_child(humansData, secondParent, childName);
    printf("%s was born\n", childName);
}

/**
 * @brief Performs option 4: Print the family tree of a person top to down.
 *
 * This function prompts the user to enter the name of a person. If the
 * person exists, it prints the family tree of the person using the print_family
 * function. The tabCounter variable is used to keep track of the indentation
 * level while printing the family tree. After printing the family tree, it
 * resets the flags in the Allhumans structure using the reset_flags function.
 *
 * @param[in,out] humansData Pointer to the Allhumans structure.
 */
void do_option4(Allhumans *humansData) {
    // Counter for indentation level
    unsigned int tabCounter = 0;

    printf("Enter the name of the person:\n");
    // Name of the person from the user
    char *humanName = scan_string();

    // Check if the person exists
    if (if_name_exists(humansData, humanName) == 0) {
        printf("The person does not exist\n");
        // Return from the function if the person does not exist
        return;
    }
    // Print the family tree of the person
    print_family(humansData, humanName, tabCounter);

    // Reset flags for the printing in the Allhumans structure
    reset_flags(humansData);
}

/**
 * @brief Performs option 5:Pass the number of years in the Allhumans structure.
 *
 * This function prompts the user to enter the number of years. Then, it
 * passes the specified number of years in the Allhumans structure using the
 * pass_the_time function.
 *
 * @param humansData Pointer to the Allhumans structure.
 */
void do_option5(Allhumans *humansData) {
    printf("Enter number of years:\n");
    // Number of years to pass
    unsigned int amountOfYears;

    // Read the input from the user for the amount of years to pass
    scanf(" %u", &amountOfYears);

    // Pass the specified number of years in the Allhumans structure
    pass_the_time(humansData, amountOfYears);
}

/**
 * @brief Performs option 6: Display the number of people in the Allhumans
 * structure.
 *
 * checks the number of people stored in the Allhumans structure. If the
 * number of people is 1, it prints a message indicating that there is one
 * person. Otherwise, it prints a message indicating the total number of people.
 *
 * @param humansData Pointer to the Allhumans structure.
 */
void do_option6(Allhumans *humansData) {
    // Check the number of people in the Allhumans structure
    if (humansData->humansAmount == 1) {
        // Print message if there is one person
        printf("There is one person\n");
    } else {
        // Print message with the total number of people
        printf("There are %d people\n", humansData->humansAmount);
    }
}

/**
 * @brief Performs option 7: Print cousins of a person up to the specified
 * degree in the Allhumans structure.
 *
 * This function prompts the user to enter the name of a person and the
 * degree level. If the degree level is 0, it prints
 * the person's name and returns from the function.  If the degree level is
 * greater than 0, it prints the header for the cousins and proceeds to find
 *  and print the cousins of the person up to the specified degree using the
 * `print_cousins` function. The `reset_flags` function is called before
 * finding cousins to reset any previously set flags in the Allhumans structure.
 *
 * @param humansData Pointer to the Allhumans structure.
 */
void do_option7(Allhumans *humansData) {
    printf("Enter the name of the person:\n");
    // prompt the name od the person from the user
    char *humanName = scan_string();

    printf("Enter degree:\n");
    int degreeLevel;
    // Read the degree level input from the user
    scanf(" %d", &degreeLevel);

    // Check if the person exists
    if (if_name_exists(humansData, humanName) == 0) {
        printf("The person does not exist\n");
        // Return from the function if the person does not exist
        return;
    }

    // Check the degree level
    if (degreeLevel == 0) {
        // Print the person's name if the degree level is 0
        printf("%s\n", humanName);
        return;
    } else {
        printf("Cousins:\n");
        // Reset any previously set flags
        reset_flags(humansData);

        // Find and print cousins up to the specified degree
        print_cousins(humansData, humanName, degreeLevel);
    }
}

/**
 * @brief Checks if a person exists in the Allhumans structure.
 *
 * This function traverses the linked list of humans in the Allhumans
 * structure  and compares the name of each person with the specified name. If
 * a match is found, it returns 1 indicating that the person already exists
 * in the list. If no match is found after traversing the entire list, it
 * returns 0 indicating that the person does not exist in the list.
 *
 * @param humansData Pointer to the Allhumans structure.
 * @param headName Name of the person to check.
 *
 * @return 1 if the person exists, 0 otherwise.
 */
int if_name_exists(Allhumans *humansData, char *headName) {
    // Pointer to the current first human in the list
    Node *currentHuman = humansData->data;

    if (currentHuman == NULL) {
        // Human not found in the list
        return 0;
    }

    // Traverse the linked list of humans
    while (currentHuman != NULL) {
        if (strcmp(currentHuman->person->name, headName) == 0) {
            // Name matches, human is already in the list
            return 1;
        }
        // Move to the next human in the list
        currentHuman = currentHuman->next;
    }

    // Human not found in the list
    return 0;
}

/**
 * @brief Adds a new human to the Allhumans structure.
 *
 * This function creates a new Node and Humanbeing structure to represent the
 * new human. It assigns the provided name and age to the human, initializes
 * other fields to default values, and adds the human to the Allhumans
 * structure by appending it to the linked list.
 *
 * @param humansData Pointer to the Allhumans structure.
 * @param headName Name of the new human.
 * @param headAge Age of the new human.
 */
void add_human(Allhumans *humansData, char *headName, unsigned int headAge) {
    // check if the list of the HumansData is empty
    if (humansData->data == NULL) {
        humansData->data = (Node *) malloc(sizeof(Node));
        humansData->data->person = (Humanbeing *) malloc(sizeof(Humanbeing));

        // Allocate memory for the name and copy the contents
        humansData->data->person->name = (char *) malloc(strlen(headName) + 1);
        strcpy(humansData->data->person->name, headName);

        // Assign other fields of the Humanbeing structure
        humansData->data->person->age = headAge;
        humansData->data->person->flagForVisit = 0;
        humansData->data->person->dad = NULL;
        humansData->data->person->mom = NULL;
        humansData->data->person->partner = NULL;
        humansData->data->person->sons = NULL;
        humansData->data->next = NULL;
    } else {
        // traverse through the linked list until we find the last person
        Node *currentHuman = humansData->data;
        while (currentHuman->next != NULL) {
            currentHuman = currentHuman->next;
        }
        currentHuman->next = (Node *) malloc(sizeof(Node));
        currentHuman->next->person = (Humanbeing *) malloc(sizeof(Humanbeing));

        // Allocate memory for the name and copy the contents
        currentHuman->next->person->name = (char *) malloc(
                strlen(headName) + 1);
        strcpy(currentHuman->next->person->name, headName);

        // Assign other fields of the Humanbeing structure
        currentHuman->next->person->age = headAge;
        currentHuman->next->person->flagForVisit = 0;
        currentHuman->next->person->dad = NULL;
        currentHuman->next->person->mom = NULL;
        currentHuman->next->person->partner = NULL;
        currentHuman->next->person->sons = NULL;
        currentHuman->next->next = NULL;
    }

    //We increase the amount of humansAmount by one, for adding a new person.
    humansData->humansAmount = humansData->humansAmount + 1;
}

/**
 * @brief Checks if a person is married.
 *
 * This function searches for a person with the specified name in the
 * Allhumans  structure. If the person is found and they have a non-null
 * partner, it indicates that they are married.
 *
 * @param humansData Pointer to the Allhumans structure.
 * @param humanName Name of the person to check.
 *
 * @return Returns 1 if the person is married, 0 otherwise.
 */
int check_marraige(Allhumans *humansData, char *humanName) {
    Node *currentHuman = humansData->data;

    // Traverse the linked list of humans
    while (currentHuman != NULL) {
        // Check if the current human's name matches the specified name
        if (strcmp(currentHuman->person->name, humanName) == 0) {
            // Check if the current human has a partner
            if (currentHuman->person->partner == NULL) {
                // The person is not married
                return 0;
            }
            // The person is married
            return 1;
        }
        // Move to the next human in the linked list
        currentHuman = currentHuman->next;
    }

    // The person was not found in the linked list, so they are not married
    return 0;
}

/**
 * @brief Checks if a person's age is valid for marriage.
 *
 * This function searches for a person with the specified name in the
 * Allhumans  structure. If the person is found and their age is greater than
 * or equal to a valid age threshold, it indicates that their age is valid.
 *
 * @param humansData Pointer to the Allhumans structure.
 * @param humanName Name of the person to check.
 *
 * @return Returns 1 if the person's age is valid, 0 otherwise.
 */
int check_age_validation(Allhumans *humansData, char *humanName) {
    Node *currentHuman = humansData->data;

    // Traverse through the linked list
    while (currentHuman != NULL) {
        // checks if this is the human we are looking for
        if (strcmp(currentHuman->person->name, humanName) == 0) {
            if (currentHuman->person->age >= VALIDAGE) {
                // The person's age is valid
                return 1;
            }
            // The person's age is not valid
            return 0;
        }
        currentHuman = currentHuman->next;
    }

    // The person was not found in the linked list.
    return 0;
}

/**
 * @brief Finds the node containing information about a person with the name.
 *
 * This function searches for a person with the specified name in the
 * Allhumans structure and returns the node containing information for a person.
 *
 * @param humansData Pointer to the Allhumans structure.
 * @param humanName Name of the person to find.
 *
 * @return Returns a pointer to the node containing information about the
 * person, or NULL if not found.
 */
Node *find_person_node(Allhumans *humansData, char *humanName) {
    Node *currentNode = humansData->data;

    // Traverse through the linked list
    while (currentNode != NULL) {
        if (strcmp(currentNode->person->name, humanName) == 0) {
            // Person found, return the corresponding node
            return currentNode;
        }
        //move to the next Node in the data structure.
        currentNode = currentNode->next;
    }
    // Person not found
    return NULL;
}

/**
 * @brief Connects a couple by assigning each person as the partner of the other
 *
 * connects a couple by assigning each person as the partner of the other. It
 * searches for the nodes containing information about the first and second
 * parent in the data structure, and assigns the corresponding partner pointers.
 *
 * @param humansData Pointer to the Allhumans structure.
 * @param firstParent Name of the first parent.
 * @param secondParent Name of the second parent.
 */
void connect_couple(Allhumans *humansData, char *firstParent, char
*secondParent) {

    // Find the first parent and assign the second parent as their partner
    Node *firstOfCouple = humansData->data;
    while (firstOfCouple != NULL) {
        // checks if this is the right person
        if (strcmp(firstOfCouple->person->name, firstParent) == 0) {
            Humanbeing *current = find_person_struct(humansData, secondParent);
            // Assign the second parent as the partner of the first parent
            firstOfCouple->person->partner = current;
        }
        //move to the next node
        firstOfCouple = firstOfCouple->next;
    }

    // Find the second parent and assign the first parent as their partner
    Node *secondOfCouple = humansData->data;
    while (secondOfCouple != NULL) {
        // checks if this is the right person
        if (strcmp(secondOfCouple->person->name, secondParent) == 0) {
            Humanbeing *current = find_person_struct(humansData, firstParent);
            // Assign the first parent as the partner of the second parent
            secondOfCouple->person->partner = current;
        }
        //move to the next node
        secondOfCouple = secondOfCouple->next;
    }
}

/**
 * @brief Checks if two parents are married to each other.
 *
 * This function checks if the given first parent and second parent are
 * married to each other.
 *
 * @param humansData Pointer to the Allhumans structure containing the data.
 * @param firstParent Name of the first parent to check.
 * @param secondParent Name of the second parent to check.
 *
 * @return Returns 1 if the parents are married to each other, 0 otherwise.
 */
int check_couple_marrige(Allhumans *humansData, char *firstParent, char
*secondParent) {
    // temp1 temp2 are the person structs of the parents
    Humanbeing *temp1 = find_person_struct(humansData, firstParent);
    Humanbeing *temp2 = find_person_struct(humansData, secondParent);

    //checks if The parents are married to each other
    if ((temp1->partner == temp2) && (temp2->partner == temp1)) {
        //return 1 if they are married
        return 1;
    }
    // The parents are not married to each other
    return 0;
}

/**
 * @brief Connects a parent with a child in the family tree.
 *
 * This function establishes a connection between a parent and a child in the
 * provided Allhumans data structure. It creates a new node for the child and
 * appends it to the list of children of the specified parent.
 *
 * @param humansData Pointer to the Allhumans structure.
 * @param currentParent Name of the current parent.
 * @param childName Name of the child to be connected.
 */
void connect_parent_child(Allhumans *humansData, char *currentParent, char *
childName) {
    // Find the current parent in the data structure
    Node *current = find_person_node(humansData, currentParent);

    // Create a new node for the child and assign the child's information
    Node *newChildNode = (Node *) malloc(sizeof(Node));
    newChildNode->person = find_person_struct(humansData, childName);
    newChildNode->next = NULL;

    // Connect the child to the parent
    if (current->person->sons == NULL) {
        // If the parent has no existing children, assign the new child as
        // the first child
        current->person->sons = newChildNode;
    } else {
        // If the parent already has children, find the last child and append
        // the new child
        Node *currentChild = current->person->sons;
        while (currentChild->next != NULL) {
            currentChild = currentChild->next;
        }
        currentChild->next = newChildNode;
    }
}

/**
 * @brief Checks if two individuals have a common father or share a common
 * ancestor in the family tree.
 *
 * This function determines whether two individuals in the family tree have
 * a common father or if they share a common ancestor. It traverses the
 * family tree upwards from each parent's ancestors to check for a common
 * father or shared ancestor.
 *
 * @param humansData Pointer to the data structure containing all humans.
 * @param firstParent Name of the first parent.
 * @param secondParent Name of the second parent.
 *
 * @return Returns 1 if there is a common father or shared ancestor, 0 otherwise.
 */
int check_common_dad(Allhumans *humansData, char *firstParent,
                     char *secondParent) {
    // Find the structure of the first parent
    Humanbeing *fisrtParentStruct = find_person_struct(humansData, firstParent);
    // Find the structure of the second parent
    Humanbeing *secondParentStruct =find_person_struct(humansData,secondParent);

    // Get the father structures of both parents
    Humanbeing *parent1Dad = fisrtParentStruct->dad;
    Humanbeing *parent2Dad = secondParentStruct->dad;

    // Traverse the family tree upwards from firstParent's ancestors
    while (parent1Dad != NULL) {
        Humanbeing *current = parent2Dad;
        // Check if parent2Dad is equal to or an ancestor of parent1Dad
        while (current != NULL) {
            if (strcmp(current->name, parent1Dad->name) == 0) {
                // Common ancestor found
                return 1;
            }
            current = current->dad;
        }
        parent1Dad = parent1Dad->dad;
    }

    // Traverse the family tree upwards from secondParent's ancestors
    while (parent2Dad != NULL) {
        Humanbeing *current = parent1Dad;
        // Check if parent2Dad is equal to or an ancestor of parent1Dad
        while (current != NULL) {
            if (strcmp(current->name, parent2Dad->name) == 0) {
                // Common ancestor found
                return 1;
            }
            current = current->dad;
        }
        parent2Dad = parent2Dad->dad;
    }
    // No common ancestor found
    return 0;
}

/**
 * @brief Adds a new child to the family tree with the specified parents.
 *
 * This function adds a new child to the family tree by creating a new node
 * in the data structure.  The child's name, age, parents, and other
 * attributes are set accordingly. If the data structure is empty, the new
 * child becomes the first node. Otherwise, it is appended to the end of the
 * existing nodes.
 *
 * @param humansData Pointer to the data structure containing all humans.
 * @param childName Name of the child to be added.
 * @param firstParent Name of the first parent.
 * @param secondParent Name of the second parent.
 */
void add_child(Allhumans *humansData, char *childName, char *firstParent,
               char *secondParent) {
    if (humansData->data == NULL) {
        // Create the first node if the data structure is empty
        humansData->data = (Node *) malloc(sizeof(Node));
        humansData->data->person = (Humanbeing *) malloc(sizeof(Humanbeing));

        // assign all the feilds with the right parameters
        humansData->data->person->name = childName;
        humansData->data->person->age = 0;
        humansData->data->person->dad = find_person_struct(humansData,
                                                           firstParent);
        humansData->data->person->mom = find_person_struct(humansData,
                                                           secondParent);
        humansData->data->person->flagForVisit = 0;
        humansData->data->person->partner = NULL;
        humansData->data->person->sons = NULL;
        humansData->data->next = NULL;
    } else {
        // Append the new child to the end of the existing nodes
        Node *currentHuman = humansData->data;
        while (currentHuman->next != NULL) {
            currentHuman = currentHuman->next;
        }
        currentHuman->next = (Node *) malloc(sizeof(Node));
        currentHuman->next->person = (Humanbeing *) malloc(sizeof(Humanbeing));

        // assign all the feilds with the right parameters
        currentHuman->next->person->name = childName;
        currentHuman->next->person->age = 0;
        currentHuman->next->person->dad = find_person_struct(humansData,
                                                             firstParent);
        currentHuman->next->person->mom = find_person_struct(humansData,
                                                             secondParent);
        currentHuman->next->person->flagForVisit = 0;
        currentHuman->next->person->partner = NULL;
        currentHuman->next->person->sons = NULL;
        currentHuman->next->next = NULL;
    }
    // we increase the humansAmount by one for adding new child.
    humansData->humansAmount = humansData->humansAmount + 1;
}

/**
 * @brief Prints the family tree starting from the specified human.
 *
 * This function prints the family tree of a given human and their
 * descendants recursively. It uses a tab counter to create indentation for
 * each level of the family tree.
 *
 * @param humansData Pointer to the data structure containing all humans.
 * @param humanName Name of the human to start printing the family tree from.
 * @param tabCounter Number of tabs for indentation.
 */
void print_family(Allhumans *humansData, char *humanName,
                  unsigned int tabCounter) {
    // Print indentation using tabs
    for (unsigned int i = 0; i < tabCounter; ++i) {
        printf("\t");
    }
    // Find the current human in the data structure
    Node *current = find_person_node(humansData, humanName);

    // Print the current human's information
    if (current->person->partner == NULL) {
        printf("%s (%d)\n", current->person->name, current->person->age);
    } else {
        printf("%s (%d) - %s (%d)\n", current->person->name,
               current->person->age, current->person->partner->name,
               current->person->partner->age);
    }

    // Set the flagForVisit to prevent infinite recursion
    current->person->flagForVisit = 1;

    // Recursively print the family tree of each child
    Node *currentChild = current->person->sons;
    while (currentChild != NULL) {
        // make sure there is no duplicates.
        if (currentChild->person->flagForVisit != 1) {
            print_family(humansData, currentChild->person->name,
                         tabCounter + 1);
        }
        // move to the next child node
        currentChild = currentChild->next;
    }
}

/**
 * @brief Updates the age of all humans in the data structure.
 *
 * This function increases the age of each human in the data structure by the
 * specified amount of years.
 *
 * @param humansData Pointer to the data structure containing all humans.
 * @param amountOfYears The number of years to be added to each human's age.
 */
void pass_the_time(Allhumans *humansData, unsigned int amountOfYears) {
    Node *current = humansData->data;

    // Update the age of each human by the specified amount of years
    while (current != NULL) {
        current->person->age = current->person->age + amountOfYears;
        // move to the next Node
        current = current->next;
    }
}

/**
 * @brief Resets the flagForVisit value of all humans in the data structure.
 *
 * This function sets the flagForVisit value of each human in the data
 * structure to 0, indicating that they have not been visited or processed.
 *
 * @param humansData Pointer to the data structure containing all humans.
 */
void reset_flags(Allhumans *humansData) {
    Node *current = humansData->data;

    // Reset the flagForVisit value of each human to 0
    while (current != NULL) {
        current->person->flagForVisit = 0;
        // move to the next Node
        current = current->next;
    }
}

/**
 * @brief Finds a specific Humanbeing structure in the data structure by name.
 *
 * This function searches for a Humanbeing structure with the specified name
 * in  the data structure. If found, it returns a pointer to the matching
 * Humanbeing structure; otherwise, it returns NULL.
 *
 * @param humansData Pointer to the data structure containing all humans.
 * @param humanName  Pointer to the name of the human to find.
 *
 * @return Pointer to the matching Humanbeing structure if found, NULL otherwise
 */
Humanbeing *find_person_struct(Allhumans *humansData, char *humanName) {
    Node *currentNode = humansData->data;

    // Traverse the data structure to find the desired Humanbeing structure
    while (currentNode != NULL) {
        // check if this is the desired name
        if (strcmp(currentNode->person->name, humanName) == 0) {
            return currentNode->person;
        }
        // move to the net node
        currentNode = currentNode->next;
    }
    // Person not found
    return NULL;
}

/**
 * @brief Links two linked lists together.
 *
 * This function takes two linked lists, list1 and list2, and links them
 * together by appending list2 at the end of list1. The resulting linked list
 * is returned.
 *
 * @param list1 Pointer to the head of the first linked list.
 * @param list2 Pointer to the head of the second linked list.
 *
 * @return Pointer to the head of the merged linked list.
 */
Node *link_lists(Node *list1, Node *list2) {

    // If either list is empty, return the other list
    if (list1 == NULL) {
        return list2;
    }
    if (list2 == NULL) {
        return list1;
    }

    // Traverse list1 to the last node
    Node *current = list1;
    while (current->next != NULL) {
        current = current->next;
    }

    // Append list2 to list1
    current->next = list2;

    // Return the head of the merged linked list
    return list1;
}

/**
 * @brief Creates a new node and initializes it with the given Humanbeing struct
 *
 * This function dynamically allocates memory for a new node and initializes
 * it with the provided Humanbeing struct. The flagForVisit is set to 0, and
 * the next pointer is set to NULL.
 *
 * @param humanStruct Pointer to the Humanbeing struct to be stored in a new
 * node
 *
 * @return Pointer to the newly created node, or NULL if memory allocation fails
 */
Node *create_node(Humanbeing *humanStruct) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    if (newNode == NULL) {
        // Failed to allocate memory for the new node
        return NULL;
    }
    // set the fields to the right parameters
    newNode->person = humanStruct;
    newNode->person->flagForVisit = 0;
    newNode->next = NULL;
    // return the new node
    return newNode;
}

/**
 * @brief Finds the degree-level parents of a given Humanbeing struct.
 *
 * This recursive function finds the parents at the specified degree level
 * of the given Humanbeing struct.It traverses the family tree upward,
 * finding the grandparents at the specified degree level.
 * The function returns a linked list of nodes containing the grandparents.
 *
 * @param humanStruct Pointer to the Humanbeing struct to find the
 * degree-level parents.
 * @param degreeLevel The degree level of parents to find.
 *
 * @return Pointer to the linked list of nodes containing the degree-level
 * parents, or NULL if the input is invalid or no parents are found.
 */
Node *find_degree_parents(Humanbeing *humanStruct, int degreeLevel) {

    // Check for invalid input or base case of reaching degree level 0
    if (humanStruct == NULL || degreeLevel < 0) {
        return NULL;
    }
    if (degreeLevel == 0) {
        // Create a node for the current Humanbeing struct
        return create_node(humanStruct);
    }

    // Check if the current Humanbeing struct has no parents
    if (humanStruct->dad == NULL && humanStruct->mom == NULL) {
        // No parents found, return NULL
        return NULL;
    }

    // Recursively find the grandparents at degreeLevel - 1 for both parents
    Node *grand1 = find_degree_parents(humanStruct->dad, degreeLevel - 1);
    Node *grand2 = find_degree_parents(humanStruct->mom, degreeLevel - 1);

    // Combine the linked lists of grandparents from both parents
    Node *grandparents = link_lists(grand1, grand2);
    // Return the linked list of degree-level parents
    return grandparents;
}

/**
 * @brief Finds the degree-level sons of a given Humanbeing struct.
 *
 * This recursive function finds the sons at the specified degree level of
 * the given Humanbeing struct. It traverses the family tree downward,
 * finding the sons at the specified degree level.
 *
 * @param humanStruct Pointer to the Humanbeing struct to find the
 * degree-levelsons.
 * @param degreeLevel The degree level of sons to find.
 *
 * @return Pointer to the linked list of nodes containing the degree-level
 * sons, or NULL if the input is invalid or no sons are found.
 */
Node *find_degree_sons(Humanbeing *humanStruct, int degreeLevel) {

    // Check for invalid input or base case of reaching degree level 0
    if (humanStruct == NULL || degreeLevel < 0) {
        return NULL;
    }
    if (degreeLevel == 0) {
        // Create a node for the current Humanbeing struct
        return create_node(humanStruct);
    }

    Node *sonsList = NULL;
    Node *son = humanStruct->sons;

    // Traverse through the linked list of sons
    while (son != NULL) {
        if (son->person != NULL) {
            // Recursively find the grandsons at degreeLevel - 1 for each son
            Node *grandsons = find_degree_sons(son->person, degreeLevel - 1);
            // Combine the linked lists of grandsons
            sonsList = link_lists(sonsList, grandsons);
        }
        son = son->next;
    }
    // Return the linked list of degree-level sons
    return sonsList;
}

/**
 * @brief Prints the cousins of a given person at a specified degree level.
 *
 * This function finds and prints the cousins of the given person at the
 * specified degree level. It first finds the grandparents of the person at
 * the degree level, then finds all the sons of those grandparents.
 * Finally, it sorts the names of the sons and prints them.
 *
 * @param humansData Pointer to the Allhumans struct containing the data of all humans.
 * @param humanName Name of the person whose cousins are to be printed.
 * @param degreeLevel The degree level of cousins to be printed.
 */
void print_cousins(Allhumans *humansData, char *humanName, int degreeLevel) {
    Humanbeing *personStruct = find_person_struct(humansData, humanName);

    // Find the grandparents at the specified degree level
    Node *grandParentsList = find_degree_parents(personStruct, degreeLevel);
    // create new linkedlist
    Node *allSonsList = NULL;

    Node *currentSons = malloc(sizeof(Node));
    currentSons->next = NULL;

    // Find all the sons at the degree level for each grandparent
    while (grandParentsList != NULL) {
        Humanbeing *currentGrandparent = grandParentsList->person;

        // Find the sons of the current grandparent at the specified degree level
        currentSons = find_degree_sons(currentGrandparent, degreeLevel);

        // Append the sons to the overall list of sons
        allSonsList = link_lists(allSonsList, currentSons);

        // move to the next grandson
        grandParentsList = grandParentsList->next;
    }

    // call the function sort names with parameter (allsonslist)
    sort_names(allSonsList);
    free_list(grandParentsList);
    free_list(currentSons);
}

/**
 * @brief Sorts the names of persons in the given linked list and prints them.
 *
 * This function sorts the names of persons in the linked list using the
 * bubble sort algorithm. It compares the names of each pair of adjacent
 * nodes and swaps them if necessary to achieve ascending order. After
 * sorting the names, it prints each name once, ensuring that duplicates are
 * not printed.
 *
 * @param allSonsList Pointer to the head of the linked list containing the
 * persons whose names are to be sorted and printed.
 */
void sort_names(Node *allSonsList) {
    Node *current = allSonsList;

    if (current == NULL){
        printf("No cousins\n");
        free_list(allSonsList);
        return;
    }

    // Sort the names using bubble sort algorithm
    while (current->next != NULL) {
        // Initialize current2 to the node next to current
        Node *current2 = current->next;

        while (current2 != NULL) {
            // Compare the names of current and current2, swap them if necessary
            if (strcmp(current->person->name, current2->person->name) > 0) {
                Humanbeing *temp = current->person;
                current->person = current2->person;
                current2->person = temp;
            }
            // Move to the next node in the list
            current2 = current2->next;
        }
        // Move to the next node in the list
        current = current->next;
    }
    // we start again from the head of the list
    current = allSonsList;
    while (current != NULL) {
        if (current->person->flagForVisit == 0) {
            // Print the name if it has not been visited before
            printf("%s\n", current->person->name);
            current->person->flagForVisit = 1;
        }
        // move to the next node
        current = current->next;
    }
    free_list(allSonsList);
}

/**
 * @brief Frees the memory allocated for all sons in the linked list.
 *
 * This function iterates through the linked list of sons and frees the memory
 * allocated for each son until all sons in the list have been freed.
 *
 * @param sonsList Pointer to the head of the linked list of sons.
 */
void free_list(Node* sonsList) {
    Node* current = sonsList;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}


