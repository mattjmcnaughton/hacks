"""
The test dispatcher will dispatch tests against any registered test runners when
the repo observer sends it a 'dispatch' message with the commit ID to be used.
It will store results when the test runners have completed running the tests and
send back the results in a 'results' message.

It can register as many test runners as you like.
"""

import argparse
import SocketServer

class ThreadingTCPServer(SocketServer.ThreadingMixIn, SocketServer.TCPServer):
    pass
    # TODO

class DispatcherHandler(SocketServer.BaseRequestHandler):
    pass
    # TODO

def serve():
    parser = argparse.ArgumentParser()
    parser.add_argument('--host',
                        help="dispatcher's host, by defaultlocalhost it users localhost",
                        default="localhost",
                        action="store")
    parser.add_argument('--port',
                        help="dispatcher's port, by default it uses 8888",
                        default=8888,
                        action="store")
    args = parser.parse_args()

    # Create the server
    server = ThreadingTCPServer((args.host, int(args.port)), DispatcherHandler)

    # TODO


if __name__ == "__main__":
    serve()
