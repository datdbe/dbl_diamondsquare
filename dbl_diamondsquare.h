// dbl_diamondsquare.h
// public domain
//
// LICENSE
//
//   This software is in the public domain. Where that dedication is not
//   recognized, you are granted a perpetual, irrevocable license to copy,
//   distribute, and modify this file as you see fit.
//
//

// Usage:
// Do
//     #define STB_PERLIN_IMPLEMENTATION
// in *one* CPP file that includes this file, and then include this file for usage


// Documentation:
// data: pointer to float array - must be size*size length
// size: size of the generated array - must be of form (2^n)+1
// minValue: Minimum value of the generated data
// maxValue: Maximum value of the generated data
// noiseValue: Determines the contrast of the data - lower values gives a blurred result, higher values gives a higher contrasted value.

typedef unsigned __int32 power_of_two_plus_one;
extern void dbl_generate_diamondsquare_array(float* data, power_of_two_plus_one size, float minValue, float maxValue, float noiseValue);

#ifdef DBL_DIAMONDSQUARE_IMPLEMENTATION
#include <stdlib.h>

#define __dbl_random (double)rand() / ((double)RAND_MAX + 1)
#define __dbl_random_range(min, max) ((min) + ((max) - (min))*(__dbl_random))


inline int __dbl__xy_to_index(int x, int y, int size)
{
	return (((y)* (size)) + (x));
}



void dbl_generate_diamondsquare_array(float* data, power_of_two_plus_one size, float minValue = 0.0f, float maxValue = 1.0f, float noiseValue = .07f)
{
	const unsigned int sizeMinusOne = size - 1;
	for (size_t y = 0; y < size; y++)
	{
		for (size_t x = 0; x < size; x++)
		{
			data[y*size + x] = 0;

		}
	}

	data[__dbl__xy_to_index(sizeMinusOne, 0, size)] = __dbl_random;
	data[__dbl__xy_to_index(sizeMinusOne, 0, size)] = __dbl_random;

	data[__dbl__xy_to_index(0, sizeMinusOne, size)] = __dbl_random;
	data[__dbl__xy_to_index(sizeMinusOne, sizeMinusOne, size)] = __dbl_random;

	int x = (size - 1) * sizeMinusOne + 0;

	float sample0, sample1, sample2, sample3;
	float d0, d1, d2, d3, cn;


	float noiseModifier = 0;

	for (int iteration = sizeMinusOne; iteration > 1; iteration /= 2)
	{
		noiseModifier = (maxValue - minValue) * noiseValue * ((float)iteration / sizeMinusOne);

		for (int y = 0; y < sizeMinusOne; y += iteration)
		{
			for (int x = 0; x < sizeMinusOne; x += iteration)
			{
				sample0 = data[__dbl__xy_to_index(x, y, size)];
				sample1 = data[__dbl__xy_to_index(x + iteration, y, size)];
				sample2 = data[__dbl__xy_to_index(x, y + iteration, size)];
				sample3 = data[__dbl__xy_to_index(x + iteration, y + iteration, size)];

				float avg = (sample0 + sample1 + sample2 + sample3) / 4.0f;
				data[__dbl__xy_to_index(x + (iteration / 2), y + (iteration / 2), size)] = avg + __dbl_random_range(-noiseModifier, noiseModifier);
			}
		}

		for (int y = 0; y < sizeMinusOne; y += iteration)
		{
			for (int x = 0; x < sizeMinusOne; x += iteration)
			{
				sample0 = data[__dbl__xy_to_index(x, y, size)];
				sample1 = data[__dbl__xy_to_index(x + iteration, y, size)];
				sample2 = data[__dbl__xy_to_index(x, y + iteration, size)];
				sample3 = data[__dbl__xy_to_index(x + iteration, y + iteration, size)];
				cn = data[__dbl__xy_to_index(x + (iteration / 2), y + (iteration / 2), size)];

				if (y <= 0)
					d0 = (sample0 + sample1 + cn) / 3.0f;
				else
					d0 = (sample0 + sample1 + cn + data[__dbl__xy_to_index(x + (iteration / 2), y - (iteration / 2), size)]) / 4.0f;

				if (x <= 0)
					d1 = (sample0 + cn + sample2) / 3.0f;
				else
					d1 = (sample0 + cn + sample2 + data[__dbl__xy_to_index(x - (iteration / 2), y + (iteration / 2), size)]) / 4.0f;

				if (x >= sizeMinusOne - iteration)
					d2 = (sample1 + cn + sample3) / 3.0f;
				else
					d2 = (sample1 + cn + sample3 + data[__dbl__xy_to_index(x + iteration + (iteration / 2), y + (iteration / 2), size)]) / 4.0f;

				if (y >= sizeMinusOne - iteration)
					d3 = (cn + sample2 + sample3) / 3.0f;
				else
					d3 = (cn + sample2 + sample3 + data[__dbl__xy_to_index(x + (iteration / 2), y + iteration + (iteration / 2), size)]) / 4.0f;

				data[__dbl__xy_to_index(x + (iteration / 2), y, size)] = d0 + __dbl_random_range(-noiseModifier, noiseModifier);
				data[__dbl__xy_to_index(x, y + (iteration / 2), size)] = d1 + __dbl_random_range(-noiseModifier, noiseModifier);
				data[__dbl__xy_to_index(x + iteration, y + (iteration / 2), size)] = d2 + __dbl_random_range(-noiseModifier, noiseModifier);
				data[__dbl__xy_to_index(x + (iteration / 2), y + iteration, size)] = d3 + __dbl_random_range(-noiseModifier, noiseModifier);
			}
		}

	}
}
#endif