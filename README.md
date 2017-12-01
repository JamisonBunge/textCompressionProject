# textCompressionProject
Created a alogorithm to compress .txt files using huffmen code principles 
devloped for: Microsoft Windows 


This code works by: 
  
  PART 1: Streaming in text file information and building huffman tree

  1) Reading in text file and keeping track of the frequency of each character
  2) After this is complete, the result is a linked list that with the character and its frequncy
  3) The list is then traversed and the two nodes with the lowest frequncy become the left and right children of a new node (with no character information).
  4) this new node is added to the original linked list and the two previously mentioned are removed
  5) this process is repeated until only one node remains in the original linked list; the resulting structure is a binary tree.
  6) Using huffman code principes, the binary tree can be considereda huffmen tree
          a) characters orginal charcter nodes are leaves of the tree
          b) a unique code of 1s and 0s is associated with each character by tracing its path from root to leave
                .) going to the left adds a 0 to its code 
                .) going to the right adds a 1 to its code 
  7) a table is created that maps each character to its new code
  
  PART 2: Compressing the file.
  
  1) The original text file is read in again
  2) Every time a character is read from the file, its code from the table is added to a buffer that can hold eight 1s or 0s
  3) Once this buffer is full, a character is is written to to the new compressed file whose ASCI value is the valve stored in the buffer
  4) This proccess is repeated until the entire original text file is read in.
  5) if the buffer has any left over information, it is filled with zeros and the final character is written to the file.
        a) the amount of 'fake zeros' is kept track of for decompression to keep the integredity of the data.
  6) A header is then included at beginning of the compressed file to use as a decompression key 
        a) this header is stored in its original text (does not get changed by the buffer)
  7) the header includes the number of fakes zeros, and the original character / frequncy information ( that was first used to build the huffmen tree)
  7 The compressed text file is saved as "orginalFileName"Compressed.txt
  
  PART 3: Decompressing the file 
  
  1) The header is read in first
       a) Part 1 is essentially repeated to recreated the original tree and table 
  2) The compressed file is read in, each character is converted to a string of its ASCII value
  3) The tree is then traversed using the buffer 
      .) a 0 means travel to left child
      .) a 1 means travel to right child
  4) Once a leave is reached, write the character valve and start back at the root
  5) on the final character read from the compressed text, the fake zeros are removed once the ASCII string is created
      a) Again this ensures the integrity of the file
  6) This decompressed text file is saves as "orginalFileName"Decompressed.txt
  
  
================================================================================================================
A noteable bug:
        There is a problem with the decompression procedure. With large files it will randomly stop the proccess in the middle of a file.
        the text that is decompressed before this random termination is the correct.
        
        There is no problem with compression large text files. 
