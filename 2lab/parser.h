#pragma once

#include "worker.h"

#include <string>
#include <vector>


class IParser {
public:
	virtual std::vector<IWorker*> get_workers() const = 0;
	virtual std::vector<IWorker::ID> get_program() const = 0;
};

class Parser: public IParser {
public:
	Parser(const std::string& wf, const std::string& in, const std::string& out):
		wf_fname(wf), in_fname(in), out_fname(out)
	{};
	std::vector<IWorker*> get_workers() const override;
	std::vector<IWorker::ID> get_program() const override;

private:
	IWorker* parse_block(std::string bs) const;

	const std::string wf_fname;
	const std::string in_fname;
	const std::string out_fname;
};
