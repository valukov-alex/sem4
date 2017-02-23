#include<iostream>
#include<map>
#include<fstream>
#include<algorithm>
#include<vector>
#include<string>

std::string prepare(std::string& s)
{
	std::string res;
	std::transform(s.begin(), s.end(), s.begin(), ::tolower);
	res = s;
	
	// FIXIT: в рассылке же писал, что так не нужно проверять
	// нужно либо создать множество из символов пунктуации, либо воспользоваться ф-ями ispunct или isalpha
	if ( (res[res.length()] == ',') || (res[res.length()] == '.') || (res[res.length()] == ';') )
		res.pop_back();

	return s;
}

struct Statistic {
	int count;
	std::string word;
};

// FIXIT: по константной ссылке нужно передать, чтобы избежать ненужного копирования
// обычно в подобных ф-ях аргументы называют lhs и rhs: left/right hand side
bool comp(Statistic p1, Statistic p2)
{
	return p1.count > p2.count;
}

int main()
{
	Statistic stat;
	std::ifstream file("book.txt");
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
			// it->second
			// it->first
			s.at(i).count = (*it).second;
			s.at(i).word = (*it).first;
			i++;
		}
		std::sort(s.begin(), s.end(), comp);
		// FIXIT: для 50 отдельная константа
		for ( i = 0; i < 50; i++) {
			std::cout << s[i].count << ' ' << s[i].word << std::endl;
		}
	}
}
