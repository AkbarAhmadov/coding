#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
  #define COLOR_RESET  ""
  #define COLOR_NAME   ""
  #define COLOR_VALUE  ""
  #define COLOR_TIME   ""
#elif defined(COMP_TEST)
  #define COLOR_RESET  ""
  #define COLOR_NAME   ""
  #define COLOR_VALUE  ""
  #define COLOR_TIME   ""
#else
  #define COLOR_RESET  "\033[0m"
  #define COLOR_NAME   "\033[1;36m"
  #define COLOR_VALUE  "\033[1;31m"
  #define COLOR_TIME   "\033[1;32m"
#endif

struct _Timer {
    chrono::time_point<chrono::high_resolution_clock> start;
    _Timer() { start = chrono::high_resolution_clock::now(); }
    ~_Timer() {
        auto end = chrono::high_resolution_clock::now();
        cerr << COLOR_TIME << "\n[Calisma Suresi: " 
             << chrono::duration_cast<chrono::milliseconds>(end - start).count() 
             << " ms]" << COLOR_RESET << "\n";
    }
} _global_timer;

void __print(int x) {cerr << COLOR_VALUE << x << COLOR_RESET;}
void __print(long x) {cerr << COLOR_VALUE << x << COLOR_RESET;}
void __print(long long x) {cerr << COLOR_VALUE << x << COLOR_RESET;}
void __print(unsigned x) {cerr << COLOR_VALUE << x << COLOR_RESET;}
void __print(unsigned long x) {cerr << COLOR_VALUE << x << COLOR_RESET;}
void __print(unsigned long long x) {cerr << COLOR_VALUE << x << COLOR_RESET;}
void __print(float x) {cerr << COLOR_VALUE << x << COLOR_RESET;}
void __print(double x) {cerr << COLOR_VALUE << x << COLOR_RESET;}
void __print(long double x) {cerr << COLOR_VALUE << x << COLOR_RESET;}
void __print(char x) {cerr << COLOR_VALUE << '\'' << x << '\'' << COLOR_RESET;}
void __print(const char *x) {cerr << COLOR_VALUE << '\"' << x << '\"' << COLOR_RESET;}
void __print(const string &x) {cerr << COLOR_VALUE << '\"' << x << '\"' << COLOR_RESET;}
void __print(bool x) {cerr << COLOR_VALUE << (x ? "true" : "false") << COLOR_RESET;}

template<typename T, typename V>
void __print(const pair<T, V> &x);
template<typename T>
void __print(const T &x);

template<size_t i, typename T>
void print_tuple_helper(const T& tup) {
    if constexpr (i < tuple_size<T>::value) {
        if constexpr (i > 0) cerr << COLOR_VALUE << ", " << COLOR_RESET;
        __print(get<i>(tup));
        print_tuple_helper<i + 1>(tup);
    }
}
template<typename... T>
void __print(const tuple<T...>& tup) {
    cerr << COLOR_VALUE << '{' << COLOR_RESET; 
    print_tuple_helper<0>(tup); 
    cerr << COLOR_VALUE << '}' << COLOR_RESET;
}

template<typename T, typename V>
void __print(const pair<T, V> &x) {
    cerr << COLOR_VALUE << '{' << COLOR_RESET; 
    __print(x.first); 
    cerr << COLOR_VALUE << ", " << COLOR_RESET; 
    __print(x.second); 
    cerr << COLOR_VALUE << '}' << COLOR_RESET;
}

template<typename T>
void __print(const T &x) {
    int f = 0;
    cerr << COLOR_VALUE << '{' << COLOR_RESET;
    for (auto &i: x) {
        if (f++) cerr << COLOR_VALUE << ", " << COLOR_RESET;
        __print(i);
    }
    cerr << COLOR_VALUE << '}' << COLOR_RESET;
}

template<typename T>
void __print(stack<T> s) {
    vector<T> v;
    while (!s.empty()) { v.push_back(s.top()); s.pop(); }
    reverse(v.begin(), v.end());
    __print(v);
}

template<typename T>
void __print(queue<T> q) {
    vector<T> v;
    while (!q.empty()) { v.push_back(q.front()); q.pop(); }
    __print(v);
}

template<typename T>
void __print(priority_queue<T> pq) {
    vector<T> v;
    while (!pq.empty()) { v.push_back(pq.top()); pq.pop(); }
    __print(v);
}

void _print_vertical(string names) { (void)names; }

template <typename T, typename... V>
void _print_vertical(string names, T t, V... v) {
    size_t comma = names.find(',');
    string name = names.substr(0, comma);
    
    // Boşlukları temizle
    name.erase(0, name.find_first_not_of(" \t\n\r"));
    name.erase(name.find_last_not_of(" \t\n\r") + 1);

    cerr << COLOR_NAME << name << COLOR_RESET << " = ";
    __print(t);
    cerr << endl;

    if constexpr (sizeof...(v) > 0) {
        _print_vertical(names.substr(comma + 1), v...);
    }
}

#define debug(x...) _print_vertical(#x, x)
