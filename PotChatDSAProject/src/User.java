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
import java.util.*;

public class User {
    public String name;
    public ArrayList<String> Likes;
    public ArrayList<String> Dislikes;
    
    
    public User(String s){
        name=s;
        Likes=new ArrayList<String>();
        Dislikes=new ArrayList<String>();
    }
    
    public User(String s, ArrayList<String> l, ArrayList<String> d){
        name=s;
        Likes=new ArrayList<String>();
        Dislikes=new ArrayList<String>();
        
        Likes.addAll(l);
        
        Dislikes.addAll(d);
    }
    
    //sets likes
    public void setLikes(ArrayList<String> l){
        Likes.addAll(l);
    }
    
    //sets dislikes
    public void setDislikes(ArrayList<String> d){
        Dislikes.addAll(d);
    }
}
