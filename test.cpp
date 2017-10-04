#include <iostream>
#include <stdlib.h>
#include <time.h>

#include <assert.h>

#include "reference.h"
#include "avx2.h"

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
    for (int i = 0; i < 10000; i++) {
        size_t offset = rand() % (TEST_DATA_SIZE / 2);
        size_t len =  rand() % (TEST_DATA_SIZE / 2);

        uint32_t sum1_left = rand() % 65535;
        uint32_t sum2_left = rand() % 65535;
        uint32_t sum1_right = sum1_left;
        uint32_t sum2_right = sum2_left;
        if (fletcher32_ref(data + offset, len, sum1_left, sum2_left) != fletcher32_naive(data + offset, len, sum1_right, sum2_right)) {
            std::cout<<"Reference vs naive, failed at iteration "<<i + 1<<std::endl;
            std::cout<<"Left: "<<sum1_left<<" "<<sum2_left<<std::endl;
            std::cout<<"Right: "<<sum1_right<<" "<<sum2_right<<std::endl;
            break;
        }
        if (fletcher32_ref(data + offset, len, sum1_left, sum2_left) != fletcher32_avx2(data + offset, len, sum1_right, sum2_right)) {
            std::cout<<"Reference vs AVX2, failed at iteration "<<i + 1<<std::endl;
            std::cout<<"Left: "<<sum1_left<<" "<<sum2_left<<std::endl;
            std::cout<<"Right: "<<sum1_right<<" "<<sum2_right<<std::endl;
            break;
        }
    }

    free(data);
    return 0;
}
