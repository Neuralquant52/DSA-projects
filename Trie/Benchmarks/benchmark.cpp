#include <benchmark/benchmark.h>
#include <cstdlib>
#include <string>
#include "../Trie.hpp" 

void _insert(benchmark::State& state){
	std::string availableChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	Trie trie;

	for (auto _ : state){
		state.PauseTiming();
		std::string toInsert;
		for (int i{}; i < std::rand() % 100; i++){
			toInsert.push_back(availableChars[std::rand() % availableChars.size()]);
		}
		state.ResumeTiming();
		
		trie.insert(toInsert);
	}
}


void _contains(benchmark::State& state){
	std::string availableChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	Trie trie;
	
	for (int _{} ;_ < 1'000; _++){
		std::string toInsert;
		for (int i{}; i < std::rand() % 100; i++){
			toInsert.push_back(availableChars[std::rand() % availableChars.size()]);
		}
		
		trie.insert(toInsert);
	}

	for (auto _ : state){
		state.PauseTiming();
		std::string toCheck;
		for (int i{}; i < std::rand() % 10; i++){
			toCheck.push_back(availableChars[std::rand() % availableChars.size()]);
		}
		state.ResumeTiming();
		
		trie.contains(toCheck);
	}
}

void _starts_with(benchmark::State& state){
	std::string availableChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	Trie trie;
	
	for (int _{} ;_ < 1'000; _++){
		std::string toInsert;
		for (int i{}; i < std::rand() % 10; i++){
			toInsert.push_back(availableChars[std::rand() % availableChars.size()]);
		}
		
		trie.insert(toInsert);
	}

	for (auto _ : state){
		state.PauseTiming();
		std::string toCheck;
		for (int i{}; i < std::rand() % 100; i++){
			toCheck.push_back(availableChars[std::rand() % availableChars.size()]);
		}
		state.ResumeTiming();
		
		trie.startsWith(toCheck);
	}
}


BENCHMARK(_insert);
BENCHMARK(_contains);
BENCHMARK(_starts_with);
BENCHMARK_MAIN();
