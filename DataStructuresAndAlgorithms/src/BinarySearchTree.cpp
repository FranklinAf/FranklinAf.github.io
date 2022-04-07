//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Austin Franklin
// Version     : 6.4
// Description : Binary search tree functionality for csv input data
//============================================================================

//algorithm was missing, added library
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
    int count; //used to count number of duplicates for string search
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

struct Node {
	Bid bid;
	Node* left;
	Node* right;
	Node* leftAmount; //left tracker
	Node* rightAmount; //right tracker
	Node* parentAmount; //track parent

	//Default
	Node(){
		left = nullptr;
		right = nullptr;
	}

	//To initialize with a bid (same as linked list) but new node
	Node(Bid singleBid) : Node(){
		this->bid = singleBid;
	}
};

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

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;
    Node* rootAmount; // housekeeping variable

    void addNode(Node* node, Bid bid);
    void inOrder(Node* node);
    Node* removeNode(Node* node, string bidId);
    void insertAmount(Node* newNode, Bid bid);
    void inOrderAmount(Node* node); //add new methods, note lowercase
    void searchByAmount(Node* node, double leftBound, double rightBound); //lowercase method

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void Insert(Bid bid);
    void Remove(string bidId);
    Bid Search(string bidId);
    void InOrderAmount(); //add new methods
    void SearchByAmount(double leftBound, double rightBound);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
	//Initialize node, and children
	root = nullptr;
	rootAmount = nullptr; //used to construct amount tree functionality
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
	if(root == nullptr) return;
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
	//inorder is left, root, right
	this->inOrder(root);
}

/**
 *
 */
void BinarySearchTree::InOrderAmount() {
	this->inOrderAmount(this->rootAmount); //execute inorder using root
}

void BinarySearchTree::inOrderAmount(Node* node) {
	//perform inorder left, print, right
		if (node != nullptr){
			//move left recurse
			inOrderAmount(node->left);

			//print current node information
			cout << node->bid.bidId << ": " << node->bid.title << " | " << node->bid.amount << " | "
					<< node->bid.fund << endl;

			//move right recurse
			inOrderAmount(node->right);
		}
}

/**
 * Insert a bid
 *
 * @param bid Id used to insert into binary search tree
 */
void BinarySearchTree::Insert(Bid bid) {
	if(root == nullptr){
		//if root is empty, make root the new bid
		root = new Node(bid);
		rootAmount = new Node(bid);
	}else{
		//if not empty then add new node to the root using the bid (same as linked list)
		//Addnode is a recursive function
		this->addNode(root, bid);
		this->insertAmount(rootAmount, bid);
	}
}

/**
 * Remove a bid
 *
 * @param bid Id to be removed from binary search tree
 */
void BinarySearchTree::Remove(string bidId) {
	this->removeNode(root,bidId);
}

//Do the same as the addNode except return node pointer
/**
 * private function remove a specific node
 *
 * @param node current node
 * @param bidId to be removed
 */
Node* BinarySearchTree::removeNode(Node* node, string bidId){
	//check if tree is empty,if so return
	if (node == nullptr){
		return node;
	}
	//traverse down left tree
	if (node->bid.bidId.compare(bidId) > 0){
		//if current node greater than bid passed in function, move left and recurse
		node->left = removeNode(node->left, bidId);
	}else if (node->bid.bidId.compare(bidId) < 0){
		//traverse right tree
		node->right = removeNode(node->right, bidId);
	}else{
		//check if node is leaf
		if (node->left == nullptr && node->right == nullptr){
			delete node;
			node = nullptr;
		}
		//check if only child to the left
		else if (node->left != nullptr && node->right == nullptr){
			//create temporary variable for deletion
			Node* tmp = node;
			//set current node to left node
			node = node->left;
			delete tmp;
		}
		//check if only child to the right
		else if (node->right != nullptr && node->left == nullptr){
			//create temp variable for deletion
			Node* tmp = node;
			//set current node to right node
			node = node->right;
			delete tmp;
		}
		//Check if two children
		else{
				//check which child has to be set to current node
				Node* tmp = node->right;
				//traverse left
				while (tmp->left != nullptr){
					tmp = tmp->left;
				}
				//after finding leaf, set current node
				node->bid = tmp->bid;
				//remove node using recursion
				node->right = removeNode(node->right, tmp->bid.bidId);
		}
	}
	return node;
}

/**
 * Search for a bid
 *
 *  @param bidId to return a single bid
 */
Bid BinarySearchTree::Search(string bidId) {
	//set root as the current node
	Node* current = root;

	while (current != nullptr){
		if (current->bid.bidId.compare(bidId) == 0){
			//Match to current bid, return the bid found
			return current->bid;
		}
		//traverse left tree
		if (current->bid.bidId.compare(bidId) > 0){
			current = current->left;
		}
		//traverse right tree
		else{
			current = current->right;
		}
	}

	//if not found return initialized bid
	Bid bid;
    return bid;
}

void BinarySearchTree::SearchByAmount(double leftAmount, double rightAmount) {
	searchByAmount(this->rootAmount, leftAmount, rightAmount);
}


/**
 * follow same syntax as before, searchByAmount
 */
void BinarySearchTree::searchByAmount(Node* node, double leftAmount, double rightAmount) {
	//set root as the current node
		Node* current = node; //set amount root amount bst to current

		//hook into inorder functionality, only print amounts from the rootAmount pointer
			if (node != nullptr){
				//move left recurse
				searchByAmount(current->left, leftAmount, rightAmount);

				//print current node information
				if(current->bid.amount >= leftAmount && current->bid.amount <= rightAmount){
					cout << current->bid.bidId << ": " << current->bid.title << " | " << current->bid.amount << " | "
							<< current->bid.fund << endl;
				}

				//move right recurse
				searchByAmount(current->right, leftAmount, rightAmount);
			}
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Bid bid) {

	//if the node is greater than 0 add current bid to left child of current node
	if (node->bid.bidId.compare(bid.bidId) > 0){
		//check if left node doesnt have value, if so then add new node with current bid
		if(node->left == nullptr){
			node->left = new Node(bid);
		}else{
			//value exists in left child recursive call addNode with child value
			this->addNode(node->left, bid);
		}

	}
	//check if right child exists
	else {
		if (node->right == nullptr){
			node->right = new Node(bid);
		} else {
			//not a null node, recursive call
			this->addNode(node->right, bid);
		}
	}
	return;
}
/**
 * Setup the binary search tree based on the amount
 */
void BinarySearchTree::insertAmount(Node* newNode, Bid bid) {

	//if the node is greater than 0 add current bid to left child of current node
	if (newNode->bid.amount < bid.amount){
		//check if left node doesnt have value, if so then add new node with current bid
		if(newNode->left == nullptr){
			newNode->left = new Node(bid);
		}else{
			//value exists in left child recursive call addNode with child value
			this->insertAmount(newNode->left, bid);
		}

	}
	//check if right child exists
	else {
		if (newNode->right == nullptr){
			newNode->right = new Node(bid); //set right node to input bid
		} else {
			//not a null node, recursive call
			this->insertAmount(newNode->right, bid);
		}
	}
	return;
}

/**
 * Display all nodes in current bst
 *
 * @param node Starting node
 */
void BinarySearchTree::inOrder(Node* node) {
	//left, node, right
	if (node != nullptr){
		//move left recurse
		inOrder(node->left);

		//print current node information
		cout << node->bid.bidId << ": " << node->bid.title << " | " << node->bid.amount << " | "
				<< node->bid.fund << endl;

		//move right recurse
		inOrder(node->right);
	}
}



//============================================================================
// Static methods used for testing
//============================================================================



/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            // push this bid to the end
            bst->Insert(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
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
    string csvPath, bidKey;

    //Create variables for new amount functionality
    double lowAmount, highAmount;

    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98109";
        lowAmount = 50;
        highAmount = 100;
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        lowAmount = 50;
        highAmount = 100;
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        bidKey = "98109";
        lowAmount = 50;
        highAmount = 100;
    }

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all bids
    BinarySearchTree* bst;

    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  5. Display All Bids sorted by Amount" << endl;
        cout << "  6. Search For Bids In Range" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            bst = new BinarySearchTree();

            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bst);

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
        	//Display all bids
            bst->InOrder();
            break;

        case 3:
        	//Find bid by Id
            ticks = clock();

            bid = bst->Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
            	cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 4:
        	//Remove specific bid by Id
            bst->Remove(bidKey);
            break;
        case 5:
        	bst->InOrderAmount();
        	break;
        case 6:
        	bst->SearchByAmount(lowAmount, highAmount);
        	break;
        default: //no a valid option
        	cout << "Please enter a valid menu option." << endl;
        	break;
        }
    }

    cout << "Good bye." << endl;

	return 0;
}
