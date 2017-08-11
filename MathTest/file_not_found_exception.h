#ifndef FILE_NOT_FOUND_EXCEPTION_H
#define FILE_NOT_FOUND_EXCEPTION_H

#include <exception>

class FileNotFoundException : public std::exception {
public:
	const char *what() const noexcept override
	{
		return "File path provided is not valid.";
	}
};

#endif //FILE_NOT_FOUND_EXCEPTION_H
