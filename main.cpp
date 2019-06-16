#include <iostream>
#include <set>
#include <map>
#include <string>
#include <functional>
#include <vector>
#include <unordered_map>


void set_function(){ 
	// <set> eigenschaften:sortiert automatisch,ignoriert doppelte einträge des gleichen werts 
	// für mehrfache einträge des gleichen werts std::multiset<int> verwenden.
	std::set<int> s_set; // Default: std::set<int, std::less<int>> aufsteigende anordnung 
						 //			 std::set<int, std::greater<int>> absteigende anordnung
	s_set.insert(4);
	s_set.insert(8);
	s_set.insert(9);
	s_set.insert(6);
	s_set.insert(7); 
	s_set.insert(7);// nur möglich mit multiset

	for (auto i = s_set.begin();i!= s_set.end();++i)
	{
		std::cout << *i << std::endl;
	}
}

void map_function()
{
	std::map<int, std::string> m_map;
	m_map.insert(std::pair<int, std::string>(2, "peter"));

	std::cout << m_map.find(2)->second << std::endl; 
	//find(key) gibt pointer auf die stelle zurück wo sich das element befindet
	//Wird anschließend mit ->second dereferenziert um den gespeicherten wert zu erhalten.
}

void multimap_function()
{
	std::multimap<int, std::string> m_multimap;
	m_multimap.insert(std::pair<int, std::string>(2, "lala"));
	m_multimap.insert(std::pair<int, std::string>(2, "Uwe"));
	m_multimap.insert(std::pair<int, std::string>(3, "Luke"));

	//std::cout << m_multimap.find(2)->second << std::endl; // find() sucht nur den ersten vertreter

	auto iters = m_multimap.equal_range(2);
	for (auto i = iters.first; i != iters.second;++i)
	{
		std::cout << i->second << std::endl;
	}
}

struct Key
{
	size_t size;
	std::string name;
	friend bool operator ==(const Key& k1, const Key& k2)
	{
		return k1.size == k2.size && k1.name == k2.name;
	}
};
std::vector<std::string> filepaths;
namespace std
{
	template<> struct hash<Key>
	{
		size_t operator()(const Key& key)const 
		{
			return key.size + std::hash<std::string>()(key.name)*7;
		}
	};
}


int main(int argc, char* argv[])
{
	set_function();
	map_function();
	multimap_function();

	Key key;
	key.name = "Rick";
	key.size = 22000;
	std::hash<Key> keyHash;
	std::cout << keyHash(key);

	std::unordered_map<Key, std::string> pfade;
	pfade.insert(std::pair<Key, std::string>(key, "irgendwo"));

	std::cout << pfade.find(key)->second << std::endl;

	return 0;	
}
