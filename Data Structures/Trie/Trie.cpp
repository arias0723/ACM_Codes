// Trie
class Trie {

public:
	Trie() {
		addNode();
	}

	// Insert a new word in the Trie
	void insert(char* str, const int id = 0) {
		// Update node word count
		nodes[id].word_cnt ++;
		// End of word (... as we know it :D)
		if(*str == 0) {
			nodes[id].word_end ++;
			return;
		}
		// Init
		if(nodes[id].children[*str - first_char] == -1) {
			int idx = addNode();
			nodes[id].children[*str - first_char] = idx;
		}
		insert(str + 1, nodes[id].children[*str - first_char]);
	}
	// Removes an existing word (return true on success)
	bool erase(char* str, const int id = 0) {
		// Word not found
		if(id == -1) return false;
		// End of word 
		if(*str == 0) {
			// Exist in trie (can delete it)
			if(nodes[id].word_end > 0) {
				nodes[id].word_cnt --;
				nodes[id].word_end --;
				return true;
			}
			return false;
		}
		// Check if word exist
		bool exist = erase(str + 1, nodes[id].children[*str - first_char]);
		if(exist) {
			nodes[id].word_cnt --;
		}
		return exist;
	}
	int find(char* str, const int id = 0) {
		// Word not found
		if(id == -1) return 0;
		// End of word
		if(*str == 0) {
			return nodes[id].word_end;
		}
		return find(str + 1, nodes[id].children[*str - first_char]);
	}
	int countPrefix(char* prefix, const int id = 0) {
		// Prefix not found
		if(id == -1) return 0;
		// End of word
		if(*prefix == 0) {
			return nodes[id].word_cnt;
		}
		return countPrefix(prefix + 1, nodes[id].children[*prefix - first_char]);
	}

private:
	static const int alpha_size = 30;
	static const char first_char = 'a';
	struct Node {
		// Node data
		int id, word_cnt, word_end;
		int children[alpha_size];

		Node() {
			id = word_cnt = word_end = 0;
			memset(children, -1, sizeof children);
		}
	};
	vector<Node> nodes;

	// Push new node
	int addNode() {
		Node n;
		n.id = nodes.size();
		nodes.push_back(n);
		return nodes.size() - 1;
	}
};

Trie T;