#include <stdint.h>
#include <iostream>
#include <stdio.h>

using namespace std;

extern int compress_line(uint8_t * pixels, uint8_t * output);

int main()
{
    printf("Hello world\n");

	FILE * f = fopen("/home/nlbutts/temp/image.bin", "rb");
	fseek(f, 0, SEEK_END);
    size_t size = ftell(f);
	fseek(f, 0, SEEK_SET);

    uint8_t * data = new uint8_t[size];
    fread(data, 1, size, f);
    fclose(f);

    uint8_t * line_ch_data_b = new uint8_t[1928];
    uint8_t * line_ch_data_g = new uint8_t[1928];
    uint8_t * line_ch_data_r = new uint8_t[1928];

    uint8_t * output_line_ch_data_b = new uint8_t[1928];
    uint8_t * output_line_ch_data_g = new uint8_t[1928];
    uint8_t * output_line_ch_data_r = new uint8_t[1928];

    uint32_t compressed_size = 0;

    for (int line = 0; line < 10; line++)
    {
        uint8_t * linedata = &data[1928*3*line];
        for (int w = 0; w < 1928; w++)
        {
            line_ch_data_b[w] = linedata[(w * 3)+ 0];
            line_ch_data_g[w] = linedata[(w * 3)+ 1];
            line_ch_data_r[w] = linedata[(w * 3)+ 2];
        }
        int comp_size_b = compress_line(line_ch_data_b, output_line_ch_data_b);
        int comp_size_g = compress_line(line_ch_data_g, output_line_ch_data_g);
        int comp_size_r = compress_line(line_ch_data_r, output_line_ch_data_r);

        compressed_size += comp_size_b;
        compressed_size += comp_size_g;
        compressed_size += comp_size_r;
    }

    uint32_t input_size = 10 * 1928 * 3 * 8;
    compressed_size *= 8;
    cout << std::dec << "Input size: " << input_size << " compressed size: " << compressed_size << endl;

    delete [] data;

    delete [] line_ch_data_b;
    delete [] line_ch_data_g;
    delete [] line_ch_data_r;

    delete [] output_line_ch_data_b;
    delete [] output_line_ch_data_g;
    delete [] output_line_ch_data_r;
}
