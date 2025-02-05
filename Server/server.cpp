#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "Message.h"
using namespace std;

#define MAX_NUM_MESSAGES 20
#define MAX_MESSAGE_LENGTH 80
#define DEFAULT_PORT 5514

//Joanna Mijares
//Ex8

//CITATIONS:
//Ex8 Discussion Video: https://www.youtube.com/watch?v=vNHNcdpWImo
//more citations throughout code :-)

class ServerWall{

private:
    int maxMessages;
    vector<string> messages;
public:
    ServerWall(int maxMessages = 20) : maxMessages(maxMessages){}

    void updateMessages(int max){
        //delete first item in wall
        //CITE: https://stackoverflow.com/questions/56184930/c-popping-the-first-element-of-a-vector
        if(messages.size() > max){
                messages.erase(messages.begin());
        }

    }

    void addMessage(const string& message){
        //add msg to wall
        messages.push_back(message);

    }

    void clearWall(int client){
        //send message to client wall is clear
        send(client, CLEAR_MESSAGE, strlen(CLEAR_MESSAGE), 0);

        messages.clear();   
        //clear wall
    }

    string getWallContents() const {

        string header = WALL_HEADER;
        string fullContent;

        if(messages.empty()){
            fullContent = EMPTY_MESSAGE;
        }else{
            for(const auto& message : messages){
                fullContent += message + "\n";
            }
        }
        cout<<endl;
        return header + fullContent;
    }

//CITE: https://stackoverflow.com/questions/5590381/how-to-convert-int-to-string-in-c
//CITE: https://www.geeksforgeeks.org/socket-programming-in-cpp/
    void postMessage(int client){
        //send prompt to client, ask for name
        send(client, NAME_PROMPT, strlen(NAME_PROMPT), 0);
        //recieve name from client + store
        char name[1000] = {0};
        int n = read(client, name, sizeof(name)-1);

        //dont include the newline
        string nameStr = string(name);

        //make sure name is empty/ wont carry over 
        memset(name, 0, sizeof(name));

        while(nameStr.back() == '\n'){
            if(nameStr.back() == '\n'){
                nameStr.pop_back();
            }
        }


        int maxLength = 78 - nameStr.length();
        string maxLengthStr = to_string(maxLength);

        int length = nameStr.length();

        //subtract name of client from max -2
        //ask for message content of certain length
        send(client, POST_PROMPT1, strlen(POST_PROMPT1), 0);
        send(client, maxLengthStr.c_str(), maxLengthStr.length(), 0);
        send(client, POST_PROMPT2, strlen(POST_PROMPT2), 0);

        if(nameStr.length()>=78 || (n-1) >= 78){
            send(client, "\n", strlen("\n"), 0);
            send(client, ERROR_MESSAGE, strlen(ERROR_MESSAGE), 0);
            return;
        }

        char message[1000] = {0};
        int k = read(client, message, sizeof(message)-1);

        string messageNoNewline = string(message);

        //make sure message is empty/ wont carry over to command
        memset(message, 0, sizeof(message));

        while(messageNoNewline.back() == '\n'){
            if(messageNoNewline.back() == '\n'){
                messageNoNewline.pop_back();
            }
        }

        string mssg = nameStr + ": " + messageNoNewline;

        if(messageNoNewline.length() > maxLength || (k-1)>maxLength){
            mssg.clear();
            send(client, ERROR_MESSAGE, strlen(ERROR_MESSAGE), 0);
            return;
        }else if(messageNoNewline.length() <= maxLength){
            addMessage(mssg);
            send(client, SUCCESS_MESSAGE, strlen(SUCCESS_MESSAGE), 0);
        }

        //recieve from client + store
        //if message > length, send error
        //otherwise, add message to wall + success reply
        //after exceeding queue, delete first message
    }

    void quit(int client){
        //quit message to client
        send(client, QUIT_MESSAGE, strlen(QUIT_MESSAGE), 0);
        close(client);
        //DONT CLOSE SERVER
    }

    void kill(int server, int client){
        //closes server + client
        send(client, KILL_MESSAGE, strlen(KILL_MESSAGE), 0);
        close(client);
        cout<<"Closing server... bye!"<<endl;
        close(server);
        exit(1);
    }

};

int main(int argc, char** argv){
    int maxNumMessages = 20;
    int port = 5514;

    if(argc >= 2){
        maxNumMessages = atoi(argv[1]);
    }
    if(argc>=3){
        port = atoi(argv[2]);
    }

    if(maxNumMessages <= 0){
        cerr << "Error: Max number of messages must be positive." << endl;
        exit(1);
    }

    ServerWall server(maxNumMessages);

    //socket

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    //CITE: https://www.geeksforgeeks.org/socket-programming-in-cpp/
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    //configure addr
    //bind socket to IP + Port (bind())
    bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    
    cout<<"Wall server running on port "<<port<<" with queue size "<<maxNumMessages<<"."<<endl;
    
    //listen for connections (listen())
    listen(serverSocket, maxNumMessages);

    //accept conn and handle
    while(true){
        //client conn w/ accept()
        //CITE: https://www.geeksforgeeks.org/socket-programming-cc/
        socklen_t addressL = sizeof(serverAddr);
        int clientSocket = accept(serverSocket, (struct sockaddr*)&serverAddr, &addressL);

        cout<<"Connected to client"<<endl;

        while(true){

            //send wall contents to client
            server.updateMessages(maxNumMessages);
            string wallContents = server.getWallContents();
            send(clientSocket, wallContents.c_str(), wallContents.length(), 0);

            //recieve command
            //CITE: https://www.geeksforgeeks.org/socket-programming-in-cpp/
            char comm[500];

            //make sure comm is empty
            memset(comm, '\0', sizeof(comm));

            send(clientSocket, "\n", strlen("\n"), 0);
            send(clientSocket, COMMAND_PROMPT, strlen(COMMAND_PROMPT), 0);

            int n = read(clientSocket, comm, 500);

            string command = string(comm);
            
            //this little while loop fixed my whole code lol
            while(command.back() == '\n'){
                if(command.back() == '\n'){
                    command.pop_back();
                }
            }

            memset(comm, '\0', sizeof(comm));

            //https://www.youtube.com/watch?v=Ts8eXOkx8TE&list=PLPyaR5G9aNDvs6TtdpLcVO43_jvxp4emI&index=5
            if(n <= 0){
                break;
            }

            if(command == "quit"){
                cout<<"Client quit"<<endl;
                server.quit(clientSocket);
            }else if(command == "clear"){
                cout<<"Cleared wall"<<endl;
                server.clearWall(clientSocket);
            }else if(command == "kill"){
                server.kill(serverSocket, clientSocket);
            }else if(command == "post"){
                cout<<"Awaiting post"<<endl;
                server.postMessage(clientSocket);
            }else{
                send(clientSocket, "Invalid command. Try again.\n", strlen("Invalid command. Try again.\n"), 0);
                send(clientSocket, "\n", strlen("\n"), 0);
            }

        }

        close(clientSocket);
    }

    close(serverSocket);
    return 0;

}
