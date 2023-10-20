// AUTHOR: William Kavanagh. Abertay University. CMP201.2022
// Partial Framework for AX1.3, searching

#include "Search.h"
#include <vector>
#include <stdlib.h>		// for RNG
#include <time.h>		// for RNG
#include <iostream>
#include <chrono>		// for timing
#include <map>


// Return index position of key in arr or -1 if not in collection.
// Search using a naive scan.
int LinearScan(std::vector<int> arr, int key)
{
	// TODO: Assessed [1]
	for (int i = 0; i < arr.size(); ++i)
	{
		if (arr[i] == key)
		{
			return i;
		}
	}
	return -1;
}

// Return index position of key in arr or -1 if not in collection.
// Search using binary reduction
int BinarySearch(std::vector<int> arr, int key)
{
	// TODO: Assessed [1]
	int high = arr.size() - 1;
	int low = 0;
	while (low <= high)
	{
		int mid = floor((high + low) / 2);
		if (arr[mid] == key)
		{
			return mid;
		}
		if (arr[mid] < key)
		{
			low = mid + 1;
		}
		else
		{
			high = mid - 1;
		}
	}
	return -1;
}

// Return index position of key in arr or -1 if not in collection.
// Search using interpolation guestimates.
int InterpolationSearch(std::vector<int> arr, int key)
{
	// TODO: Assessed [1]
	int start = 0;
	int end = arr.size() - 1;
	while (start <= end && key >= arr[start] && key <= arr[end])
	{
		int dist = key - arr[start];
		int valueRange = arr[end] - arr[start];
		int fraction = dist / valueRange;
		int indexRange = end - start;
		int estimate = start + (fraction * indexRange);
		if (arr[estimate] == key)
		{
			return estimate;
		}
		if (arr[estimate] < key)
		{
			start = estimate + 1;
		}
		else
		{
			end = estimate - 1;
		}
	}
	return -1;
}

/*
Generate a vector of length <size> where each element is
1-5 larger than the previous element.
*/
std::vector<int> SortedVectorGenerator(int size)
{
	std::vector<int> v = std::vector<int>();
	srand(time(NULL));
	int last_value = 0;
	for (int i = 0; i < size; i++)
	{
		int new_value = last_value + rand() % 5 + 1;
		v.push_back(new_value);
		last_value = new_value;
	}
	return v;
}

// Runs the three searches on the three vectors with the three targets supplied as parameters.
// i.e. LS(v0, t0), BS(v0, t0), IS(v0, t0), LS(v1, t1), ... etc.
// Returns a map of search name to vector of doubles with timing results in nanoseconds.
// Example map output:
//		"binary search":{13400, 6400, 238100}
//		"interpolation search":{2500, 303800, 237100}
//		"linear scan":{2200, 59700, 1.4251e+06}
std::map<std::string, std::vector<double>>
runTests(std::vector<int> v0, std::vector<int> v1, std::vector<int> v2,
int t0, int t1, int t2)
{
	std::map<std::string, std::vector<double>> timeResults;
	// TODO: Assessed [2]
	//linear scan test
	auto start = std::chrono::high_resolution_clock::now();
	LinearScan(v0, t0);
	auto end = std::chrono::high_resolution_clock::now();
	long dtResOne = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
	start = std::chrono::high_resolution_clock::now();
	LinearScan(v1, t1);
	end = std::chrono::high_resolution_clock::now();
	long dtResTwo = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
	start = std::chrono::high_resolution_clock::now();
	LinearScan(v2, t2); //culprit i think
	end = std::chrono::high_resolution_clock::now();
	long dtResThree = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
	timeResults["LinearScan"].push_back(dtResOne);
	timeResults["LinearScan"].push_back(dtResTwo);
	timeResults["LinearScan"].push_back(dtResThree);

	//binary search test
	start = std::chrono::high_resolution_clock::now();
	BinarySearch(v0, t0);
	end = std::chrono::high_resolution_clock::now();
	long dtResFour = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
	start = std::chrono::high_resolution_clock::now();
	BinarySearch(v1, t1);
	end = std::chrono::high_resolution_clock::now();
	long dtResFive = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
	start = std::chrono::high_resolution_clock::now();
	BinarySearch(v2, t2);
	end = std::chrono::high_resolution_clock::now();
	long dtResSix = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
	timeResults["BinarySearch"].push_back(dtResFour);
	timeResults["BinarySearch"].push_back(dtResFive);
	timeResults["BinarySearch"].push_back(dtResSix);

	start = std::chrono::high_resolution_clock::now();
	InterpolationSearch(v0, t0);
	end = std::chrono::high_resolution_clock::now();
	long dtResSeven = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
	start = std::chrono::high_resolution_clock::now();
	InterpolationSearch(v1, t1);
	end = std::chrono::high_resolution_clock::now();
	long dtResEight = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
	start = std::chrono::high_resolution_clock::now();
	InterpolationSearch(v2, t2);
	end = std::chrono::high_resolution_clock::now();
	long dtResNine = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
	timeResults["InterpolationSearch"].push_back(dtResSeven);
	timeResults["InterpolationSearch"].push_back(dtResEight);
	timeResults["InterpolationSearch"].push_back(dtResNine);

	return timeResults;
	
}





