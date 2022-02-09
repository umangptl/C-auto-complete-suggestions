#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>

#define Alphabet 26

/*--node in the Trie--*/
typedef struct TrieNode{
    /*-- 26 nodes--*/
    struct TrieNode *children[Alphabet];
    /*--to mark a char it contains--*/
    char character;
    /*--marking end of word--*/
    bool EndOfWord;
} TrieNode;

/*--create new node--*/
TrieNode *createTrieNode(){
    TrieNode *node;
    /*--allocates memory for nodes--*/
    node = malloc(sizeof(TrieNode));
    node->EndOfWord = false;
    /*-- making 26 nodes root--*/
    for(int i=0;i < Alphabet;i++){
        node->children[i] = NULL;
    }
    return node;
}

/*--insert new word to Trie recursively----*/
void insert(TrieNode *root, char *word){
    /*--check whether word character pointer is NULL--*/
    if (strlen(word) != 0){
        char character = *word;
        /*-- using -97 to place char in order 0-25--*/
        if (root->children[character - 97] == NULL){
            /*-- if there is not char there make one--*/
            TrieNode *node = NULL;
            node = createTrieNode();
            node->character = character;
            root->children[character - 97] = node;
        }
        /*--process the word if present--*/
        word++;
        insert(root->children[character - 97], word);
    }else {
        root->EndOfWord = true;
    }
}

/*--function to check if current node is leaf node--*/
bool isEndOfWord(TrieNode *root){
    return root->EndOfWord != false;
}

/*--function to print Trie  branch in alphabetical order--*/
void print( TrieNode *root,char *word, char str[],int level){
    /*--If node is leaf node, it indicates end of string--*/
    if (isEndOfWord(root)){
        /*--printing prefix--*/
        printf("%s",word);
        str[level]='\0';
        printf("%s\n",str);
    }
    /*--if child is found add parent key to str and--*/
    for(int i=0;i<Alphabet;i++){
        if (root->children[i]){
            str[level]= i + 'a';
            /*--call the print function recursively for child nodes--*/
            print(root->children[i],word,str,level+1);
        }
    }
}

/*--Search a word in the Trie--*/
void *search(TrieNode *root, char *word){
    TrieNode *temp;
    while (*word != '\0'){
        /*--processing each letter--*/
        char character = *word;
        if (root->children[character - 97] != NULL){
            temp = root->children[character - 97];
            word++;
            root = temp;
            /*--if prefix in null or not there--*/
        }else {
            perror("That fileName does not exist.\n");
            return 0;
        }
    }
    return root;
}
/*--autosuggestion the function called in main--*/
void autosuggestion(TrieNode *root, char *word){
    TrieNode *temp = NULL;
    /*--getting the nodes of prefix--*/
    temp = search(root,word);
    int level= 0;
    char str[20];
    /*--send it to print it out-**/
    print(temp,word,str,level);
}

/*-- handle the dots with Ascii--*/
int letterNumb(const char *firstchara){
    /*-- casting the value to change to int--*/
    int AsciiValue = (int)firstchara[0];
    if (AsciiValue == 46 || (AsciiValue >= 65 && AsciiValue <= 90) || (AsciiValue >= 97 && AsciiValue<= 122)){
     // dot value 46
        if(AsciiValue == 46)
            return 46;
        // changing fist value to lower then invert_case whole name
     if(AsciiValue >= 65 && AsciiValue <= 90)
         return  AsciiValue + 32;
     // dont change for lower case
        if (AsciiValue >= 97 && AsciiValue<= 122)
            return AsciiValue;
    }
}

/*-getting the filenames in lower if capital letter filename-*/
void invert_case(char* a) {
    while (*a != '\0') {
        if (*a >= 'A' && *a <= 'Z')
            *a = *a + 32;
        a++;
    }
}

int main(){
    TrieNode *root = NULL;
    root = createTrieNode();
    char folderName[100];
    char fileName[20];
    DIR *dir;
    struct dirent *dirctory;
    printf("Enter full path\n");
    scanf("%99s",folderName);
    dir = opendir(folderName);
    if (dir == NULL){
        perror("Path not found");
        return -1;
    }
    while (dirctory = readdir(dir)){
        if (letterNumb(dirctory->d_name)>= 97 && letterNumb(dirctory->d_name)<= 122){
            invert_case(dirctory->d_name);
            insert(root,dirctory->d_name);
        }
    }
    closedir(dir);

    while(fileName){
        printf("Enter prefix of fileName \n >>");
        scanf("%s", fileName);
        autosuggestion(root, fileName);
    }

   free(root);
    return 0;
}