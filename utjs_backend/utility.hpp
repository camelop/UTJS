#ifndef SJTU_UTILITY_HPP
#define SJTU_UTILITY_HPP

#include <utility>

namespace sjtu {

template<class T1, class T2>
class pair {
public:
	T1 first;
	T2 second;
	constexpr pair() : first(), second() {}
	pair(const pair &other) = default;
	pair(pair &&other) = default;
	pair(const T1 &x, const T2 &y) : first(x), second(y) {}
	template<class U1, class U2>
	pair(U1 &&x, U2 &&y) : first(x), second(y) {}
	template<class U1, class U2>
	pair(const pair<U1, U2> &other) : first(other.first), second(other.second) {}
	template<class U1, class U2>
	pair(pair<U1, U2> &&other) : first(other.first), second(other.second) {}

	friend std::istream& operator >> (std::istream& fin, pair &x) {
		//fin.read(reinterpret_cast<char*>(&(x.first)), sizeof(x.first));
		//fin.read(reinterpret_cast<char*>(&(x.second)), sizeof(x.second));
		fin >> x.first >> x.second;
		return fin;
	}
	friend std::ostream& operator << (std::ostream& fout, pair& x) {
		//fout.write(reinterpret_cast<char*>(&(x.first)), sizeof(x.first));
		//fout.write(reinterpret_cast<char*>(&(x.second)), sizeof(x.second));
		fout << x.first << x.second;
		return fout;
	}
};

}

#endif
