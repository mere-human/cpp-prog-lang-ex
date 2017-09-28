#include <cstdarg>
#include <iostream>

void error(int severity, ...) {
	va_list ap;
	va_start(ap, severity); // arg startup
	for (;;) {
		char* p = va_arg(ap, char*);
		if (!p) break;
		std::cerr << p << " ";
	}
	va_end(ap);
	std::cerr << "\n";
	if (severity) std::exit(severity);
}

int main() {
	error(0, "just", "warn");
	error(1, "final");
}