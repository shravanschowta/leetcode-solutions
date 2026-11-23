class ProductOfNumbers {
public:
    vector<int>ans;
    ProductOfNumbers() {
        ans.push_back(1);
    }
    
    void add(int num) {
        ans.push_back(num);
    }
    
    int getProduct(int k) {
        int i=ans.size()-k;
        int product=1;
        while(i<ans.size()){
            product*=ans[i];
            i++;
        }
        return product;
    }
};

/**
 * Your ProductOfNumbers object will be instantiated and called as such:
 * ProductOfNumbers* obj = new ProductOfNumbers();
 * obj->add(num);
 * int param_2 = obj->getProduct(k);
 */