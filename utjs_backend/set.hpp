/**
* implement a container like std::set
*/
#ifndef SJTU_SET_HPP
#define SJTU_SET_HPP

// only for std::less<T>
#include <functional>
#include <cstddef>
#include "utility.hpp"
#include "exceptions.hpp"
#include <fstream>
#include <iostream>

namespace sjtu {

	template<
		class Key,
		class Compare = std::less<Key>
	> class set {
	public:
		/**
		* the internal type of data.
		* it should have a default constructor, a copy constructor.
		* You can use sjtu::set as value_type by typedef.
		*/
		typedef Key value_type;
		/**
		* see BidirectionalIterator at CppReference for help.
		*
		* if there is anything wrong throw invalid_iterator.
		*     like it = set.begin(); --it;
		*       or it = set.end(); ++end();
		*/
		class set_node {
		public:
			value_type* data;
			int h, s;
			set_node *l, *r;
			set_node *pr, *nx;
			set_node() :l(NULL), r(NULL), nx(NULL), pr(NULL), h(-1), s(0), data(NULL) {}
			set_node(const set_node& other) :l(NULL), r(NULL), nx(NULL), pr(NULL), h(other.h), s(other.s) {
				data = new value_type(*other.data);
			}
			set_node(const value_type& e) :l(NULL), r(NULL), nx(NULL), pr(NULL), h(0), s(1) {
				data = new value_type(e);
			}
			set_node operator =(const set_node& other) {
				l = NULL; r = NULL; nx = NULL; pr = NULL; h = 0; s = 1;
				data = new value_type(*other.data);
			}
			~set_node() { delete data; }
			int bd() {
				int lh, rh;
				if (l == NULL) lh = -1; else lh = l->h;
				if (r == NULL) rh = -1; else rh = r->h;
				return lh - rh;
			}
			void h_update() {
				int lh, rh, ls, rs;
				if (l == NULL) lh = -1, ls = 0; else lh = l->h, ls = l->s;
				if (r == NULL) rh = -1, rs = 0; else rh = r->h, rs = r->s;
				if (lh > rh) h = lh + 1; else h = rh + 1;
				s = ls + rs + 1;
			}
		};
		class const_iterator;
		class iterator {
			friend class set;
			friend class const_iterator;
		private:
			set_node* p;
			const set* t;
		public:
			iterator() :p(NULL), t(NULL) {}
			iterator(set_node* p, const set* t) :p(p), t(t) {}
			iterator(const iterator &other) :p(other.p), t(other.t) {}
			iterator(const const_iterator &other) :p(other.p), t(other.t) {}
			/**
			* return a new iterator which pointer n-next elements
			*   even if there are not enough elements, just return the answer.
			* as well as operator-
			*/
			/**
			* TODO ++iter
			*/
			iterator& operator =(const iterator &other) {
				if (this == &other) return *this;
				p = other.p;
				t = other.t;
				return *this;
			}
			iterator & operator++() {
				if (p == NULL) throw invalid_iterator("from set::iterator::operator++");
				p = p->nx;
				if (p == NULL) throw invalid_iterator("from set::iterator::operator++");
				return *this;
			}
			/**
			* TODO iter++
			*/
			iterator operator++(int) {
				iterator nw(*this);
				++(*this);
				return nw;
			}
			/**
			* TODO --iter
			*/
			iterator & operator--() {
				if (p == NULL) throw invalid_iterator("from set::iterator::operator--");
				p = p->pr;
				if (p == NULL) throw invalid_iterator("from set::iterator::operator--");
				return *this;
			}
			/**
			* TODO iter--
			*/
			iterator operator--(int) {
				iterator nw(*this);
				--(*this);
				return nw;
			}
			/**
			* a operator to check whether two iterators are same (pointing to the same memory).
			*/
			value_type & operator*() const {
				return *(p->data);
			}
			bool operator==(const iterator &rhs) const {
				return (p == rhs.p);
			}
			bool operator==(const const_iterator &rhs) const {
				return (p == rhs.p);
			}
			/**
			* some other operator for iterator.
			*/
			bool operator!=(const iterator &rhs) const {
				return (p != rhs.p);
			}
			bool operator!=(const const_iterator &rhs) const {
				return (p != rhs.p);
			}
			/**
			* for the support of it->first.
			* See <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/> for help.
			*/
			value_type* operator->() const noexcept {
				return p->data;
			}
		};
		class const_iterator {
			// it should has similar member method as iterator.
			//  and it should be able to construct from an iterator.
			friend class set;
			friend class iterator;
		private:
			set_node* p;
			const set* t;
		public:
			const_iterator() :p(NULL), t(NULL) {}
			const_iterator(set_node* p, const set* t) :p(p), t(t) {}
			const_iterator(const const_iterator &other) :p(other.p), t(other.t) {}
			const_iterator(const iterator &other) :p(other.p), t(other.t) {}
			/**
			* return a new iterator which pointer n-next elements
			*   even if there are not enough elements, just return the answer.
			* as well as operator-
			*/
			/**
			* a operator to check whether two iterators are same (pointing to the same memory).
			*/
			const_iterator& operator =(const const_iterator &other) {
				if (this == &other) return *this;
				p = other.p;
				t = other.t;
				return *this;
			}
			const value_type & operator*() const {
				return *(p->data);
			}
			const_iterator & operator++() {
				if (p == NULL) throw invalid_iterator("from set::const_iterator::operator++");
				p = p->nx;
				if (p == NULL) throw invalid_iterator("from set::const_iterator::operator++");
				return *this;
			}
			/**
			* TODO iter++
			*/
			const_iterator operator++(int) {
				const_iterator nw(*this);
				++(*this);
				return nw;
			}
			/**
			* TODO --iter
			*/
			const_iterator & operator--() {
				if (p == NULL) throw invalid_iterator("from set::const_iterator::operator--");
				p = p->pr;
				if (p == NULL) throw invalid_iterator("from set::const_iterator::operator--");
				return *this;
			}
			/**
			* TODO iter--
			*/
			const_iterator operator--(int) {
				const_iterator nw(*this);
				--(*this);
				return nw;
			}

			bool operator==(const iterator &rhs) const {
				return (p == rhs.p);
			}
			bool operator==(const const_iterator &rhs) const {
				return (p == rhs.p);
			}
			bool operator!=(const iterator &rhs) const {
				return (p != rhs.p);
			}
			bool operator!=(const const_iterator &rhs) const {
				return (p != rhs.p);
			}
			/**
			* for the support of it->first.
			* See <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/> for help.
			*/
			const value_type* operator->() const noexcept {
				return p->data;
			}
		};
		/**
		* TODO two constructors
		*/
		set() :head(NULL), bg(NULL), ed(NULL) {
			bg = ed = new set_node;
		}
		set(const set &other) :head(NULL), bg(NULL), ed(NULL) {
			if (other.head == NULL) {
				bg = ed = new set_node;
				return;
			}
			head = new set_node(*other.head);
			ed = new set_node;
			copy(head, other.head);
			set_node* his = NULL;
			ldr(head, his);
			his->nx = ed;
			ed->pr = his;
		}
		/**
		* TODO assignment operator
		*/
		set & operator=(const set &other) {
			if (this == &other) return *this;
			clear();
			if (other.head == NULL) {
				return *this;
			}
			head = new set_node(*other.head);
			copy(head, other.head);
			set_node* his = NULL;
			ldr(head, his);
			his->nx = ed;
			ed->pr = his;
			return *this;
		}
		friend std::istream& operator >>(std::istream &fin, set& m) {
			m.clear();
			m.head = new set_node;
			m.read_node(fin, m.head);
			set_node* his = NULL;
			m.ldr(m.head, his);
			his->nx = m.ed;
			m.ed->pr = his;
			return fin;
		}
		void read_node(std::istream &fin, set_node* &x) {
            x->data = new value_type;
            char q[4];
            fin.read(q,sizeof(q));
            fin >> (*(x->data));
            if (q[0]=='l') {
				x->l = new set_node;
				read_node(fin, x->l);
			}
            if (q[1]=='r') {
				x->r = new set_node;
				read_node(fin, x->r);
			}
			x->h_update();
		}
		friend std::ostream& operator <<(std::ostream& fout, set& m) {
			m.write_node(fout, m.head);
			return fout;
		}
        void write_node(std::ostream &fout, set_node* x) {
            char q[4];
            q[0]=(x->l == NULL)?'n':'l';
            q[1]=(x->r == NULL)?'n':'r';
            q[2]=' ';
            q[3]=' ';
            fout.write(q,sizeof(q));
            fout << (*(x->data));
            if (x->l != NULL) write_node(fout, x->l);
			if (x->r != NULL) write_node(fout, x->r);
		}
		/**
		* TODO Destructors
		*/
		~set() {
			clear();
			delete ed;
		}
		/**
		* TODO
		* access specified element with bounds checking
		* Returns a reference to the setped value of the element with key equivalent to key.
		* If no such element exists, an exception of type `index_out_of_bound'
		*/

		iterator begin() { return iterator(bg, this); }
		const_iterator cbegin() const { return const_iterator(bg, this); }
		/**
		* return a iterator to the end
		* in fact, it returns past-the-end.
		*/
		iterator end() { return iterator(ed, this); }
		const_iterator cend() const { return const_iterator(ed, this); }
		/**
		* checks whether the container is empty
		* return true if empty, otherwise false.
		*/
		bool empty() const { return head == NULL; }
		/**
		* returns the number of elements.
		*/
		size_t size() const { return (head == NULL) ? 0 : head->s; }
		/**
		* clears the contents
		*/
		void clear() {
			clean(head);
			delete ed;
			bg = ed = new set_node;
			head = NULL;
		}
		/**
		* insert an element.
		* return a pair, the first of the pair is
		*   the iterator to the new element (or the element that prevented the insertion),
		*   the second one is true if insert successfully, or false.
		*/
		pair<iterator, bool> insert(const value_type &value) {
			set_node* p = search(head, value);
			if (p != NULL) return pair<iterator, bool>(iterator(p, this), false);
			p = insert(head, value);
			if (head->s == 1) {
				p->nx = ed;
				ed->pr = p;
				bg = p;
			}
			return pair<iterator, bool>(iterator(p, this), true);
		}
		/**
		* erase the element at pos.
		*
		* throw if pos pointed to a bad element (pos == this->end() || pos points an element out of this)
		*/
		void erase(iterator pos) {
			if (pos.t != this) throw invalid_iterator("from set::erase Not for this set");
			if (pos.p == NULL) throw invalid_iterator("from set::erase NULL");
			if (pos.p->data == NULL) throw invalid_iterator("from set::erase end()");
			remove(head, pos.p);
			//checktree(head);
		}
		/**
		* Returns the number of elements with key
		*   that compares equivalent to the specified argument,
		*   which is either 1 or 0
		*     since this container does not allow duplicates.
		* The default method of check the equivalence is !(a < b || b > a)
		*/
		size_t count(const Key &key) const {
			if (search(head, key) == NULL) return 0;
			return 1;
		}
		/**
		* Finds an element with key equivalent to key.
		* key value of the element to search for.
		* Iterator to an element with key equivalent to key.
		*   If no such element is found, past-the-end (see end()) iterator is returned.
		*/
		iterator find(const Key &key) {
			set_node* p = search(head, key);
			if (p == NULL) return end();
			iterator it(p, this);
			return it;
		}
		iterator lower_bound(const Key &key) {
			set_node* p = lower_bound(head, key);
            //if (p == NULL) throw index_out_of_bound("from set::lower_bound");
            if (p == NULL) return end();
			return iterator(p, this);
		}
		const_iterator find(const Key &key) const {
			set_node* p = search(head, key);
			if (p == NULL) return cend();
			const_iterator it(p, this);
			return it;
		}
		iterator rank(int t) {
			set_node* p = find_rank(head, t);
			if (p == NULL) return end();
			iterator it(p, this);
			return it;
		}
		const_iterator rank(int t) const {
			set_node* p = find_rank(head, t);
			if (p == NULL) return cend();
			const_iterator it(p, this);
			return it;
		}
	private:
		set_node* head;
		Compare cmp;
		set_node *bg, *ed;
		void remove(set_node* &nw, set_node* t) {
			if (nw == NULL) return;
			if (cmp(*(t->data), *(nw->data))) {
				remove(nw->l, t);
				adjust(nw);
			}
			else {
				if (cmp(*(nw->data), *(t->data))) {
					remove(nw->r, t);
					adjust(nw);
				}
				else {
					if ((nw->l != NULL) && (nw->r != NULL)) {
						set_node* p = nw->nx; //stable iterator!!!!!!
											  //value_type* temp = nw->data; nw->data = p->data; p->data = temp;
						int hh = nw->h; nw->h = p->h; p->h = hh;
						hh = nw->s; nw->s = p->s; p->s = hh;
						set_node* q;
						if (p != nw->r) {
							q = nw->r;
							while (q->l != p) q = q->l;
							q->l = nw;
							q = p->r; p->r = nw->r; nw->r = q;
							p->l = nw->l;
							nw->l = NULL;
						}
						else {
							nw->r = p->r;
							p->l = nw->l;
							p->r = nw;
							nw->l = NULL;
						}
						q = nw; nw = p; p = q;
						remove(nw->r, p);
						adjust(nw);
					}
					else {
						set_node* p = nw;
						if (nw == bg) {
							bg = bg->nx;
							bg->pr = NULL;
						}
						else {
							nw->pr->nx = nw->nx;
							nw->nx->pr = nw->pr;
						}
						if (nw->l == NULL) nw = nw->r; else nw = nw->l;
						//	std::cout << "delete " << p->data->second << std::endl;
						delete p;
					}
				}
			}
		}
		set_node* insert(set_node* &nw, const value_type& v) {
			set_node* x;
			bool rm;
			if (nw == NULL) {
				nw = new set_node(v);
				return nw;
			}
			else {
				if (cmp(v, *(nw->data))) {
					rm = (nw->l == NULL) ? 1 : 0;
					x = insert(nw->l, v);
					if (rm) {
						x->nx = nw;
						x->pr = nw->pr;
						nw->pr = x;
						if (x->pr != NULL) {
							x->pr->nx = x;
						}
						else {
							bg = x;
						}
					}
					maintain(nw, v);
					return x;
				}
				else {
					rm = (nw->r == NULL) ? 1 : 0;
					x = insert(nw->r, v);
					if (rm) {
						x->pr = nw;
						x->nx = nw->nx;
						nw->nx = x;
						x->nx->pr = x;
					}
					maintain(nw, v);
					return x;
				}
			}
		}
		set_node* search(set_node* nw, const Key &key) const {
			if (nw == NULL) return NULL;
			if (cmp(*(nw->data), key)) {
				return search(nw->r, key);
			}
			else {
				if (cmp(key, *(nw->data))) {
					return search(nw->l, key);
				}
				else {
					return nw;
				}
			}
		}
		set_node* lower_bound(set_node* nw, const Key &key) const {
			if (nw == NULL) return NULL;
			if (cmp(*(nw->data), key)) {
				if (nw->r == NULL) return nw->nx;
				return lower_bound(nw->r, key);
			}
			else {
				if (cmp(key, *(nw->data))) {
					if (nw->l == NULL) return nw;
					return lower_bound(nw->l, key);
				}
				else {
					return nw;
				}
			}
		}
		set_node* find_rank(set_node* nw, int s) const {
			if (nw == NULL) return NULL;
			if (nw->l == NULL) {
				if (s == 1) return nw;
				return find_rank(nw->r, s - 1);
			}
			if (nw->l->s >= s) return find_rank(nw->l, s);
			if (s == nw->l->s + 1) return nw;
			return find_rank(nw->r, s - 1 - nw->l->s);
		}
		void copy(set_node* nw, set_node* ori) {
			if (ori->l != NULL) {
				nw->l = new set_node(*(ori->l));
				copy(nw->l, ori->l);
			}
			if (ori->r != NULL) {
				nw->r = new set_node(*(ori->r));
				copy(nw->r, ori->r);
			}
			nw->h_update();
		}
		void ldr(set_node* nw, set_node* &his) {
			if (nw->l != NULL) {
				ldr(nw->l, his);
			}
			if (his == NULL) bg = nw;
			nw->pr = his;
			if (his != NULL) his->nx = nw;
			his = nw;
			if (nw->r != NULL) {
				ldr(nw->r, his);
			}
		}
		void clean(set_node* x) {
			if (x == NULL) return;
			clean(x->l);
			clean(x->r);
			delete x;
		}
		inline void LL(set_node* &x) {
			//		std::cout << "LL" << std::endl;
			set_node* p = x->l;
			x->l = p->r;
			p->r = x;
			x = p;
			x->r->h_update();
			x->h_update();
		}
		inline void RR(set_node* &x) {
			//		std::cout << "RR" << std::endl;
			set_node* p = x->r;
			x->r = p->l;
			p->l = x;
			x = p;
			x->l->h_update();
			x->h_update();
		}
		inline void LR(set_node* &x) {
			//		std::cout << "LR" << std::endl;
			set_node* p = x->l;
			set_node* q = p->r;
			p->r = q->l;
			x->l = q->r;
			q->l = p;
			q->r = x;
			x = q;
			x->l->h_update();
			x->r->h_update();
			x->h_update();
		}
		inline void RL(set_node* &x) {
			//		std::cout << "RL" << std::endl;
			set_node* p = x->r;
			set_node* q = p->l;
			x->r = q->l;
			p->l = q->r;
			q->l = x;
			q->r = p;
			x = q;
			x->l->h_update();
			x->r->h_update();
			x->h_update();
		}
		inline void maintain(set_node* &x, const value_type& v) {
			x->h_update();
			if (x->bd() == 2) {
				if (cmp(v, *(x->l->data))) LL(x); else LR(x);
			}
			if (x->bd() == -2) {
				if (cmp(*(x->r->data), v)) RR(x); else RL(x);
			}
		}
		inline void adjust(set_node*& x) {
			//delete l
			x->h_update();
			if (x->bd() == -2) {
				int bfr = x->r->bd();
				if (bfr == 0 || bfr == -1) RR(x); else RL(x);
			}
			//delete r
			if (x->bd() == 2) {
				int bfr = x->l->bd();
				if (bfr == 0 || bfr == 1) LL(x); else LR(x);
			}
		}
		};

}

#endif
