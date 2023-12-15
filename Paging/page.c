#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PAGE_SIZE_BITS 12 // Page size of 4096 bytes (2^12)
#define NUM_PAGES 1024 // Number of pages in the logical address space
#define NUM_FRAMES 1024 // Number of frames in the physical address space

// Function to simulate the creation of a page table for 'n' number of pages.
int* create_page_table(unsigned int num_pages, unsigned int num_frames) {
    int *page_table = malloc(num_pages * sizeof(int));
    srand((unsigned int)time(NULL)); // Seed the random number generator with the current time

    for (unsigned int i = 0; i < num_pages; ++i) {
        // Assign a random frame number for each page. Here, it is assumed that the
        // number of frames is equal to the number of pages for simplicity.
        // In a real system, you would need to handle the case where multiple pages
        // might be mapped to the same frame (e.g., with shared memory).
        page_table[i] = rand() % num_frames;
    }
    return page_table;
}

// Function to translate a logical address to a physical address using the page table.
unsigned int translate_address(int *page_table, unsigned int logical_address) {
    unsigned int page_number = logical_address >> PAGE_SIZE_BITS; //Calculate page number by setting everything to 0 except MSB
    unsigned int offset = logical_address & ((1 << PAGE_SIZE_BITS) - 1); // Calculate offset by using a bit mask
    unsigned int frame_number = page_table[page_number]; //looks up the frame number; Check if it is available
    return (frame_number << PAGE_SIZE_BITS) | offset; //Construct the physical address 
}

int main() {
    // Create a page table with random mappings
    int *page_table = create_page_table(NUM_PAGES, NUM_FRAMES);

    // Simulate logical address translation
    unsigned int logical_address;
    printf("Enter a logical address (in decimal): ");
    scanf("%u", &logical_address);

    // Translate the logical address to a physical address using the page table
    unsigned int physical_address = translate_address(page_table, logical_address);
    printf("Logical Address: %u, Physical Address: %u\n", logical_address, physical_address);

    // Cleanup
    free(page_table);

    return 0;
}
