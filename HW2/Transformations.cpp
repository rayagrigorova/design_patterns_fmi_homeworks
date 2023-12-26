#include "Transformations.h"
#include <cctype> 
#include <regex>
#include <string>
#include <sstream>

namespace {
	std::string replaceAllOccurrences(std::string str, const std::string& toReplace, const std::string& replacement) {
		size_t startPos = 0;
		while ((startPos = str.find(toReplace, startPos)) != std::string::npos) {
			str.replace(startPos, toReplace.length(), replacement);
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
	text[0] = std::toupper(static_cast<unsigned char>(text[0]));
	return text;
}

std::unique_ptr<TextTransformation> CapitalizeTransformation::clone() const {
	return std::make_unique<CapitalizeTransformation>(*this);
}

std::string TrimLeftTransformation::transform(std::string text) const {
	return std::regex_replace(text, std::regex("^\\s+"), "");
}

std::unique_ptr<TextTransformation> TrimLeftTransformation::clone() const {
	return std::make_unique<TrimLeftTransformation>(*this);
}

std::string TrimRightTransformation::transform(std::string text) const {
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

CensorTransformation::CensorTransformation(std::string toCensor) : toCensor(toCensor){

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

ReplaceTransformation::ReplaceTransformation(std::string toReplace, std::string replacement)
	: toReplace(toReplace), replacement(replacement) {

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
