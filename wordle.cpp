#include <array>
#include <cstdio>
#include <iostream>
#include "words.cpp"
using namespace std;
#define RED "\e[41m"
#define GREEN "\e[42m"
#define YELLOW "\e[43m"
#define reset "\e[0m"

auto random() -> string {
	srand((unsigned int)time(nullptr));
	return TARGETS[rand() % TARGETS.size()];
}

auto search(string s) -> bool {
	for(auto& c:s) c = tolower(c);
	if (s.length() == 5 && WORDS_SET.count(s)) {
		return true;
	}
	return false;
}

auto match(string answer, string target) {
	array<int, 5> ans;
	array<int, 5> t = {0, 0, 0, 0, 0};
	for (int i = 0; i < 5; i++) {
		ans[i] = 0;
		if (answer[i] == target[i] || answer[i] + 32 == target[i]) {
			ans[i] = 2;
			t[i] = 1;
		}
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if ((target[j] == answer[i] || answer[i] + 32 == target[j]) && t[j] == 0) {
				ans[i] = 1;
				t[j] = 1;
				break;
			}
		}
	}
	return ans;
}

auto main() -> int {
	cout << GREEN "          Welcome to Wordle!         " reset << endl;
	cout << GREEN "  Guess the target word in 6 tries!  " reset << endl;
	auto target = random();
	int tries = 6;
	while (tries) {
		string ans;
		cout << endl << (6 - tries + 1) << " >> ";
		cin >> ans;
		if (!search(ans)) {
			cout << RED "  Not a Valid Five Letter Word!  " reset << endl;
			continue;
		}
		cout << "\x1B[1F" << (6 - tries + 1) << " >> ";
		tries--;
		auto res = match(ans, target);
		auto right = 0;
		auto wrong = 0;
		auto wrongP = 0;

		for (int i = 0; i < 5; i++) {
			switch (res[i]) {
				case 0:
					cout << ans[i] << reset;
					wrong++;
					break;

				case 1:
					cout << YELLOW << ans[i] << reset;
					wrongP++;
					break;

				default:
					cout << GREEN << ans[i] << reset;
					right++;
					break;
			}
		}
		if (right == 5) {
			cout << endl << endl
				 << GREEN "You've WON!!  " << target
				 << " is the Correct Answer! " reset << endl;
			break;
		}
	}

	cout << "\n\nThe target word was: " << target << endl;

	system("pause");
}