
#include <stdexcept>

#ifndef CORE_TNTWEBWIZARDEXCEPTION_H
#define CORE_TNTWEBWIZARDEXCEPTION_H




namespace Tww {
namespace Core {

    /**
    * A exception class. This exception is help full to give more information
    * in the Browser. Tntnet catch this exception and return the error message
    * in the browser.
    */
    class TntWebWizardException : public std::runtime_error
    {
        public:

            /**
             * @err_message This message is show in the browser.
             */
            explicit TntWebWizardException( const std::string& err_message )
                : std::runtime_error( err_message ){}
    };

} // end namespace Core
} // namespace Tww

#endif
