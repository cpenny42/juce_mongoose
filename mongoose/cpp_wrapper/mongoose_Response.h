
/**
 * A response to a request
 */
namespace Mongoose
{
    class Response 
    {
        public:
            Response();
            virtual ~Response();

            /**
             * Test if the given header is present
             *
             * @param string the header key
             *
             * @return bool true if the header is set
             */
            virtual bool hasHeader(std::string key);

            /**
             * Sets the header
             *
             * @param key the header key
             *
             * @param value the header value
             */
            virtual void setHeader(std::string key, std::string value);

            /**
             * Get the data of the response, this will contain headers and
             * body
             *
             * @return string the response data
             */
            virtual std::string getData();

            /**
             * Gets the response body
             *
             * @return string the response body
             */
            virtual std::string getBody()=0;

            /**
             * Sets the cookie, note that you can only define one cookie by request
             * for now
             *
             * @param string the key of the cookie
             * @param string value the cookie value
             */
            virtual void setCookie(std::string key, std::string value);

            /**
             * Sets the response code
             */
            virtual void setCode(int code);

        protected:
            int code;
            std::map<std::string, std::string> headers;
    };
}

