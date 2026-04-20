#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

// подсчет веса решения
int totalWeight(const vector<int>& sol, const vector<int>& weight) {
    int sum = 0;
    for (size_t i = 0; i < sol.size(); i++) {
        if (sol[i]) sum += weight[i];
    }
    return sum;
}

// подсчет ценности
int totalValue(const vector<int>& sol, const vector<int>& value) {
    int sum = 0;
    for (size_t i = 0; i < sol.size(); i++) {
        if (sol[i]) sum += value[i];
    }
    return sum;
}

int main() {

    // сюда вставляем данные из файлов

    string data = R"(30 100000
90000  90001
89750  89751
10001  10002
89500  89501
10252  10254
89250  89251
10503  10506
89000  89001
10754  10758
88750  88751
11005  11010
88500  88501
11256  11262
88250  88251
11507  11514
88000  88001
11758  11766
87750  87751
12009  12018
87500  87501
12260  12270
87250  87251
12511  12522
87000  87001
12762  12774
86750  86751
13013  13026
86500  86501
13264  13278
86250  86251
)";

    stringstream ss(data);
    int n, capacity;
    ss >> n >> capacity;

    vector<int> weight(n);
    vector<int> value(n);

    for (int i = 0; i < n; i++) {
        ss >> weight[i] >> value[i];
    }

    // алгоритм по калорийности (ценность/вес)
    // (калорийность, индекс):
    
    vector<pair<double, int>> ratio(n);
    for (int i = 0; i < n; i++) {
        ratio[i] = { (double)value[i] / weight[i], i };
    }

    sort(ratio.begin(), ratio.end(), greater<pair<double, int>>());

   
    vector<int> best(n, 0);
    int current_weight = 0;

    for (auto& r : ratio) {
        int idx = r.second;
        if (current_weight + weight[idx] <= capacity) {
            best[idx] = 1;
            current_weight += weight[idx];
        }
    }

    int best_value = totalValue(best, value);

    
    cout << best_value << endl;
    for (int i = 0; i < n; i++) {
        if (best[i]) {
            cout << i << " ";
        }
    }
    cout << endl;

    return 0;
}