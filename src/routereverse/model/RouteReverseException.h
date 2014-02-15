
#include <stdexcept>

#ifndef ROUTEREVERSE_ROUTEREVERSEEXCEPTION_H
#define ROUTEREVERSE_ROUTEREVERSEEXCEPTION_H




namespace Tww {
namespace RouteReverse {

    /**
    * A exception class. This exception is help full to give more information
    * in the Browser. Tntnet catch this exception and return the error message
    * in the browser.
    */
    class RouteReverseException : public std::runtime_error
    {
        public:

            /**
             * @err_message This message is show in the browser.
             */
            explicit RouteReverseException( const std::string& err_message )
                : std::runtime_error( err_message ){}
    };

} // end namespace RouteReverse
} // namespace Tww

#endif
