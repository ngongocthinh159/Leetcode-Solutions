class FreqStack {
public:
    unordered_map<int,vector<int>> fToList;
    unordered_map<int,int> valToF;
    int mxf = 0;
    FreqStack() {
    }
    
    void push(int val) {
        int f = ++valToF[val];
        if (mxf < f) mxf++;
        fToList[f].push_back(val);
    }
    
    int pop() {
        auto &l = fToList[mxf];
        int res = l.back();
        l.pop_back();
        valToF[res]--;
        if (l.empty()) mxf--;
        return res;
    }
};

/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack* obj = new FreqStack();
 * obj->push(val);
 * int param_2 = obj->pop();
 */