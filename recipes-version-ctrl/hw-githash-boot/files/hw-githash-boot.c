#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include "hw-githash-config.h"

//#define BASE_ADDR 0x40000000
#define MAP_SIZE 4096

int main() {
    int fd;
    volatile uint32_t *reg, *reg2, *reg3, *reg4;

    fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd < 0) {
        perror("Can't open /dev/mem. Make sure you have permissions.");
        return -1;
    }

    reg = mmap(NULL, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, BASE_ADDR);
    if (reg == MAP_FAILED) {
        perror("mmap operation failed");
        close(fd);
        return -1;
    }

    reg2 = reg + 4/sizeof(uint32_t);  // pointer arithmetic to the second register
    reg3 = reg + 8/sizeof(uint32_t);
    reg4 = reg + 0xC/sizeof(uint32_t);
    printf("----------------------------------------------------\n");
    printf("--------------------TDG Boot------------------------\n");
    printf("----------------------------------------------------\n");
    printf("Register at 0x%X: 0x%X\n", BASE_ADDR, *reg);
    printf("Register at 0x%X: 0x%X\n", BASE_ADDR + 4, *reg2);
    printf("Register at 0x%X: 0x%X\n", BASE_ADDR + 8, *reg3);
    printf("Register at 0x%X: 0x%X\n", BASE_ADDR + 0xC, *reg4);
    printf("----------------------------------------------------\n");
    printf("----------------------------------------------------\n");
    printf("----------------------------------------------------\n");

    munmap((void*)reg, MAP_SIZE);
    close(fd);
    return 0;
}