#include "spellcheck.h"
#include <assert.h>
#include <string>
#include <cstring>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>

#define VERBOSE 0
#define BUFFER_LENGTH 255
#define NEW_LINE '\n'
#define EOS '\0'

using namespace std;

namespace {

    class Node {
        string _txt;
        map <int, Node> _children;
    public:
        void set_text(const string& txt) {
            assert(txt.size() < MAX_WORD_LENGTH);
            clear();
            _txt = txt;
        }

        void clear() {
            _txt = "";
            _children.clear();
        }

        int size() const {
            int i = 1;
            for (auto n : _children) {
                i += n.second.size();
            }
            return i;
        }

        void insert(const string& txt) {
            assert(txt.size() < MAX_WORD_LENGTH);
            if (_txt == "") {
                clear();
                set_text(txt);
            } else {
                const int d = word_distance(txt.c_str(), _txt.c_str());
                if (d == 0)
                    return;
                else if (_children.find(d) != _children.end())
                    _children[d].insert(txt);
                else {
                    _children[d] = Node();
                    _children[d].set_text(txt);
                }
            }
        }

        void lookup(const string& txt, vector<string>& matches) {
            const int d = word_distance(txt.c_str(), _txt.c_str());
            if (d <= TOLERANCE)
                matches.push_back(_txt);
            const int p1 = d - TOLERANCE;
            const int p2 = d + TOLERANCE;
            for (auto n : _children) {
                if (n.first >= p1 && n.first <= p2)
                    n.second.lookup(txt, matches);
            }
        }
    };

    class Comparer {
        const string _s;
    public:
        Comparer(const string& s) : _s(s) {}

        bool operator()(const string& left, const string& right) const {
            const int d1 = word_distance(left.c_str(), _s.c_str());
            const int d2 = word_distance(right.c_str(), _s.c_str());

            return d1 < d2;
        }
    };
}

static Node _tree;

#ifdef __cplusplus
extern "C" {
#endif

    int find_matches(CONST_STR_PTR psz, char m[MAX_MATCHES][MAX_WORD_LENGTH]) {
        vector<string> matches;
        _tree.lookup(psz, matches);
        Comparer comparer(psz);
        sort(matches.begin(), matches.end(), comparer);
        if (matches.size() >= MAX_MATCHES)
            matches.erase(matches.begin() + MAX_MATCHES, matches.end());
        for (int i = 0; i < MAX_MATCHES && i < matches.size(); ++i)
            strcpy(m[i], matches[i].c_str());
        return matches.size();
    }

    int set_dict(CONST_STR_PTR psz) {
        _tree.clear();
        char buffer[BUFFER_LENGTH];
        FILE* input = fopen(psz, "r");
        if (input == NULL)
            return errno;
        while (fgets(buffer, BUFFER_LENGTH, input)) {
            if (buffer[strlen(buffer) - 1] == NEW_LINE) {
                buffer[strlen(buffer) - 1] = EOS;
                _tree.insert(buffer);
            } else {
                _tree.clear();
                fclose(input);
                return EIO;
            }
        }
        fclose(input);
        return _tree.size();
    }


#ifdef __cplusplus
}
#endif
