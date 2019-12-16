#pragma once

#include "worker.h"

class IValidator {
public:
        virtual void validate_workers(const std::vector<IWorker*>&) = 0;
        virtual void validate_program(const std::vector<IWorker*>&, const std::vector<IWorker::ID>&) = 0;
};

class Validator: public IValidator {
        void validate_workers(const std::vector<IWorker*>&) override;
        void validate_program(const std::vector<IWorker*>&, const std::vector<IWorker::ID>&) override;
};
