//#define MAX1 448
//#define MAX1 512
//#define MAX1 1024
#define MAX1 4096

#include "MAX.h" //this header is for assigning MAX values and NUM_LOOP globally



//global data for sequentila matrix operations
unsigned char a_char[MAX1][MAX2] __attribute__(( aligned(16)));
unsigned char b_char[MAX2][MAX3] __attribute__(( aligned(16)));
unsigned char c_char[MAX1][MAX3] __attribute__(( aligned(16)));
unsigned short int temp[8];


int main()
{
	int i, j, w=0, sad=0;
	struct timespec tStart, tEnd;
 	double tTotal , tBest=10000;
 	//__m128i sad_temp;
 	__m128i vec1, vec2, vecT, sad_total;
 	sad_total= _mm_setzero_si128();
 	
	do{
		clock_gettime(CLOCK_MONOTONIC,&tStart);
	 
		
		
		
		for(i=0; i<MAX1; i++){
			//sad_temp= _mm_setzero_si128();
			for(j=0; j<MAX2; j+=16){//IACA_START
					
					//SAD3
					//sad_temp = _mm_sub_epi8 ( _mm_load_si128((__m128i *)&a_char[i][j]) ,  _mm_load_si128((__m128i *)&b_char[i][j]));
					//sad_temp = _mm_abs_epi8(sad_temp);
					//sad_total = _mm_add_epi16 ( sad_temp , sad_total);
					
					//SAD2
					//sad_temp = _mm_sub_epi8 ( _mm_load_si128((__m128i *)&a_char[i][j]) ,  _mm_load_si128((__m128i *)&b_char[i][j]));
					//sad_temp = _mm_sign_epi8(sad_temp , sad_temp);
					//sad_total = _mm_add_epi16 ( sad_temp , sad_total);
					
					
					//SAD1
					//sad_temp  = _mm_sad_epu8 ( _mm_load_si128((__m128i *)&a_char[i][j]) ,  _mm_load_si128((__m128i *)&b_char[i][j]));
					vec1 = _mm_load_si128((__m128i *)&a_char[i][j]);
					vec2 = _mm_load_si128((__m128i *)&b_char[i][j]);
					vecT = _mm_sad_epu8( vec1 , vec2);
					sad_total = _mm_add_epi16(vecT, sad_total);
					//sad_total = _mm_add_epi16 ( _mm_sad_epu8 ( _mm_load_si128((__m128i *)&a_char[i][j]) ,  _mm_load_si128((__m128i *)&b_char[i][j])) , sad_total);

				}//IACA_END
			}
		_mm_store_si128((__m128i *)&temp[0], sad_total);
		sad=temp[0]+temp[2]+temp[4]+temp[6];	
		
		clock_gettime(CLOCK_MONOTONIC,&tEnd);
		tTotal = (tEnd.tv_sec - tStart.tv_sec);
		tTotal += (tEnd.tv_nsec - tStart.tv_nsec) / 1000000000.0;
		if(tTotal<tBest)
			tBest=tTotal;
		pTime += tTotal;
		
	} while(w++ < NUM_LOOP && pTime < mTime);
	printf(" The best time: %lf sec in %d repetition for %dX result is %d matrix\n",tBest,w, MAX1, sad);
	//printf("%d \n", sad);
	return 0;
}

