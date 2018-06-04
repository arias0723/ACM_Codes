// STREE
template<class T>
class Stree {

public:
	Stree(int size) {
		this->size = size;
		stree.reserve(size*4);
		build(1, 0, size -1);
	}

	void updateRange(int x, int y, T val) {
		__updateRange(1, 0, this->size -1, x, y, val);
	}
	T queryRange(int x, int y) {
		return __queryRange(1, 0, this->size -1, x, y);
	}

private:
	// Funtion used for combine results of the children
	static T combine(T v1, T v2) {
		// ... reimplement for problem specifics
		return v1 + v2;
	}
	template<typename U/*, typename V*/>
	struct Node {
		U val, lazy;
		int left, right;

		Node() {}
		Node(U v, U lz) {val = v; lazy = lz;}
		Node(U v, U lz, int l, int r) {val = v; lazy = lz; left = l; right = r;}
		// Init node with default value
		void init(Node& lchild, Node& rchild) {
			// ... reimplement for problem specifics
			this->lazy = 0;
			if(this->left == this->right) {
				this->val = 0;
			}
			else {
				this->val = combine(lchild.value(), rchild.value());
			}			
		}
		// Get node value
		U value() {
			// ... reimplement for problem specifics
			return val;
		}		
		// Apply on updates
		void apply(U v) {
			// ... reimplement for problem specifics
			this->val += v*(right - left + 1);
			this->lazy += v;
		}
		// Push lazy values to node children
		void pushLazy(Node& lchild, Node& rchild) {
			// ... reimplement for problem specifics
			if(lazy) {
				lchild.apply(lazy);
				rchild.apply(lazy);
				this->lazy = 0;
			}
		}
		// Update node val with children values
		void update(Node& lchild, Node& rchild) {
			// ... reimplement for problem specifics
			this->val = combine(lchild.value(), rchild.value());
		}
	};
	vector<Node<T>> stree;
	int size;

	void build(int root, int l, int r) {

		if(r > l) {
			build(2*root, l, (l+r)/2);
			build(2*root +1, (l+r)/2 +1, r);
		}
		stree[root].left = l; stree[root].right = r;
		stree[root].init(stree[root*2], stree[root*2 + 1]);
	}
	void __updateRange(int root, int i, int j, const int l, const int r, const T val) {

		// Completely out-range
		if(i > j || i > r || j < l) return;
		// Completely in-range
		if(i >= l && j <= r) {
			// Update node and lazy value(to push() later)
			stree[root].apply(val);
			return;
		}
		// If you go down into node children, you need to:
		// 1: Push lazy stored values to children
		stree[root].pushLazy(stree[root*2], stree[root*2 + 1]);
		// 2: Split the range
		__updateRange(2*root, i, (i+j)/2, l, r, val);
		__updateRange(2*root +1, (i+j)/2 +1, j, l, r, val);
		// 3: Update node value with children values
		stree[root].update(stree[root*2], stree[root*2 + 1]);
	}
	T __queryRange(int root, int i, int j, const int l, const int r) {

		// Completely out-range
		if(i > j || i > r || j < l) return 0;
		// Completely in-range
		if(i >= l && j <= r) {
			return stree[root].value();
		}
		// Push lazy value to children
		stree[root].pushLazy(stree[root*2], stree[root*2 + 1]);
		// Partialy in-range
		T v1 = __queryRange(2*root, i, (i+j)/2, l, r);
		T v2 = __queryRange(2*root +1, (i+j)/2 +1, j, l, r);

		return combine(v1, v2);
	}


};

// 0-based indexes
// inclusive ranges
Stree<ll> stree(N);
