#include <iostream>
#include <string.h>
#include <emmintrin.h>

#ifdef VTUNE_ANALYSIS
#include <ittnotify.h>
#endif // VTUNE_ANALYSIS

#define N 1000

using namespace std;

int main() {

#ifdef VTUNE_ANALYSIS
    __itt_pause();
#endif // VTUNE_ANALYSIS

    int *matA[N];
    int *matB_T[N];
    int *matX[N];

    /* initialize matrix */
    cout << "Initializing data ..." << endl;

    for (int i = 0; i < N; ++i) {
        matA[i] = (int*) malloc(N * sizeof(int));
        matB_T[i] = (int*) malloc(N * sizeof(int));
        for (int j = 0; j < N; ++j) {
            matA[i][j] = i * N + j;
            matB_T[i][j] = i * N + j;
        }
    }

    for (int i = 0; i < N; ++i) {
        matX[i] = (int*) malloc(N * sizeof(int));
        memset(matX[i], 0, N);
    }


    /* cache-friendly matmul */
    cout << "Performing fast matrix multiplication ..." << endl;

#if (defined VTUNE_ANALYSIS && defined MM_FAST)
    __itt_resume();
#endif // VTUNE_ANALYSIS
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                matX[i][j] += matA[i][k] * matB_T[j][k];
            }
        }
    }
#if (defined VTUNE_ANALYSIS && defined MM_FAST)
    __itt_pause();
#endif // VTUNE_ANALYSIS


    /* cache-unfriendly matmul */
    cout << "Performing slow matrix multiplication ..." << endl;

#if (defined VTUNE_ANALYSIS && defined MM_SLOW)
    __itt_resume();
#endif // VTUNE_ANALYSIS
    for (int k = 0; k < N; ++k) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                matX[i][j] += matA[i][k] * matB_T[j][k];
            }
        }
    }
#if (defined VTUNE_ANALYSIS && defined MM_SLOW)
    __itt_pause();
#endif // VTUNE_ANALYSIS


    cout << "Done" << endl;

    return 0;
}
