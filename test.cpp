#include <iostream>
#include <stdlib.h>
#include <time.h>

#include <assert.h>

#include "reference.h"

const size_t TEST_DATA_SIZE = 1024 * 1000;

int main() {
    uint16_t* data = reinterpret_cast<uint16_t*>(malloc(TEST_DATA_SIZE * sizeof(uint16_t)));
    assert(data);

    // Initialize with random data
    srand(time(NULL));
    for (size_t i = 0; i < TEST_DATA_SIZE; i++) {
        data[i] = uint16_t(rand());
    }

    // Iterate with random offset and length
    for (int i = 0; i < 1000; i++) {
        size_t offset = rand() % (TEST_DATA_SIZE / 2);
        size_t len = rand() % (TEST_DATA_SIZE / 2);
        if (fletcher32_ref(data + offset, len) != fletcher32_naive(data + offset, len)) {
            std::cout<<"Reference vs naive, failed at iteration "<<i + 1<<std::endl;
            break;
        }
    }

    free(data);
    return 0;
}
