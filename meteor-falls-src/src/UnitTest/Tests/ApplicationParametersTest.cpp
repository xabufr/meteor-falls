#include "../UnitTest.h"
#include "Application/applicationparameters.h"
#include "Utils/Exception/BasicException.h"
#include "Application/parameterparserexception.h"

BOOST_AUTO_TEST_CASE(ApplicationParametersTest)
{
    /*BOOST_CHECK_NO_THROW(
    ApplicationParameters app(std::vector<std::string>({"--gui", "n", "--help"}))
    )
    BOOST_CHECK_THROW(
    ApplicationParameters app(std::vector<std::string>({"--gui", "y", "--help", "y","--netconsole", "y"}))
    , BasicException)

    BOOST_CHECK_THROW(
    ApplicationParameters app(std::vector<std::string>({"--gui", "y", "--help", "y","--netconsole", "y", "d"}))
    , BasicException)

    BOOST_CHECK_THROW(
    ApplicationParameters app(std::vector<std::string>({"--gui", "y", "--help","--netconsole", "y", "--unknowArgument"}))
    , ParameterParserException)

    BOOST_CHECK_THROW(
    ApplicationParameters app(std::vector<std::string>({"--gui", "y", "--help","--netconsole", "y", "-unknowArgument"}))
    , ParameterParserException)

    ApplicationParameters app(std::vector<std::string>({"--gui", "n", "--help","--netconsole", "y"}));
    ApplicationParametersKeys &key = app.getKeys();
    BOOST_CHECK(key["help"]=="y");
    BOOST_CHECK(key["netconsole"]=="y");
    BOOST_CHECK(key["gui"]=="n"); */
}
