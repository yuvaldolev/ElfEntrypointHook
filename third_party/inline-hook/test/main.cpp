
#include "../hooker/HookerFactory.h"
#include <iostream>
#include <cstring>
#include <future>
#include <cstdio>
#include <random>
#include <memory>

void print(const char *s) {
    std::cout << s << std::endl;
}

int (*old_strcmp)(const char *, const char *);

int my_strcmp(const char *s1, const char *s2) {
    std::cout << s1 << " " << s2 << ",haha, it's been hooked" << std::endl;

	if (old_strcmp) {
		std::cout << "old result is: " << old_strcmp(s1, s2) << std::endl;
	}
    return 0;
}

void test_hook(int x) {
  std::cout << "test has been hooked: x=" << x << std::endl;
}

void test(int x) { std::cout << "x: " << x << std::endl; }

int main() {
    const char *s1 = "hello";
    const char *s2 = "world";

    using namespace hooker;
	std::unique_ptr<HookerFactory> factory = HookerFactory::getInstance();
    const Hooker& hooker = factory->getHooker();

    test(5);
    test(6);

    hooker.hook(reinterpret_cast<void *>(test),
                reinterpret_cast<void *>(test_hook), nullptr);

    test(7);
    test(8);

    return 0;
}
