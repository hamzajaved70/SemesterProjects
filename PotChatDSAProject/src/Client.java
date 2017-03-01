/*
Potato Chat
Data Structures And Algorithms
End Semester Project
BESE-5B
Group Members:
Muhammad Ibtesam
Hamza Javed
*/

import java.io.*;
import java.net.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

// This clas is used for adding friends
public class Client extends JFrame{
	
    private JTextField userText;
    private JTextArea chatWindow;
    private ObjectOutputStream output;
    private ObjectInputStream input;
    private String message = "";
    private String serverIP;
    private Socket connection;

    /*
    Constructor
    It takes a String parameter which is actually the IP address of the server.
    */
    public Client(String host){
        setTitle("Client");
        serverIP = host;
        userText = new JTextField();
        userText.setEditable(false);
        userText.addActionListener(
                        new ActionListener(){
                                public void actionPerformed(ActionEvent event){
                                        sendMessage(event.getActionCommand());
                                        userText.setText("");
                                }
                        }
        );


        add(userText, BorderLayout.NORTH);

        chatWindow = new JTextArea();

        add(new JScrollPane(chatWindow),BorderLayout.CENTER);

        setSize(300,150);

        setVisible(true);
    }

    //Starts running the server
    public void startRunning(){
        try{
                connectToServer();
                setupStreams();
                whileChatting();
        }catch(EOFException eofException){
                showMessage("\n Client terminated connection!");
        }catch(IOException ioException){
                ioException.printStackTrace();
        }finally{
                closeCrap();
        }
    }

    //Connects to Server, gets the serverIP and converts it into an address with a port number 6789
    private void connectToServer() throws IOException{
            showMessage("Attempting connection...\n");
            connection = new Socket(InetAddress.getByName(serverIP),6789);
            showMessage("Connected to " + connection.getInetAddress().getHostName());

    }

    /*
    In this function, we setup the inputStream and outputStream.
    The inputstreams are the streams that the client accepts from the server.
    The outputstreams are the streams that the server accepts from the user.
    That is the outputstreams go away from the user.
    */
    private void setupStreams() throws IOException{
            output = new ObjectOutputStream(connection.getOutputStream());
            output.flush();
            input = new ObjectInputStream(connection.getInputStream());
            showMessage("\n Streams are setup\n");
    }

    /*
    This method is a loop and it continuously accepts messages from the server
    */
    private void whileChatting() throws IOException{
        ableToType(true);
        do{
            try{
                    message = (String) input.readObject();
                    showMessage("\n" + message);
            }catch(ClassNotFoundException classNotFoundException){
                    showMessage("\n I dont know that object type \n");
            }
        }while(!message.equals("SERVER - END"));
    }

    //This closes down all the sockets etc.
    public void closeCrap(){
        showMessage("\n closing crap down...");
        ableToType(false);
        try{
                output.close();
                input.close();
                connection.close();
        }catch(IOException ioException){
                ioException.printStackTrace();
        }

    }

    //This method is used for sending a message through the outputstreams to the server.
    //It takes a string parameter which is the message to be sent
    private void sendMessage(String message){
        try{
            output.writeObject("CLIENT - " + message);
            output.flush();
            showMessage("\nCLIENT - " + message);
        }catch(IOException ioException){
            chatWindow.append("\n something messed up while sending message!");
        }
    }

    //This method is for showing the message at the client side.
    //it takes a string parameter and appends it in the Client side chatwindow
    private void showMessage(final String message){
        SwingUtilities.invokeLater(
            new Runnable(){
                public void run(){
                    chatWindow.append(message);
                }
            }
        );
    }

    //This method basically allows the user to be able to type.
    //it does this by setting the setEditable as either true or false.
    private void ableToType(final boolean TorF){
        SwingUtilities.invokeLater(
            new Runnable(){
                public void run(){
                    userText.setEditable(TorF);
                }
            }
        );
    }

    //main function
    public static void main(String[] args) {
            Client threadClient;
            threadClient = new Client("127.0.0.1");
            threadClient.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            threadClient.startRunning();

    }


}
