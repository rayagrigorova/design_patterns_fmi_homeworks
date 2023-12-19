#pragma once

#include <string>
#include <typeinfo>

// Add all transformations to one file to prevent scattering of code 

// Base class for all transformations
class TextTransformation {
public:
	virtual std::string transform(std::string text) const = 0;

	virtual bool equals(const TextTransformation& other) const {
		// For most transformations, they should simply be of the same type to be equal
		return typeid(*this) == typeid(other);
	}
};

// The first few transformations don't require any additional information to be executed
class CapitalizeTransformation : public TextTransformation {
public:
	std::string transform(std::string text) const override;
};

class TrimLeftTransformation : public TextTransformation {
public:
	std::string transform(std::string text) const override;
};

class TrimRightTransformation : public TextTransformation {
public:
	std::string transform(std::string text) const override;
};

class NormalizeSpaceTransformation : public TextTransformation {
public:
	std::string transform(std::string text) const override;
};

class DecorateTransformation : public TextTransformation {
public:
	std::string transform(std::string text) const override;
};

// The following 2 transformations require additional information 
class CensorTransformation : public TextTransformation {
	std::string toCensor;
public:
	CensorTransformation(std::string toCensor) : toCensor(toCensor){}
	std::string transform(std::string text) const override;

	bool equals(const TextTransformation& other) const override;
};

class ReplaceTransformation : public TextTransformation {
	std::string toReplace;
	std::string replacement;
public:
	ReplaceTransformation(std::string toReplace, std::string replacement) : toReplace(toReplace), replacement(replacement){}
	std::string transform(std::string text) const override;

	bool equals(const TextTransformation& other) const override;
};
