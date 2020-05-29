#include<bits/stdc++.h>
using namespace std;

// Credits: https://github.com/mission-peace

int main()
{
	string s;
	cout << "Enter input string:\n";
	cin >> s;

	string temp = "$";
	for(auto x : s) {
		temp += x;
		temp += '$';
	}
	s = temp;
	
	int n = s.size();
	int palindrome_length[n] = {0};
	int start = 0, end = 0;
	for(int i = 0; i < n;) {
		while(start > 0 && end < n-1 && s[start-1] == s[end+1]) {
			--start, ++end;
		}
		palindrome_length[i] = end - start + 1;
		if(end == n-1) {
			break;
		}
		int new_center = end + (i%2 == 0 ? 1:0);
		for(int j = i+1; j <= end; ++j) {
			palindrome_length[j] = min(palindrome_length[i - (j-i)], 2*(end-j) + 1);
			if(j + palindrome_length[i - (j-i)]/2 == end) {
				new_center = j;
				break;
			}
		}
		i = new_center;
		end 	= i + palindrome_length[i]/2;
		start 	= i - palindrome_length[i]/2;
	}

	int max_length = 0, idx = 0;
	for(int i = 0; i < n; ++i) {
		if(max_length < palindrome_length[i]) {
			max_length = palindrome_length[i], idx = i;
		}
	}

	cout << max_length/2 << endl;
	for(int i = idx - max_length/2; i <= idx + max_length/2; ++i) {
		if(s[i] != '$')
			cout << s[i];
	}
	cout << endl;
}