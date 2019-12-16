#include "validator.h"
#include "worker.h"

#include <set>
#include <typeinfo>
#include <iostream>
#include <string>

void Validator::validate_workers(const std::vector<IWorker*>& workers) {
	std::set<IWorker::ID> ids;
	for (auto& w: workers) {
		auto p = ids.insert(w->id());
		if (p.second == false) {
			throw "Duplicate worker ID: " + std::to_string(w->id());
		}
	}
}

void Validator::validate_program(const std::vector<IWorker*>& workers, const std::vector<IWorker::ID>& program) {
	std::set<IWorker::ID> ids;
        for (auto& w: workers) {
		ids.insert(w->id());
                if (w->id() == program.front() && w->name() != "readfile") {
                        throw "The first block must be a readfile";
                }
                if (w->id() == program.back() && w->name() != "writefile") {
                       throw "The last block must be a writefile";
                }
                if ((w->name() == "readfile" || w->name() == "writefile") && (w->id() != program.front() && w->id() != program.back())) {
                        throw "Block readfile/writefile cannot be in the middle of the program" + std::to_string(w->id()) + std::to_string(program.front());
                }

        }
	for (auto& id: program) {
		if (ids.count(id) != 1) {
			throw "Unknown worker ID: " + std::to_string(id);
		}
	}
}
