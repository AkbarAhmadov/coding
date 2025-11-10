// Wavelet tree implementation v2.0
struct wavelet{
	int mn, mx, nxt=1;
	vector <vector <int>> t, pr;
	vector <int> L, R;
	void init(int mi, int ma) {
		mn = mi, mx = ma;
		t.pb({});
		pr.pb({});
		L.pb(-1);
		R.pb(-1);
	}
	void build(int v, int tl, int tr, vector <int> &a) {
		int tm = (tl + tr) / 2;
		if (v == 1) {
			t.pb({});
			for (int i = 0; i < a.size(); i++) t[v].pb(a[i]);
		}
		while (pr.size() <= v) pr.pb({});
		pr[v].pb(0);
		for (int i = 0; i < t[v].size(); i++) {
			if (t[v][i] <= tm) pr[v].pb(1);
			else pr[v].pb(0);
		}
		for (int i = 1; i < pr[v].size(); i++) pr[v][i] += pr[v][i-1];
		if (tl == tr) return;
		while (L.size() <= v) L.pb(-1);
		while (R.size() <= v) R.pb(-1);
		L[v] = ++nxt;
		R[v] = ++nxt;
		while (t.size() <= R[v]) t.pb({});
		for (int i = 0; i < t[v].size(); i++) {
			if (t[v][i] <= tm) t[L[v]].pb(t[v][i]);
			else t[R[v]].pb(t[v][i]);
		}
		if (t[L[v]].size()) build(L[v], tl, tm, a);
		if (t[R[v]].size()) build(R[v], tm+1, tr, a);
	}
	int findk(int v, int tl, int tr, int l, int r, int k) {
		if (tl == tr) return tl;
		int tm = (tl + tr) / 2;
		int ct = pr[v][r+1] - pr[v][l];
		if (ct >= k) return findk(L[v], tl, tm, pr[v][l], pr[v][r+1] - 1, k);
		else return findk(R[v], tm+1, tr, l - pr[v][l], r - pr[v][r+1], k - ct);
	}
    int kth(int l, int r, int k) { return findk(1, mn, mx, l, r, k); }
};
