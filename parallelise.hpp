#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include "stack.hpp"

template<typename T>
struct parallelise
{
  threadsafe_stack<T> chunks;
  int thread_num;
  std::atomic<bool> end_of_data;
  std::vector<std::thread> threads;

  parallelise(int _thread_num)
    :thread_num(_thread_num)
    ,end_of_data(false)
  {
  }
  ~parallelise()
  {
  }
  void add_work(T&& chunk)
  {
    chunks.push(chunk);
  }
  void start()
  {
    end_of_data = false;
    threads.clear();
    for (int i = 0; i < thread_num; i++)
    {
      threads.push_back(std::thread(&parallelise::run_mult, this));
    }
    for (int i = 0; i < threads.size(); i++)
    {
      threads[i].join();
    }
  }
  void try_mult()
  {
    try {
      std::shared_ptr<T> a = chunks.pop();
      (*a)();
    }
    catch(empty_stack& e)
    {
      end_of_data = true;
    }
  }
  void run_mult()
  {
    while(!end_of_data)
    {
      try_mult();
      std::this_thread::yield();
    }
  }
};
