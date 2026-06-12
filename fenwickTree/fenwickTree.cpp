#include <bits/stdc++.h>
#pragma GCC optimize("O3") // O3 or we may time out :(
using namespace std;  

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
 
 
int solve()
{   
    int n;
    cin>>n;
    vector<int> arr(n);
    for(int i=0; i<n; i++) cin>>arr[i];

    fTree f = fTree(n);

    for(int i=0; i<n; i++) {
        f.update(i, arr[i]);
    }

    int q;
    cin>>q;

    while(q--) {
        int type;
        cin>>type;
        if(type==1) {
            int l,r;
            cin>>l>>r;

            //get sum
            cout<< f.getSum(l,r) <<endl;
        } else {
            int idx,val;
            cin>>idx>>val;

            f.update(idx, val - arr[idx]);  //update the value with the difference 
            arr[idx] = val;
        }
    }

    
    
    
    return 0;
}
 
signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
 
    // long long t;
    // cin >> t;
    // while (t--)
 
        solve();
 
    return 0;
}