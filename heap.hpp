#pragma once
#include <math.h>

#include <iostream>
using namespace std;

#ifndef HEAPHPP
#define HEAPHPP

template <class T>
void Heap<T>::_bubbleUp(int index) {
	while (index > 0) {
		int parent = floor((index - 1) / 2); //compute index of parent
		if (_heap[index] > _heap[parent]) {
			swap(_heap[index], _heap[parent]);
			index = parent;
		}
		else {
			return;
		}
	}
}

template <class T>
void Heap<T>::_bubbleDown(int index) {
	while (index < _n) {
		int leftChild = (2 * index) + 1;
		int rightChild = (2 * index) + 2;
		if (_heap[leftChild] > _heap[index] && leftChild < _n) { 
			//either smaller than left only or smaller than both
			if (_heap[rightChild] > _heap[index] && rightChild < _n) { 
				//smaller than both left and right
				if (_heap[leftChild] > _heap[rightChild]) {		
					//swap with bigger child (left)
					swap(_heap[index], _heap[leftChild]);
					index = leftChild;
				}
				else {
					swap(_heap[index], _heap[rightChild]);		
					//swap with bigger child (right)
					index = rightChild;
				}
			}
			else {
				//smaller than left only
				swap(_heap[index], _heap[leftChild]);
				index = leftChild;
				
			}
		}
		else if (_heap[rightChild] > _heap[index] && rightChild < _n) {	
			//smaller than right only
			swap(_heap[index], _heap[rightChild]);
			index = rightChild;
		}
		else {
			return;
		}
	}
	return;
}

template <class T>
void Heap<T>::insert(T item) {
	_heap[_n] = item;
	_bubbleUp(_n);
	_n++;
}

template <class T>
T Heap<T>::extractMax() {
	swap(_heap[0], _heap[_n - 1]);
	_n--;
	_bubbleDown(0);
	return T(_heap[_n]);
}


template <class T>
void Heap<T>::printHeapArray() {
	for (int i = 0; i < _n; i++) 
		cout << _heap[i] << " ";
	cout << endl;
}

template <class T>
int Heap<T>::_lookFor(T x){ // not a very good implementation, but just use this for now.
    int i;
    for(i=0;i<_n;i++)
        if (_heap[i] == x)
            return i;
    
    return -1;
}

template <class T>
void Heap<T>::decreaseKey(T from, T to)
{	
	int index = _lookFor(from);
	_heap[index] = to;
	_bubbleDown(index);
}


template <class T>
void Heap<T>::increaseKey(T from, T to)
{
	int index = _lookFor(from);
	_heap[index] = to;
	_bubbleUp(index);
}

template <class T>
void Heap<T>::deleteItem(T x){
	int index = _lookFor(x);
	swap(_heap[index], _heap[_n - 1]);
	_n--;
	if (x > _heap[index]) {
		_bubbleDown(index);
	}
	else if (_heap[index] > x) {
		_bubbleUp(index);
	}
}

template <class T>
void Heap<T>::printTree() {
    int parity = 0;
	if (_n == 0)
		return;
	int space = pow(2,1 + (int) log2f(_n)),i;
	int nLevel = (int) log2f(_n)+1;
	int index = 0,endIndex;
    int tempIndex;
	
	for (int l = 0; l < nLevel; l++)
	{
		index = 1;
        parity = 0;
		for (i = 0; i < l; i++)
			index *= 2;
		endIndex = index * 2 - 1;
		index--;
        tempIndex = index;
        while (index < _n && index < endIndex) {
            for (i = 0; i < space-1; i++)
                cout << " ";
            if(index==0)
                cout << "|";
            else if (parity)
                cout << "\\";
            else
                cout << "/";
            parity = !parity;
            for (i = 0; i < space; i++)
                cout << " ";
			index++;
		}
        cout << endl;
        index=tempIndex;
		while (index < _n && index < endIndex) {
			for (i = 0; i < (space-1-((int) log10(_heap[index]))); i++)
				cout << " ";
			cout << _heap[index];
			for (i = 0; i < space; i++)
				cout << " ";
			index++;
		}
		
		cout << endl;
		space /= 2;
	}

}






#endif
