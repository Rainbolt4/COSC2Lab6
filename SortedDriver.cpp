// SortedDriver.cpp

// tom bailey   1445  25 mar 2014
// Construct sorted sequences and call functions that
//   process the sorted sequences.

//Dominic Rainbolt 


#include "RandomUtilities.h"
#include "ContainerPrinting.h"
#include "winTimer.h"//CHANGE: this to unixTimer.h if on mac/linux
#include <list>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// post: a sorted vector of listSize random doubles from
//         the range minNum to maxNum has been returned.
vector<double>
getNums(size_t listSize, double minNum, double maxNum)
{
	vector<double> theList;
	for (size_t i = 0; i < listSize; ++i)
	{
		theList.push_back(randReal(minNum, maxNum));
	}

	sort(begin(theList), end(theList));

	return theList;
}


// post: a sorted list of numWords words of length
//         wordLength with characters chosen randomly from
//         alphabet has been returned.
list<string>
getWords(size_t numWords, size_t wordLength, string alphabet)
{
	list<string> theWords;
	for (size_t i = 0; i < numWords; ++i)
	{
		string word;
		for (size_t j = 0; j < wordLength; ++j)
		{
			word += alphabet.at(randInt(0, alphabet.size()));
		}
		theWords.push_back(word);
	}

	theWords.sort();

	return theWords;
}


// pre:  number is not empty;
//       number is sorted from smallest to largest
// post: The most isolated entry in number has been returned
double
mostIsolated(vector<double> & number)
{
	sort(begin(number), end(number));
	int position = 0;
	double biggestDiff = 0;
	// STUB  STUB  STUB           fine the most isolated number
	// dont use two iterations must be linear
	// look at first, compare second ( posistion is first or last cases should be handled)
	//	middle casses should compare last and next and if its the greatest value seen need to save the position and the difference to contine comparing
	for (int i = 0; i < number.size(); i++) { // 1 for loop so we will not have exponential growth Satisifies time complexity requirements
		if (i == 0) { // first case just checks to see if the 
			biggestDiff = abs(number[0] - number[1]);
			position = i;
		}
		else if (i == number.size() - 1) {// end of the line case
			double currentdif = 0;
			currentdif = abs(number[number.size() - 1] - number[number.size() - 2]);
			if (currentdif > biggestDiff) {
				biggestDiff = currentdif; // end of the tree this is the biggest difference we have seen
				position = i;
			}
		}
		else // standard case for everything not at the beginning
		{
			double currentdif1 = 0;
			currentdif1 = abs(number[i] - number[i + 1]);// checking the right neighbor
			double currentdif2 = 0;
			currentdif2 = abs(number[i] - number[i - 1]); // checking the left neighbor
			double smallestdif = 0; //how far away is the nearest neighbor going to be? the lesser of the right and left neighbors
			if (currentdif1 < currentdif2) { // the right neighbor is the nearest neighbor
				smallestdif = currentdif1;
			}
			else { // the left neighbor is the nearest
				smallestdif = currentdif2;
			}
			if (smallestdif > biggestDiff) { // if this index is more isolated then any other index seen
				biggestDiff = smallestdif; // set the new biggest difference
				position = i;	// save this index location as the  most isolated
			}
			

		}






	}
	return number[position];
}


// pre:  A and B are sorted.
// post: The number of strings in A that do not occur in B
//         has been returned.






int
unmatched(list<string> & A, list<string> & B)
{
	//takes in two sorted lists, counts how many words in list a do not occur in list b
	// both lists are sorted so if a value in list a is > than the value in list b list b should increment this can be done by looping through list a
	// everytime list a is > than list b list b's index can be incremented
	int count = A.size(); // used to keep track of how many items in A are not in list B
	bool hasAppeared = false; // this will be the logic for if a particular value in list a has been seen in list b
	std::list<std::string>::iterator it1 = A.begin(); // iterator for list A
	std::list<std::string>::iterator it2 = B.begin();	// iterator for list B// this will be used to keep track of how many words are in a and not in b
	for (int i = 0; i < (A.size()-1)*2; i++) {  // dupilcate are possible
		if (*it1 > *it2) { // a's first value is greater than b's becuase both lists are sorted we can increment b. 
			advance(it2, 1); // increment b's iterator
		}
		else if (*it1 < *it2) { // this is the case that a's value is less than b's value so we increment a 
			advance(it1, 1); //increment a's iterator
		}
		else if (*it1 == *it2) { // the values of the lists are indeed equal
			hasAppeared = true;
			count--;
			advance(it1, 1);
			/*count--; // decrement the count becuase we have equality
			std::list<std::string>::iterator it11 = it1;
			std::list<std::string>::iterator it22 = it2;
			advance(it11, 1); // look at teh next item in a
			advance(it22, 1); // look at teh next item in b
			if (*it11 == *it22) {
				advance(it1, 1);
				advance(it2, 1); // both of the next items in each list is the same we can increment both of them
			}
			else if (*it1 == *it11) { // this is the case when a's next value is equal to a's current value if so, we must also compare that value 
				// to the current b value before we increment b, other wise we can increment both values
				advance(it1, 1);

			}

			else if (*it22 == *it2) {
				advance(it2, 1); // b's next itme is the same as b so we need to check it compared to teh current a
			}
			else {
				advance(it1, 1);
				advance(it2, 1); //increment both iterators as we have found equality so they can both be increased 1 to check the next values
			}
			*/
		}




	}

	

	return count;
}


int
main()
{
	cout << "Find the most isolated number" << endl
		<< "-----------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for numbers: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct a sorted list of numbers
		Timer get;
		get.start();
		vector<double> numbers = getNums(n, -n, n);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (n < 10)
			cout << numbers << endl << endl;

		// Report a most isolated isolated number
		Timer time;
		time.start();
		double isolated = mostIsolated(numbers);
		time.stop();
		cout << "The most isolated number is "
			<< isolated << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}


	cout << endl << endl;
	cout << "Count the unmatched words" << endl
		<< "-------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for words lists: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter word length: ";
		int wordSize;
		cin >> wordSize;
		cout << "Enter alphabet: ";
		string alphabet;
		cin >> alphabet;

		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct two sorted vectors of words
		Timer get;
		get.start();
		list<string> A = getWords(n, wordSize, alphabet);
		list<string> B = getWords(n, wordSize, alphabet);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (wordSize * n < 60)
		{
			cout << "A is: " << A << endl
				<< "B is: " << B << endl;
		}

		// Report the number of words in the first sorted list
		//   that are not in the second sorted list
		Timer time;
		time.start();
		int count = unmatched(A, B);
		time.stop();
		cout << count
			<< " words in A were not in B" << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}

	return 0;
}
