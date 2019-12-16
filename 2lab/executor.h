#pragma once

#include "worker.h"

#include <string>

class IExecutor {
public:
	virtual void execute(const std::vector<IWorker*>&, const std::vector<IWorker::ID>&) const = 0;
};

class Executor: public IExecutor {
public:
	void execute(const std::vector<IWorker*>&, const std::vector<IWorker::ID>&) const override;
};
