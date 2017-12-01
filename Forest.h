#ifndef FOREST_H
#define FOREST_H
#include <string>

//structures
struct entry
{
	char key;
	int freq;
	std::string code;
};


struct node
{
	node* next;
	int priority;
	char key;
	int freq;
	node *left,*right;
};




//class
class Forest {

public:

	Forest();
	void populate(std::string fileName);
	void walk();
	std::string createHeader();
	//char getLastCharUpperBound();


	const int getSize() const;
	const int getLeavesNum() const;
	entry* passTable();
	void decodeFile(std::string fileName);
	void travelList();
//	void writeHeader(char N);

	
	void inOrderPrint();
	void buildHoffman();
	void populateFromHeader(std::string &header);
	
	
	//void addTree(char key, treeLink* lastNode);
	//void removeTree(huffNode* prevNode);
	//void populate();

private:

node *head;
int pCount; //used to set prioritys
int size; //number of nodes
int leaves; // number of leaves;
int length; //length of original linked list ( #of tree roots)

	void createNode(node*,char);
	void addDefNode(char key, int freq);
	node* newForest(node* origHead, node* ignore1, node* ignore2, node* newNode);
	void subTreeCall(node *T,std::string s, int &i,entry* t);
	node* treeNode(node* L, node* R);
	void removeNodeLink(node* pN, node* n);
	void inOrderSubTreePrint(node *T);
	void replaceNodeLink(node*pN, node* newNode);
	
};

void compressAndWrite(entry*,int size,std::string fileName,std::string header);
void writeHeader(entry*,int size);

char getLastCharUpperBound(entry*, int size);
char binStringToChar(std::string s);
int stringToInt(std::string);
std::string charToBinString(unsigned char ch);






#endif