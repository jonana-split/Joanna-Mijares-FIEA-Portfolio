#include <cstdint>
#include <functional>
#include <iostream>
using namespace std;

// linked list, stores blocks/holes in memory
//CITE: https://www.geeksforgeeks.org/doubly-linked-list/
struct Block {
  int size;
  uint16_t first;
  bool isfree;

  Block* prev;
  Block* next;

  Block(int x, uint16_t firstX, bool freeX) {
    size = x;
    first = firstX;
    isfree = freeX;
    prev = next = nullptr;
  }

};

class MemoryManager
  {
    public:
      MemoryManager(unsigned wordSize, function<int(int, void *)> allocator);
      ~MemoryManager();
      void initialize(size_t sizeInWords);
      void shutdown();
      void* allocate(size_t sizeInBytes);
      void free(void *address);
      void setAllocator(function<int(int, void *)> allocator);
      int dumpMemoryMap(char *filename);
      void *getList();
      unsigned getWordSize();
      void *getMemoryStart();
      unsigned getMemoryLimit();
    private:
      uint8_t* memory = nullptr;
      Block* head = nullptr;
      int wordSize;
      int sizeinwords;
      function<int(int, void *)> defaultAllocator;
  };

int bestFit(int sizeInWords, void *list);
int worstFit(int sizeInWords, void *list);
