/*
Potato Chat
Data Structures And Algorithms
End Semester Project
BESE-5B

Group Members:
Muhammad Ibtesam
Hamza Javed
*/
import java.util.*;

public class Graph {
	
    //For storing the edges
	public class Edge {
		public String start;
		public String end;
		int edge;
		//Constructor of Edges. Takes the edge vertices as the parameters
		public Edge(String s1, String s2){
		start=s1;
		end=s2;
		edge=1;
		}
	}
	
	public Vector<String> Vertices;
	public Vector <Edge> Edges;
	int adj_Matrix[][];
	int vertexCount;

        //graph constructor, initialises vertex count to 0
	public Graph(){
		vertexCount=0;
		
	}
	
        
	void Set(){
		for (int row = 0; row < vertexCount; row++)
			for (int col = 0; col < vertexCount; col++){
				adj_Matrix[row][col] = 0;
			}
	}

        //for adding vertex, takes username as parameter and adds it to Vertices vector
        void addVertex(String username)
	{
		Vertices.add(username);
		vertexCount++;
	}
	
        //returns the number of vertices
	public int getVerticesCount(){
		return vertexCount;
	}
	
        //adds edge to the Edges vector and takes the user name vertices as parameters
	public void addEdge(String user1, String user2){
		Edges.add(new Edge(user1,user2));
		//BuildAdjacencyMatrix(user1,user2);
	}
	

        //builds adjacency matrix, not used.
	private void BuildAdjacencyMatrix(String s1, String s2) {
		for (int row = 0; row < vertexCount; row++)
			for (int col = 0; col < vertexCount; col++){
				if(Vertices.get(row).equals(s1)&&Vertices.get(col).equals(s2))
				adj_Matrix[row][col] = 1;
			}
	}


        //Returns the number of edges
	public int getEdgeCount()
	{
		return Edges.size();
	}
	
        
        //for displaying the vertices, not used
	public void display()
	{
		for (int i = 0; i < vertexCount; i++)
		{
			System.out.println(Vertices.get(i)+ " ");
		}
		
		
		for (int i = 0; i < vertexCount; i++)
		{
			System.out.println(Vertices.get(i)+ " |");
		}
	}
	
        
        //for searching vertex.
	public String getVertex(String s){
			for(int i=0;i<vertexCount;i++)
				if(Vertices.get(i)==s)
					return Vertices.get(i);

				else{
					System.out.println("Trying to access non-existant vertex");
					return null;
				}
			return null;
	}
        
        /*
        Does the Breadth First Traversal.
        Takes the user, with respect to who we're traversing as a parameter
        */
          
        ArrayList BFS(String r){

            Vector<Node> n = new Vector<Node>();
            ArrayList<Integer> distArray = new ArrayList();


            Node root = null;
            for (int i = 0; i < vertexCount; i++)
            {
                n.add(new Node(Vertices.elementAt(i),null,-1));


                if (n.elementAt(i).user.equals(r))
                    root = n.elementAt(i);
            
            }

            Queue<Node> Q = new ArrayDeque<Node>();

            if (root==null){
                    return null;
            }

            root.distance = 0;
            Q.add(root);

            while (!Q.isEmpty()){
                    Node current = Q.poll();

                for (int i = 0; i < vertexCount; i++){
                    if(GetDistance(current.user,i,n.elementAt(i).user)!=0){
                            if (n.elementAt(i).distance == -1){
                            n.elementAt(i).distance = current.distance + 1;
                            n.elementAt(i).parent = current.user;
                            System.out.println(current.user);
                            Q.add(n.elementAt(i));
                        }
                    }
                }
            }
            for (int i = 0; i < vertexCount; i++)
            {
                    System.out.println(n.elementAt(i).user+ "   "+ n.elementAt(i).distance);
                    distArray.add(n.elementAt(i).distance);
            }
            return distArray;
    }

        /*
        Returns distance between two vertices. Takes the vertices as parameters
        */
        private int GetDistance(String user,int i, String user2) {
            for(int j=0;j<Edges.size();j++){
                if(Edges.elementAt(j).start.equals(user) && Edges.elementAt(j).end.equals(user2)
                    ||(Edges.elementAt(j).start.equals(user2) && Edges.elementAt(j).end.equals(user)))
                            
                        return Edges.elementAt(j).edge;
            }
            return 0;
    }



        //node, as in, each vertex
    public class Node {
            public String user;
            public String parent;
            public int distance;

            public Node(){
                    distance=-1;
            }
            public Node(String s, String u,int x){
                    user=s;
                    parent=u;
                    distance=x;
            }
	}

    //graph main for testing, not used in actual program
	public Graph myGraph;
	public static void main(String[] args) {
		Graph myGraph=new Graph();
		myGraph.Vertices=new Vector<String>();
		myGraph.Edges=new Vector<Edge>();
		myGraph.adj_Matrix=new int[10][10];
	
		System.out.println( "Testing graph ...\n");
		System.out.println( "Use hard-coded graph (y/n)? ");

		char choice='Y';

		if (choice == 'Y' || choice == 'y')
		{
			myGraph.addVertex("User1");
			myGraph.addVertex("User2");
			myGraph.addVertex("User3");
			myGraph.addVertex("User4");
			myGraph.addVertex("User5");
			myGraph.addVertex("User6");
			
			myGraph.Set();
			myGraph.addEdge("User1","User2");
			myGraph.addEdge("User1","User3");
			myGraph.addEdge("User1","User4");
			myGraph.addEdge("User1","User5");
			myGraph.addEdge("User2","User3");
			myGraph.addEdge("User3","User4");
			myGraph.addEdge("User3","User5");
			myGraph.addEdge("User4","User5");
			myGraph.addEdge("User4","User6");
			myGraph.addEdge("User5","User6");
		}

		
		System.out.println("\n");
		for (int i=0; i<6; i++){
			System.out.println( "Starting vertex: "+ myGraph.Vertices.get(i));

			System.out.println( "Breadth-First Traversal:\n");
			myGraph.BFS(myGraph.Vertices.elementAt(i));
			
                }
	}
	
	
}