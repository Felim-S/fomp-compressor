#include <stdio.h>
#include <stdlib.h>

int main(void){
    FILE *f;
    
    // Test 1: All zeros (should compress very well)
    f = fopen("test_zeros.bin", "wb");
    for(int i = 0; i < 1000; i++) {
        fputc(0x00, f);  // 8000 zero bits
    }
    fclose(f);
    printf("Created test_zeros.bin: 1000 bytes of zeros\n");
    
    // Test 2: All ones (should compress very well) 
    f = fopen("test_ones.bin", "wb");
    for(int i = 0; i < 1000; i++) {
        fputc(0xFF, f);  // 8000 one bits
    }
    fclose(f);
    printf("Created test_ones.bin: 1000 bytes of ones\n");
    
    // Test 3: Alternating bytes (should expand badly)
    f = fopen("test_alternating.bin", "wb");
    for(int i = 0; i < 1000; i++) {
        fputc(0xAA, f);  // 10101010 pattern - lots of transitions
    }
    fclose(f);
    printf("Created test_alternating.bin: 1000 bytes of 0xAA (alternating bits)\n");
    
    // Test 4: Large blocks 
    f = fopen("test_blocks.bin", "wb");
    // 500 bytes of zeros, then 500 bytes of ones
    for(int i = 0; i < 500; i++) fputc(0x00, f);
    for(int i = 0; i < 500; i++) fputc(0xFF, f);
    fclose(f);
    printf("Created test_blocks.bin: 500 zeros + 500 ones\n");
    
    // Test 5: Random data (worst case)
    f = fopen("test_random.bin", "wb");
    srand(42);  // Fixed seed for reproducible results
    for(int i = 0; i < 1000; i++) {
        fputc(rand() % 256, f);
    }
    fclose(f);
    printf("Created test_random.bin: 1000 bytes of random data\n");

    return 0;
}
