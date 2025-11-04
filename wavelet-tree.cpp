// My first Wavelet Tree Implementation
struct wavelet{
	int n, mn, mx, sz;
	vector <vector <int>> t, id;
	vector <vector <int>> pr;
	void init(int n1, int mi, int ma) {
		n = n1;
		mn = mi;
		mx = ma;
		sz = mx - mn + 1;
		t.resize(120*(n+2));
		id.resize(120*(n+2));
		pr.resize(120*(n+2));
	}
	void build(int v, int tl, int tr, vector <int> &a) {
		int tm = (tl + tr) / 2;
		if (v == 1) {
			for (int i = 0; i < a.size(); i++) {
				t[v].pb(a[i]);
				id[v].pb(i);
			}
		}
		pr[v].pb(0);
		for (int i = 0; i < t[v].size(); i++) {
			if (t[v][i] <= tm) pr[v].pb(1);
			else pr[v].pb(0);
		}
		for (int i = 1; i < pr[v].size(); i++) pr[v][i] += pr[v][i-1];
		if (tl == tr) return;
		for (int i = 0; i < t[v].size(); i++) {
			if (t[v][i] <= tm) {
				t[v*2].pb(t[v][i]);
				id[v*2].pb(id[v][i]);
			}
			else {
				t[v*2+1].pb(t[v][i]);
				id[v*2+1].pb(id[v][i]);
			}
		}
		if (!t[v*2].empty()) build(v*2, tl, tm, a);
		if (!t[v*2+1].empty()) build(v*2+1, tm+1, tr, a);
	}
	int find(int v, int tl, int tr, int l, int r, int x) {
		if (tl == tr) return r - l + 1;
		int tm = (tl + tr) / 2;
		if (x <= tm) return find(v*2, tl, tm, pr[v][l], pr[v][r+1] - 1, x);
		else return find(v*2+1, tm+1, tr, l - pr[v][l], r - pr[v][r+1], x);
	}
	int findk(int v, int tl, int tr, int l, int r, int k) {
		if (tl == tr) return tl;
		int tm = (tl + tr) / 2;
		int ct = pr[v][r+1] - pr[v][l];
		if (ct >= k) return findk(v*2, tl, tm, pr[v][l], pr[v][r+1] - 1, k);
		else return findk(v*2+1, tm+1, tr, l - pr[v][l], r - pr[v][r+1], k - ct);
	}
	void bld(vector <int> &a) {
		build(1, mn, mx, a);
	}
	int get(int l, int r, int x) {
		return find(1, mn, mx, l, r, x);
	}
	int kth(int l, int r, int k) {
		return findk(1, mn, mx, l, r, k);
	}
};
