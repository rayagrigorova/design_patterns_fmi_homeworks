#pragma once

#include "FileVisitor.h"
#include "Observable.h"
#include "StrategyChecksumCalculator.h"

class HashStreamWriter : public FileVisitor, public Observable, public Observer {
	StrategyChecksumCalculator calc;
	std::ostream& os;
	const Directory* directoryTraversed = nullptr; 

	size_t currentIndex = -1;
public:
	HashStreamWriter(std::ostream& os, std::unique_ptr<CryptoPP::HashTransformation>&& strategy);
	HashStreamWriter(std::ostream& os, StrategyChecksumCalculator&& calc);

	void visitFile(const File& file) override;
	void visitDirectory(const Directory& dir)override;

	virtual void subscribe(std::shared_ptr<Observer> o) override;

	class Memento {
		friend class HashStreamWriter;
		friend class ProgressReporter; 
		
		const Directory* directoryTraversed = nullptr;
		std::optional<fs::path> rootDirPath;
		StrategyChecksumCalculator calc;
		std::vector<std::shared_ptr<Observer>> subscribers;
		size_t currentIndex = -1;

		std::uintmax_t totalBytes = 0;
		std::uintmax_t bytesProcessed = 0;
		std::chrono::time_point<std::chrono::steady_clock> startTime;

		void setStreamWriterState(const const Directory* directoryTraversed, const std::optional<fs::path>& rootDirPath,
			const StrategyChecksumCalculator& calc, const std::vector<std::shared_ptr<Observer>>& subscribers, size_t currentIndex);

		void setProgressReporterState(std::uintmax_t totalBytes, std::uintmax_t bytesProcessed,
			const std::chrono::time_point<std::chrono::steady_clock>& startTime);

		Memento(const Directory* directoryTraversed, const std::optional<fs::path>& rootDirPath,
			const StrategyChecksumCalculator& calc, const std::vector<std::shared_ptr<Observer>>& subscribers, size_t currentIndex,
			std::uintmax_t totalBytes, std::uintmax_t bytesProcessed, const std::chrono::time_point<std::chrono::steady_clock>& startTime);
		
		Memento(const HashStreamWriter& hsr); 
		Memento(const ProgressReporter& r);
		Memento() = default;
	public:
		virtual ~Memento() = default;

		Memento(const Memento&) = delete;
		Memento& operator=(const Memento&) = delete;
	};

	Memento save() const;
	void restore(const Memento& m);

	virtual void update(const Observable& sender, const std::string& context) override;
};