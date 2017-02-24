#include<iostream>
#include<map>
#include<fstream>
#include<algorithm>
#include<vector>
#include<string>
#include<locale>

const int WORDS_COUNT = 50;

std::string prepare(std::string& s)
{
	std::string res;
	std::transform(s.begin(), s.end(), s.begin(), ::tolower);
	res = s;
	res.erase(std::remove_if(res.begin(), res.end(), ::ispunct ), res.end());
	
	return res;
}

struct Statistic {
	int count;
	std::string word;
};

bool comp(const Statistic& lhs, const Statistic& rhs)
{
	return lhs.count > rhs.count;
}

int main()
{
	Statistic stat;
	std::ifstream file("book4.txt");
	std::map<std::string, int> mymap;
	std::map<std::string, int>::iterator it;
	if (file.is_open())
	{
		std::string word;
		while (!file.eof()) 
		{
			file >> word;
			word = prepare(word);
			mymap[word]++;
		}
		file.close();
		std::vector<Statistic> s;
		int i = 0;
		for (it = mymap.begin(); it != mymap.end(); ++it) {
			s.push_back(stat);
			s.at(i).count = (*it).second;
			s.at(i).word = (*it).first;
			i++;
		}
		std::sort(s.begin(), s.end(), comp);
		for ( i = 0; i < WORDS_COUNT; i++) {
			std::cout << s[i].count << ' ' << s[i].word << std::endl;
		}
	}
}
