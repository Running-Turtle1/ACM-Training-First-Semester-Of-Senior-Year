
#include <iostream>
#include <string>

using namespace std;

int main() {
    // 提示用户输入两个字符，用逗号分隔
    cout << "请输入两个字符，用逗号分隔：" << endl;
    string input;
    getline(cin, input);
    
    // 查找逗号位置
    size_t commaPos = input.find(',');
    
    // 确保输入正确
    if (commaPos == string::npos || input.length() != 3) {
        cout << "输入格式错误，请输入两个字符，用逗号分隔。" << endl;
        return 1;
    }
    
    // 提取字符
    char char1 = input[0];
    char char2 = input[2];
    
    // 输出结果
    cout << "The ASCII code of " << char1 << " is " << static_cast<int>(char1) << endl;
    cout << "The ASCII code of " << char2 << " is " << static_cast<int>(char2) << endl;
    
    return 0;
}
