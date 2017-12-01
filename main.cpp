
#include <iostream>
#include <fstream> 
#include <string>
#include "Forest.h"
using namespace std;

bool compressProcedure(string fileName);
bool decompressProcedure(string fileName);

int main()
{
	int choice=0;
	string fileName;

	while(true)
	{
		//prompt user
		cout << "=====================================================\n\n";
		cout << "1] Compress Text File\n2] Decompress Text File\n3] Exit Program\n\n>>";
		cin >> choice; 
		cin.ignore();

		if(choice==1)
		{
			
			cout << "\nFILE NAME: ";
			std::getline(cin,fileName);
			bool b=compressProcedure(fileName);

		}
		else if(choice==2)
		{
			cout << "\nFILE NAME: ";
			std::getline(cin,fileName);
			bool b=decompressProcedure(fileName);
		}
		else if (choice==3)
		{
			break;
		}
		else
		{
			cout <<"\nERROR: Please select one of the option!\n";
		}
	}
	
	return 0;
}


bool compressProcedure(string fileName)
{
	system("CLS");
	cout << "=====================================================\n\n";
	cout << "COMPRESSING...\n\n";

	//create Forest
	Forest tree;
	//populate original chain of tree nodes with file information
	tree.populate(fileName);
//
//	tree.walk();

	//create header from this chain
		//this ensures that the future decompression tree with not have issues with
		//nodes that have equal freq's

		string header = tree.createHeader();
		//this string will need to be ammended before the header is finished
		//it is missing the lastCharUpperBound at the start of it
		
		//build the hoffman tree from this original list
		//equal frequnices are resolved by taking the node with the lower priority
		
		tree.buildHoffman();

		//tree.inOrderPrint();

		//get table with codes
		//this table will gather the key's and assign them their huffman code
		//dirved from the Hoffman tree
//
		entry* table = tree.passTable();


		//temp, used to check codes
		cout << endl;
		/*for(int i=0; i< tree.getLeavesNum(); i++)
		{
			cout << table[i].key << ":" << table[i].code << " " << table[i].freq << endl;
		}*/

		compressAndWrite(table,tree.getLeavesNum(),fileName,header);


		cout << fileName << " was compressed!\n";

		system("pause");
		system("CLS");


	return true;
}

bool decompressProcedure(string fileName)
{
	//crate tree
	Forest decompressTree;
	
	//decompress
	decompressTree.decodeFile(fileName);
	
	return true;
}