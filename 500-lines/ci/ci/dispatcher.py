"""
The test dispatcher will dispatch tests against any registered test runners when
the repo observer sends it a 'dispatch' message with the commit ID to be used.
It will store results when the test runners have completed running the tests and
send back the results in a 'results' message.

It can register as many test runners as you like.
"""

import argparse
import re
import os
import socket
import socketserver
import time
import threading

import helpers

def dispatch_tests(server, commit_id):
    # In practice, this method will normally not run forever.
    while True:
        print("Trying to dispatch to runners")
        for runner in server.runners:
            response = helpers.communicate(runner["host"],
                    int(runner["port"]), "runtest:%s" % commit_id)

            if response == "OK":
                print("adding id %s" % commit_id)
                server.dispatched_commits[commit_id] = runner
                if commit_id in server.pending_commits:
                    server.pending_commits.remove(commit_id)
                return

        time.sleep(2)

class ThreadingTCPServer(socketserver.ThreadingMixIn, socketserver.TCPServer):
    runners = [] # Keeps track of test runner pool
    dead = False # Indicate to other threads that we are no longer running
    dispatched_commits = {} # Keeps track of commits we've dispatched
    pending_commits = [] # Keep track of commits that we've yet to dispatch


class DispatcherHandler(socketserver.BaseRequestHandler):
    """
    The RequestHandler class for our dispatcher. This will dispatch test runners
    against the incoming commit and handle their requests and test results.

    https://docs.python.org/3.7/library/socketserver.html#socketserver.BaseRequestHandler
    """
    command_re = re.compile(r"(\w+)(:.+)*")
    BUF_SIZE = 1024

    def handle(self):
        # self.request is the TCP socket connected to the client.
        self.data = self.request.recv(self.BUF_SIZE).strip().decode()
        command_groups = self.command_re.match(self.data)

        if not command_groups:
            self.request.sendall(b"Invalid command")
            return
        command = command_groups.group(1)

        if command == "status":
            print("in status")
            self.request.sendall(b"OK")

        elif command == "register":
            # Add the test runner to the pool
            print("register")
            address = command_groups.group(2)
            host, port = re.findall(r":(\w*)", address)
            runner = {"host": host, "port": int(port)}
            self.server.runners.append(runner)
            self.request.sendall(b"OK")

        elif command == "dispatch":
            print("going to dispatch")
            commit_id = command_groups.group(2)[1:]
            if not self.server.runners:
                self.request.sendall(b"No runners are registered")
            else:
                self.request.sendall(b"OK")
                dispatch_tests(self.server, commit_id)

        elif command == "results":
            print("got test results")
            results = command_groups.group(2)[1:]
            results = results.split(":")
            commit_id = results[0]
            length_msg = int(results[1])
            # 3 is the bumber of ":" in the sent command
            remaining_buffer = self.BUF_SIZE - (len(command) + len(commit_id) + len(results[1]) + 3)
            if length_msg > remaining_buffer:
                self.data += self.request.recv(length_msg - remaining_buffer).strip()
            del self.server.dispatched_commits[commit_id]
            if not os.path.exists("test_results"):
                os.makedirs("test_results")
            with open("test_results/%s" % commit_id, "w") as f:
                data = self.data.split(":")[3:]
                data = "\n".join(data)
                f.write(data)
            self.request.sendall(b"OK")
        else:
            self.request.sendall(b"Invalid command")


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
    print("serving on %s:%s" % (args.host, int(args.port)))

    # Create a thread to check the runner pool
    def runner_checker(server):
        # Manages the commit lists when a runner fails
        def manage_commit_lists(runner):
            for commit, assigned_runner in server.dispatched_commits.items():
                if assigned_runner == runner:
                    del server.dispatched_commits[commit]
                    server.pending_commits.append(commit)
                    break
            server.runners.remove(runner)

        while not server.dead:
            time.sleep(1)
            for runner in server.runners:
                s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                try:
                    response = helpers.communicate(runner["host"],
                            int(runner["port"]), "ping")
                    if response != "pong":
                        print("Removing runner %s" % runner)
                        manage_commit_lists(runner)
                except socket.error as e:
                    manage_commit_lists(runner)

    # Create a thread to kick off tests that failed
    def redistribute(server):
        while not server.dead:
            for commit in server.pending_commits:
                print("running redistribute")
                print(server.pending_commits)
                dispatch_tests(server, commit)
                time.sleep(5)

    runner_heartbeat = threading.Thread(target=runner_checker, args=(server,))
    redistributor = threading.Thread(target=redistribute, args=(server,))

    try:
        runner_heartbeat.start()
        redistributor.start()

        # Activate the server; it'll run until the program is interrupted.
        server.serve_forever()
    except (KeyboardInterrupt, Exception):
        # If any exception, kill all threads.
        server.dead = True
        runner_heartbeat.join()
        redistributor.join()


if __name__ == "__main__":
    serve()
