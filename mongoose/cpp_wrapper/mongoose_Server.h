
/**
 * Wrapper for the Mongoose server
 */
namespace Mongoose
{
    class Server
    {
        public:
            /**
             * Constructs the server
             *
             * @param int the number of the port to listen to
             * @param std::string documentRoot the root that should be used for static files
             */
            Server(int port = 80, const char *documentRoot = "www");
            virtual ~Server();

            /**
             * Runs the Mongoose server
             */
            void start();

            /**
             * Stops the Mongoose server
             */
            void stop();

            /**
             * Register a new controller on the server
             *
             * @param Controller* a pointer to a controller
             */
            void registerController(Controller *);

            /**
             * Internally used to process a request
             *
             * @param struct mg_connection* the mongoose connection
             */
            int _handleRequest(struct mg_connection *conn);

            /**
             * Internally used to process a file upload
             *
             * @param struct mg_connection* the mongoose conneciton
             * @param const char * the name of the uploaded file
             */
            void _upload(struct mg_connection *conn, const char *fileName);

            /**
             * Handles a web socket connection
             *
             * @param struct mg_connection* the mongoose connection with the client
             */
            void _webSocketReady(struct mg_connection *conn);

            /**
             * Handles web sockets data
             *
             * @param struct mg_connection* the mongoose connection
             * @param int flags the data flags
             * @param char* the data
             * @param size the data size
             *
             * @return int if we have to keep the connection opened
             */
            int _webSocketData(struct mg_connection *conn, std::string data);

            /**
             * Process the request by controllers
             *
             * @param Request the request
             *
             * @return Response the response if one of the controllers can handle it,
             *         NULL else
             */
            Response *handleRequest(Request &request);

            /**
             * Sets a mongoose extra option
             *
             * @param std::string the name of the option
             * @param std::string the value of the option
             */
            void setOption(std::string key, std::string value);

#ifndef NO_WEBSOCKET
            /**
             * Returns the WebSockets container
             *
             * @return WebSockets the web sockets container
             */
            WebSockets &getWebSockets();
#endif

            /**
             * Print statistics
             */
            void printStats();

            /**
             * Polls the server
             */
            void poll();

            /**
             * Does the server handles url?
             */
            bool handles(std::string method, std::string url);

        protected:
            volatile bool stopped;
            volatile bool destroyed;
            Sessions sessions;
            Mutex mutex;
            std::map<std::string, std::string> optionsMap;
            std::map<struct mg_connection*, Request *> currentRequests;
            struct mg_server *server;

#ifndef NO_WEBSOCKET
            WebSockets websockets;
#endif

            std::vector<Controller *> controllers;

            // Statistics
            int requests;
            int startTime;
    };
}
