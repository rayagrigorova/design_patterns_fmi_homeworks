#include "Transformations.h"
#include <cctype> 
#include <regex>
#include <string>

std::string CapitalizeTransformation::transform(std::string text) const {
	if (text.empty()) return "";
	text[0] = std::toupper(static_cast<unsigned char>(text[0]));
	return text;
}

std::string TrimLeftTransformation::transform(std::string text) const {
	return std::regex_replace(text, std::regex("^\\s+"), "");
}

std::string TrimRightTransformation::transform(std::string text) const {
	return std::regex_replace(text, std::regex("\\s+$"), "");
}

std::string NormalizeSpaceTransformation::transform(std::string text) const {
	return std::regex_replace(text, std::regex("\\s+"), " ");
}

std::string DecorateTransformation::transform(std::string text) const {
	return "-={" + text + "}=-";
}

std::string CensorTransformation::transform(std::string text) const {
	return std::regex_replace(text, std::regex(toCensor), std::string(toCensor.size(), '*'));
}

bool CensorTransformation::operator==(const TextTransformation& other) const{
	if (!TextTransformation::operator==(other))return false;

	const CensorTransformation* tt = dynamic_cast<const CensorTransformation*>(&other);

	if (tt) {
		return toCensor == tt->toCensor;
	}

	return false;
}

std::string ReplaceTransformation::transform(std::string text) const {
	return std::regex_replace(text, std::regex(toReplace), replacement);
}

bool ReplaceTransformation::operator==(const TextTransformation& other) const{
	if (!TextTransformation::operator==(other))return false;

	const ReplaceTransformation* rt = dynamic_cast<const ReplaceTransformation*>(&other);

	if (rt) {
		return toReplace == rt->toReplace && replacement == rt->replacement;
	}

	return false;
}
