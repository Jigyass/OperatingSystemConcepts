#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filepath = "example.txt";

    // Open the file
    int fd = open(filepath, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Get the size of the file
    struct stat fileInfo;
    if (fstat(fd, &fileInfo) == -1) {
        perror("Error getting the file size");
        close(fd);
        return EXIT_FAILURE;
    }

    // Ensure the file is not empty
    if (fileInfo.st_size == 0) {
        fprintf(stderr, "Error: File is empty\n");
        close(fd);
        return EXIT_FAILURE;
    }

    // Map the file into memory
    char *mappedFile = mmap(NULL, fileInfo.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (mappedFile == MAP_FAILED) {
        perror("Error mapping the file");
        close(fd);
        return EXIT_FAILURE;
    }

    // Read from the mapped memory
    for (size_t i = 0; i < fileInfo.st_size; i++) {
        printf("%c", mappedFile[i]);
    }
    printf("\n");

    // Clean up
    munmap(mappedFile, fileInfo.st_size);
    close(fd);

    return EXIT_SUCCESS;
}

