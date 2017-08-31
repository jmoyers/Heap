#include "stdafx.h"
#include "Heap.h"

#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <assert.h>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

int main()
{
  Heap<int> heap;

  vector<int> test;
  auto epoch = (int)std::chrono::high_resolution_clock::now().time_since_epoch().count();
  std::default_random_engine gen(epoch);
  std::uniform_int_distribution<int> dist(-100, 100);

  for (size_t i = 0; i < 100; i++)
  {
    test.push_back(dist(gen));
    heap.push(test.back());
  }

  while (!test.empty())
  {
    assert(heap.size() == test.size());
    auto max = std::max_element(test.begin(), test.end());    
    cout << "Heap max: " << heap.max() << endl;
    cout << "Vector max: " << *max << endl << endl;
    assert(heap.max() == *max);
    test.erase(max);
    heap.pop_max();
  }
  

  cin.get();

  return 0;
}

