#include<iostream>

int main() {
#if defined(ENVIROMENT_VSCODE)
	std::cout << "TEST - VSCODE RUNNING" << std::endl;
#endif
	std::cout << "TEST" << std::endl;
}