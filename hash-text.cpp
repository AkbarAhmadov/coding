#include <bits/stdc++.h>
using namespace std;

using u64 = unsigned long long;
using u8 = unsigned char;

u64 mix64_from_string(const string &s) {
    u64 h = 1469598103934665603ULL;
    for (unsigned char c : s) {
        h ^= (u64)c;
        h *= 1099511628211ULL;
        h = (h ^ (h >> 33)) * 0xff51afd7ed558ccdULL;
        h ^= (h >> 33);
    }
    // scramble more
    h += (u64)s.size() * 0x9e3779b97f4a7c15ULL;
    h ^= (h >> 30);
    h *= 0xbf58476d1ce4e5b9ULL;
    h ^= (h >> 27);
    h *= 0x94d049bb133111ebULL;
    h ^= (h >> 31);
    return h;
}

u64 splitmix64_next(u64 &state) {
    u64 z = (state += 0x9e3779b97f4a7c15ULL);
    z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9ULL;
    z = (z ^ (z >> 27)) * 0x94d049bb133111ebULL;
    return z ^ (z >> 31);
}

string b64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

string base64_encode(const string &in) {
    string out;
    int val = 0, valb = -6;
    for (unsigned char c : in) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            out.push_back(b64_chars[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6) out.push_back(b64_chars[((val << 8) >> (valb + 8)) & 0x3F]);
    while (out.size() % 4) out.push_back('=');
    return out;
}

string base64_decode(const string &in) {
    vector<int> T(256, -1);
    for (int i = 0; i < (int)b64_chars.size(); ++i) T[(unsigned char)b64_chars[i]] = i;
    string out;
    int val = 0, valb = -8;
    for (unsigned char c : in) {
        if (T[c] == -1) {
            if (c == '=') break;
            else continue;
        }
        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0) {
            out.push_back(char((val >> valb) & 0xFF));
            valb -= 8;
        }
    }
    return out;
}

string hex_encode_with_alphabet(const string &in, const string &alpha) {
    static const char *hex = "0123456789abcdef";
    string out;
    for (unsigned char c : in) {
        out.push_back(alpha[(c >> 4) & 0xF]);
        out.push_back(alpha[c & 0xF]);
    }
    return out;
}

string hex_decode_with_alphabet(const string &in, const string &alpha) {
    unordered_map<char,int> idx;
    for (int i=0;i<16;i++) idx[alpha[i]] = i;
    string out;
    if (in.size() % 2 != 0) return "";
    for (size_t i=0;i<in.size(); i+=2) {
        char a = in[i], b = in[i+1];
        if (!idx.count(a) || !idx.count(b)) return "";
        unsigned char v = (idx[a] << 4) | idx[b];
        out.push_back((char)v);
    }
    return out;
}

string random_hex_alphabet(u64 seed) {
    string base = "0123456789abcdef";
    vector<char> v(base.begin(), base.end());
    u64 s = seed;
    for (int i = v.size()-1; i>0; --i) {
        u64 r = splitmix64_next(s);
        size_t j = (size_t)(r % (u64)(i+1));
        swap(v[i], v[j]);
    }
    return string(v.begin(), v.end());
}

string xor_with_keystream(const string &data, u64 seed) {
    string out = data;
    u64 s = seed;
    size_t n = data.size();
    for (size_t i=0;i<n;i++) {
        u64 k = splitmix64_next(s);
        unsigned char kb = (unsigned char)(k & 0xFF);
        out[i] = char((unsigned char)data[i] ^ (kb));
    }
    return out;
}

string permute_bytes(const string &data, u64 seed) {
    size_t n = data.size();
    vector<size_t> idx(n);
    for (size_t i=0;i<n;i++) idx[i]=i;
    u64 s = seed;
    for (size_t i = n; i > 1; --i) {
        u64 r = splitmix64_next(s);
        size_t j = (size_t)(r % i);
        swap(idx[i-1], idx[j]);
    }
    string out(n, 0);
    for (size_t i=0;i<n;i++) out[i] = data[idx[i]];
    return out;
}

string inverse_permute_bytes(const string &data, u64 seed) {
    size_t n = data.size();
    vector<size_t> idx(n);
    for (size_t i=0;i<n;i++) idx[i]=i;
    u64 s = seed;
    for (size_t i = n; i > 1; --i) {
        u64 r = splitmix64_next(s);
        size_t j = (size_t)(r % i);
        swap(idx[i-1], idx[j]);
    }
    vector<size_t> inv(n);
    for (size_t i=0;i<n;i++) inv[idx[i]] = i;
    string out(n, 0);
    for (size_t i=0;i<n;i++) out[i] = data[inv[i]];
    return out;
}

string encrypt(const string &plain, const string &pass) {
    if (plain.empty()) return "";
    string s = plain;
    reverse(s.begin(), s.end());
    u64 seed = mix64_from_string(pass);
    s = xor_with_keystream(s, seed ^ 0xA5A5A5A5A5A5A5A5ULL);
    s = permute_bytes(s, seed ^ 0xC3C3C3C3C3C3C3C3ULL);
    s = base64_encode(s);
    string alpha = random_hex_alphabet(seed ^ 0xF0F0F0F0F0F0F0F0ULL);
    s = hex_encode_with_alphabet(s, alpha);
    unsigned short plen = (unsigned short)(plain.size() & 0xFFFF);
    string header;
    header.push_back(char((plen >> 8) & 0xFF));
    header.push_back(char(plen & 0xFF));
    header = hex_encode_with_alphabet(header, alpha);
    return header + s;
}

string decrypt(const string &cipher, const string &pass) {
    if (cipher.size() < 4) return "";
    u64 seed = mix64_from_string(pass);
    string alpha = random_hex_alphabet(seed ^ 0xF0F0F0F0F0F0F0F0ULL);
    string header = cipher.substr(0,4);
    string body_hex = cipher.substr(4);
    string header_raw = hex_decode_with_alphabet(header, alpha);
    if (header_raw.size() != 2) return "";
    unsigned short plen = ( (unsigned char)header_raw[0] << 8 ) | (unsigned char)header_raw[1];
    string b64 = hex_decode_with_alphabet(body_hex, alpha);
    if (b64.empty() && !body_hex.empty()) return "";
    string permuted = base64_decode(b64);
    string xored = inverse_permute_bytes(permuted, seed ^ 0xC3C3C3C3C3C3C3C3ULL);
    string rev = xor_with_keystream(xored, seed ^ 0xA5A5A5A5A5A5A5A5ULL);
    reverse(rev.begin(), rev.end());
    return rev;
}

int main(){
    string str[3];
    cout << "Mode encrypr/decrypt(e/d):\n";
    cin >> str[0];
    cout << "Text:\n";
    cin.ignore();
    getline(cin, str[1]);
    cout << "Pass:\n";
    cin >> str[2];
    int cnt=1;
    /*
        If you want you can open rows of 201 and 202.
        This allow you to encyrp or decrypt a text with password for many times with only 1 run.
        Initially, code doing this only 1 time.
    */
    // cout << "How many time:\n";
    // cin >> cnt;
    int argc = 5;
    if (argc < 4) {
        cerr << "Usage:\n  " << str[0] << " encrypt \"text\" \"pass\"\n  " << str[0] << " decrypt \"ciphertext\" \"pass\"\n";
        return 1;
    }
    string mode = str[0];
    string a = str[1];
    string pass = str[2];
    if (tolower(mode[0]) == 'e') {
        string out = encrypt(a, pass);
        cnt--;
        while (cnt--) out = encrypt(out, pass);
        cout << out << "\n";
    } else if (tolower(mode[0]) == 'd') {
        string out = decrypt(a, pass);
        cnt--;
        while (cnt--) out = decrypt(out, pass);
        cout << out << "\n";
    } else {
        cerr << "Unknown mode: " << mode << "\n";
        return 1;
    }
    return 0;
}
