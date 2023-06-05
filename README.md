# C-auto-complete-suggestions

This C program generates auto-complete suggestions similar to the behavior of Bash when beginning to type a command and pressing the "Tab" key. The program reads all file names in a user-provided directory and stores them in a data structure known as a Trie. The Trie is implemented using a linked list structure. Each letter of the alphabet has its own linked list within the Trie, storing filenames that start with that letter in alphabetical order.

The program allows the user to enter the beginning of a filename they are interested in. Upon pressing enter, all filenames that match that prefix will be printed in alphabetical order. The program will continue to prompt for filename prefixes until an empty string is entered.

To implement this functionality, the program includes the following functions:

- **createTrieNode():** Creates a new Trie node and initializes its fields.
- **insert():** Inserts a new word into the Trie recursively.
- **isEndOfWord():** Checks if a Trie node is the end of a word.
- **print():** Prints all filenames that match a given prefix in alphabetical order.
- **search():** Searches for a word in the Trie.
- **autosuggestion():** Provides auto-complete suggestions based on the entered prefix.

Additionally, the program includes the following helper functions:

- **letterNumb():** Handles special characters and converts uppercase letters to lowercase ASCII values.
- **invert_case():** Converts uppercase letters in filenames to lowercase.

To use the program, the user needs to provide the full path of the directory containing the files they want to autocomplete. The program then reads the filenames from that directory and constructs the Trie. The user can then enter prefixes of filenames to get auto-complete suggestions.

Please note that this program does not use any pre-existing C library functions for implementing the Trie. It is a manual implementation of the Trie data structure.

## Sample Interaction
```
$ ./filecomplete
 
Enter a folder name: /usr/bin
&gt; zi

Files starting with zi in /usr/bin:
zip 
zipcloak 
zipgrep 
zipinfo 
zipnote 
zipsplit 

&gt; zipc
Files starting with zipc in /usr/bin:

zipcloak
```
