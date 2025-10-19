//select * from orders where namesurname contains word 'ALI'(keyword)
#include<bits/stdc++.h>
using namespace std;

// 解析一行 CSV（支持双引号和逗号）
vector<string> splitCSVLine(const string& line) {
    vector<string> fields;
    string field;
    bool inQuotes = false;

    for (size_t i = 0; i < line.size(); ++i) {
        char c = line[i];

        if (c == '"') {
            if (inQuotes && i + 1 < line.size() && line[i + 1] == '"') {
                field += '"';
                ++i; // 跳过转义引号
            } else {
                inQuotes = !inQuotes;
            }
        }
        else if (c == ',' && !inQuotes) {
            fields.push_back(field);
            field.clear();
        }
        else {
            field += c;
        }
    }
    fields.push_back(field);
    return fields;
}
string toUpper(const string& str) {
    string result;
    result.reserve(str.size());
    for (char c : str){
        if (c>='a' && c<='z')result += c - 'a' + 'A';
        else result += c;
    }
    return result;
}
bool checkContains(const string& str,const string& keyword) {
    return (str.find(" "+keyword+" ") != string::npos)
        || (str.find(" "+keyword) != string::npos)
        || (str.find(keyword+" ") != string::npos)
        || (str.find(keyword) != string::npos);
}
int main(){
    string filename = "Orders.csv";
    ifstream file(filename);
    ofstream fout("select_results.out");
    if (!file.is_open()) {
        cerr << "无法打开文件: " << filename << endl;
        return 1;
    }

    int selectId = 4;//which column to select
    string keyword = "ALI";//select what
    string line;

    auto start = chrono::high_resolution_clock::now();

    // 逐行读取文件
    getline(file, line);
    fout << line << endl; // 写入表头
    while (getline(file, line)) {
        auto fields = splitCSVLine(line);
        if (checkContains(toUpper(fields[selectId]),keyword)) fout << line << endl;
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    cerr << fixed << setprecision(3) << "\ntime: " << 1000.0 * elapsed.count() << " ms" << endl;

    file.close();
    return 0;
}