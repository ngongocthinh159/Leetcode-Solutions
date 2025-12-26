#define iii pair<int,pair<int,int>>
auto cmp = [](iii& p1, iii& p2) {
    return p2 > p1;
};
class FreqStack {
public:
    int time = 0;
    priority_queue<iii,vector<iii>,decltype(cmp)> q;
    unordered_map<int,int> f;
    FreqStack() {
        q = priority_queue<iii,vector<iii>,decltype(cmp)>(cmp);
    }
    
    void push(int val) {
        int freq = ++f[val];
        q.push({freq, {time, val}});
        time++;
    }
    
    int pop() {
        auto p = q.top();
        q.pop();
        f[p.second.second]--;
        return p.second.second;
    }
};

/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack* obj = new FreqStack();
 * obj->push(val);
 * int param_2 = obj->pop();
 */