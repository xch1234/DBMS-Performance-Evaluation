//select * from orders where namesurname contains word 'ALI'(keyword)
#include<bits/stdc++.h>
using namespace std;

string keyword = "a";//update what
string updateword = "A";
int updateId = 4;//which column to update
inline string update(const string& field) {
    size_t pos = 0, prev = 0;
    string result="";
    while ((pos = field.find(keyword, pos)) != std::string::npos) {
        result.append(field, prev, pos - prev);
        result += updateword;
        prev = pos + updateword.size();
        pos += keyword.size();
    }
    return field;
}
string splitAndUpdate(const string& line) {
    string result="";
    string field;
    bool inQuotes = false;
    int cnt=0;

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
            if(cnt==updateId)field=update(field);
            result+=field+",";
            field.clear();
            cnt++;
        }
        else {
            field += c;
        }
    }
    if(cnt==updateId)field=update(field);
    result+=field;
    return result;
}

int main(){
    string filename = "Orders.csv";
    ifstream file(filename);
    ofstream fout("update_results.out");
    if (!file.is_open()) {
        cerr << "无法打开文件: " << filename << endl;
        return 1;
    }

    string line;

    auto start = chrono::high_resolution_clock::now();

    // 逐行读取文件
    getline(file, line);
    fout << line << endl; // 写入表头
    while (getline(file, line)) {
        fout << splitAndUpdate(line) << endl;
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    cerr << fixed << setprecision(3) << "\ntime: " << 1000.0 * elapsed.count() << " ms" << endl;

    file.close();
    return 0;
}