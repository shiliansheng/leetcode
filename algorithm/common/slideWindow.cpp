// ��������

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int lengthOfLongestSubstring(string s) {
    int left = 0;                     // ��ָ��
    int right = 0;                    // ��ָ��
    int maxLen = 0;                   // ��Ӵ�����
    unordered_map<char, int> window;  // ������ÿ���ַ����ֵĴ���

    while (right < s.size()) {  // ��ָ�����ַ�����Χ��
        char c = s[right];      // ��ָ��ָ����ַ�
        right++;                // ��ָ�������ƶ�

        // ���´�����ÿ���ַ����ֵĴ���
        window[c]++;

        // ��������г����ظ��ַ�����ָ�������ƶ�ֱ�������в������ظ��ַ�
        while (window[c] > 1) {
            char d = s[left];  // ��ָ��ָ����ַ�
            left++;            // ��ָ�������ƶ�
            // ���´�����ÿ���ַ����ֵĴ���
            window[d]--;
        }

        // ������Ӵ�����
        maxLen = max(maxLen, right - left);
    }

    return maxLen;
}

string minWindow(string s, string t) {
    unordered_map<char, int> needs, window;  // ��Ҫ����ĸ������ִ�������ǰ�����е���ĸ������ִ���
    for (char c : t)
        needs[c]++;
    int left = 0, right = 0;       // �������ڵ�����ָ��
    int start = 0, len = INT_MAX;  // ��¼��ǰ��С�Ӵ�����ʼλ�ã���С�ִ��ĳ���
    int valid = 0;                 // ��ǰ�������Ѿ�������t����ĸ�ĸ���
    while (right < s.size()) {     // �����ڵ��ұ߽�û�г���s�ı߽�ʱ�������ƶ���ָ�����󴰿�
        char c = s[right];         // ȡ���ַ�c
        right++;                   // ��ָ������һλ
        if (needs.count(c)) {      // ���c��t�е��ַ�������window��c�ļ���
            window[c]++;
            if (window[c] == needs[c])  // ���window��c�ļ�������t��c�ļ�����˵��window���Ѿ�������t������c������
                valid++;                // ����valid��ֵ
        }
        while (valid == needs.size()) {  // ���window�Ѿ�������t�����е��ַ�����ʼ�ƶ���ָ����С����
            if (right - left < len) {    // �����ǰ���ڱȵ�ǰ��СֵС��������Сֵ
                start = left;            // ��¼��ǰ��С�Ӵ�����ʼλ��
                len = right - left;      // ��¼��ǰ��С�Ӵ��ĳ���
            }
            char d = s[left];               // ȡ����ָ����ָ���ַ�d
            left++;                         // ��ָ������һλ
            if (needs.count(d)) {           // ���d��t�е��ַ�������window��d�ļ���
                if (window[d] == needs[d])  // ���window��d�ļ�������t��d�ļ�����˵��window���Ѿ����ٰ���t������d������
                    valid--;                // ����valid��ֵ
                window[d]--;                // ����window��d�ļ���
            }
        }
    }
    // ���δ�ҵ������������Ӵ������ؿմ�
    return len == INT_MAX ? "" : s.substr(start, len);  // ���ط�����������С�Ӵ�
}

string minWindow2(string s, string t) {
    unordered_map<char, int> needs, window;
    string res = "";
    int minsize = INT_MAX, size = s.size(), l = 0, r = 0, valid = 0, validsize = 0, begin = 0;
    for (auto& c : t) {
        needs[c]++;
    }
    validsize = needs.size();
    while (r < size) {
        while (r < size && valid != validsize) {
            if (needs.count(s[r])) {
                window[s[r]]++;
                if (window[s[r]] == needs[s[r]]) {
                    ++valid;
                }
            }
            ++r;
        }
        while (l < r && validsize == valid) {
            if (needs.count(s[l])) {
                window[s[l]]--;
                if (window[s[l]] < needs[s[l]]) {
                    if (minsize > r - l) {
                        begin = l;
                        minsize = r - l;
                    }
                    --valid;
                }
            }
            ++l;
        }
    }
    return minsize == INT_MAX ? "" : s.substr(begin, minsize);
}

int main() {
    // string s = "abcabcbb";
    // int len = lengthOfLongestSubstring(s);
    // cout << len << endl; // ���3����"abc"�ĳ���
    // cout << minWindow2("ADOBECODEBANC", "ABC") << endl;
    cout << minWindow2("cabwefgewcwaefgcf", "cae") << endl;
    return 0;
}
