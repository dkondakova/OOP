#include "workflow.h"

void Workflow::parse() {
	workers = parser.get_workers();
	program = parser.get_program();
}

void Workflow::validate() {
	validator.validate_workers(workers);
	validator.validate_program(workers, program);
}
	
void Workflow::execute() {
	executor.execute(workers, program);
}
