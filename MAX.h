//included library
#include <immintrin.h>
#include <stdio.h>
#include <time.h>
#include <sched.h> 
//#include "iacaMarks.h"
#define singleCore assignToThisCore(2,3);//  -D _GNU_SOURCE should be added to command line
cpu_set_t  mask;


//#define MAX1 192
//#define MAX1 224

//#define MAX1 384
//#define MAX1 448

//#define MAX1 672

//#define MAX1 1600

//#define MAX1 128
//#define MAX1 256
//#define MAX1 512
//#define MAX1 1152
//#define MAX1 1888
//#define MAX1 2016

//FIR 
//#define MAX1 4096*4096

//#define MAX1 128
//#define MAX1 1024

#define MAX1 128
#define MAX2 MAX1
#define MAX3 MAX1

#define NUM_LOOP 1000

//temporal array for printing vectors
unsigned short int tempi16[16];
int tempi32[8];
float tempps[8];


//print a integer vector 
void printVeci16(__m256i vec)
{
	_mm256_store_si256((__m256i *)&tempi16[0], vec);
	printf("tempi16[0]= %u, tempi16[1]=%u, tempi16[2]=%u, tempi16[3]=%u, tempi16[4]=%u, tempi16[5]=%u, tempi16[6]=%u, tempi16[7]=%u, tempi16[8]= %u,	  tempi16[9]=%u, tempi16[10]=%u, tempi16[11]=%u, tempi16[12]=%u, tempi16[13]=%u,  tempi16[14]=%u, tempi16[15]=%u \n\n",
	 tempi16[0],tempi16[1],tempi16[2],tempi16[3],tempi16[4],tempi16[5],tempi16[6],
	 tempi16[7],tempi16[8],tempi16[9],tempi16[10],tempi16[11],tempi16[12],tempi16[13],tempi16[14],tempi16[15]  ) ;

}
void printVeci32(__m256i vec)
{
	_mm256_store_si256((__m256i *)&tempi32[0], vec);
	printf("tempi32[0]= %d, tempi32[1]=%d, tempi32[2]=%d, tempi32[3]=%d, tempi32[4]=%d, tempi32[5]=%d, tempi32[6]=%d, tempi32[7]=%d \n\n",
	 tempi32[0],tempi32[1],tempi32[2],tempi32[3],tempi32[4],tempi32[5],tempi32[6],
	 tempi32[7]) ;

}
//print a float vector 
void printVecps(__m256 vec)
{
	_mm256_store_ps(&tempps[0], vec);
	printf(", tempps[0]=%3.2f, tempps[1]=%3.2f, tempps[2]=%3.2f, tempps[3]=%3.2f, tempps[4]=%3.2f, tempps[5]=%3.2f, tempps[6]=%3.2f, tempps[7]=%3.2f \n",
	tempps[0],tempps[1],tempps[2],tempps[3],tempps[4],tempps[5],tempps[6],tempps[7]) ;

}
//print a float matrix
void printMatrixf(float a[MAX1][MAX2])
{
	int i,j;
	printf("The matrix is :\n" );
	for(i=0; i<MAX1; i++){
		
		for(j=0; j<MAX2; j++){
			printf("%3.2f , ", a[i][j]);
			
		}
		printf("\n");
	}
}
//print an integer matrix
void printMatrixi(int a[MAX1][MAX2])
{
	int i,j;
	printf("The matrix is :\n" );
	for(i=0; i<MAX1; i++){
		
		for(j=0; j<MAX2; j++){
			printf("%3d , ", a[i][j]);
			
		}
		printf("\n");
	}
}
// for increamenting a vector by 1
inline __m256i _mm256_inc_epi16(__m256i a)
{
    return _mm256_add_epi16(a, _mm256_set1_epi16(1));
}
// my horizontal addition of epi32
inline int _mm256_hadd2_epi32(__m256i a)
{
	__m256i a_hi;
	a_hi = _mm256_permute2x128_si256(a, a, 1); //maybe it should be 4 
	a = _mm256_hadd_epi32(a, a_hi);
	a = _mm256_hadd_epi32(a, a);
	a = _mm256_hadd_epi32(a, a);
	return _mm256_extract_epi32(a,0);
}
// my horizontal addition of ps
inline float _mm256_hadd2_ps(__m256 p)
{
	__m256 p_hi;
	p_hi = _mm256_permute2f128_ps(p, p, 1); //maybe it should be 4 
	p = _mm256_hadd_ps(p, p_hi);
	p = _mm256_hadd_ps(p, p);
	p = _mm256_hadd_ps(p, p);
	//return _mm256_extract_ps(p,0);
}
//for assigning a core to the program I use this 
void assignToThisCore(int core_id1, int core_id2)
{
	CPU_ZERO(&mask);
	CPU_SET(core_id1, &mask);
	CPU_SET(core_id2, &mask);

	sched_setaffinity(0, sizeof(mask), &mask);
}



