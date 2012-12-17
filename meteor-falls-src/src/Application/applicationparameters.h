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
	std::string server_name, server_map;
	unsigned short server_max_client;
	Parameters()
	{
		server  		  = false;
		verbose 		  = false;
		server_max_client = 64;
		server_name       = "Default server name";
		server_map        = "test";
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
