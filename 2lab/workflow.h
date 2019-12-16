#pragma once

#include "parser.h"
#include "validator.h"
#include "executor.h"

#include <vector>

class Workflow {
public:
	Workflow(IParser& p, IValidator& v, IExecutor& e):
		parser(p), validator(v), executor(e)
	{}
	void parse();
	void validate();
	void execute();

private:
	std::vector<IWorker*> workers;
	std::vector<IWorker::ID> program;

	IParser& parser;
	IValidator& validator;
	IExecutor& executor;
};
