#include <benchmark/benchmark.h>
#include <cstdlib>
#include <ctime>
#include <random>
#include <set>
#include <vector>
#include "../treap.hpp"

void _insert(benchmark::State& state){
	std::srand(std::time({}));
	int input = state.range(0);

	Treap<int> treap(input);
	
	for (auto _ : state){
		treap.insert(std::rand() % 100'000);
	}
}

void _remove(benchmark::State& state){
	int input = state.range(0);

	Treap<int> treap(input);

	for (int i{}; i < 10'000; i++){
	    treap.insert(i);
	}

	std::mt19937 gen(42);
	for (auto _ : state){
		int key = gen() % 10'000;
		treap.remove(key);

		state.PauseTiming();
		treap.insert(key);
		state.ResumeTiming();
	}
}

void _min(benchmark::State& state){
	std::srand(std::time({}));

	int input = state.range(0);
	Treap<int> treap(input);
	
	for (int i{}; i < 10'000; i++)
		treap.insert(std::rand() % 10'000);

	for (auto _ : state){
		treap.min();

		state.PauseTiming();
		treap.insert(std::rand() % 10'000);
		state.ResumeTiming();
	}
}


void _max(benchmark::State& state){
	std::srand(std::time({}));

	int input = state.range(0);
	Treap<int> treap(input);
	
	for (int i{}; i < 10'000; i++)
		treap.insert(std::rand() % 10'000);

	for (auto _ : state){
		treap.max();

		state.PauseTiming();
		treap.insert(std::rand() % 10'000);
		state.ResumeTiming();
	}
}

BENCHMARK(_insert)->DenseRange(10'000, 100'000, 10'000);
BENCHMARK(_remove)->DenseRange(10'000, 100'000, 10'000);
BENCHMARK(_min)->DenseRange(10'000, 100'000, 10'000);
BENCHMARK(_max)->DenseRange(10'000, 100'000, 10'000);
BENCHMARK_MAIN();
