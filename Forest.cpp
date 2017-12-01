#include "Forest.h"
#include <string>
#include <cmath>
#include <fstream>
#include <iostream>
using namespace std;


Forest::Forest()
{
	head=nullptr;
	pCount=0;
	size=0;
	length=0;
	leaves=0;
}

void Forest::populate(string fileName)
{

	//stream in original text
	char ch;
	fstream fin(fileName,fstream::in);
	
	//get key's & frequenices
	while (fin >> noskipws >> ch)
	{
		
		
		if(length==0)
		{
			node* walker=nullptr;
			createNode(walker,ch);
			length++;
			leaves++;
		}
		else
			{
			node* walker=head;

				while(true)
				{
					if(walker->key==ch)
						{
						walker->freq++;
						break;
						}
					else
					{
						if(walker->next==nullptr)
						{
							createNode(walker,ch);
							length++;
							leaves++;
							break;
						}
						else
						{
							if(walker->key==ch)
							{
								walker->freq++;
								break;
							}
							else
								walker=walker->next;
						}
					}

				}
				
			}
	}
}

void Forest::walk()
{
	node* w=head;
	while(w!=nullptr)
	{
		cout << w->key << ": " << w->freq <<  " pri: " << w->priority << endl;
		w=w->next;
	}
}

void Forest::createNode(node* last,char key)
{
	//create node
	node* newNode;
	newNode = new node;

	//link tree to the forest
	if(last==nullptr)
		{
			head=newNode;
		}
	else
		last->next=newNode;
	
	//initliize
	newNode->freq=1;
	newNode->priority=pCount;
	newNode->key=key;
	newNode->left=nullptr;
	newNode->right=nullptr;
	newNode->next=nullptr;
	size++;
	pCount++;
	
}

string Forest::createHeader()
{
	string header="";
	node* w=head;

	while(w!=nullptr)
	{
		header+=w->key;
		header+=to_string(w->freq);
		header+=",";
		w=w->next;
	}
	header+=",,";

	//cout << header;

	return header;
}

char getLastCharUpperBound(entry* t, int size)
{
	char N;
	//string s;
	double M=0;
	//summation of code size * freq
	for(int i=0;i<size;i++)
		{
			M+= t[i].freq * (t[i].code).length();
		}
	
	M = (M / 8.0) - static_cast<int> (M/8);
	M = M*8.0;

	//return corresponding char
	if(M==0)
		N='8';
	else if(M==1)
		N='1';
	else if(M==2)
		N='2';
	else if(M==3)
		N='3';
	else if(M==4)
		N='4';
	else if(M==5)
		N='5';
	else if(M==6)
		N='6';
	else if(M==7)
		N='7';

	return N;
}

void Forest::buildHoffman()
{

	while(length>1)
	{

	//	travelList();

	//walker
	node* w = head;
	node* pW = nullptr;


	node*smallest;
	node*prevSmallest;
	node*small;
	node*prevSmall;
	
	//MAINTAIN INTEGREDITY OF SMALLEST < SMALL
	
	//CASE ONE: head < head->next
	if(head->freq < head->next->freq)
	{
		//head is smallest
		smallest = head;
		prevSmallest = nullptr;
		
		//head->next is small
		small = head->next;
		prevSmall = head;

	}
	//CASE TWO: equal frequencys
	//IF THE FREQUENCYS ARE EQUAL, THE LOWER PRIORITY WILL BE CHOSEN
	else if(head->freq==head->next->freq)
	{
			//smaller priority becomes smallest
			if(head->priority < head->next->priority)
			{
				//head is smallest
				smallest = head;
				prevSmallest = nullptr;
		
				small = head->next;
				prevSmall = head;
			}
			else
			{
				//head->next is smallest
				smallest = head->next;
				prevSmallest = head;
		
				small = head;
				prevSmall = nullptr;
			}
	}
	else
	{
		//head->next is smallest
		smallest = head->next;
		prevSmallest = head;
		small = head;
		prevSmall = nullptr;

	}
		
	//cout << "(" << small->freq << "," << smallest->freq << ")" << " ";
	
	//NOW, GET TWO LOWEST FREQUNECYS
	while(w!=nullptr)
	{
	
		//this condition ensures that a node will no be re-selected during the walk
		if(!(w==smallest || w==small))
		{
			//////////////////////////////////////////////////////////////////////////////////
			
			//OUTER IF: CASE 1, walker is less than small
			if(w->freq < small->freq)
				{
					//INNER IF: CASE 1, walker is less than smallest
					if(w->freq < smallest->freq)
					{
						//if it is, shift everything
						small=smallest;
						prevSmall=prevSmallest;

						smallest=w;
						prevSmallest=pW;
					}
					//INNER IF: CASE 2, walker is equal to smallest
					//if they are equal, key values must be checked to determine one will stay
					else if(w->freq == smallest->freq)
					{
							//PRIORITY'S RESOLUTION
							//the node with the lower priority is considered the smallest
								if(w->priority < smallest->priority) 
									{
									//smallest moves up to small
									small=smallest;
									prevSmall=prevSmallest;
									//walker has lower priority and takes the place of smallest
									smallest=w;
									prevSmallest=pW;
									}
								else
								{
									//smallest retains its position
									//walker becomes small
									small=w;
									prevSmall=pW;
								}
					}
					//INNER IF: Case 3, walker is greater than smallest so it is not considered for that position
					else
					{
						//walker takes the place of small
						small=w;
						prevSmall=pW;
					}
			
				}

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//OUTER IF: CASE 2, walker is equal to small
			else if(w->freq==small->freq)
			{
				//BECAUSE THE FREQ'S ARE EQUAL, THE PRIORITYS WILL DETMERMINE THE POSITIONS
					
				//INNER IF: CASE 1, check the prioritys are walker and 
				if(w->priority < small->priority)
				{
					//if w->freq is the same as smallest, we must also check their prioritys
					if(w->freq==smallest->freq)
					{
						//check prioritys
						if(w->priority < smallest->priority)
						{
								//smallest moves up to small
								small=smallest;
								prevSmall=prevSmallest;
								//walker has lower priority and takes the place of smallest
								smallest=w;
								prevSmallest=pW;
						}
						else
						{
								//smallest retains its position
								//walker becomes small
								small=w;
								prevSmall=pW;

						}
					}
					else
					{
						//walker becomes small
						small=w;
						prevSmall=pW;

					}
				}
				else
				{
					//do nothing
				}

			//cout << "(" << small->freq << "," << smallest->freq << ")" << " ";
			}
		//move walker along
		
	}	
		pW=w;
		w=w->next;
	
	}
	
	//cout << endl;
	
	//cout << "[" << length << "]";
	//travelList();
	//create new node with added frequncies
	
	//cout << "[" << length << "]";
	//remap forest 
	
	node* newNode = treeNode(smallest, small);
	size++;
	head=newForest(head,smallest,small,newNode);
	length--;
	//cout << newNode->priority << endl;
	//system("pause");





		//cout << "smallest: " << smallest->freq <<"," << smallest->key << "\nsmall: " << small->freq <<"," << small->key<< endl << "======================\n";
		//length--;
}

	cout << endl;

	//system("pause");
}



node* Forest::newForest(node* origHead, node* ignore1, node* ignore2, node* newNode)
	{//create newNode
	//	Forest temp;
	
	//add new node
	head=newNode;
	
	node* w = origHead;
	node* last=head;
	node* prevLast=nullptr;
	
	while(w!=nullptr)
	{
		if(w==ignore1 || w==ignore2)
		{
			//ignore
			last->next=nullptr;
		}
		else
		{
			//add to temp
			//cout <<"add";
			
			last->next=w;
			last=last->next;
		}
		//move along
		w=w->next;
	}

	last=nullptr;

	return head;
}

node* Forest::treeNode(node* L, node* R)
{
	//initilise
	node* newNode;
	newNode = new node;

	//initlise
	newNode->freq=L->freq+R->freq;
	newNode->key=NULL; //will change to NULL
	newNode->right=R;
	newNode->priority=pCount;
	newNode->left=L;
	newNode->next=nullptr;
	pCount++;

	return newNode;
}

void Forest::removeNodeLink(node* pN, node* n)
{
	cout <<"^";
	if(pN==nullptr)
		{
			cout <<"#";
			if(head->next!=nullptr)
				{
				head=head->next;
				cout <<"%";
				//cout << head->next;
			}
			else
			{cout <<"@";
				head=nullptr;
				
			}
		}
	else
	{
			cout <<"?";
			pN->next=pN->next->next;
	}
}

void Forest::travelList()
{
	node* w;
	w=head;

	while(w!=nullptr)
	{
		cout << w->freq << " -> " ;
		w=w->next;
	}
	cout << endl;

}

void Forest:: inOrderSubTreePrint(node *T)
{
	if(T!=nullptr)
	{
		inOrderSubTreePrint(T->left);
		cout << T->key << "|" <<T->freq << ", ";
		inOrderSubTreePrint(T->right);
	}
}

void Forest::inOrderPrint()
{
	//this function is merly for user interface so no paramter is required 
	inOrderSubTreePrint(head);
}
const int Forest::getSize() const
{
	return size;
}

void Forest::subTreeCall(node *T,string s,int &i,entry* t) 
{
	if(T==nullptr)
		return;



	//if T is a leaf 
	if(T->left==nullptr && T->right==nullptr)
	{
		t[i].key=T->key;
		t[i].freq=T->freq;
		t[i].code=s;
		i++;
		return;
	}
	else
	{
		string l = s;
		string r = s;
		l.append("1");
		r.append("0");
		
		subTreeCall(T->left,l,i,t);
		subTreeCall(T->right,r,i,t);

	}
}

entry* Forest::passTable()
{
	string s = ""; //huffCode
	int i=0; //index for huffTable
	
	entry* huffTable;
	huffTable = new entry[getLeavesNum()];
	subTreeCall(head,s,i,huffTable);
	
	return huffTable;
}

const int Forest::getLeavesNum() const
{
	return leaves;
}

void compressAndWrite(entry* t,int size,string fileName,string header)
{


	//get lastCharUpper bound
	char bound = getLastCharUpperBound(t,size);
	//cout << bound;

	
	string newfileName=fileName.substr(0,(fileName.length()-4));
	newfileName=newfileName + "Compressed.txt";

//	cout <<fileName;

	ofstream fout;
	fout.open((newfileName),ios::out);

	fout << bound;
	fout <<header;
	
	//stream objects
	fstream fin(fileName, fstream::in);

		int num =0;
	char e;
	string compressionBuffer="";
	string code="";
	char ch;

	while (fin >> noskipws >> ch)
	{
		string temp="";
		//get code
		for(int i=0;i<size;i++)
		{
			if(t[i].key==ch)
			{
				code=t[i].code;
				break;
			}
		}


		if(compressionBuffer.length()+code.length() < 8)
		{
			//cout << "|A|" << endl;
			compressionBuffer+=code;
		}
		else if(compressionBuffer.length()+code.length()== 8)
		{
			//cout << "|B|" << endl;
			//place
			compressionBuffer+=code;
			//write
		//	cout << compressionBuffer << endl;
			e=binStringToChar(compressionBuffer);
			//cout << e;
			fout << e;
		
			num++;
			//clear 
			compressionBuffer="";

		}
		else
		{
			while(code.length()!=0)
			{
				int cLength = compressionBuffer.length();
				int bound = 8 - cLength;
				//cout << bound << endl;
				//system("pause");
			//	cout << compressionBuffer << "," << temp << endl;
				//for loop to fill buffer 
				for(int i=0; i<bound;i++)
				{
					//if there is more empty space than code avalible 
					if(i==code.length() || i > code.length())
						{
							break;
						}
			//	cout << "+";
					temp+=code[i];
				}
				compressionBuffer+=temp;
			//	cout << compressionBuffer << endl;
				temp="";

				// adjust string
				for(int i=bound; i < code.length();i++)
				{
					temp +=code[i];
				//	cout << "*";
				}
				code=temp;
				temp="";
				
			//	cout << endl << "remaining: " << code << endl;

				//if full; store it 
				if(compressionBuffer.length()==8)
					{
						//cout << "|D|\n" << compressionBuffer << endl;
						e=binStringToChar(compressionBuffer);
					//	cout << e;
						fout << e;
						fout.flush();
						num++;
					
						//clear buffer14
						compressionBuffer="";
				}
			}
		}
	}

	fin.close();
	
	if(compressionBuffer.length()!=0)
	{
		while(compressionBuffer.length()!=8)
		{
			compressionBuffer+= '0';
		}
		e=binStringToChar(compressionBuffer);
		//cout << "|FR|\n" << compressionBuffer << endl;
		//cout << e;		
		fout << e;
		fout.flush();
	}
	fout.close();
	


	//cout << endl << num << endl;
	//fstream check;
	//check.open((fileName + "Compressed.dat"),fstream::in);


	//char b = NULL;

	//while(true)
	//{
	//	if(check >> noskipws >> ch)
	//	{
	//		if(!b)
	//		{
	//			b=ch;
	//		}
	//		else
	//		{
	//			//cout << b;
	//			b = ch;
	//		}
	//	}
	//	else
	//	{
	//		//cout << b;
	//	//	cout << "\nLAST";
	//		break;

	//	}

	//}

	//check.close();

}

char binStringToChar(string s)
{
	int power=0;
	double dec=0;

	for(int p=7;p>-1;p--)
	{
		if(s[p]=='1')
			{
				dec= dec + pow(2.0,power);
			}
		power++;
	}
	return static_cast<char>(dec);
}






void Forest::decodeFile(string fileName)
{
	fstream streamIn;
	streamIn.open(fileName,fstream::in);
	
	string newfileName=fileName.substr(0,(fileName.length()-14));
	newfileName=newfileName + "Decompressed.txt";

	cout <<fileName;

	ofstream fout;
	fout.open((newfileName),ios::out);


	unsigned char ch;
	unsigned char prevCh=NULL;
	int N =0;				//bound for last char; this accounts for extra zeros that are not apart of the compression 
	string term="---";		//header terminator sequence
	string buffer="";
	string temp="";		//used in term reassigning
	string headerInfo="";	//string holds information to create huffman tree
	bool header= false;		//true if header is terminated 
	node* w=nullptr;				//used to walk decompressTree
	
	while (true)
	{
		if(streamIn >> noskipws >> ch)
		{
			if(!prevCh)
			{
				prevCh=ch;
			//	cout << "*" << prevCh;
			}
			else
			{
				//PROCCESS INFO
				
			
			if(!header)
			{
				//include character in headerInfo to be used in huffmanTree
				headerInfo+=prevCh;

				//update term string to accurately check for terminator sequence
					//this code will revised to do the job more effiecently 
					temp=term[1];
					temp+=term[2];
					temp+=prevCh;
					term=temp;
					temp="";
					//cout << "{" << term << "}";
				//check for to see if terminal sequence is reached
					if(term==",,,")
					{
						// N = todec(headerInfo[0]); 
						//send string to become huffman tree
						populateFromHeader(headerInfo.substr(1));
						cout <<"\n\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n";
						walk();
						cout <<"\n\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n";
						buildHoffman();
						cout << "\n\n>>>>>>>>>>>>>>>>>>>>\n\n";
						inOrderPrint();
						cout << endl;
						//w.decompressTree.getHead();

						//cout << headerInfo << endl;
						//mark header as true
						w=head;
						header=true;
				
					}
					//move Ch along
					prevCh=ch;
			}
			else
				{
				//cout << prevCh;
				//fill buffer
				//system("pause");

				buffer=charToBinString(prevCh);

				//Traverse Tree w/buffer
				for(int i=0;i<8;i++)
				{
					if(buffer[i]=='1')
					{
						w=w->left;
					}
					else if(buffer[i]=='0')
					{
						w=w->right;
					}
					else
					{
						cout << "ERROR";
					}
					
					if(w->right==nullptr && w->left==nullptr)//we have a leaf & have reached a character
					{
						//write key
						//cout << w->key;
						fout << w->key;
						//move walker back to start of tree
						w=head;
					}
			
				}

			prevCh=ch;

				}
			}
		}
		else
		{
			cout << prevCh << ", " <<ch << "}";
				//LAST CHAR 
			//UNIQUE UPPER BOUND IS USED
			//Traverse Tree w/buffer
				for(int i=0;i<N ;i++)
				{
					
					if(buffer[i]=='1')
					{
						w=w->left;
					}
					else if(buffer[i]=='0')
					{
						w=w->right;
					}
					else
					{
						cout << "ERROR";
					}
					
					if(w->right==nullptr && w->left==nullptr)//we have a leaf & have reached a character
					{
						//write key
						fout << w->key;
						//cout << w->key;
						//move walker back to start of tree
						w=head;
					}
			
				}


				break;
		}

	/////

}
}

void Forest::populateFromHeader(string &header)
{
	//local vars
	//entry* table;
	string temp="";

	entry table[1000];
	bool key=false;
	int size=1;	//make room for first entry
	//table = new entry[size];
	string empt="";


	//last 3 characters are the terminator sequence: remove them

	header=header.substr(0,header.length()-3);
	//cout << header;
	//cout << endl << "!";
	//system("pause");



	//seperate info from string

	int k=0;
	for(int i=0; i < header.length(); i++)
	{
		if(header[i]==',')
			{
				if(!key)
				{
					table[k].key = header[i];	//set key
					table[k].code="";
					temp="";
					key=true;
						
				}
				else
				{
				
				//table[k].code=temp;
				size++; //make space for next entry
				k++;
				key=false;	//update key as not set
				//cout <<"*";
				}
			}
		else
		{
			if(!key) //if key is not set, set it
			{
			//	cout << header[i];
				table[k].key = header[i];	//set key
				table[k].code="";
				temp="";
				key=true;			//mark it as set

			}
			else
			{
				temp= temp + header[i];
				table[k].code=temp;
				
			}


		}
	}

	
	//populate
	for(int i=0; i < size; i++)
	{
		table[i].freq = stringToInt(table[i].code);
		addDefNode(table[i].key,stringToInt(table[i].code));
	}

	
	//system("pause");

}
void Forest::addDefNode(char key, int freq)
{
	//locals
	node* w; 
	node* newNode;

	w=nullptr;
	newNode = new node;
	
	if(head==nullptr)
	{
		newNode->key=key;
		newNode->freq=freq;
		newNode->priority=pCount;
		newNode->next=nullptr;
		newNode->right=nullptr;
		newNode->left=nullptr;
		head=newNode;
	}
	else
	{
	//	cout << "D";
		w=head;
		while(w->next!=nullptr)
			{
				w=w->next;
			}
		//once at end of list, create new node;
		newNode->key=key;
		newNode->freq=freq;
		newNode->priority=pCount;
		newNode->next=nullptr;
		newNode->right=nullptr;
		newNode->left=nullptr;
		
		//create link
		w->next=newNode;
	}

	length++;
	size++;
	pCount++;
}

int stringToInt(string freqString)
{
	int N=0;
	int power=1;
	int temp=0;
	int length=freqString.length();


	for(int i=0;i<length;i++)
	{

		//get matching char
		
		if(freqString[i]=='0')
			temp=0;
		else if(freqString[i]=='1')
			temp=1;
		else if(freqString[i]=='2')
			temp=2;
		else if(freqString[i]=='3')
			temp=3;
		else if(freqString[i]=='4')
			temp=4;
		else if(freqString[i]=='5')
			temp=5;
		else if(freqString[i]=='6')
			temp=6;
		else if(freqString[i]=='7')
			temp=7;
		else if(freqString[i]=='8')
			temp=8;
		else if(freqString[i]=='9')
			temp=9;

		N+= temp * pow(10.0,length-power);
	
		power++;

	}

	return N;
}

string charToBinString(unsigned char ch)
{
	string binaryRep="";

	int dec = static_cast<unsigned int>(ch);
//	cout << dec << endl;
	
	while(dec!=0)
	{
		binaryRep= to_string(dec % 2) + binaryRep;
		dec=dec/2;
	} 

	//number of values missing from 8 characters

	int N=8-binaryRep.length();
	
	if(N!=8)
		for(int i=0;i<N;i++)
			binaryRep = '0' + binaryRep;

	return binaryRep;
	
}