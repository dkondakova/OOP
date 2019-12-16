#include "executor.h"

#include <map>

void Executor::execute(const std::vector<IWorker*>& workers, const std::vector<IWorker::ID>& program) const {
	std::map<IWorker::ID, IWorker*> wmap;
	for (auto& w: workers) {
		wmap[w->id()] = w;
	}
	TData text;
	for (auto& id: program) {
		text = wmap[id]->execute(text);
	}
}
