#include <deque>
class MyStack {
public:

    typedef std::deque<int> Queue;

    /** Initialize your data structure here. */
    MyStack() {
        front = &queues[0];
        back = &queues[1];
    }
    
    /** Push element x onto stack. */
    void push(int x) {
        front->push_back(x);
    }
    
    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        while (front->size() > 1) {
            back->push_back(front->front());
            front->pop_front();
        }
        int ret = front->front();
        front->pop_front();
        swap();
        return ret;
    }
    
    /** Get the top element. */
    int top() {
        int ret;
        while (!front->empty()) {
            ret = front->front();
            back->push_back(front->front());
            front->pop_front();
        }
        swap();
        return ret;
    }
    
    /** Returns whether the stack is empty. */
    bool empty() {
       return front->empty();
    }

private:

    void swap() {
        Queue *tmp = front;
        front = back;
        back = tmp;
    }

    Queue queues[2];
    Queue *front;
    Queue *back;
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack obj = new MyStack();
 * obj.push(x);
 * int param_2 = obj.pop();
 * int param_3 = obj.top();
 * bool param_4 = obj.empty();
 */
