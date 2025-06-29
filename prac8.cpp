#include <bits/stdc++.h>
using namespace std;

// Memo key: i1,i2,len  --> valor: 0 = desconocido, 1 = true, -1 = false
unordered_map<string,int> memo;

// Comprueba si s2[pos2 .. pos2+len-1] es scramble de s1[pos1 .. pos1+len-1]
bool isScrambleRec(const string &s1, int pos1, const string &s2, int pos2, int len) {
    // Caso base: longitud 1
    if (len == 1)
        return s1[pos1] == s2[pos2];

    // Construir clave para memo
    string key = to_string(pos1) + "," + to_string(pos2) + "," + to_string(len);
    if (memo.count(key))
        return memo[key] == 1;

    // Poda rápida: si los multiconjuntos de caracteres no coinciden, imposible
    array<int,26> cnt = {};
    for (int i = 0; i < len; i++) {
        cnt[s1[pos1 + i] - 'a']++;
        cnt[s2[pos2 + i] - 'a']--;
    }
    for (int x : cnt) {
        if (x != 0) {
            memo[key] = -1;
            return false;
        }
    }

    // Intentamos cada posible punto de corte [1..len-1]
    for (int cut = 1; cut < len; cut++) {
        // 1) Sin swap: [0..cut) con [0..cut) y [cut..len) con [cut..len)
        if (isScrambleRec(s1, pos1,        s2, pos2,        cut) &&
            isScrambleRec(s1, pos1 + cut, s2, pos2 + cut, len - cut)) {
            memo[key] = 1;
            return true;
        }
        // 2) Con swap:   [0..cut) con [len-cut..len) y [cut..len) con [0..len-cut)
        if (isScrambleRec(s1, pos1,        s2, pos2 + len - cut, cut) &&
            isScrambleRec(s1, pos1 + cut, s2, pos2,             len - cut)) {
            memo[key] = 1;
            return true;
        }
    }

    memo[key] = -1;
    return false;
}

bool isScramble(const string &s1, const string &s2) {
    int n = s1.size();
    memo.clear();
    return isScrambleRec(s1, 0, s2, 0, n);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s1, s2;
    cin >> s1 >> s2;

    bool ans = isScramble(s1, s2);
    cout << (ans ? "true" : "false") << "\n";
    return 0;
}
