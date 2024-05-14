#pragma once
class textureException : public std::exception {
public:
	virtual const char* what() const throw() = 0;
	virtual ~textureException() {};
};