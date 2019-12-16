#pragma once

#include "worker.h"

class IValidator {
public:
        virtual void validate_workers(const std::vector<IWorker*>&) = 0;
        virtual void validate_program(const std::vector<IWorker*>&, const std::vector<IWorker::ID>&) = 0;
};

class Validator: public IValidator {
        virtual void validate_workers(const std::vector<IWorker*>&);
        virtual void validate_program(const std::vector<IWorker*>&, const std::vector<IWorker::ID>&);
};
