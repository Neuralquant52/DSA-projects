#include <cstddef>
#include <list>
#include <optional>
#include <unordered_map>

template <typename T, typename U>
class LRUCache {
public:
	LRUCache(std::size_t capacity) : capacity_(capacity) 
	{}
	
	void insert(T key, U value){
		if (cache.contains(key)){
			cache[key]->second = value;
			queue.splice(queue.begin(), queue, cache[key]);
			return;
		}	

		if (cache.size() == capacity_)
			evict();

		queue.emplace_front(key, value);
		cache[key] = queue.begin();
	}


	std::optional<U> get(T key){
		if (!cache.contains(key))
			return std::nullopt;

		return cache[key]->second;
	}

private:
	void evict(){
		auto& [key, value] = queue.back();
		cache.erase(key);
		queue.pop_back();
	}

	std::list<std::pair<T, U>> queue;
	std::unordered_map<T, typename std::list<std::pair<T, U>>::iterator> cache;
	std::size_t capacity_;
};

