#include "worker.h"

#include <algorithm>
#include <fstream>
#include <iterator>

IWorker* make_worker(IWorker::ID id, std::string name, std::vector<std::string>& params) {
        if (name == "readfile")
            return new Readfile(id, params);
        if (name == "writefile")
            return new Writefile(id, params);
        if (name == "grep")
            return new Grep(id, params);
        if (name == "sort")
            return new Sort(id, params);
        if (name == "replace")
            return new Replace(id, params);
        if (name == "dump")
            return new Dump(id, params);
        throw "Unknown block name: " + name;
}

TData Readfile::execute(TData &text) {
	std::ifstream ifs(params[0]);
	if (!ifs.is_open()) {
		throw "Unable to open file: " + params[0];
	}
	std::vector<std::string> res;
	for (std::string line; std::getline(ifs, line);) {
		res.push_back(line);
	}
	return res;
}

TData Writefile::execute(TData &text) {
	std::ofstream ofs(params[0]);
	if (!ofs.is_open()) {
		throw "Unable to open file: " + params[0];
	}
    	std::copy(text.begin(), text.end(), std::ostream_iterator<std::string>(ofs, "\n"));
	return TData{};;
}

TData Grep::execute(TData &text) {
	std::vector<std::string> res;
    	std::copy_if(text.begin(), text.end(), std::back_inserter(res), [&](const std::string& s){return s.find(params[0]) != std::string::npos;});
	return res;
}

TData Sort::execute(TData &text) {
	std::sort(text.begin(), text.end());
	return text;
}

TData Replace::execute(TData &text) {
	std::vector<std::string> res = text;
        for (auto it : res) {
            auto w1_pos = it.find(params[0]);
            while (w1_pos != std::string::npos) {
                it.replace(it.begin() + w1_pos, it.begin() + w1_pos + params[0].size(), params[1]);
                w1_pos = it.find(params[0]);
            }
        }
	return res;
}

TData Dump::execute(TData &text) {
	std::ofstream ofs(params[0]);
	if (!ofs.is_open()) {
		throw "Unable to open file: " + params[0];
	}
    	std::copy(text.begin(), text.end(), std::ostream_iterator<std::string>(ofs, "\n"));
	return text;
}
