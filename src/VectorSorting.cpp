//============================================================================
// Name        : VectorSorting.cpp
// Author      : Brandon Thibeaux
// Date        : 9/27/2020
// Class       : CS-260-H1166
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Vector Sorting Algorithms
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << endl;
    return;
}

/**
 * Prompt user for bid information using console (std::in)
 *
 * @return Bid struct containing the bid info
 */
Bid getBid() {
    Bid bid;

    cout << "Enter Id: ";
    cin.ignore();
    getline(cin, bid.bidId);

    cout << "Enter title: ";
    getline(cin, bid.title);

    cout << "Enter fund: ";
    cin >> bid.fund;

    cout << "Enter amount: ";
    cin.ignore();
    string strAmount;
    getline(cin, strAmount);
    bid.amount = strToDouble(strAmount, '$');

    return bid;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
vector<Bid> loadBids(string csvPath) {
    cout << "Loading CSV file " << csvPath << endl;

    // Define a vector data structure to hold a collection of bids.
    vector<Bid> bids;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            bids.push_back(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
    return bids;
}

// FIXME (2a): Implement the quick sort logic over bid.title

/**
 * Partition the vector of bids into two parts, low and high
 *
 * @param bids Address of the vector<Bid> instance to be partitioned
 * @param begin Beginning index to partition
 * @param end Ending index to partition
 */
int partition(vector<Bid>& bids, int begin, int end)
{
	int l = 0;
	int h = 0;
	int midpoint = 0;
	int pivot=0;
	Bid temp;
	bool completionStatus = false;

	//pick middle element as pivot
	//midpoint = begin + (end-begin) / 2;
	pivot = begin + (end - begin) / 2;

	l = begin;
	h = end;
	while(!completionStatus)
	{
		//increment l while bids[l] < pivot
		while (bids.at(l).title.compare(bids.at(pivot).title) < 0)
		{
			//cout<<"increment l "<<bids.at(l).title.compare(pivot.title)<<endl;//Debugging

			l++;
		}

		//decrement h while pivot < bids[h]
		while(bids.at(pivot).title.compare(bids.at(h).title)<0)
		{
			//cout<<"decrement h "<<pivot.title.compare(bids.at(h).title)<<endl;//Debugging
			h--;
		}

		/* if there are zero or one element(s) remaing,
		 *  all numbers are partitioned. return h*/
		if(l>=h)
		{
			completionStatus = true;
		}
		else
		{
			//Swap bids[l] and bids[h] update l and h
			temp = bids.at(l);
			bids.at(l) = bids.at(h);
			bids.at(h) = temp;
			l++;h--;
			//cout<<"Status: not complete"<<endl;//Debugging
			//cout<<"Swap was made"<<endl;//Debugging

		}
	}
	return h;
	//cout<<"Status: complete"<<endl;//Debugging
}

/**
 * Perform a quick sort on bid title
 * Average performance: O(n log(n))
 * Worst case performance O(n^2))
 *
 * @param bids address of the vector<Bid> instance to be sorted
 * @param begin the beginning index to sort on
 * @param end the ending index to sort on
 */
void quickSort(vector<Bid>& bids, int begin, int end)
{
	int j = 0;

	/*Base case: if there are 1 or 0 elements to sort,
	 * partition is alredy sorted*/
	if(begin>=end)
	{
		return;//exits quicksort
	}

	/*Partition the data within the array. Value j returned from
	 * partitioning is location of last element in low partition*/

	j = partition(bids,begin,end);//setting out midpoint

	//Recursively sort low partition (i to j) and high partition (j+1 to k)
	quickSort(bids,begin,j);//checks beginning half of partition
	quickSort(bids,j+1,end);//checks ending half of partition

}

// FIXME (1a): Implement the selection sort logic over bid.title
/**
 * Perform a selection sort on bid title
 * Average performance: O(n^2))
 * Worst case performance O(n^2))
 *
 * @param bid address of the vector<Bid>
 *            instance to be sorted
 */
void selectionSort(vector<Bid>& bids) //Fixed
{
	int indexSmallest = 0;
	Bid temp;
	int max = bids.size();
	for(int i = 0; i<max; i++)
	{
		//Find index of smallest remaining element
		indexSmallest = i;
		for(int j = i+1; j<max; j++)
		{
			if (bids.at(j).title.compare(bids.at(indexSmallest).title)< 0)
			{
				indexSmallest = j;
			}
		}
		//swap number[i] and number[indexSmallest]
		temp = bids.at(i);
		bids.at(i) = bids.at(indexSmallest);
		bids.at(indexSmallest) = temp;
	}
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
    }

    // Define a vector to hold all the bids
    vector<Bid> bids;

    // Define a timer variable
    clock_t ticks;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Selection Sort All Bids" << endl;
        cout << "  4. Quick Sort All Bids" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            bids = loadBids(csvPath);

            cout << bids.size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 2:
            // Loop and display the bids read
            for (int i = 0; i < bids.size(); ++i) {
                displayBid(bids[i]);
            }
            cout << endl;

            break;

        // FIXME (1b): Invoke the selection sort and report timing results
        case 3:
        	// Initialize a timer variable before loading bids
        	ticks = clock();
        	selectionSort(bids);
        	// Calculate elapsed time and display result
        	ticks = clock() - ticks; // current clock ticks minus starting clock ticks
        	cout << "time: " << ticks << " clock ticks" << endl;
        	cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
        	break;

        case 4:
        	ticks = clock();

        	quickSort(bids, 0, bids.size()-1);

        	// Calculate elapsed time and display result
        	ticks = clock() - ticks; // current clock ticks minus starting clock ticks
        	cout << "time: " << ticks << " clock ticks" << endl;
        	cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
        	break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
