#ifndef APPLICATIONPARAMETERS_H
#define APPLICATIONPARAMETERS_H

#include <unordered_map>
#include <string>
#include <vector>
#include <argp.h>

struct Parameters
{
	bool gui, server, verbose;
	bool server_wan;
	Parameters()
	{
		server  = false;
		verbose = false;
	}
};
class ApplicationParameters
{
    public:
        ApplicationParameters(int argc, char **argv);
        ApplicationParameters(std::vector<std::string> args);
        virtual ~ApplicationParameters();
		Parameters parametres;
		static error_t parse_opt(int key, char *arg, argp_state *state);
};

#endif // APPLICATIONPARAMETERS_H
