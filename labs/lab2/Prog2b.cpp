#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

/* Prog2b.cpp
 * Author: Ian Lumsden
 * Date: August 25, 2017
 * 
 * This program creates random cards until at least
 * one of each face card is "drawn" for a suit. Each time
 * a card is drawn, it is added to a List object that stores
 * the cards in the order that they were drawn. However, if
 * the card is already present in the list, the card is placed
 * at the front of the list (index 0). Once each face card as been drawn
 * for a suit, the lists are printed, showing the user what
 * cards have been drawn. Two stars ("**") are also printed
 * after the line for the suit that stopped the "game."
 */

const string face[] = { "Ace", "2", "3", "4", "5", "6", "7",
                        "8", "9", "10", "Jack", "Queen", "King" }; 
const string suit[] = { "Clubs", "Diamonds", "Hearts", "Spades" };

// List Class for storing card order
class List {
    private:
        struct Node {
            //Stores the memory address of the next Node
            Node *next;
            //Stores the Node's data (an index for the global face array)
	    int face_index;
	    Node(int data=-1) {next = NULL; face_index = data;}
	};
        //A head node to mark the starting point of the List.
	Node *head;
        //An int that stores the number of elements in the List.
	int num_elem;
    public:
        List() {head = new Node; num_elem = 0;}
	~List();
        //This function returns the size of the List for external purposes.
	int size() {return num_elem;}
        void insert(int);
    friend ostream & operator<<(ostream &, const List &); 
};

List::~List() {
    /* If there are still elements in the List,
     * each individual node is unlinked and deleted.
     * Then, the head node is deleted.
     */
    while (num_elem != 0) {
        Node *p = head->next;
	Node *pp = p->next;
	head->next = pp;
	delete p;
	num_elem--;
    }
    delete head;
}

/* This function inserts "cards" (Nodes containing the index
 * for a card value) in the following ways:
 *    - If the "card" is already in the list, that card
 *      is moved to the front of the List (index 0).
 *    - Otherwise, the card is added to the back
 *      of the List (index num_elem-1).
 */
void List::insert(int ind) {
    /* If there are not any Nodes in List besides head,
     * a new node is created and linked directly to head.
     * The new node's next element remains NULL.
     */
    if (num_elem == 0) {
        Node *firstnode = new Node(ind);
	head->next = firstnode;
	num_elem++;
	return;
    }
    /* This block creates two Node pointers:
     * curr, which points to the Node currently
     * being worked with, and prev, which points
     * to the Node before curr. Then, it loops through
     * the list, searching for an element where face_index
     * is the same as ind. If it finds such an element,
     * the code will unlink it from the List and relink it
     * at index 0 (head->next). If the element is already at
     * index 0, the code just returns since there is no need
     * to do any unlinking or relinking.
     */
    Node *prev = head;
    Node *curr = head->next;
    for (int i = 0; i < num_elem; i++) {
        if (curr->face_index == ind) {
	    if (i == 0) {
	        return;
	    }
	    else {
                prev->next = curr->next;
		curr->next = head->next;
		head->next = curr;
		return;
	    }
	}
	prev = curr;
	curr = curr->next;
    }
    /* If the function has not returned at this point,
     * a new node is created for this "card," and it is added
     * to the end of the List (at prev->next).
     */
    Node *newnode = new Node(ind);
    prev->next = newnode;
    num_elem++;
    return;
}

/* This function overloads the output stream operator
 * to print a List. The content that is printed by this
 * operator is a space-seperated line of text containing
 * the strings from the global face array that are
 * represented by the face_index member of the Nodes.
 */
ostream & operator<<(ostream &out, const List &L) {
    List::Node *p = L.head->next;
    for (int i = 0; i < L.num_elem; i++) {
        out << " " << face[p->face_index];
	p = p->next;
    }
    return out;
}

string random_card(bool verbose=false) {
    string card;

    card = face[ rand()%13 ];
    card += " of ";
    card += suit[ rand()%4 ];

    if (verbose)
        cout << card << "\n";

    return card;
}

int main(int argc, char *argv[])
{
    bool verbose = false;
    int seedvalue = 0;

    for (int i=1; i<argc; i++) {
        string option = argv[i];
	if (option.compare(0,6,"-seed=") == 0) {
	    seedvalue = atoi(&argv[i][6]);
	} 
        else if (option.compare("-verbose") == 0) {
	    verbose = true;
	} 
        else 
	    cout << "option " << argv[i] << " ignored\n";
	}

    srand(seedvalue);

    /* Creates an array deck to store the Lists
     * for each suit. Also creates an array of ints
     * that stores the number of times a face card
     * has been drawn for each suit. Finally, creates
     * an int break_row to store the number for the suit that
     * causes the loop below to break.
     */
    List deck[4];
    int num_faces[4][13] = {};
    int break_row;

    /* Indefinite loop (with a manual break) that gets a
     * random card, uses the card's value and suit to
     * update deck, and breaks out once all the face
     * cards of a single suit has been drawn.
     */
    while (1) {
        string card = random_card(verbose);
	//These variables store the rank, garbage string, and suit of the card respectively
	string rank, garbage, type;
	stringstream ss;
        ss << card;
	ss >> rank >> garbage >> type;
	/* This block of code determines the indicies of the global
	 * suit and face arrays which correspond with the values of
	 * the variables type and rank. These indicies are stored in ind1
	 * and ind2. Then, the insert function is called on the List
         * stored at ind1 in deck. This function is passed ind2. Finally,
         * if ind2 represents a face card, the corresponding value in num_faces
         * is incremented.
	 */
	int ind1, ind2;
	for (int i = 0; i < 4; i++) {
            if (type == suit[i]) {
                ind1 = i;
		break;
	    }
	}
	for (int j = 0; j < 13; j++) {
            if (rank == face[j]) {
                ind2 = j;
		break;
	    }
	}
        deck[ind1].insert(ind2);
	if (ind2 == 10 || ind2 == 11 || ind2 == 12) {
            num_faces[ind1][ind2-10]++;
	}
	/* This block of code breaks the while loop when
	 * all the face cards for a single suit have been
	 * pulled at least once. There is a single statement
	 * for each suit to insure the break command breaks
	 * out of the while loop (instead of a for loop).
	 */
        if ((num_faces[0][0] >= 1 && num_faces[0][1] >= 1 && num_faces[0][2] >= 1)) {
            break_row = 0;
            break;
	}
        if ((num_faces[1][0] >= 1 && num_faces[1][1] >= 1 && num_faces[1][2] >= 1)) {
            break_row = 1;
            break;
	}
        if ((num_faces[2][0] >= 1 && num_faces[2][1] >= 1 && num_faces[2][2] >= 1)) {
            break_row = 2;
            break;
	}
        if ((num_faces[3][0] >= 1 && num_faces[3][1] >= 1 && num_faces[3][2] >= 1)) {
            break_row = 3;
            break;
	}
    }

    for (int i = 0; i < 4; i++) {
        /* Adds the suit name to the correct
	 * output row.
	 */
	switch(i) {
            case(0): {
                cout << setw(9) << right << "Clubs:"; 
		break;
	    }
	    case(1): {
                cout << setw(9) << right << "Diamonds:";
		break;
	    }
	    case(2): {
                cout << setw(9) << right << "Hearts:";
		break;
	    }
	    case(3): {
                cout << setw(9) << right << "Spades:";
		break;
	    }
	}
        //Prints the contents of the corresponding List for the current suit.
	cout << deck[i];
        //Prints " **" after the line for the suit that broke the while loop.
	if (i == break_row) {
            cout << " **";
	}
	cout << endl;
    }
    return(0);
}
