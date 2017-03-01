/*
Potato Chat
Data Structures And Algorithms
End Semester Project
BESE-5B

Group Members:
Muhammad Ibtesam
Hamza Javed
*/

import java.net.*;
import java.io.*;
import java.util.*;
import javax.swing.JFrame;
import javax.swing.SwingWorker;

public class ClientFrame extends javax.swing.JFrame 
{
    SuggestionScreen Suggested;
    FriendsList FriendsLIST;
    String username, address = "localhost", userName;
    List<String> users = new ArrayList();
    public static int port;
    Boolean isConnected = false;
    
    Socket sock;
    BufferedReader reader;
    PrintWriter writer;
    
    //--------------------------//
    
    public void ListenThread() 
    {
         Thread IncomingReader = new Thread(new IncomingReader());
         IncomingReader.start();
    }
    
    //--------------------------//
    
    //Whenever a user is connected, it is added to the user array list via this function
    //This function takes a string parameter which contains the user name
    public void userAdd(String data) 
    {
         users.add(data);
    }
    
    //--------------------------//
    
    /*
    When a user disconnects, a notification is shown to the client, which says that 
    the user is now offline.
    This method takes a string parameter which is the username
    */
    public void userRemove(String data) 
    {
         ta_chat.append(data + " is now offline.\n");
    }
    
    //--------------------------//
    
    //not used
    public void writeUsers() 
    {
         String[] tempList = new String[(users.size())];
         users.toArray(tempList);
         for (String token:tempList) 
         {
             //users.append(token + "\n");
         }
    }
    
    //--------------------------//
    
    //This is called when the client clicks the disconnect button.
    //it sends the disconnect token to the server 
    public void sendDisconnect() 
    {
        String bye = (username + ": :Disconnect");
        try
        {
            writer.println(bye); 
            writer.flush(); 
        } catch (Exception e) 
        {
            ta_chat.append("Could not send Disconnect message.\n");
        }
    }

    //--------------------------//
    /*
    Shows the message that you have disconnected, it also closes the socket
    */
    public void Disconnect() 
    {
        try 
        {
            ta_chat.append("Disconnected.\n");
            sock.close();
        } catch(Exception ex) {
            ta_chat.append("Failed to disconnect. \n");
        }
        isConnected = false;
        

    }
    
    /*
    Constructor, takes the port number as a parameter
    */
    public ClientFrame(int port_no) 
    {
        initComponents();
        port=port_no;
     
    }
    
    /*
    Another constructor, here you can also specify the username along with the port number
    */
    public ClientFrame(int port_no, String username) 
    {
        initComponents();
        port = port_no;
        userName = username;
    }
    
    //--------------------------//
    
    /*
    the incoming reader is the most important part.
    This is where the communication between Server and Client takes place.
    */
    public class IncomingReader implements Runnable
    {
        /*
        The messages from the server are split over the ":" here. There is a token at the end
        of the message which specifies what kind of message it is.
        */
        @Override
        public void run() 
        {
            FriendsLIST = new FriendsList();
            Suggested = new SuggestionScreen();
            String[] data;
            String stream, done = "Done", connect = "Connect", disconnect = "Disconnect", chat = "Chat",
                    prevMessages="OldMessages",interestSuggestion="LikeSuggest",
                    mutualSuggestion="MutualSuggest",listFriends="listFriends";

            try 
            {
                //while there is a message in the stream
                while ((stream = reader.readLine()) != null) 
                {
                     data = stream.split(":");

                     
                     if (data[2].equals(chat)) 
                     {
                        ta_chat.append(data[0] + ": " + data[1] + "\n");
                        
                        ta_chat.setCaretPosition(ta_chat.getDocument().getLength());
                     }
                     
                     else if (data[2].equals(connect))
                     {
                        ta_chat.removeAll();
                        userAdd(data[0]);
                     } 
                     else if (data[2].equals(disconnect)) 
                     {
                         userRemove(data[0]);
                     } 
                     else if (data[2].equals(done)) 
                     {                      
                        writeUsers();
                        users.clear();
                     }
                     else if (data[2].equals(listFriends)) 
                     {                      
                        if(data[0].equals(userName)){
                            FriendsLIST.setVisible(true);
                            FriendsLIST.showFriends(data[1]);
                        }
                     }
                     else if (data[2].equals(interestSuggestion)){
                        if(data[0].equals(userName)){
                                Suggested.setVisible(true);
                                Suggested.interestSuggestions(data[1]);
                        }
                     }
                     
                     else if (data[2].equals(mutualSuggestion)){
                        if(data[0].equals(userName)){
                                Suggested.setVisible(true);
                                Suggested.mutualSuggestions(data[1]);
                        }
                     }
                     else if (data[2].equals("Notify")){
                         
                         if(data[1].equals(userName)){
                             SwingWorker<Void,Void> BuddyChatter=new SwingWorker<Void,Void>(){
                                 @Override
                                 protected Void doInBackground() throws Exception {
                                     Client c1=new Client("127.0.0.1");
                                     c1.startRunning();
                                     c1.addWindowListener(new java.awt.event.WindowAdapter() {
                                         @Override
                                         public void windowClosing(java.awt.event.WindowEvent windowEvent) {
                                            c1.closeCrap();
                                            c1.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                                            done();
                                         }
                                     });
                                     return null;
                                 }
                                 
                                 protected void done(){
                                     System.out.println("Done");
                              
                                 }
                             };
                             BuddyChatter.execute();
                             
                         }
                     }  
                     
                     else if(data[2].equals("OldMessages")){
                         if(data[0].equals(username)){
                             ta_chat.append(data[1] + "\n");
                             ta_chat.setCaretPosition(ta_chat.getDocument().getLength());
                         }
                     }
                         

                
                }
           }catch(Exception ex) { }
        }
    }
    

    //--------------------------//
    
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        b_connect = new javax.swing.JButton();
        b_disconnect = new javax.swing.JButton();
        b_anonymous = new javax.swing.JButton();
        jScrollPane1 = new javax.swing.JScrollPane();
        ta_chat = new javax.swing.JTextArea();
        tf_chat = new javax.swing.JTextField();
        b_send = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("Chat - Client's frame");
        setName("client"); // NOI18N
        setResizable(false);

        b_connect.setText("Connect");
        b_connect.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                b_connectActionPerformed(evt);
            }
        });

        b_disconnect.setText("Disconnect");
        b_disconnect.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                b_disconnectActionPerformed(evt);
            }
        });

        b_anonymous.setText("Anonymous Login");
        b_anonymous.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                b_anonymousActionPerformed(evt);
            }
        });

        ta_chat.setColumns(20);
        ta_chat.setRows(5);
        jScrollPane1.setViewportView(ta_chat);

        tf_chat.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                tf_chatActionPerformed(evt);
            }
        });

        b_send.setText("SEND");
        b_send.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                b_sendActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addComponent(b_anonymous, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addGroup(javax.swing.GroupLayout.Alignment.LEADING, layout.createSequentialGroup()
                        .addComponent(tf_chat, javax.swing.GroupLayout.PREFERRED_SIZE, 352, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(b_send, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                    .addComponent(jScrollPane1, javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(javax.swing.GroupLayout.Alignment.LEADING, layout.createSequentialGroup()
                        .addComponent(b_connect, javax.swing.GroupLayout.PREFERRED_SIZE, 230, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(5, 5, 5)
                        .addComponent(b_disconnect, javax.swing.GroupLayout.PREFERRED_SIZE, 234, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(0, 0, Short.MAX_VALUE)))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(b_anonymous)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(b_connect)
                    .addComponent(b_disconnect))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 310, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(tf_chat)
                    .addComponent(b_send, javax.swing.GroupLayout.DEFAULT_SIZE, 31, Short.MAX_VALUE))
                .addGap(22, 22, 22))
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    /*
    For connecting automatically.
    It connects with the server without pressing the "Connect" button.
    
    */
    public void connectAuto(){
        if (isConnected == false) 
        {
            username = userName;
            

            try 
            {
                sock = new Socket(address, port);
                InputStreamReader streamreader = new InputStreamReader(sock.getInputStream());
                reader = new BufferedReader(streamreader);
                writer = new PrintWriter(sock.getOutputStream());
                writer.println(username + ":has connected.:Connect");
                writer.flush(); 
                isConnected = true; 
            } 
            catch (Exception ex) 
            {
                ta_chat.append("Cannot Connect! Try Again. \n");
                
            }
            
            ListenThread();
            
        } else if (isConnected == true) 
        {
            ta_chat.append("You are already connected. \n");
        }
    }
    
    //for connecting with button
    private void b_connectActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_b_connectActionPerformed
        if (isConnected == false) 
        {
            username = userName;
            

            try 
            {
                sock = new Socket(address, port);
                InputStreamReader streamreader = new InputStreamReader(sock.getInputStream());
                reader = new BufferedReader(streamreader);
                writer = new PrintWriter(sock.getOutputStream());
                writer.println(username + ":has connected.:Connect");
                writer.flush(); 
                isConnected = true; 
            } 
            catch (Exception ex) 
            {
                ta_chat.append("Cannot Connect! Try Again. \n");
                
            }
            
            ListenThread();
            
        } else if (isConnected == true) 
        {
            ta_chat.append("You are already connected. \n");
        }
    }//GEN-LAST:event_b_connectActionPerformed

    private void b_disconnectActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_b_disconnectActionPerformed
        sendDisconnect();
        Disconnect();
    }//GEN-LAST:event_b_disconnectActionPerformed

    //connects as anonymous user
    private void b_anonymousActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_b_anonymousActionPerformed
        
        if (isConnected == false) 
        {
            String anon="anon";
            Random generator = new Random(); 
            int i = generator.nextInt(999) + 1;
            String is=String.valueOf(i);
            anon=anon.concat(is);
            username=anon;
            
            

            try 
            {
                sock = new Socket(address, port);
                InputStreamReader streamreader = new InputStreamReader(sock.getInputStream());
                reader = new BufferedReader(streamreader);
                writer = new PrintWriter(sock.getOutputStream());
                writer.println(anon + ":has connected.:Connect");
                writer.flush(); 
                isConnected = true; 
            } 
            catch (Exception ex) 
            {
                ta_chat.append("Cannot Connect! Try Again. \n");
                
            }
            
            ListenThread();
            
        } else if (isConnected == true) 
        {
            ta_chat.append("You are already connected. \n");
        }        
    }//GEN-LAST:event_b_anonymousActionPerformed
    
    //Lists friends. Takes a string as a parameter. The string is the client user's name
    public void listFriends(String s){
        writer.println(s + ":" + "none" + ":listFriends");
        writer.flush();
    }
    
    /*
    Searches for friend in Server. Takes the name of the friend to be searched as
    a String parameter
    */
    public void searchFriend(String s){
        writer.println(username + ":" + s + ":Search");
        writer.flush();
    }
    
    /*
    Notifies for message. Takes the name of the friend to be searched as
    a String parameter
    */
    public void notifyMessage(String s){   
            
               writer.println(username+":"+ s + ":Message");
               writer.flush(); // flushes the buffer
    }
    
    /*
    Takes suggestions from server
    */
    public void initiateSuggestions(){
        writer.println(username+":something"+":Suggest");
    }
    
    /*
    Takes all the mutual friends from server
    */
    public void getFriends(){
        writer.println(username+":something"+":Mutual");
    }
    
    /*
    Sends likes dislikes to server for comparison with other user.
    Takes ArrayList parameters of Likes and Dislikes
    */
    public void LikesDislikesSender(ArrayList<String> Likes,ArrayList<String> Dislikes){
        for(int i=0;i<Likes.size();i++){
            //System.out.println(username+":"+ Likes.get(i) + ":Likes");
            writer.println(username+":"+ Likes.get(i) + ":Likes");
            writer.flush(); // flushes the buffer
        }
        for(int i=0;i<Dislikes.size();i++){
            writer.println(username+":"+ Dislikes.get(i) + ":Dislikes");
            writer.flush(); // flushes the buffer
        }
    }
    
    /*
    For sending the main chat message
    */
    private void b_sendActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_b_sendActionPerformed
        String nothing = "";
        if ((tf_chat.getText()).equals(nothing)) {
            tf_chat.setText("");
            tf_chat.requestFocus();
        } else {
            try {
               writer.println(username + ":" + tf_chat.getText() + ":" + "Chat");
               writer.flush(); // flushes the buffer
            } catch (Exception ex) {
                ta_chat.append("Message was not sent. \n");
            }
            tf_chat.setText("");
            tf_chat.requestFocus();
        }

        tf_chat.setText("");
        tf_chat.requestFocus();
    }//GEN-LAST:event_b_sendActionPerformed

    private void tf_chatActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_tf_chatActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_tf_chatActionPerformed

    //main
    public static void main(String args[]) 
    {
        java.awt.EventQueue.invokeLater(new Runnable() 
        {
            @Override
            public void run() 
            {
                new ClientFrame(port).setVisible(true);
            }
        });
    }
    
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton b_anonymous;
    private javax.swing.JButton b_connect;
    private javax.swing.JButton b_disconnect;
    private javax.swing.JButton b_send;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JTextArea ta_chat;
    private javax.swing.JTextField tf_chat;
    // End of variables declaration//GEN-END:variables
}
