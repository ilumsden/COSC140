#include <iostream>
#include <list>

using namespace std;

template <typename T>
class neq {
    public:
        neq(const T&);
        bool operator()(const T&);
        bool operator()(const T&, const T&);
    private:
        T target;
};

template <typename T>
neq<T>::neq(const T &in_target) {
    target = in_target;
}

template <typename T>
bool neq<T>::operator()(const T &comp) {
    return target != comp;
}

template <typename T>
bool neq<T>::operator()(const T &comp1, const T &comp2) {
    return comp1 != comp2;
}

template <typename It, typename Functor>
int count(It i1, It i2, Functor cond) {
    int numeq = 0;
    while (i1 != i2) {
        if (cond(*i1)) {
            numeq++;
        }
        ++i1;
    } 
    return numeq;
}

int main(int argc, char *argv[]) {
    list<int> v;
    list<int>::iterator iv;
    int value, target;
    while (cin >> value)
        v.push_back(value);
    cin.clear();
    cout << "Set target ";
    cin >> target;
    int N = count(v.begin(), v.end(), neq<int>(target));
    cout << "Found " << N << " elements not equal to target\n";
}
