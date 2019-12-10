/// c u r s e d
#include "SortingAlgorithms.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <windows.h>
#include <iostream>
#include <functional>
#include <string>
#include <bits/stdc++.h>
#include <climits>
extern int Comps, Swaps, maxx, Marked[1000], n;
extern float delay;
const sf::Time OneMilisecondSleep = sf::milliseconds(1);
const sf::Time OneMicrosecondSleep = sf::microseconds(1);
extern bool StartedSorting, lostFocus, raisedStoppedSorting;
extern sf::Sound sound1, sound2;
void setPitch(sf::Sound &sound, int element){
    sound.stop();
    sound.setPitch((static_cast<float>(element)/(n-1) * 1.7) + 0.5f);
}
void finishedsort(int v[]){
    for(int i = 0; i < n; i++){
        Marked[i] = 10;
        setPitch(sound1, v[i]);
        sound1.play();
        for(int k = 0; k < 5000000/(n*2) && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);
    }
    sound1.stop();
}
void smecherShuffle(int v[]){
    for(int i = 0; i <=n/2; i++){
        int randomIndex1 = rand ()%n, randomIndex2;
        while((randomIndex2 = rand ()%n)==randomIndex1){
        }
        Marked[randomIndex1] = 1;
        Marked[randomIndex2] = 1;
        std::swap(v[randomIndex1], v[randomIndex2]);
        Swaps++;
        setPitch(sound1, v[randomIndex1]);
        sound1.play();
        setPitch(sound2, v[randomIndex2]);
        sound2.play();
        for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);
        Marked[randomIndex1] = 0;
        Marked[randomIndex2] = 0;
    }
    sound1.stop();
    sound2.stop();
}
void reset(){
    StartedSorting = false;
    memset(Marked, 0, sizeof(Marked));
}
int BitNum(int n){
	int c = 0;
	if(n==0) return 1;
	while(n){
		n>>=1;
		c++;
	}
	return c;
}
void BubbleSort(int v[]){
    bool sorted = false;
    int k = 0;
    while(!sorted){
        sorted = true;
        for(int i = 0; i<n-1-k; i++){
            Marked[i] = 10;
            if(v[i]>v[i+1]){
                std::swap(v[i], v[i+1]);
                Marked[i+1] = 1;
                sorted = false;
                Swaps++;
            }
            if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
            }
            setPitch(sound1, v[i]);
            setPitch(sound2, v[i+1]);
            sound1.play();
            sound2.play();
            for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);
            Marked[i] = 0;
            Marked[i+1] = 0;
            Comps++;
            ///while(lostFocus) sf::sleep(OneMicrosecondSleep);
        }
        k++;
    }
    sound1.stop();
    sound2.stop();
    finishedsort(v);
    reset();
}
void CocktailSort(int v[]){
    bool sorted = false;
    int start = 0;
    int ending = n-1;
    while(!sorted){
        sorted = true;
        for(int i = start; i<ending; i++){
            Marked[i+1] = 1;
            if(v[i]>v[i+1]){
                std::swap(v[i], v[i+1]);
                sorted = false;
                Swaps++;
            }
            if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
            }
            Comps++;
            setPitch(sound1, v[i]);
            setPitch(sound2, v[i+1]);
            sound1.play();
            sound2.play();
            for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);
            Marked[i+1] = 0;
        }
        if(sorted) break;
        sorted = true;
        ending --;
        for(int i = ending - 1; i >= start; i--){
            Marked[i] = 1;
            if(v[i]>v[i+1]){
                std::swap(v[i], v[i+1]);
                sorted = false;
                Swaps++;
            }
            if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
            }
            Comps++;
            setPitch(sound1, v[i]);
            setPitch(sound2, v[i+1]);
            sound1.play();
            sound2.play();
            for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);
            Marked[i] = 0;
        }
        start++;
    }
    sound1.stop();
    sound2.stop();
    finishedsort(v);
    reset();
}
void insertionSort(int v[]){
    for(int i = 1; i<n; i++){
        int p = i - 1;
        Marked[p] = 1;
        while(p>=0 && v[p]>v[p+1]){
            std::swap(v[p], v[p+1]);
            Marked[p] = 1;
            Marked[p+1] = 1;
            if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
            }
            setPitch(sound1, v[p]);
            setPitch(sound2, v[p+1]);
            sound1.play();
            sound2.play();
            for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);
            Marked[p] = 0;
            Marked[p+1] = 0;
            p--;
            Comps++;
            Swaps++;
        }
        Comps++;
        for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);;
        Marked[p] = 0;
    }
    sound1.stop();
    sound2.stop();
    finishedsort(v);
    reset();
}
void selectionSort(int v[]){
    for(int i = 0; i<n-1; i++){
        int minn = v[i], minnpos = -1;
        Marked[i] = 10;
        for(int j = i+1; j<n; j++){
            Marked[j] = 1;
            if(v[j]<minn){
                minn = v[j];
                if(minnpos!=-1) Marked[minnpos] = 0;
                minnpos = j;
                Marked[j] = 2;
            }
            if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
            }
            setPitch(sound1, v[j]);
            sound1.play();
            for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);
            if(j!=minnpos)Marked[j] = 0;
            Comps++;
        }
        Marked[i] = 0;
        if(minnpos!=-1){
            Marked[minnpos] = 0;
            std::swap(v[i], v[minnpos]);
            Swaps++;
        }
    }
    sound1.stop();
    finishedsort(v);
    reset();
}
void shellSort(int v[]){
    for(int gap = n / 2; gap > 0; gap/=2){
        for(int i = gap; i<n; i++){
            int j;
            Marked[i] = 1;
            for(j = i; j>= gap && v[j-gap]> v[j] && j-gap>=0; j-=gap){
                Marked[i] = 0;
                Marked[j] = 1;
                Marked[j-gap] = 1;
                std::swap(v[j], v[j-gap]);
                if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
                }
                setPitch(sound1, v[j]);
                setPitch(sound2, v[j-gap]);
                sound1.play();
                sound2.play();
                for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);
                Marked[j] = 0;
                Marked[j-gap] = 0;
                Comps++;
                Swaps++;
            }
            Comps++;
            for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);;
            Marked[i] = 0;
        }
    }
    sound1.stop();
    sound2.stop();
    finishedsort(v);
    reset();
}
void shellSortCustomGaps(int v[]){
    /// Not Implemented Yet
    int gaps2[] = {1, 4, 10, 23, 57, 132, 301, 701};
    int indexx = 7;
    for(int indice = indexx; indice>=0; indice--){
        int gap = gaps2[indice];
        for(int i = gap; i<n; i++){
            int j;
            Marked[i] = 1;
            for(j = i; j>= gap && v[j-gap]> v[j] && j-gap>=0; j-=gap){
                Marked[i] = 0;
                Marked[j] = 1;
                Marked[j-gap] = 1;
                std::swap(v[j], v[j-gap]);
                if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
                }
                setPitch(sound1, v[j]);
                setPitch(sound2, v[j-gap]);
                sound1.play();
                sound2.play();
                for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);;
                Marked[j] = 0;
                Marked[j-gap] = 0;
                Comps++;
                Swaps++;
            }
            Comps++;
            for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);;
            Marked[i] = 0;
        }
    }
    sound1.stop();
    sound2.stop();
    finishedsort(v);
    reset();
}
void QuickSortHoare(int v[], int st, int dr){
    if(st < dr){
        int m = (st + dr) / 2;
        std::swap(v[st], v[m]);
        Marked[m] = 3;
        for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);
        Swaps++;
        int i = st , j = dr, d = 0;
        while(i < j){
            if(v[i] > v[j]){
                std::swap(v[i], v[j]);
                Marked[i] = 1;
                Marked[j] = 1;
                if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
                }
                setPitch(sound1, v[i]);
                setPitch(sound2, v[j]);
                sound1.play();
                sound2.play();
                for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);
                Marked[i] = 0;
                Marked[j] = 0;
                d = 1 - d;
                Swaps++;
            }
            Swaps++;
            Comps++;
            i += d;
            j -= 1 - d;
        }
        Marked[m] = 0;
        QuickSortHoare(v, st , i - 1);
        if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
        }
        QuickSortHoare(v, i + 1 , dr);
    }
}
void QuickSortHoareInit(int v[]){
    QuickSortHoare(v, 0, n - 1);
    sound1.stop();
    sound2.stop();
    if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
            }
    finishedsort(v);
    reset();
}
int partitionLomuto(int v[], int st, int dr){
    int pivot = v[dr];
    int i = st - 1;
    Marked[dr] = 3;
    Marked[i] = 1;
    for(int j = st; j<=dr-1; j++){
        Marked[j] = 1;
        if(v[j]<=pivot){
            i++;
            Marked[i-1] = 0;
            Marked[i] = 1;
            std::swap(v[i], v[j]);
            if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return -1;
            }
            Swaps++;
            setPitch(sound1, v[i]);
            setPitch(sound2, v[j]);
            sound1.play();
            sound2.play();
            for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);
        }
        Marked[j] = 0;
        Comps++;
    }
    Marked[i] = 0;
    Marked[dr] = 0;
    std::swap(v[i+1], v[dr]);
    Swaps++;
    return i+1;
}
void QuickSortLomuto(int v[], int st, int dr){
    if(st < dr){
        int p = partitionLomuto(v, st, dr);
        if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
        }
        QuickSortLomuto(v, st, p-1);
        if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
        }
        QuickSortLomuto(v, p+1, dr);
    }
}
void QuickSortLomutoInit(int v[]){
    QuickSortLomuto(v, 0, n-1);
    sound1.stop();
    sound2.stop();
    if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
            }
    finishedsort(v);
    reset();
}
void MergeSort(int v[], int tmp[], int st, int dr){
    if(st < dr){
        int m = (st + dr) / 2;
        MergeSort(v, tmp, st , m);
        if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
        }
        MergeSort(v, tmp, m + 1 , dr);
        int i = st, j = m + 1, k = 0;
        while( i <= m && j <= dr ){
            if( v[i] < v[j]){
                if(i>0) Marked[i-1] = 0;
                Marked[i] = 1;
                if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
                }
                setPitch(sound1, v[i]);
                sound1.play();
                for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);
                tmp[++k] = v[i++];
            }
            else{
                if(j>1) Marked[j-1] = 0;
                Marked[j] = 1;
                if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
                }
                setPitch(sound2, v[j]);
                sound2.play();
                for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);
                tmp[++k] = v[j++];
            }
            Comps++;
        }
        sound2.stop();
        if(j>1) Marked[j-1] = 0;
        if(i>1)Marked[i-1] = 0;
        sound1.stop();
        sound2.stop();
        while(i <= m){
            Marked[i] = 1;
            if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
            }
            setPitch(sound1, v[i]);
            sound1.play();
            for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);
            tmp[++k] = v[i++];
            Marked[i-1] = 0;
        }
        while(j <= dr){
            Marked[j] = 1;
            if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
            }
            setPitch(sound2, v[j]);
            sound2.play();
            for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);
            tmp[++k] = v[j++];
            Marked[j-1] = 0;
        }
        sound2.stop();
        for(i = st , j = 1 ; i <= dr ; i ++ , j ++){
            /*
            if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
            }
            */
            v[i] = tmp[j];
            if(i>1)Marked[i-1] = 0;
            Marked[i] = 1;
            setPitch(sound1, v[i]);
            sound1.play();
            for(int k = 0; k<delay*500; k++) sf::sleep(OneMicrosecondSleep);
            Swaps++;
        }
        if(i>1)Marked[i-1] = 0;
    }
}
void MergeSortInit(int v[]){
    int *tmp = (int * )calloc(1000, sizeof(int));
    MergeSort(v, tmp, 0, n-1);
    delete[] tmp;
    sound1.stop();
    sound2.stop();
    if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
            }
    finishedsort(v);
    reset();
}
void countSort(int v[], int exp, int base){
	int output[1010] = {0};
	int i, count[base] = {0};
	for (i = 0; i < n; i++){
        if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
        }
        output[i] = v[i];
		if(i>0) Marked[i-1] = 0;
		count[ (v[i]/exp)%base ]++;
		Marked[i] = 1;
		setPitch(sound1, v[i]);
        sound1.play();
		for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);
	}
	Marked[i-1] = 0;
	int bkt[base+1] = {0};
	std::partial_sum(count, count+base, bkt+1);
	for(int i = 0; i < base; i++){
        if(bkt[i]>=n) continue;
        Marked[bkt[i]] = 3;
	}
	for (i = 0;  i < n; i++) {
	    /*
            if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
            }
            */
		int r = output[i] / exp % base;
		Marked[bkt[r]] = 1;
        v[bkt[r]++] = output[i];
        setPitch(sound1, v[bkt[r]-1]);
        sound1.play();
        for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);
        Marked[bkt[r]-1] = 0;
        Swaps++;
	};
}
void radixsortLSD(int v[], int base) {
	for (int exp = 1; maxx/exp > 0; exp *= base){
        if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
        }
		countSort(v,exp, base);
	}
    sound1.stop();
}
void radixsortLSDInit(int v[]){
    maxx = n + 1;
    radixsortLSD(v, 4);
    if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
            }
    finishedsort(v);
    reset();
}
void heapify(int v[],int n, int i) {
	int largest = i;
	int l = 2*i;
	int r = 2*i + 1;
	if (l < n && v[l] > v[largest]){
		largest = l;
		Comps++;
	}
	if (r < n && v[r] > v[largest]){
		largest = r;
		Comps++;
	}
	if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
    }
	if (largest != i) {
		std::swap(v[i], v[largest]);
		setPitch(sound1, v[largest]);
		sound1.play();
		Marked[i] = BitNum(i)-1;
		Marked[largest] = BitNum(largest)-1;
		for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);
		Swaps++;
		heapify(v,n,  largest);
	}
}
void heapSort(int v[]) {
    for(int i = 0; i<n; i++){
        if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
        }
		Marked[i] = BitNum(i)-1;
		for(int k = 0; k<delay*500; k++) sf::sleep(OneMicrosecondSleep);
	}
	for (int i = n / 2; i >=0; i--)
		heapify(v,n,  i);
	for (int i=n-1; i>=0; i--) {
        if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
        }
		std::swap(v[0], v[i]);
		setPitch(sound1, v[i]);
		sound1.play();
		Swaps++;
		Marked[i] = 0;
		Marked[0] = BitNum(0)-1;
		heapify(v, i, 0);
	}
	sound1.stop();
	finishedsort(v);
	reset();
}
void RadixSortMSD(int v[], int lo, int hi, unsigned depth, unsigned int RADIX){
	// radix and base calculations
	unsigned int pmax = floor( log(maxx+1) / log(RADIX) );
	int base = pow(RADIX, pmax - depth);
	std::vector<int> count(RADIX, 0);
	for (int i = lo; i < hi; ++i){
        if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
            }
		Marked[i] = 1;
		setPitch(sound1, v[i]);
        sound1.play();
		for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);
		int r = v[i] / base % RADIX;
		count[r]++;
		Marked[i] = 0;

	}
	std::vector<int> bkt(RADIX, 0);
	std::partial_sum(count.begin(), count.end(), bkt.begin());
	for (unsigned i = 0; i < bkt.size(); ++i) {
		if (bkt[i] == 0) continue;
		Marked[lo+bkt[i]-1] = 3;
	}
	for (int i=0, j; i < (hi-lo); )
	{
		while ( (j = --bkt[ (v[lo+i] / base % RADIX) ]) > i )
		{
		    if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
            }
			std::swap(v[lo+i], v[lo+j]);
			setPitch(sound1, v[lo+i]);
			setPitch(sound2, v[lo+j]);
			sound1.play();
			sound2.play();
			for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);
			Swaps++;
		}
		i += count[ (v[lo+i] / base % RADIX) ];
	}
	// no more depth to sort?
	if (depth+1 > pmax) return;
    memset(Marked + lo, 0, (hi-lo)*sizeof(int));
	int sum = lo;
	for (unsigned i = 0; i < RADIX; ++i)
	{
	    for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);
		if (count[i] <= 1) continue;
		RadixSortMSD(v, sum, sum+count[i], depth+1, RADIX);
		memset(Marked + sum, 0, (count[i])*sizeof(int));
		sum += count[i];
	}
}
void RadixSortMSDInit(int v[]){
    maxx = n + 1;
    RadixSortMSD(v, 0, n, 0, 4);
    sound1.stop();
    sound2.stop();
    if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
            }
    finishedsort(v);
    reset();
}
void BogoSort(int v[]){
    bool sorted = false;
    while(!sorted && n > 1){
        smecherShuffle(v);
        sorted = true;
        for(int i = 0; i<n-1; i++){
            if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
            }
            setPitch(sound1, v[i]);
            sound1.play();
            if(v[i]>v[i+1]){
                sorted = false;
                break;
            }
            Marked[i] = 10;
            for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);
            Comps++;
        }
        if(!sorted) memset(Marked, 0, sizeof(Marked));
    }
    sound1.stop();
    finishedsort(v);
    reset();
}
void LessBogoSort(int v[]){
    int last = 0;
    for(int i = 0; i<n; i++){
        bool sorted = false;
        while(!sorted && n > 1){
            if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
            }
            sorted = true;
            std::random_shuffle(v+i, v+ n);
            Swaps+=n-i;
            Marked[i] = 1;
            setPitch(sound1, v[i]);
            sound1.play();
            if(v[i]-1==last){
                last = v[i];
                sorted = true;
            }
            else {
                sorted = false;
            }
            Comps++;
            for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);
            Marked[i] = 0;
        }
    }
    sound1.stop();
    finishedsort(v);
    reset();
}
void flip(int v[], int i){
    int temp, start = 0;
    while (start < i){
        if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
            }
        temp = v[start];
        v[start] =v[i];
        v[i] = temp;
        setPitch(sound1, v[start]);
        setPitch(sound2, v[i]);
        sound1.play();
        sound2.play();
        start++;
        i--;
        Swaps++;
        for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);
    }
    sound1.stop();
    sound2.stop();
}
int findMax(int v[], int size){
    int mi, i;
    for(mi = 0, i = 0; i<size; i++){
        if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return -1;
            }
        setPitch(sound1, v[i]);
        sound1.play();
        Marked[i] = 1;
        if(v[i]>v[mi]){
            Marked[mi] = 0;
            mi = i;
            Marked[mi] = 2;
        }
        Comps++;
        for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);
        Marked[i] = 0;
    }
    sound1.stop();
    return mi;
}
void PancakeSort(int v[]){
    for(int size = n; size>1; size--){
        if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
            }
        Marked[size-1] = 1;
        int mi = findMax(v, size);
        if(mi!=size-1){
            flip(v, mi);
            flip(v, size-1);
        }
        for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);
        Marked[size-1] = 0;
    }
    sound1.stop();
    finishedsort(v);
    reset();
}
void CombSort(int v[]){
    const double shrinkFactor = 1.3;
    int gap = n;
    bool sorted = false;
    while(!sorted){
        gap = floor(double(gap)/shrinkFactor);
        if(gap<=1){
            gap = 1;
            sorted = true;
        }
        for(int i = 0; i+gap<n; i++){
            if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
            }
            Marked[i] = 1;
            if(v[i]>v[i+gap]){
                Marked[i+gap] = 1;
                std::swap(v[i], v[i+gap]);
                sorted = false;
                Swaps++;
            }
            setPitch(sound1, v[i]);
            sound1.play();
            setPitch(sound2, v[i+gap]);
            sound2.play();
            for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);
            Marked[i] = 0;
            Marked[i+gap] = 0;
            Comps++;
        }
    }
    sound1.stop();
    sound2.stop();
    finishedsort(v);
    reset();
}
void oddEvenSort(int v[]){
    bool sorted = false;
    while(!sorted){
        sorted = true;
        for(int i = 1; i<n-1; i+=2){
            if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
            }
            Marked[i] = 1;
            if(v[i]>v[i+1]){
                std::swap(v[i], v[i+1]);
                sorted = false;
                Marked[i+1] = 1;
                Swaps++;
            }
            setPitch(sound1, v[i]);
            sound1.play();
            setPitch(sound2, v[i+1]);
            sound2.play();
            for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);
            Marked[i] = 0;
            Marked[i+1] = 0;
            Comps++;
        }
        for(int i = 0; i<n-1; i+=2){
            if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
            }
            Marked[i] = 1;
            if(v[i]>v[i+1]){
                std::swap(v[i], v[i+1]);
                sorted = false;
                Marked[i+1] = 1;
                Swaps++;
            }
            setPitch(sound1, v[i]);
            sound1.play();
            setPitch(sound2, v[i+1]);
            sound2.play();
            for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);
            Marked[i] = 0;
            Marked[i+1] = 0;
            Comps++;
        }
    }
    sound1.stop();
    sound2.stop();
    finishedsort(v);
    reset();
}
void CycleSort(int v[]){
    int rank = 0;
    for(int c_start = 0 ; c_start < n-1; c_start++){
        int item = v[c_start];
        Marked[c_start] = 2;
        do{
            rank = c_start;
            v[c_start] = item;
            for(int i = c_start + 1; i < n; i++){
                if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
                }
                Marked[i] = 1;
                if(v[i]<item) rank++;
                if(rank != c_start){
                    Marked[rank] = 3;
                }
                setPitch(sound1, v[i]);
                setPitch(sound2, v[rank]);
                sound1.play();
                sound2.play();
                for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);
                if(rank != c_start){
                    Marked[rank] = 0;
                }
                Marked[i] = 0;
                Comps++;
            }
            if(rank == c_start){
                break;
            }
            while (item == v[rank])
                rank++;
            std::swap(v[rank], item);
            Swaps++;
        }while(rank!=c_start);
        Marked[c_start] = 0;
    }
    sound1.stop();
    sound2.stop();
    finishedsort(v);
    reset();
}
void CountingSort(int v[]){
    maxx = n + 1;
    int count[maxx + 1] = {},
        output[n] = {};
    for(int i = 0; i < n; i++){
        if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
            }
        Marked[i] = 1;
        output[i] = v[i];
        count[v[i]]++;
        setPitch(sound1, v[i]);
        sound1.play();
        for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);
        Marked[i] = 0;
    }
    for(int i = 1; i <= maxx; i++){
        count[i] = count[i-1] + count[i];
    }
    for(int i = n - 1; i>=0; i--){
        /*
            if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
            }
            */
        Marked[count[output[i]]-1] = 1;
        v[count[output[i]]-1] = output[i];
        setPitch(sound1, v[count[output[i]]-1]);
        sound1.play();
        for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);
        Marked[count[output[i]]-1] = 0;
        count[output[i]]--;
        Swaps++;
    }
    sound1.stop();
    finishedsort(v);
    reset();
}
/// HybridMergeSort
const int RUN = 32;
void insertSort(int v[], int st, int dr){
    for(int i = st + 1; i <= dr; i++){
        int p = i - 1;
        Marked[i] = 1;
        while(v[p]>v[p+1] && p >= st){
            if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
            }
            std::swap(v[p], v[p+1]);
            setPitch(sound1, v[p]);
            setPitch(sound2, v[p+1]);
            sound1.play();
            sound2.play();
            Marked[p] = 1;
            Marked[p+1] = 1;
            for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);
            Marked[p] = 0;
            Marked[p+1] = 0;
            p--;
            Comps++;
            Swaps++;
        }
        Comps++;
        for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);;
    }
    memset(Marked + st, 0, sizeof(int) * (dr - st));
    sound1.stop();
    sound2.stop();
}
void MyMerge(int v[], int st, int m, int dr){
    int len1 = m - st + 1, len2 = dr - m;
    int left[len1], right[len2];
    for(int i = 0; i<len1; i++){
        if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
            }
        Marked[st+i] = 1;
        left[i] = v[st+i];
        setPitch(sound1, v[st+i]);
        sound1.play();
        for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);
        Marked[st+i] = 0;
    }
    for(int i = 0; i < len2; i++){
        if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
            }
        Marked[m+1+i] = 1;
        right[i] = v[m+1+i];
        setPitch(sound1, v[m+1+i]);
        sound1.play();
        for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);
        Marked[m+1+i] = 0;
    }

    ///Interclasare
    int i = 0, j = 0, k = st;
    while(i<len1 && j < len2){
        /*
            if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
            }
            */
        Marked[k] = 1;
        if(left[i] <= right[j]){
            v[k] = left[i];
            i++;
            setPitch(sound1, v[k]);
            sound1.play();
            for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);
        }
        else{
            v[k] = right[j];
            j++;
            setPitch(sound1, v[k]);
            sound1.play();
            for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);
        }
        Marked[k] = 0;
        k++;
        Comps++;
        Swaps++;
    }
    while(i<len1){
        /*
            if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
            }
            */
        Marked[k] = 1;
        v[k++] = left[i++];
        setPitch(sound1, v[k-1]);
        sound1.play();
        for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);
        Marked[k-1] = 0;
        Swaps++;
    }
    while(j<len2){
        /*
            if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
            }
            */
        Marked[k] = 1;
        v[k++] = right[j++];
        setPitch(sound1, v[k-1]);
        sound1.play();
        for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);
        Marked[k-1] = 0;
        Swaps++;
    }
    sound1.stop();
}
///HybridMergeSort
void HybridMergeSort(int v[]){
    /// sort individual arrays
    for(int i = 0; i < n; i+=RUN){
        insertSort(v, i, std::min(i+31, n-1));
    }
    for(int size = RUN; size < n; size = 2 * size){
        for(int left = 0; left < n; left += 2 * size){
            int mid = std::min((left + size - 1), (n - 1));
            int right = std::min(left+2*size - 1, n-1);
            MyMerge(v, left, mid, right);
        }
    }
    sound1.stop();
    sound2.stop();
    if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
            }
    finishedsort(v);
    reset();
}
///Bead Sort
int GetNumber(int index, bool mat[][1001]){
    int nr = 0;
    for(int i = 0; i < 1001; i++){
        if(mat[index][i]) nr++;
    }
    return nr;
}
bool ShiftTrues(bool mat[][1001]){
    bool swapped = false;
    for(int i = 1001; i > 0; i--){
        for(int j = n - 1; j > 0; j--){
            if(!mat[j][i] && mat[j-1][i]){
                swapped = true;
                std::swap(mat[j][i], mat[j-1][i]);
            }
        }
    }
    for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);
    return swapped;
}
void SetNumber(int index, int val, bool mat[][1001]){
    for(int i = 1; i < 1001; i++){
        if(i<=val){
            mat[index][i] = 1;
        }
        else{
            mat[index][i] = 0;
        }
    }
}
void BeadSort(int v[]){
    bool mat[n][1001];
    int k = n, x = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 1001; j++) mat[i][j] = false;
    }
    for(int i = 0; i < n; i++){
        SetNumber(i, v[i], mat);
    }
    while(ShiftTrues(mat)){
        Swaps += k--;
        for(int i = x; i<n; i++){
            if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
            }
            v[i] = GetNumber(i, mat);
            setPitch(sound1, v[i]);
            sound1.play();
            for(int k = 0; k<delay*1000/n; k++) sf::sleep(OneMicrosecondSleep);
        }
        x++;
    }
    sound1.stop();
    finishedsort(v);
    reset();
}
int introPartition(int v[], int st, int dr){
    int pivot = v[dr - 1];
    int i = st;
    Marked[dr-1] = 3;
    Marked[i] = 1;
    for(int j = st; j < dr -1; j++){
        if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return -1;
            }
        Marked[j] = 1;
        setPitch(sound1, v[j]);
        sound1.play();
        sound2.stop();
        if(v[j] < pivot){
            std::swap(v[i], v[j]);
            setPitch(sound2, v[i]);
            sound2.play();
            Marked[i] = 0;
            i++;
            Marked[i] = 1;
            Swaps++;
        }
        Comps++;
        for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);
        Marked[j] = 0;
    }
    std::swap(v[i], v[dr-1]);
    Marked[i] = 0;
    Marked[dr-1] = 0;
    sound1.stop();
    sound2.stop();
    return i;
}
void introInsert(int v[], int st, int dr){
    for(int i = st + 1; i < dr; i++){
        int j = i - 1;
        Marked[j+1] = 1;
        Comps++;
        while(v[j+1]<v[j] && j >= st){
            if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
            }
            Marked[j] = 1;
            Marked[j+1] = 1;
            setPitch(sound1, v[j]);
            setPitch(sound2, v[j+1]);
            sound1.play();
            sound2.play();
            std::swap(v[j+1], v[j]);
            for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);
            Marked[j] = 0;
            Marked[j+1] = 0;
            j--;
            Comps++;
            Swaps++;
        }
        Marked[j+1] = 0;
    }
    sound1.stop();
    sound2.stop();
}
void introHeapify(int v[], int n, int i, int st){
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if(l < n && v[l] > v[largest]) largest = l;
    if(r < n && v[r] > v[largest]) largest = r;
    Marked[st+largest] = 1;
    if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
            }
    if(largest!=i){
        std::swap(v[i], v[largest]);
        setPitch(sound1, v[largest]);
        sound1.play();
        for(int k = 0; k < delay* 1000 && !raisedStoppedSorting; k++) sf::sleep(OneMicrosecondSleep);
        introHeapify(v, n, largest, st);

    }
    Marked[st+largest] = 0;
}
void introHeapSort(int v[], int n, int st){
    for(int i = n / 2 - 1; i>=0; i--){
        introHeapify(v, n, i, st);
    }
    for(int i = n - 1; i >= 0; i--){
        std::swap(v[0], v[i]);
        introHeapify(v, i, 0, st);
    }
}
/// This procedure finds the median of three in the array and returns its position
int MedianOfThree(int v[], int a, int b, int c){
    if(v[a] < v[b] && v[b] < v[c]) return b;
    if(v[a] < v[c] && v[c] <= v[b]) return c;
    if(v[b] <= v[a] && v[a] < v[c]) return a;
    if(v[b] < v[c] && v[c] <= v[a]) return c;
    if(v[c] <= v[a] && v[a] < v[b]) return a;
    if(v[c] <= v[b] && v[b] <= v[a]) return b;
}
void introSort(int v[], int st, int dr, int depth){
    if(dr==st) return;
    if(dr-st-1 <= 16){
        introInsert(v, st, dr);
    }
    else if(depth == 0){
        introHeapSort(v + st, dr - st, st);
    }
    else{
        int pos = MedianOfThree(v, st, st+(dr-st+1)/2, dr-1);
        std::swap(v[pos], v[dr-1]);
        if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
            }
        int p = introPartition(v, st, dr);
        if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
            }
        introSort(v, st, p, depth - 1);
        if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
        }
        introSort(v, p, dr, depth - 1);
    }
}
void introSortInit(int v[]){
    int depth =  2*floor(log(n));
    std::cout << depth << std::endl;
    introSort(v, 0, n, depth);
    if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
    }
    sound1.stop();
    sound2.stop();
    if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
            }
    finishedsort(v);
    reset();
}
int BinarySearchUtil(int v[], int item, int st, int dr){
    if(dr <= st){
        return(item > v[st]) ? (st+1) : st;
    }
    Comps++;
    int mid = (st+dr) /2 ;
    Marked[mid] = 2;
    for(int k = 0; k < delay * 1000; k++) sf::sleep(OneMicrosecondSleep);
    Marked[mid] = 0;
    if(item == v[mid]) return mid + 1;
    if(item > v[mid]) return BinarySearchUtil(v, item, mid+1, dr);
    return BinarySearchUtil(v, item, st, mid - 1);
}
void BinaryInsertionSort(int v[]){
    for(int i = 1; i < n; i++){
        int j = i - 1;
        int place = BinarySearchUtil(v, v[i], 0, j);
        while(j>=place){
            if(raisedStoppedSorting){
                    sound1.stop();
                    sound2.stop();
                    reset();
                    return;
            }
            Marked[j] = 1;
            Marked[j+1] = 1;
            setPitch(sound1, v[j]);
            setPitch(sound2, v[j+1]);
            sound1.play();
            sound2.play();
            std::swap(v[j+1], v[j]);
            for(int k = 0; k < delay * 1000; k++) sf::sleep(OneMicrosecondSleep);
            Marked[j] = 0;
            Marked[j+1] = 0;
            j--;
            Swaps++;
        }
    }
    sound1.stop();
    sound2.stop();
    finishedsort(v);
    reset();
}

