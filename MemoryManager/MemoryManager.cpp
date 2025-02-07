#include "MemoryManager.h"
#include <iostream>
#include <functional>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <bitset>
#include <vector>

using namespace std;

//
// Joanna Mijares
//
//I'm very very grateful for my extensions, it helped me out so much. Thank you, Professor!
//and thank you to the TAs who helped me out :)

// do initialize, shutdown, allocate, free, getList and the allocators FIRST

MemoryManager::MemoryManager(unsigned wordSize, function<int(int, void *)> allocator){
  this-> wordSize = wordSize;
  this-> defaultAllocator = allocator;
}
//store wordsize
//store passed in allocator func as member var

MemoryManager::~MemoryManager(){
        shutdown();
        wordSize = 0;
        defaultAllocator = nullptr;
}
//deleted heap mem
//never called directly
//if obj initialized, call shutdown

void MemoryManager::initialize(size_t sizeInWords){

    if(sizeInWords > 65536) {
        return;
    }

    if(head!=nullptr) {
        shutdown();
    }
    if(memory!=nullptr){
        delete[] memory;
    }

    this->sizeinwords = sizeInWords;
    this->wordSize = wordSize;
    this-> defaultAllocator = defaultAllocator;

    int sizeInBytes = sizeInWords * wordSize;

    memory = new uint8_t[sizeInBytes];

    head = new Block(sizeInBytes, 0, true);
    
}
//check documentation

//CITE: https://www.geeksforgeeks.org/write-a-function-to-delete-a-linked-list/
//CITE: https://stackoverflow.com/questions/52691072/created-a-linked-list-but-how-to-delete-all-the-nodes-in-c
//CITE: https://www.alphacodingskills.com/cpp/ds/cpp-delete-all-nodes-of-the-doubly-linked-list.php
void MemoryManager::shutdown(){

    //blocks!

    while(head != nullptr) {
        Block* current = head->next;
        delete head;
        head = current;
    }

    //member vars!
    head = nullptr;
    sizeinwords = 0;
    //wordSize = 0; //might move to destructor
    delete[] memory;
    memory = nullptr;
    //defaultAllocator = nullptr;

}
//clears block data, frees heap mem, resets mem vars, clear data structures

void *MemoryManager::allocate(size_t sizeInBytes){
    
    size_t numWords;

    if(wordSize == 0){
        return 0;
    }

    if(sizeInBytes % wordSize > 0 ) {
         numWords = (sizeInBytes / wordSize) + 1;
    }else {
        numWords = sizeInBytes / wordSize;
    }

    //CITE: https://stackoverflow.com/questions/2622441/c-integer-floor-function
    uint16_t* arr = static_cast<uint16_t *>(getList());

    if(arr == nullptr) {
        delete[] arr;
        return nullptr;
    }

    int offset = defaultAllocator(numWords, arr);
    int offsetBytes = offset*wordSize;

    Block* current = head;

    //CITE: https://www.geeksforgeeks.org/delete-a-node-in-a-doubly-linked-list/
    //CITE: https://stackoverflow.com/questions/23718785/how-to-change-linkedlist-head-pointer-globally-and-not-locally

    while(current != nullptr) {


        if(offset == current->first && sizeInBytes == current->size && current->isfree == true) {
            current->isfree = false;
            break;
        }else if(offset == current->first && sizeInBytes < current->size && current->isfree == true){
            //if at the start!  
            Block *newBlock = new Block(sizeInBytes, offset, false);

            //this little if statement fixed so many issues ;-;
            if(current == head){
                head = newBlock;
            }

            newBlock->next = current;
            newBlock->prev = current->prev;

            if(current->prev != nullptr){
                current->prev->next = newBlock;
            }

            current->prev = newBlock;
            current->first = current->first + numWords;
            current->size = current->size - sizeInBytes;

            break;

        }else if(offset > current->first && sizeInBytes < current->size && current->first + (current->size/wordSize) - numWords == offset && current->isfree == true){
            //the end!

            Block *newBlock = new Block(sizeInBytes, offset, false);
            newBlock->next = current->next;
            current->next->prev = newBlock;
            newBlock->prev = current;
            current->next = newBlock;
            current->size = current->size - sizeInBytes;
        
            break;

        }else if(offset > current->first && offset < current->next->first && sizeInBytes < current->size && current->first + (current->size/wordSize) - numWords < offset && current->isfree == true){
            //in the middle

            Block *newBlock = new Block(sizeInBytes, offset, false);
            Block *endBlock = new Block(current->size-sizeInBytes, offset+numWords, true);
            current->next->prev = endBlock;
            endBlock->next = current->next;
            current->next = newBlock;
            newBlock->next = endBlock;
            newBlock->prev = current;
            endBlock->prev = newBlock;
            current->size = current->size - sizeInBytes - endBlock->size;
        
            break;
        }

        current = current->next;
    }

    //nothing to allocate :(
    if(current == nullptr){
        delete[] arr;
        return nullptr;
    }

    //delete!
    delete[] arr;

    return (void*)(memory + offset*wordSize);

    //bytes "rented out"
    //allocate more and more heap memory
    //free the memory getlist allocated (delete)
    //return a ptr in mem block to starting location of newly allocated space
}


//CITE: https://www.geeksforgeeks.org/cpp-program-for-deleting-a-node-in-a-linked-list/
//CITE: https://www.geeksforgeeks.org/delete-a-node-in-a-doubly-linked-list/
//CITE: https://www.alphacodingskills.com/cpp/ds/cpp-doubly-linked-list-traversal.php
//CITE: https://stackoverflow.com/questions/70468653/traverse-a-doubly-linked-list-to-a-given-index
//CITE: https://stackoverflow.com/questions/40219833/removing-nodes-from-linked-list-not-working-properly

void MemoryManager::free(void *address){

    Block* current = head;

    //for every node/block...
    while(current != nullptr) {

        //if the address to free is within the current block (greater than start of block, less than end of block)
        if(address >= (void*)(memory+(current->first*wordSize)) && address < (void*)((memory+(current->first*wordSize)) + current->size)) {

            //no neighbors
            if(current->prev != nullptr && current->next != nullptr && current->next->isfree == false && current->prev->isfree == false){
                current->isfree = true;
                return;
            }

            //if its the head + no neighbors
            if(head == current && current->next != nullptr && current->next->isfree == false){
                current->isfree = true;
                return;
            }

            //if next is hole
            if(current->next != nullptr && current->next->isfree == true) {
                current->isfree = true;
                Block* temp = current->next;
                current->size += temp->size;
                current->next = temp->next;
                if(temp->next != nullptr){
                    temp->next->prev = current;
                }
                delete temp;
              
            }
            //if prev is hole
            if(current->prev != nullptr && current->prev->isfree == true) {
                current->isfree = true;
                Block* temp = current->prev;
                current->first = temp->first;
                current->size += temp->size;
                if(temp == head){
                    head = current;
                }else{
                    current->prev = temp->prev;
                }
                if(temp->prev != nullptr){
                    temp->prev->next = current;
                }
                delete temp;
                
            }
           
        }

        if(current->next!=nullptr){
            current = current->next;
        }else{
            return;
        }
    }
    //TO DO:
    // addr is starting loc of space to be freed
    //will match smth from allocate in the last
    //if block freed, prev hole gets extended
    //freeing block in middle != new hole
    return;
}

void MemoryManager::setAllocator(function<int(int, void *)> allocator){
    this->defaultAllocator = allocator;
}

int MemoryManager::dumpMemoryMap(char *filename){

    //CITE: https://www.geeksforgeeks.org/input-output-system-calls-c-create-open-close-read-write/
    
    int fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0777);

    if(fd == -1) {
        perror("open failed");
        return -1;
    }

    uint16_t* arr = static_cast<uint16_t *>(getList());

    //CITE: https://stackoverflow.com/questions/11063748/output-commas-between-elements
    //CITE: https://stackoverflow.com/questions/35185503/how-to-write-to-a-file-using-open-and-printf
    //CITE: https://stackoverflow.com/questions/47874098/writing-a-list-of-integers-to-a-file-using-write
    //CITE: https://cplusplus.com/reference/cstdio/sprintf/

    char buffer[1024];
    int strSize;

    for(int i=1; i<=(2*arr[0]); i++) {

        if(i % 2 == 0 && i != arr[0]*2) {
            strSize = sprintf(buffer, "[%d, %d] - ", arr[i-1], arr[i]);
            write(fd, buffer, strSize);
        }else if(i%2 == 0 && i == arr[0]*2) {
            strSize = sprintf(buffer, "[%d, %d]", arr[i-1], arr[i]);
            write(fd, buffer, strSize);
        }
    }

    close(fd);

    delete[] arr;


  return 0;
}

//getlist.. scary
void *MemoryManager::getList(){

    if(!head) {
        return nullptr;
    }

    if(!memory){
        return nullptr;
    }

    int numHoles = 0;

    Block* current = head;

    //go through every block
    while (current != nullptr) {
        //number of holes AKA arr[0]
        if(current->isfree){
            numHoles ++;
        }
        current = current->next;
    }

    //2 bit array to return
    uint16_t* arr = new uint16_t[(2*numHoles)+1];

    if(arr == nullptr){
        return nullptr;
    }

    arr[0] = numHoles;

    if(numHoles == 0){
        return arr;
    }
    
    //add values to arr
    //this is incorrect rn
    Block* curr = head;

    int arrIndex = 1;

    while (curr != nullptr) {

        int arrSize = 0;
        
        if(wordSize != 0 && curr->size !=0){
            arrSize = (curr->size)/wordSize;
        }

        if(curr->isfree == true){
            arr[arrIndex] = curr->first;
            arrIndex ++;
            arr[arrIndex] = arrSize;
            arrIndex ++;
        }

        if(curr->next!=nullptr){
            curr = curr->next;
        }else{
            return arr;
        }
    }

    return arr;
 }

unsigned MemoryManager::getWordSize(){
    return wordSize;
}

void *MemoryManager::getMemoryStart(){
    return memory;
}

unsigned MemoryManager::getMemoryLimit(){
    unsigned sizeInBytes = wordSize * sizeinwords;
    return sizeInBytes;
    //total bytes u can store
}

int bestFit(int sizeInWords, void *list){

    //CITE: https://stackoverflow.com/questions/27852372/void-typed-function-parameter
    
    uint16_t* arr = (uint16_t*)list;

    int sizeinbytes = sizeInWords;

    if(!arr) {
        return -1;
    }else if(arr[0] == 0){
        return -1;
    }

    int offset = -1;
    int smallestHole = arr[2];
    //starting at arr[2] because it's the first length value

    for(int i=1; i <= 2*arr[0] ; i++) {
        if(i % 2 == 0) {
            if(arr[i]<=smallestHole && arr[i]>=sizeInWords) {
                smallestHole = arr[i];
                offset = arr[i-1];
            }
        }
    }
    //list is like getlist
    //hole in list that best fits (aka smallest hole)
    //returns word offset (aka num before size)

    return offset;
}

int worstFit(int sizeInWords, void *list){

    uint16_t* arr = (uint16_t*)list;

    if(!arr) {
        return -1;
    }else if(arr[0] == 0){
        return -1;
    }

    int offset = -1;
    int largestHole = arr[2];
    //starting at arr[2] because it's the first length value

    for(int i=1; i <= 2*arr[0] ; i++) {
        if(i % 2 == 0) {
            if(arr[i]>=largestHole && arr[i]>=sizeInWords) {
                largestHole = arr[i];
                offset = arr[i-1];
            }
        }
    }

    //list like getList
    //hole in list that is largest

    return offset;

}

