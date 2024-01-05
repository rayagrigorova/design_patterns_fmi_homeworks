#pragma once

#include <string>
#include <typeinfo>
#include <memory>

// All transformations are added to one file to prevent scattering of code 

// Base class for all transformations
class TextTransformation {
public:
	virtual ~TextTransformation() = default; 

	virtual std::string transform(std::string text) const = 0;
	virtual bool equals(const TextTransformation& other) const;

	/* The Label interface uses Label* clone() (raw pointers) and
	   TextTransformation uses std::unique_ptr<TextTransformation> clone() (smart opointers).
	   Mixing the two types of pointers is generally considered bad practice,
	   but due to the implementation of the decorator removal logic it is necessary.
	*/
	virtual std::unique_ptr<TextTransformation> clone() const = 0;
};

// The first few transformations don't require any additional information to be executed
class CapitalizeTransformation : public TextTransformation {
public:
	std::string transform(std::string text) const override;
	virtual std::unique_ptr<TextTransformation> clone() const override;
};

class TrimLeftTransformation : public TextTransformation {
public:
	std::string transform(std::string text) const override;
	virtual std::unique_ptr<TextTransformation> clone() const override;
};

class TrimRightTransformation : public TextTransformation {
public:
	std::string transform(std::string text) const override;
	virtual std::unique_ptr<TextTransformation> clone() const override;
};

class NormalizeSpaceTransformation : public TextTransformation {
public:
	std::string transform(std::string text) const override;
	virtual std::unique_ptr<TextTransformation> clone() const override;
};

class DecorateTransformation : public TextTransformation {
public:
	std::string transform(std::string text) const override;
	virtual std::unique_ptr<TextTransformation> clone() const override;
};

// The following 2 transformations require additional information 
class CensorTransformation : public TextTransformation {
	std::string toCensor;
public:
	CensorTransformation(const std::string& toCensor);
	CensorTransformation(const CensorTransformation& other);

	std::string transform(std::string text) const override;
	bool equals(const TextTransformation& other) const override;

	virtual std::unique_ptr<TextTransformation> clone() const override;
};

class ReplaceTransformation : public TextTransformation {
	std::string toReplace;
	std::string replacement;
public:
	ReplaceTransformation(const std::string& toReplace, const std::string& replacement);
	ReplaceTransformation(const ReplaceTransformation& other);

	std::string transform(std::string text) const override;
	bool equals(const TextTransformation& other) const override;

	virtual std::unique_ptr<TextTransformation> clone() const override;
};
