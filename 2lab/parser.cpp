#include "parser.h"
#include "worker.h"

#include <fstream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

std::vector<IWorker*> Parser::get_workers() const {
	std::ifstream wfs(wf_fname);
	if (!wfs.is_open()) {
		throw "Unable to open workflow file: " + wf_fname;
	}
	std::vector<IWorker*> workers;

	// skip until "desc"
	do {
		std::string s;
		std::getline(wfs, s);
		if (s == "desc") {
			break;
		}
	} while (!wfs.eof());

	IWorker::ID max_id = 0;
	// read blocks
	do {
		std::string s;
		std::getline(wfs, s);
		if (s == "csed") {
			break;
		}
		auto w = parse_block(s);
		if (max_id < w->id()) {
			max_id = w->id();
		}
		workers.push_back(w);
	} while (!wfs.eof());

	if (!in_fname.empty()) {
		std::vector<std::string> p;
		p.push_back(in_fname);
		auto w = make_worker(++max_id, "readfile", p);
		workers.push_back(w);
	}
	if (!out_fname.empty()) {
		std::vector<std::string> p;
		p.push_back(out_fname);
		auto w = make_worker(++max_id, "writefile", p);
		workers.push_back(w);
	}
	return workers;
}

std::vector<IWorker::ID> Parser::get_program() const {
        std::ifstream wfs(wf_fname);
        if (!wfs.is_open()) {
            throw "Unable to open workflow file: " + wf_fname;
        }
        std::vector<IWorker::ID> program;

        // skip until "csed"
        std::string s;
        do {
                std::getline(wfs, s);
                if (s == "csed") {
                        std::getline(wfs, s); // read next string with a program scheme
                        break;
                }
        } while (!wfs.eof());

        // parse a program scheme
        std::istringstream iss(s);
        std::vector<std::string> id;
        std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(id));

	IWorker::ID max_id = 0;
        for (size_t i = 0; i <= id.size(); i = i + 2) {
                if (max_id < stoi(id[i])) {
                    max_id = stoi(id[i]);
                }
                program.push_back(stoi(id[i]));
        }

        if (!in_fname.empty()) {
                program.insert(program.begin(), ++max_id);
        }
	if (!out_fname.empty()) {
                program.push_back(++max_id);
	}
        return program;
}

IWorker* Parser::parse_block(std::string bs) const {
	std::istringstream iss(bs);
	std::vector<std::string> words;
	std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(words));
	std::vector<std::string> params(words.begin() + 3, words.end());
	return make_worker(std::stoi(words[0]), words[2], params);
}
