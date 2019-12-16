#include "workflow.h"
#include "parser.h"
#include "validator.h"
#include "executor.h"

#include <iostream>
#include <string>

std::string usage(const std::string& prog) {
	return "Usage: " + prog + " <workflow-file> [-i input] [-o output]";
}

void cmd_args(int argc, char* argv[], std::string& wf, std::string& in, std::string& out) {
	const std::string prog(argv[0]);
	if (argc != 2 && argc != 4 && argc != 6) {
		throw usage(prog);
	}
	wf = argv[1];
	for (int i = 2; i < argc; i+=2) {
		if (argv[i] == std::string("-i")) {
			in = argv[i+1];
		} else if (argv[i] == std::string("-o")) {
			out = argv[i+1];
		} else {
			throw usage(prog);
		}
	}
}

int main(int argc,char* argv[]) {
	try {
		std::string wf_fname,  // workflow filename
			    in_fname,  // input filename
			    out_fname; // output filename
		cmd_args(argc, argv, wf_fname, in_fname, out_fname);

		Parser p(wf_fname, in_fname, out_fname);
		Validator v;
		Executor e;

		Workflow w(p, v, e);
		w.parse();
		w.validate();
		w.execute();
	} catch (const char* e) {
		std::cerr << "Exception: " << e << std::endl;
		exit(1);
	} catch (const std::string& e) {
		std::cerr << "Exception: " << e << std::endl;
		exit(1);
	} catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
		exit(1);
	}
}
