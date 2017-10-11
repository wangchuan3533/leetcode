#include <vector>
#include <list>
using namespace std;
// Below is the interface for Iterator, which is already defined for you.
// **DO NOT** modify the interface for Iterator.
class Iterator {
    struct Data;
	Data* data;
public:
	Iterator(const vector<int>& nums);
	Iterator(const Iterator& iter);
	virtual ~Iterator();
	// Returns the next element in the iteration.
	int next();
	// Returns true if the iteration has more elements.
	bool hasNext() const;
};


class PeekingIterator : public Iterator {
    int peekedNum;
    bool isPeeked;

public:
	PeekingIterator(const vector<int>& nums) : Iterator(nums) {
	    // Initialize any member here.
	    // **DO NOT** save a copy of nums and manipulate it directly.
	    // You should only use the Iterator interface methods.
        isPeeked = false;
	}

    // Returns the next element in the iteration without advancing the iterator.
	int peek() {
        if (isPeeked) return peekedNum;
        if (Iterator::hasNext()) {
            peekedNum = Iterator::next();
            isPeeked = true;
            return peekedNum;
        } else {
            return Iterator::next();
        }
	}

	// hasNext() and next() should behave the same as in the Iterator interface.
	// Override them if needed.
	int next() {
        if (isPeeked) {
            isPeeked = false;
            return peekedNum;
        }

        return Iterator::next();
	    
	}

	bool hasNext() const {
        if (isPeeked) return true;
        return Iterator::hasNext();
	}
};
