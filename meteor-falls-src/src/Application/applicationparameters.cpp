#include "applicationparameters.h"
#include "parameterparserexception.h"
#include "../Utils/Exception/BasicException.h"
#include "../precompiled/lexical_cast.h"
#include <iostream>
#include <argp.h>
#define OPT_ABORT  1            /* --abort */

const char *argp_program_version     = "Meteor-Falls v0.1";
const char *argp_program_bug_address = "none@epsi.fr";
ApplicationParameters::ApplicationParameters(int argc, char** argv)
{
    static char doc[] =
                    "Meteor-falls, le jeu\
                    \vtout droit réservé";
                    static char args_doc[] = "";
    static argp_option options[] = {
            {"server-lan", 1, 0, 0, "Démarre le server lan"},
            {"server-wan", 2, 0, 0, "Démarre le server wan"},
            {"server-name", 3, "NAME", 0, "Nom du serveur"},
            {"server-map", 4, "MAPNAME", 0, "Nom de la carte" },
            {"server-max-clients", 5, "MAXCLIENTS", 0, "Maximum de clients autorisés sur ce serveur"},
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
    case 1:
        params->server=true;
        params->server_wan=false;
        break;
    case 2:
        params->server=true;
        params->server_wan=true;
        break;
    case 3:
        params->server_name = arg;
        break;
    case 4:
        params->server_map = arg;
        break;
    case 5:
        params->server_max_client = boost::lexical_cast<unsigned short>(arg);
        break;
    }
    return 0;
}
