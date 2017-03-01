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
import java.util.*;
import java.util.ArrayList;


public class ServerFrame extends javax.swing.JFrame 
{
   ArrayList<Integer> distArray;
   ArrayList<Integer> friendDistArray;   //send back to user
   Graph friendGraph;
   Queue<String> PrevMessages;
   ArrayList clientOutputStreams;
   ArrayList<String> users;
   ArrayList<User> USERS;
   User singleUser;
   
   

   public class ClientHandler implements Runnable	
   {
       BufferedReader reader;
       Socket sock;
       PrintWriter client;
       
   
       /*
       Constructor for client handler,
       Takes information of client socket.
       */
       public ClientHandler(Socket clientSocket, PrintWriter user) 
       {
            client = user;
            try 
            {
                sock = clientSocket;
                InputStreamReader isReader = new InputStreamReader(sock.getInputStream());
                reader = new BufferedReader(isReader);
            }
            catch (Exception ex) 
            {
                ta_chat.append("Unexpected error... \n");
            }

       }
       
       /*
       This is where the client and server communicate
       Token Based Communication
       */
       @Override
       public void run() 
       {
            String message, connect = "Connect", disconnect = "Disconnect", chat = "Chat" 
                    ,notifyMessage="Message", likes="Likes",dislikes="Dislikes",
                    suggest="Suggest",mutual="Mutual",search="Search",listFriends="listFriends";
         
            String[] data;

            try 
            {
                while ((message = reader.readLine()) != null) 
                {
                    ta_chat.append("Received: " + message + "\n");
                    data = message.split(":");
                    
                    for (String token:data) 
                    {
                        ta_chat.append(token + "\n");
                    }

                    if (data[2].equals(connect)) 
                    {
                        tellEveryone((data[0] + ":" + data[1] + ":" + chat));
                        userAdd(data[0]);
                        singleUser=new User(data[0]);
                        for(Iterator it = PrevMessages.iterator();it.hasNext();)  {
                            tellUser(data[0],it.next().toString());
                        }
                    } 
                    else if (data[2].equals(disconnect)) 
                    {
                        tellEveryone((data[0] + ":has disconnected." + ":" + chat));
                        userRemove(data[0]);
                    } 
                    else if (data[2].equals(chat)) 
                    {
                        if(PrevMessages.size()<6){
                            PrevMessages.add(data[0]+"; "+data[1]);
                        }
                        
                        else if(PrevMessages.size()>5){
                            PrevMessages.poll();
                            PrevMessages.add(data[0]+"; "+data[1]);
                        }
                        
                        tellEveryone(message);
                    } 
                    else if (data[2].equals(notifyMessage)){
                        Notify(data[0],data[1]);
                        
                    }
                    else if (data[2].equals(listFriends)){
                        listofFriends(data[0]);            
           
                    }
                    else if (data[2].equals(likes)){
                        singleUser.Likes.add(data[1]);
                        
                        for(int i=0;i<USERS.size();i++){
                            if(USERS.get(i).name.equals(data[0])){
                                USERS.get(i).Likes.add(data[1]);
                            }
                        }
                    }
                    
                    else if (data[2].equals(dislikes)){
                        singleUser.Dislikes.add(data[0]); 
                        
                        for(int i=0;i<USERS.size();i++){
                            if(USERS.get(i).name.equals(data[0])){
                                USERS.get(i).Dislikes.add(data[1]);
                            }
                        }
                    }
                    else if (data[2].equals(suggest)){
                        suggestFriendsInterests(data[0]);
                        
                    }
                    
                    else if (data[2].equals(mutual)){
                        suggestFriendsMutual(data[0]);   
                    }
                    else if (data[2].equals(search)){
                        searchFriend(data[1],data[0]);
                    }
                    else 
                    {
                        ta_chat.append("No Conditions were met. \n");
                    }
                } 
             } 
             catch (Exception ex) 
             {
                ta_chat.append("Lost a connection. \n");
                ex.printStackTrace();
                clientOutputStreams.remove(client);
             } 
	} 
    }
   
   //function for displaying list of friends
   //takes the username as argument
    public void listofFriends(String s){
       friendDistArray = new ArrayList();
       friendDistArray = friendGraph.BFS(s);
       for(int i = 0;i < friendDistArray.size(); i++){
            System.out.println(friendGraph.Vertices.get(i)+"  -  "+friendDistArray.get(i));
            
            if(friendDistArray.get(i) == 1){
                tellEveryone(s+":"+friendGraph.Vertices.get(i)+":listFriends");
            }
        }
   } 
   
   public ArrayList<Float> similarityLevel;
   
   //function for suggesting mutual friends
   //takes the username to be suggested to as function argument
   public void suggestFriendsMutual(String suggestTo){
        distArray =new ArrayList();
        distArray = friendGraph.BFS(suggestTo);
        for(int i = 0;i < distArray.size(); i++){
            System.out.println(friendGraph.Vertices.get(i)+"  -  "+distArray.get(i));
            
            if(distArray.get(i) == 2){
                tellEveryone(suggestTo+":"+friendGraph.Vertices.get(i)+":MutualSuggest");
            }
        }
        
   }
   
    //suggests friends based on Likes/Dislikes
   //Takes user to be suggested to as function argument
    public void suggestFriendsInterests(String suggestTo){
        similarityLevel=new ArrayList<Float>();
        int max1=0,max2=0,max3=0;
       
        for (int i=0;i<USERS.size();i++){
           float similarityValue;
           
            float L1nL2=0,D1nD2=0,L1nD2=0,L2nD1=0;
            float L1UL2UD1UD2=singleUser.Likes.size()+singleUser.Dislikes.size()
                   +USERS.get(i).Likes.size()+USERS.get(i).Dislikes.size();
           
            if(!USERS.get(i).name.equals(suggestTo)){
               
                for(int j=0;j<singleUser.Likes.size();j++){
                   
                    for(int k=0;k<USERS.get(i).Likes.size();k++){
                       
                        if(j<singleUser.Likes.size() && k<USERS.get(i).Likes.size())
                        if(USERS.get(i).Likes.get(k).equals(singleUser.Likes.get(j))){
                           L1nL2++;
                           L1UL2UD1UD2--;
                       }
                        if(j<singleUser.Dislikes.size() && k<USERS.get(i).Dislikes.size())
                        if(USERS.get(i).Dislikes.get(k).equals(singleUser.Dislikes.get(j))){
                           D1nD2++;
                           L1UL2UD1UD2--;
                        }
                       
                        if(j<singleUser.Dislikes.size() && k<USERS.get(i).Likes.size())
                        if(USERS.get(i).Likes.get(k).equals(singleUser.Dislikes.get(j))){
                           L1nD2++;
                           L1UL2UD1UD2--;
                        }
                       
                       
                        if(j<singleUser.Likes.size() && k<USERS.get(i).Dislikes.size())
                        if(USERS.get(i).Dislikes.get(k).equals(singleUser.Likes.get(j))){
                           L2nD1++;
                           L1UL2UD1UD2--;
                        }
                    }
                }
               
                similarityValue=(L1nL2+D1nD2-L1nD2-L2nD1)/L1UL2UD1UD2;
                similarityLevel.add(similarityValue);
               
            }
        }
       float maximum1=-1,maximum2=-1,maximum3=-1;
       max1=1;max2=2;max3=3;
       for (int i=0;i<similarityLevel.size();i++){
           if(similarityLevel.get(i)>maximum1){
               maximum3=maximum2;
               max3=max2;
               maximum2=maximum1;
               max2=max1;
               maximum1=similarityLevel.get(i);
               max1=i;
           }
           
           else if(similarityLevel.get(i)>maximum2){
               maximum3=maximum2;
               max3=max2;
               maximum2=similarityLevel.get(i);
               max2=i;
           }
           else if(similarityLevel.get(i)>maximum3){
               maximum3=similarityLevel.get(i);
               max3=i;
               
           }
        }
       
       for (int i=0;i<similarityLevel.size();i++){
           System.out.println("User"+i+"  -  "+similarityLevel.get(i));
       }
       
       tellEveryone(suggestTo+":"+USERS.get(max1).name+":LikeSuggest");
       tellEveryone(suggestTo+":"+USERS.get(max2).name+":LikeSuggest");
       tellEveryone(suggestTo+":"+USERS.get(max3).name+":LikeSuggest");
   }
   
    //for loading users for like dislike comparison
   public void LoadUsers(){
       USERS=new ArrayList<User>();
       ArrayList<String> LIKEDA=new ArrayList(Arrays.asList("Anime","Manga","TV Serials","Food")); 
       ArrayList<String> LIKEDB=new ArrayList(Arrays.asList("Movies","Arsenal","Acting","Singing"));
       ArrayList<String> LIKEDC=new ArrayList(Arrays.asList("Music","Marvel","DC","Science"));
       ArrayList<String> LIKEDD=new ArrayList(Arrays.asList("Programming","Comics","Sherlock","Cats"));
       ArrayList<String> LIKEDE=new ArrayList(Arrays.asList("Anime","Supernatural","Demons","Food"));
       ArrayList<String> LIKEDF=new ArrayList(Arrays.asList("Anime","Football","Arsenal","Suits"));
       ArrayList<String> LIKEDG=new ArrayList(Arrays.asList("Drawing","Manga","Marvel","Food")); 
       ArrayList<String> LIKEDH=new ArrayList(Arrays.asList("Culture","Tea","Oprah","Food"));
       ArrayList<String> LIKEDI=new ArrayList(Arrays.asList("Japan","Travelling","Reading","Sherlock"));
       ArrayList<String> LIKEDJ=new ArrayList(Arrays.asList("Suits","Sherlock","Supernatural","Demons"));
       ArrayList<String> LIKEDK=new ArrayList(Arrays.asList("DC","Manga","Marvel","Cats"));
       ArrayList<String> LIKEDL=new ArrayList(Arrays.asList("Anime","Manga","Comics","Sherlock"));
       
       ArrayList<String> DISLIKEDA= new ArrayList(Arrays.asList("Movies","Arsenal","Acting","Singing")); 
       ArrayList<String> DISLIKEDB= new ArrayList(Arrays.asList("Music","Marvel","DC","Science"));
       ArrayList<String> DISLIKEDC= new ArrayList(Arrays.asList("Programming","Comics","Sherlock","Cats"));
       ArrayList<String> DISLIKEDD= new ArrayList(Arrays.asList("Drawing","Manga","Marvel","Food"));
       ArrayList<String> DISLIKEDE= new ArrayList(Arrays.asList("Japan","Travelling","Reading","Sherlock"));
       ArrayList<String> DISLIKEDF= new ArrayList(Arrays.asList("DC","Manga","Marvel","Cats"));
       ArrayList<String> DISLIKEDG= new ArrayList(Arrays.asList("Anime","Supernatural","Demons","Tea")); 
       ArrayList<String> DISLIKEDH= new ArrayList(Arrays.asList("DC","Manga","Marvel","Cats"));
       ArrayList<String> DISLIKEDI= new ArrayList(Arrays.asList("Suits","Football","Supernatural","Demons"));
       ArrayList<String> DISLIKEDJ= new ArrayList(Arrays.asList("Music","Tea","Anime","Anime"));
       ArrayList<String> DISLIKEDK= new ArrayList(Arrays.asList("Tea","Suits","Football","Demons"));
       ArrayList<String> DISLIKEDL= new ArrayList(Arrays.asList("Tea","Suits","Football","Demons"));
     
       USERS.add(new User("UserA",LIKEDA,DISLIKEDA));
       USERS.add(new User("UserB",LIKEDB,DISLIKEDB));
       USERS.add(new User("UserC",LIKEDC,DISLIKEDC));
       USERS.add(new User("UserD",LIKEDD,DISLIKEDD));
       USERS.add(new User("UserE",LIKEDE,DISLIKEDE));
       USERS.add(new User("UserF",LIKEDF,DISLIKEDF));
       USERS.add(new User("UserG",LIKEDG,DISLIKEDG));
       USERS.add(new User("UserH",LIKEDH,DISLIKEDH));
       USERS.add(new User("UserI",LIKEDI,DISLIKEDI));
       USERS.add(new User("UserJ",LIKEDJ,DISLIKEDJ));
       USERS.add(new User("UserK",LIKEDK,DISLIKEDK));
       USERS.add(new User("UserL",LIKEDL,DISLIKEDL));
       
       for (int i=0;i<12;i++){
           for (int j=0;j<4;j++)
           System.out.println(USERS.get(i).name+" - "+USERS.get(i).Likes.get(j)+" - "
                   +USERS.get(i).Dislikes.get(j));
       }
   }
   
   public void LoadGraph(){
       
        friendGraph=new Graph();
        friendGraph.Vertices=new Vector<String>();
        friendGraph.Edges=new Vector<Graph.Edge>();
	friendGraph.adj_Matrix=new int[10][10];
  
        friendGraph.addVertex("User1");
        friendGraph.addVertex("User2");
        friendGraph.addVertex("User3");
        friendGraph.addVertex("User4");
        friendGraph.addVertex("User5");
        friendGraph.addVertex("User6");
        friendGraph.addVertex("User7");


        friendGraph.Set();
        friendGraph.addEdge("User1","User2");
        friendGraph.addEdge("User1","User3");
        friendGraph.addEdge("User1","User4");
        friendGraph.addEdge("User1","User5");
        friendGraph.addEdge("User2","User3");
        friendGraph.addEdge("User3","User4");
        friendGraph.addEdge("User3","User5");
        friendGraph.addEdge("User4","User5");
        friendGraph.addEdge("User4","User6");
        friendGraph.addEdge("User5","User6");
        friendGraph.addEdge("User4","User7");

   }
   
   //for sending old messages to user
   public void tellUser(String name,String oldMessages){
       tellEveryone(name+":"+oldMessages+":OldMessages");
   }
   
   //for notifying user for message request
   public void Notify(String Sender, String Receiver){
       tellEveryone(Sender+":"+Receiver+":"+"Notify");
   }
   
   //for sending friends list
   public void sendFriendList(String toSend, String friend){
       tellEveryone(toSend+":"+friend+":listFriends");
   }

   //function for searching for a friend and adding him to "Addto" username
   public void searchFriend(String s, String addTo){
       boolean found = false;
       int i;
       for(i = 0; i < friendGraph.Vertices.size(); i++){
           if(friendGraph.Vertices.get(i).equals(s)){
               found = true;
               System.out.println("\nFound");
               break;
           }
       }
       if(found){
           System.out.println("is added!");
           friendGraph.addEdge(addTo,s);
       }
       else {
           System.out.println("\n Not found.");
       }
   }
   
   //constructor
    public ServerFrame() 
    {
        initComponents();
        LoadUsers();
        LoadGraph();
        
    }

    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jScrollPane1 = new javax.swing.JScrollPane();
        ta_chat = new javax.swing.JTextArea();
        b_start = new javax.swing.JButton();
        b_end = new javax.swing.JButton();
        b_users = new javax.swing.JButton();
        b_clear = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("Chat - Server's frame");
        setName("server"); // NOI18N
        setResizable(false);

        ta_chat.setColumns(20);
        ta_chat.setRows(5);
        jScrollPane1.setViewportView(ta_chat);

        b_start.setText("START");
        b_start.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                b_startActionPerformed(evt);
            }
        });

        b_end.setText("END");
        b_end.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                b_endActionPerformed(evt);
            }
        });

        b_users.setText("Online Users");
        b_users.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                b_usersActionPerformed(evt);
            }
        });

        b_clear.setText("Clear");
        b_clear.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                b_clearActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jScrollPane1)
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                            .addComponent(b_end, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addComponent(b_start, javax.swing.GroupLayout.DEFAULT_SIZE, 75, Short.MAX_VALUE))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 291, Short.MAX_VALUE)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                            .addComponent(b_clear, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addComponent(b_users, javax.swing.GroupLayout.DEFAULT_SIZE, 103, Short.MAX_VALUE))))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jScrollPane1, javax.swing.GroupLayout.DEFAULT_SIZE, 340, Short.MAX_VALUE)
                .addGap(18, 18, 18)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(b_start)
                    .addComponent(b_users))
                .addGap(18, 18, 18)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(b_clear)
                    .addComponent(b_end))
                .addGap(20, 20, 20))
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void b_endActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_b_endActionPerformed
        try 
        {
            Thread.sleep(5000);                 //5000 milliseconds is five second.
        } 
        catch(InterruptedException ex) {Thread.currentThread().interrupt();}
        
        tellEveryone("Server:is stopping and all users will be disconnected.\n:Chat");
        ta_chat.append("Server stopping... \n");
        
        ta_chat.setText("");
    }//GEN-LAST:event_b_endActionPerformed

    private void b_startActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_b_startActionPerformed
        Thread starter = new Thread(new ServerStart());
        starter.start();
        
        ta_chat.append("Server started...\n");
    }//GEN-LAST:event_b_startActionPerformed

    private void b_usersActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_b_usersActionPerformed
        ta_chat.append("\n Online users : \n");
        for (String current_user : users)
        {
            ta_chat.append(current_user);
            ta_chat.append("\n");
        }    
        
    }//GEN-LAST:event_b_usersActionPerformed

    private void b_clearActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_b_clearActionPerformed
        ta_chat.setText("");
    }//GEN-LAST:event_b_clearActionPerformed

    public static void main(String args[]) 
    {
        java.awt.EventQueue.invokeLater(new Runnable() 
        {
            @Override
            public void run() {
                new ServerFrame().setVisible(true);
            }
        });
    }
    
    public class ServerStart implements Runnable 
    {
        @Override
        public void run() 
        {
            PrevMessages=new ArrayDeque<String>();
            clientOutputStreams = new ArrayList();
            users = new ArrayList();  
            

            try 
            {
                ServerSocket serverSock = new ServerSocket(5555);

                while (true) 
                {
				Socket clientSock = serverSock.accept();
				PrintWriter writer = new PrintWriter(clientSock.getOutputStream());
				clientOutputStreams.add(writer);

				Thread listener = new Thread(new ClientHandler(clientSock, writer));
				listener.start();
				ta_chat.append("Got a connection. \n");
                }
            }
            catch (Exception ex)
            {
                ta_chat.append("Error making a connection. \n");
            }
        }
    }
    
    //function called when a user connects
    //adds user to user arraylist as well as other places where user is used
    public void userAdd (String data) 
    {
        String message, add = ": :Connect", done = "Server: :Done", name = data;
        ta_chat.append("Before " + name + " added. \n");
        users.add(name);
        USERS.add(new User(name));
        boolean found=false;
        for (int i=0; i<friendGraph.Vertices.size();i++){
            if(friendGraph.Vertices.get(i).equals(name))
                found=true;
        }
        
        if(!found){
            friendGraph.addVertex(name);
        }
        
        ta_chat.append("After " + name + " added. \n");
        String[] tempList = new String[(users.size())];
        users.toArray(tempList);

        for (String token:tempList) 
        {
            message = (token + add);
            tellEveryone(message);
        }
        tellEveryone(done);
    }
    
    //called when a user disconnects, disconnects user and removes name from arrayList
    public void userRemove (String data) 
    {
        String message, add = ": :Connect", done = "Server: :Done", name = data;
        users.remove(name);
        String[] tempList = new String[(users.size())];
        users.toArray(tempList);

        for (String token:tempList) 
        {
            message = (token + add);
            tellEveryone(message);
        }
        tellEveryone(done);
    }
    
    //function for sending "message" to all users
    public void tellEveryone(String message) 
    {
	Iterator it = clientOutputStreams.iterator();

        while (it.hasNext()) 
        {
            try 
            {
                PrintWriter writer = (PrintWriter) it.next();
		writer.println(message);
		ta_chat.append("Sending: " + message + "\n");
                writer.flush();
                ta_chat.setCaretPosition(ta_chat.getDocument().getLength());

            } 
            catch (Exception ex) 
            {
		ta_chat.append("Error telling everyone. \n");
            }
        } 
    }
    
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton b_clear;
    private javax.swing.JButton b_end;
    private javax.swing.JButton b_start;
    private javax.swing.JButton b_users;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JTextArea ta_chat;
    // End of variables declaration//GEN-END:variables
}
