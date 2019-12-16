#pragma once

#include <vector>
#include <string>

typedef std::vector<std::string> TData;

class IWorker {
public:
	typedef int ID;
	virtual TData execute(TData& input) = 0;
	virtual IWorker::ID id() const = 0;
        virtual std::string name() const = 0;
};

IWorker* make_worker(IWorker::ID, std::string, std::vector<std::string>&);

class Worker: public IWorker {
public:
	Worker(IWorker::ID id, std::vector<std::string>& p, std::string n):
		params(p), ident(id), nam(n)
	{}
	virtual IWorker::ID id() const {
		return ident;
	}
        virtual std::string name() const {
                return nam;
        }
	virtual TData execute(TData& input) override = 0;

protected:
	std::vector<std::string> params;
private:
	IWorker::ID ident;
        std::string nam;
};


class Readfile: public Worker {
public:
        Readfile(IWorker::ID id, std::vector<std::string>& p):
                Worker(id, p, "readfile")
        {
            if (p.size() != 1) {
                throw "Invalid number of parameters in " + std::to_string(id) + " block";
            }
        }
	virtual TData execute(TData& text) override;
};

class Writefile: public Worker {
public:
        Writefile(IWorker::ID id, std::vector<std::string>& p):
                Worker(id, p, "writefile")
        {
            if (p.size() != 1) {
                throw "Invalid number of parameters in " + std::to_string(id) + " block";
            }
        }
	virtual TData execute(TData& text) override;
};

class Grep: public Worker {
public:
        Grep(IWorker::ID id, std::vector<std::string>& p):
                Worker(id, p, "grep")
        {
            if (p.size() != 1) {
                throw "Invalid number of parameters in " + std::to_string(id) + " block";
            }
        }
	virtual TData execute(TData& text) override;
};

class Sort: public Worker {
public:
        Sort(IWorker::ID id, std::vector<std::string>& p):
                Worker(id, p, "sort")
        {
            if (p.size() != 0) {
                throw "Invalid number of parameters in " + std::to_string(id) + " block";
            }
        }
	virtual TData execute(TData& text) override;
};

class Replace: public Worker {
public:
        Replace(IWorker::ID id, std::vector<std::string>& p):
                Worker(id, p, "replace")
        {
            if (p.size() != 2) {
                throw "Invalid number of parameters in " + std::to_string(id) + " block";
            }
        }
	virtual TData execute(TData& text) override;
};

class Dump: public Worker {
public:
        Dump(IWorker::ID id, std::vector<std::string>& p):
                Worker(id, p, "dump")
        {
            if (p.size() != 1) {
                throw "Invalid number of parameters in " + std::to_string(id) + " block";
            }
        }
	virtual TData execute(TData& text) override;
};
