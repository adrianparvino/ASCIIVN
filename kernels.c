#include <immintrin.h>
#include <string.h>
#include <kernels.h>

inline void
hadd_(float * restrict x, float * restrict y)
{
	x = __builtin_assume_aligned (x, 32);
	y = __builtin_assume_aligned (y, 32);
#ifdef  __AVX2__
	__m256 mx = _mm256_load_ps(x);
	__m256 my = _mm256_load_ps(y);
	mx = _mm256_hadd_ps(mx, my);
	_mm256_store_ps(x, mx);
#else

	int i = 0;
	for (; i < 4; ++i)
		{
			x[i] = x[2*i] + x[2*i+1];
		}
	for (; i < 8; ++i)
		{
			x[i] = y[2*i - 8] + y[2*i - 7];
		}
#endif
}

inline void
hadd(float *x)
{
	x = __builtin_assume_aligned (x, 32);
#ifdef  __AVX2__
	__m256 mx = _mm256_load_ps(x);
	mx = _mm256_hadd_ps(mx, mx);
	_mm256_store_ps(x, mx);
#else
	float y [8] __attribute__ ((aligned (32))) = {0};
	memcpy(y, x, 8 * sizeof *y);

	hadd_(x, y);
#endif
}
