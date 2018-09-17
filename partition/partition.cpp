#include <algorithm>
#include <cassert>
#include <cmath>
#include "partition.h"

string Partition::name()
{
	return "Partition";
}

int64_t Partition::total(int n)
{
	int k = f.size();
	return (0 <= n && n < k) ? f[n] : INT64_MAX;
}

vector<int> first(int n) {
	vector<int> ans(n);
	for (int i = 0; i < n; i++) {
		ans[i] = 1;
	}
	return ans;
}

vector<int> last(int n) {
	vector<int> ans(n);
	ans[0] = n;
	for (int i = 1; i < n; i++) {
		ans[i] = 0;
	}
	return ans;
}

static vector <int> nextel(vector <int> v)
{
	auto k = (int)(v.size());
	int m;
	bool unfixed = true;
	vector <int> ans = v;
	int res = 0;
	for (int i = 0; i < k; i++)
	{
		if (unfixed)
		{
			res = res + ans[i];
		}
		if (!unfixed)
		{
			if (res >= m)
			{
				ans[i] = m;
				res = res - m;
			}
			else
			{
				ans[i] = res;
				res = 0;
			}
		}
		if (i < k - 1)
		{
			if ((ans[i] > 1 && ans[i + 1] <= 1) && unfixed)
			{
				ans[i] = ans[i] - 1;
				m = ans[i];
				unfixed = false;
				res = res - 1;
				res = k - res;
			}
		}
	}
	return ans;
}

static vector <int> prevel(vector <int> v)
{
	auto k = (int)(v.size());
	int m = 0;
	vector <int> ans = v;
	for (int i = 1; i < k - 1; i++)
	{
		if (ans[i] < ans[i - 1] && (ans[i] != 0 && ans[i + 1] != 0))
		{
			m = i;
		}
	}
	int res = 0;
	for (int i = 0; i <= m; i++)
	{
		res = res + ans[i];
	}
	res++;
	ans[m]++;
	res = k - res;
	int r = k - m - 1;
	int filler = res / r;
	if (filler*r != res)
	{
		filler++;
	}
	for (int i = m + 1; i < k; i++)
	{
		if (res > filler)
		{
			ans[i] = filler;
			res = res - filler;
		}
		else
		{
			ans[i] = res;
			res = 0;
		}
	}
	return ans;
}

vector <vector <int> > Partition::generate_all(int n)
{
	vector < vector <int> > all;
	if (n < 0)
	{
		return all;
	}
	if (n == 0)
	{
		vector<int> kek(0);
		all.push_back(kek);
		return all;
	}
	else
	{
		size_t size = n;
		vector <int> cur(size);
		cur[0] = n;
		vector <int> end(size);
		for (int i = 0; i < n; i++)
		{
			end[i] = 1;
		}
		while (cur != end)
		{
			all.push_back(end);
			end = prevel(end);
		}
		all.push_back(cur);
		return all;
	}
}

bool Partition::is_valid(vector <int> const & v)
{
	auto n = (int)(v.size());
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		if (i > 0)
		{
			if (v[i] > v[i - 1])
			{
				return false;
			}
		}
		sum = sum + v[i];
	}
	if (sum != n)
	{
		return false;
	}
	return true;
}

uint64_t number(int n, int m) {
	if (m == 0) {
		if (n == 0) {
			return 1;
		}
		return 0;
	}
	if (m > n) {
		return number(n, n);
	}
	uint64_t a = number(n, m - 1) + number(n - m, m);
	if (a > INT64_MAX) {
		a = INT64_MAX;
	}
	return a;
}

int64_t Partition::number_by_object(vector <int> const & v)
{
	int n = v.size();
	int k = v[0];
	if ((n == 1) || (k == 1)) {
		return 0;
	}
	if (k == n) {
		if (k >= 406) {
			return INT64_MAX;
		}
		return total(n)-1;
	}
	vector<int> v1(n - k);
	for (int i = 0; i < n - k; i++) {
		v1[i] = v[i + 1];
	}
	uint64_t num1 = number(n, k-1);
	uint64_t num2 = number_by_object(v1);
	if (num1+num2>= 9223372036854775806){
		return 9223372036854775807;
	}
	return num1 + num2;
}

vector <int> Partition::object_by_number(int n, int64_t k)
{
	auto all = generate_all(n);
	if (k<0 || k >= int64_t(all.size()))
	{
		vector <int> kek;
		return kek;
	}
	return all[int(k)];
}

bool Partition::prev(vector <int> & v)
{
	auto k = (int)(v.size());
	if (k == 0)
	{
		return false;
	}
	else
	{
		size_t size = k;
		if (v[v.size()-1] == 1)
		{
			v = last(k);
			return false;
		}
		v = nextel(v);
		return true;
	}
}

bool Partition::next(vector <int> & v)
{
	auto n = (int)(v.size());
	if (n == 0)
	{
		return false;
	}
	else if (v[0] == n)
	{
		v = first(n);
		return false;
	}
	v = prevel(v);
	return true;
}

Partition::~Partition()
{
}

static vector <uint64_t> init_f()
{
	vector <uint64_t> f;
	f.push_back(1);
	while (true)
	{
		int s = f.size();
		uint64_t res = 0;
		for (int q = 1; (3 * q*q - q) / 2 <= s; q++)
		{
			int a = s - (3 * q*q - q) / 2;
			int b = s - (3 * q*q + q) / 2;
			uint64_t j1 = f[a];
			uint64_t j2;
			if (b >= 0)
			{
				j2 = f[b];
			}
			else
			{
				j2 = 0;
			}
			uint64_t bla = j1 + j2;
			if (q % 2 == 1)
			{
				res = res + bla;
			}
			else
			{
				res = res - bla;
			}
		}
		if (res < f[f.size() - 1] || res > INT64_MAX)  // overflow
		{
			return f;
		}
		f.push_back(res);
	}
}

vector <uint64_t> Partition::f = init_f();