#pragma once

#include <algorithm>
#include <cmath>

template <typename T>
void insertionSort(T* array, int start, int end);

template <typename T>
void heapify(T* array, int heap_size, int i);

template <typename T>
void heapSort(T* array, int heap_size);

template <typename T>
void introSort(T* array, int start, int end, int maxdepth);

template <typename T>
void hybridIntroSort(T* array, int start, int end);