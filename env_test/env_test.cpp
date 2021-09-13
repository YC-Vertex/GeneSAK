#include <iostream>
#include <emmintrin.h>

#ifdef VTUNE_ANALYSIS
#include <ittnotify.h>
#endif // VTUNE_ANALYSIS

#define COUNT 100000

using namespace std;

int main() {

#ifdef VTUNE_ANALYSIS
    // __itt_domain *domain = __itt_domain_create("EnvTest.Domain");
    // __itt_string_handle *handle_vecadd = __itt_string_handle_create("vecadd");
    __itt_pause();
#endif // VTUNE_ANALYSIS

    int vec1[COUNT+5];
    int vec2[COUNT+5];
    int vecsum[COUNT+5];

    for (int i = 0; i < COUNT; ++i) {
        vec1[i] = i;
        vec2[i] = i;
    }

    for (int i = 0; i < COUNT; ++i) {
        _mm_clflush(&vec1[i]);
    }

#ifdef VTUNE_ANALYSIS
    // __itt_task_begin(domain, __itt_null, __itt_null, handle_vecadd);
    __itt_resume();
#endif // VTUNE_ANALYSIS
    for (int i = 0; i < COUNT / 100; ++i) {
		for (int j = 0; j < 100; ++j) {
			int index = i * 100 + j;
			vecsum[index] = vec1[index] + vec2[index];
		}
    }
#ifdef VTUNE_ANALYSIS
    // __itt_task_end(domain);
    __itt_pause();
#endif // VTUNE_ANALYSIS

    for (int i = 0; i < 5; ++i) {
        cout << vec1[i] << " + " << vec2[i] << " = " << vecsum[i] << endl;
    }
    cout << "..." << endl;
    cout << vec1[COUNT-1] << " + " << vec2[COUNT-1] << " = " << vecsum[COUNT-1] << endl;

    return 0;
}
