#include "applicationparameters.h"
#include "parameterparserexception.h"
#include "../Utils/Exception/BasicException.h"
#include <iostream>
#include <argp.h>
#define OPT_ABORT  1            /* --abort */

const char *argp_program_version     = "Meteor-Falls v0.1";
const char *argp_program_bug_address = "none@epsi.fr";
ApplicationParameters::ApplicationParameters(int argc, char** argv)
{
		static char doc[] =
				       "Meteor-falls, le jeu\
							     \v tout droit réservé";
		static char args_doc[] = "";
		static argp_option options[] = {
        	{"server", 's', 0, 0, "Démarre le server"},
			{ 0 }
		};
		static argp argp_s = {
        	options, ApplicationParameters::parse_opt, args_doc, doc
		};
		argp_parse(&argp_s, argc, argv, 0, 0, &parametres);
}
ApplicationParameters::ApplicationParameters(std::vector<std::string> args)
{
}

ApplicationParameters::~ApplicationParameters()
{

}
error_t ApplicationParameters::parse_opt(int key, char *arg, argp_state *state)
{
	Parameters *params = static_cast<Parameters*>(state->input);
	switch(key)
	{
		case 's':
            params->server=true;
			break;
	}
	return 0;
}

