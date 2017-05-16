#ifndef SJTU_VECTOR_HPP
#define SJTU_VECTOR_HPP

#include <functional>
#include <cstddef>
#include "utility.hpp"
#include "exceptions.hpp"
#include <fstream>
#include <iostream>

namespace sjtu {
	template<class T>
	class vector {
	public:
		class iterator {
			friend class vector;
		public:
			iterator() :idx(0), vec(NULL) {}
			iterator(int idx, const vector* vec) :idx(idx), vec(vec) {}
			iterator(const iterator& e) : idx(e.idx), vec(e.vec) {}
			iterator& operator++() {
				++idx;
				return *this;
			}
			iterator operator++(int) {
				iterator nw = *this;
				++idx;
				return nw;
			}
			bool operator==(const iterator &rhs) const {
				if (vec != rhs.vec) return false;
				if (idx != rhs.idx) return false;
				return true;
			}
			bool operator!=(const iterator &rhs) const {
				if (vec != rhs.vec) return true;
				if (idx != rhs.idx) return true;
				return false;
			}
			T & operator*() const {
				return vec->data[idx];
			}
		private:
			int idx;
			const vector* vec;
		};
		iterator begin() {
			return iterator(0, this);
		}
		iterator end() {
			return iterator(s, this);
		}
		vector() :s(0), c(0), data(NULL) {}
        vector(const vector& other) :s(0), c(0),data(NULL){
			if (c != 0) delete[] data;
			c = other.c; s = other.s;
			data = new T[c];
			for (int i = 0; i < s; i++) {
				data[i] = other.data[i];
			}
		}
		vector& operator =(const vector& rhs) {
			if (this == &rhs) return *this;
			if (c != 0) delete[] data;
			c = rhs.c; s = rhs.s;
			data = new T[c];
			for (int i = 0; i < s; i++) {
				data[i] = rhs.data[i];
			}
			return *this;
		}
		void pop_back() {
			--s;
		}
		void push_back(const T& e) {
			if (c == 0) {
				c = 1;
				data = new T[c];
			}
			if (s == c) {
				c = c * 2;
				T* nw = new T[c];
				for (int i = 0; i < s; i++) {
					nw[i] = data[i];
				}
				delete[] data;
				data = nw;
			}
			data[s++] = e;
		}
		void clear() {
			if (c != 0) {
				delete[] data;
			}
			data = NULL;
			c = 0;
			s = 0;
		}
		const int size() const {
			return s;
		}
		T& operator [](int idx) {
			if (idx < 0 || idx >= s) throw index_out_of_bound("from vector::operator[]");
			return data[idx];
		}
		friend std::istream& operator>>(std::istream& fin, vector& v) {
			v.clear();
			fin.read(reinterpret_cast<char*>(&(v.s)), sizeof(int));
			fin.read(reinterpret_cast<char*>(&(v.c)), sizeof(int));
			v.data = new T[v.c];
            for (int i = 0; i < v.s; i++) {
                fin >> v.data[i];
			}
			return fin;
		}
		friend std::ostream& operator<<(std::ostream& fout,const vector& v) {
			fout.write(reinterpret_cast<const char*>(&(v.s)), sizeof(int));
			fout.write(reinterpret_cast<const char*>(&(v.c)), sizeof(int));
			for (int i = 0; i < v.s; i++) {
                fout << v.data[i];
			}
			return fout;
		}
        ~vector(){
            clear();
        }

	private:
		int s, c;
		T* data;
	};
};
#endif
