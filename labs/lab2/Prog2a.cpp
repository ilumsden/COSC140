#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

const string face[] = { "Ace", "2", "3", "4", "5", "6", "7",
                        "8", "9", "10", "Jack", "Queen", "King" }; 
const string suit[] = { "Clubs", "Diamonds", "Hearts", "Spades" };

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
	  } else if (option.compare("-verbose") == 0) {
	    verbose = true;
	  } else 
	    cout << "option " << argv[i] << " ignored\n";
	}

	srand(seedvalue);

	/* Creates an array deck to store the number
	 * of each card drawn and an int break_row
	 * to store the number for the row that
	 * causes the loop below to break.
	 */
	int deck[4][13] = {};
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
	   * and ind2. Then, the value of deck at row ind1 and column ind2 is
	   * incremented by 1.
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
      deck[ind1][ind2]++;
	  /* This block of code breaks the while loop when
	   * all the face cards for a single suit have been
	   * pulled at least once. There is a single statement
	   * for each suit to insure the break command breaks
	   * out of the while loop (instead of a for loop).
	   */
      if ((deck[0][10] >= 1 && deck[0][11] >= 1 && deck[0][12] >= 1)) {
          break_row = 0;
          break;
	  }
      if ((deck[1][10] >= 1 && deck[1][11] >= 1 && deck[1][12] >= 1)) {
          break_row = 1;
          break;
	  }
      if ((deck[2][10] >= 1 && deck[2][11] >= 1 && deck[2][12] >= 1)) {
          break_row = 2;
          break;
	  }
      if ((deck[3][10] >= 1 && deck[3][11] >= 1 && deck[3][12] >= 1)) {
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
		/* Adds the number of each card that was
		 * drawn to the table
		 */
        for (int j = 0; j < 13; j++) {
            cout << setw(4) << right << deck[i][j];
			//Adds "**" to the end of the suit row that broke the while loop
			if (j == 12 && i == break_row) {
                cout << " **";
			}
		}
		cout << endl;
	}
	return(0);
}
