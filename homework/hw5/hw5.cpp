#include <iostream>

using namespace std;

template <typename T>
class Stats {
    public:
	Stats();
        void push(T&);
	void print();
    private:
	T sum;
	int num;
};

template <typename T>
Stats<T>::Stats() {
    sum = T();
    num = 0;
}

template <typename T>
void Stats<T>::push(T &val) {
    sum += val;
    num++;
    return;
}

template <typename T>
void Stats<T>::print() {
    cout << "N   = " << num << endl;
    cout << "sum = " << sum << endl;
    return;
}

int main() {
    string sin1, sin2, sin3;
    int num1, num2, num3, num4, num5, num6;
    float flt1, flt2, flt3, flt4, flt5, flt6;
    Stats<string> s1; 
    Stats<int> s2;
    Stats<float> s3;
    cout << "String Test:\n-----" << endl;
    cin >> sin1 >> sin2 >> sin3;
    s1.push(sin1);
    s1.push(sin2);
    s1.push(sin3);
    s1.print();
    cout << "\nInt Test:\n-----" << endl;
    cin >> num1 >> num2 >> num3 >> num4 >> num5 >> num6;
    s2.push(num1);
    s2.push(num2);
    s2.push(num3);
    s2.push(num4);
    s2.push(num5);
    s2.push(num6);
    s2.print();
    cout << "\nFloat Test:\n-----" << endl;
    cin >> flt1 >> flt2 >> flt3 >> flt4 >> flt5 >> flt6;
    s3.push(flt1);
    s3.push(flt2);
    s3.push(flt3);
    s3.push(flt4);
    s3.push(flt5);
    s3.push(flt6);
    s3.print();
    return 0;
}
