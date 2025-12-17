// Wavelet tree implementation v3.0
struct wavelet{
    vector <int> pr;
    wavelet *l = nullptr, *r = nullptr;
    int tl, tr;
    void init(vector <int> &a, int tl, int tr) {
        this->tl = tl;
        this->tr = tr;
        if (tl == tr || a.empty()) return;
        int tm = (tl + tr) / 2;
        vector <int> vl, vr;
        pr.pb(0);
        int p = 0;
        for (int &i : a) {
            if (i <= tm) {
                vl.pb(i);
                p++;
            }
            else vr.pb(i);
            pr.pb(p);
        }
        if (!vl.empty()) {
            l = new wavelet();
            l->init(vl, tl, tm);
        }
        if (!vr.empty()) {
            r = new wavelet();
            r->init(vr, tm+1, tr);
        }
    }
    int get(int i, int x) {
        if (i < 0) return 0;
        if (tl == tr) {
            if (tl <= x) return i+1;
            else return 0;
        }
        int tm = (tl + tr) / 2;
        int lp = pr[i+1];
        if (x <= tm) {
            if (!l) return 0;
            return l[0].get(lp-1, x);
        }
        else {
            if (!r) return lp;
            return lp + r[0].get(i - lp, x);
        }
    }
};
