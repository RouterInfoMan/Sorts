#ifndef SORTINGALGORITHMS_H_INCLUDED
#define SORTINGALGORITHMS_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <windows.h>
#include <iostream>
#include <functional>
#include <string>
#include <bits/stdc++.h>
#include <algorithm>
int BitNum(int n);
void BubbleSort(int v[]);
void CocktailSort(int v[]);
void insertionSort(int v[]);
void selectionSort(int v[]);
void shellSort(int v[]);
void shellSortCustomGaps(int v[]);
void QuickSortHoareInit(int v[]);
void QuickSortLomutoInit(int v[]);
void MergeSortInit(int v[]);
void radixsortLSDInit(int v[]);
void heapSort(int v[]);
void RadixSortMSDInit(int v[]);
void BogoSort(int v[]);
void LessBogoSort(int v[]);
void PancakeSort(int v[]);
void CombSort(int v[]);
void oddEvenSort(int v[]);
void CycleSort(int v[]);
void CountingSort(int v[]);
void HybridMergeSort(int arr[]);
void BeadSort(int v[]);
void introSortInit(int v[]);
void BinaryInsertionSort(int v[]);
#endif // SORTINGALGORITHMS_H_INCLUDED
