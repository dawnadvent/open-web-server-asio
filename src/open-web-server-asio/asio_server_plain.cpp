#include "asio_server_plain.h"

//constructor. Starts the server and begins accepting connections
AsioServerPlain::AsioServerPlain(io_service &io_service, short port) :
    AsioServerBase(io_service, port)
{
    //disable naggle algorithm
    ip::tcp::no_delay no_delay_option_(true);
    acceptor_.set_option(no_delay_option_);

    //create a client session object where we will handle the communication with the client.
    ClientSessionPlain *new_session = new ClientSessionPlain(this->io_service_);

    //When a new client connects, call AsioServer::handle_accept accept
    //so that we can accept the new client and begin communicating with him.
    //Notice that we pass the new_session object we created.
    acceptor_.async_accept(new_session->socket(),
                           boost::bind(&AsioServerPlain::handle_accept, this, new_session,
                           boost::asio::placeholders::error));

    //m_acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true))
}

AsioServerPlain::~AsioServerPlain()
{

}

//async callback: called each time a new client connects
void AsioServerPlain::handle_accept(ClientSessionPlain* new_session, const boost::system::error_code& error)
{
    if (!error) {
        //if there is no error the client is accepted.

        //disable the naggle algorithm
        ip::tcp::no_delay no_delay_option_(true);
        new_session->socket().set_option(no_delay_option_);


        //**** starts recieving data inside the client session object.
        new_session->start();
        //****

        //Create a new client session for the next client
        //when it will connect, and provide the callback function to accept the connection.
        new_session = new ClientSessionPlain(this->io_service_); //= new ClientSession(io_service_);

        //When a new client connects, call AsioServer::handle_accept accept
        //so that we can accept the new client and begin communicating with him.
        //Notice that we pass the new_session object we created.
        acceptor_.async_accept(new_session->socket(),
                               boost::bind(&AsioServerPlain::handle_accept, this, new_session,
                               boost::asio::placeholders::error));

    } else {
        //if there is an error on accept delete the client session.
        delete new_session;
    }
}
