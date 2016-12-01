#include <iostream>

using namespace std;

inline int heap_parent(int i)
{
	return (i - 1) / 2;
}

inline int heap_left(int i)
{
	return 2 * i + 1;
}

inline int heap_right(int i)
{
	return 2 * i + 2;
}

template <typename T>
static void max_heapify(T *max_heap, int n, int i)
{
	int left = heap_left(i);
	int right = heap_right(i);
	int largest;

	if (left < n && max_heap[i] < max_heap[left]) largest = left;
	else largest = i;

	if (right < n && max_heap[largest] < max_heap[right]) largest = right;

	if (largest != i) {
		swap(max_heap[i], max_heap[largest]);
		max_heapify(max_heap, n, largest);
	}
}

template <typename T>
void print_k_min(T *d, int n, int k)
{
	if (d == NULL || n <= 0 || k <= 0 || n < k) {
		cout << "print_k_min parameter error!" << endl;
		return;
	}

	T *max_heap = new T[k];

	for (int i = 0; i < k; ++i)
		max_heap[i] = d[i];

	for (int i = k/2-1; i >= 0; --i)
		max_heapify(max_heap, k, i);

	for (int i = k; i < n; ++i) {
		if (d[i] < max_heap[0]) {
			max_heap[0] = d[i];
			max_heapify(max_heap, k, 0);
		}
	}

	for (int i = 0; i < k; ++i)
		cout << max_heap[i] << " ";
	cout << endl;

	delete[] max_heap;
}

int main()
{
	int d[20] = { 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

	print_k_min(d, sizeof(d)/sizeof(int), 6);

	return 0;
}
