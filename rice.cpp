#include <stdint.h>
#include <ap_int.h>
#include <iostream>

using namespace std;

#define LINE_LENGTH 1928
#define K 4

int compress_line(uint8_t * pixels, uint8_t * output)
{
    uint16_t out_index = 0;
    uint8_t prev = 0;
    uint16_t bits = 0;
    ap_uint<20> temp = 0;
    for (uint16_t i = 0; i < LINE_LENGTH; i++)
    {
        int16_t diff = pixels[i] - prev;
        ap_int<16> pos = diff << 1;
        if (pos < 0)
            pos = -pos + 1;
        prev = pixels[i];
        ap_uint<8> q = pos >> K;
        // Find the number of 1's in q
        cout << std::dec << "i: " << (int)i << std::hex << " P: " << (int)pixels[i] << " q: " << q;
        if (q != 0)
        {
            ap_uint<8> ones = 32 - __builtin_clz(q);
            temp.range(ones, 0) = q.range(ones, 0);
            cout << " Ones: " << ones << " Temp: " << temp;
            temp <<= ones;
            bits += ones;
        }
        temp <<= 1;
        temp[0] = 0;
        bits += 1;
        // Write the k bits
        temp.range(K, 0) = pos.range(K, 0);
        bits += K;

        cout << " Temp: " << temp << " Bits: " << bits;
        if (bits >= 8)
        {
            int temp2 = temp.range(bits, bits - 8);
            output[out_index++] = temp.range(bits, bits - 8);
            bits -= 8;
        }
        cout << " Temp: " << temp << " Bits: " << bits << endl;
    }

    return out_index;
}
