class fTree{
    public: 
    vector<int> bit;
    int n;
    fTree(int n) {
        bit.resize(n+1,0);
        this->n = n;
    }
    void update(int idx, int val) {
        idx++;  // 1 based indexing
        while(idx<=n) {
            bit[idx] += val;
            idx += idx & (-idx);
        }
    }

    int sum(int idx) {
        idx++;  // 1 based indexing
        int s = 0;
        while(idx>0) {
            s += bit[idx];
            idx -= idx & (-idx);
        }
        return s;
    } 

    int getSum(int l, int r) {
        int s = sum(r) - (l ? sum(l-1) : 0);
        return s;
    }
};
