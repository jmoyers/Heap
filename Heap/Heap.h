#pragma once
#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <assert.h>

using std::vector;
using std::swap;

/* 

Parent of node at k is at k/2
Children of node at k are at 2k and 2k+1 (integer div)

*/

template <class T>
class Heap
{
  vector<T> m_storage;

  inline T& at(size_t index)
  {
    return m_storage[index];
  }

  void correct_tree()
  {
    size_t size = m_storage.size();
    if (size == 0 || size == 1) return;

    size_t k = size - 1;

    T& new_item = m_storage[k];
    T& parent = m_storage[k / 2];
    
    if (new_item > parent)
    {
      swim(k);
    }
  }

  void sink(size_t index)
  {
    cout << "Sink " << index << endl;
    size_t c1 = index * 2;
    size_t c2 = index * 2 + 1;
    size_t b = c1;

    // only check the bigger of the two siblings
    if (c2 < size())
    {
      b = std::max(at(c1), at(c2)) == at(c1) ? c1 : c2;
    }

    while (b < size() && at(b) > at(index)) {
      swap(at(index), at(b));
      index = b;
      c1 = index * 2;
      c2 = index * 2 + 1;
      
      // might only be one child
      if (c2 < size())
      {
        b = std::max(at(c1), at(c2)) == at(c1) ? c1 : c2;
      }
      else
      {
        b = c1;
      }
      
    }
  }

  void swim(size_t index)
  {
    size_t next = index / 2;
    
    while (next != index && at(index) > at(next))
    {
      cout << "Swim " << index << " to " << next << endl;
      swap(m_storage[index], m_storage[next]);
      index = next;
      next = next / 2;
    }
  }
public:
  void push(T item)
  {
    m_storage.push_back(item);
    correct_tree();
  }

  const T &max() const
  { 
    assert(size() > 0);
    return m_storage.front();
  }

  void pop_max()
  { 
    assert(size() > 0);    
    bool is_last = size() == 1;
    
    if (!is_last) 
    {
      swap(at(size() - 1), at(0));
      m_storage.pop_back();
      sink(0);
    }
    else
    {
      m_storage.pop_back();
    }
  }

  size_t size() const
  {
    return m_storage.size();
  }
};
