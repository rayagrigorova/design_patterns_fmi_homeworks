#include "Transformations.h"
#include <cctype> 
#include <regex>
#include <string>
#include <sstream>

namespace {
	// I added this function for replacements instead of using a regex because 
	// replacing special symbols with regexes significantly complicated the code.
	std::string replaceAllOccurrences(std::string str, const std::string& toReplace, const std::string& replacement) {
		size_t startPos = 0;
		// Search for the next occurance of 'toReplace', starting from startPos
		while ((startPos = str.find(toReplace, startPos)) != std::string::npos) {
			// Replace the current matching 'toReplace' string 
			str.replace(startPos, toReplace.length(), replacement);
			// Continue the search from the first character after the replaced ocurrance
			startPos += replacement.length();
		}
		return str;
	}
}

bool TextTransformation::equals(const TextTransformation& other) const {
	// For most transformations, they should simply be of the same type to be equal
	return typeid(*this) == typeid(other);
}

std::string CapitalizeTransformation::transform(std::string text) const {
	if (text.empty()) return "";
	text[0] = std::toupper(text[0]);
	return text;
}

std::unique_ptr<TextTransformation> CapitalizeTransformation::clone() const {
	return std::make_unique<CapitalizeTransformation>(*this);
}

std::string TrimLeftTransformation::transform(std::string text) const {
	// The regex matches one or more whitespace
	// characters at the beginning of the string. 
	return std::regex_replace(text, std::regex("^\\s+"), "");
}

std::unique_ptr<TextTransformation> TrimLeftTransformation::clone() const {
	return std::make_unique<TrimLeftTransformation>(*this);
}

std::string TrimRightTransformation::transform(std::string text) const {
	// The regex matches one or more whitespace
	// characters at the end of the string. 
	return std::regex_replace(text, std::regex("\\s+$"), "");
}

std::unique_ptr<TextTransformation> TrimRightTransformation::clone() const {
	return std::make_unique<TrimRightTransformation>(*this);
}

std::string NormalizeSpaceTransformation::transform(std::string text) const {
	return std::regex_replace(text, std::regex("\\s+"), " ");
}

std::unique_ptr<TextTransformation> NormalizeSpaceTransformation::clone() const {
	return std::make_unique<NormalizeSpaceTransformation>(*this);
}

std::string DecorateTransformation::transform(std::string text) const {
	return "-={ " + text + " }=-";
}

std::unique_ptr<TextTransformation> DecorateTransformation::clone() const {
	return std::make_unique<DecorateTransformation>(*this);
}

CensorTransformation::CensorTransformation(const std::string& toCensor) : toCensor(toCensor){

}

CensorTransformation::CensorTransformation(const CensorTransformation& other) : toCensor(other.toCensor){

}

std::string CensorTransformation::transform(std::string text) const {
	return replaceAllOccurrences(text, toCensor, std::string(toCensor.size(), '*'));
}

std::unique_ptr<TextTransformation> CensorTransformation::clone() const {
	return std::make_unique<CensorTransformation>(toCensor);
}

bool CensorTransformation::equals(const TextTransformation& other) const{
	const CensorTransformation* tt = dynamic_cast<const CensorTransformation*>(&other);
	if (tt) {
		return toCensor == tt->toCensor;
	}
	return false;
}

ReplaceTransformation::ReplaceTransformation(const std::string& toReplace, const std::string& replacement)
	: toReplace(toReplace), replacement(replacement) {

}

ReplaceTransformation::ReplaceTransformation(const ReplaceTransformation& other) : toReplace(other.toReplace), replacement(other.replacement){

}

std::string ReplaceTransformation::transform(std::string text) const {
	return replaceAllOccurrences(text, toReplace, replacement);
}

bool ReplaceTransformation::equals(const TextTransformation& other) const{
	const ReplaceTransformation* rt = dynamic_cast<const ReplaceTransformation*>(&other);
	if (rt) {
		return toReplace == rt->toReplace && replacement == rt->replacement;
	}
	return false;
}

std::unique_ptr<TextTransformation> ReplaceTransformation::clone() const {
	return std::make_unique<ReplaceTransformation>(toReplace, replacement);
}
