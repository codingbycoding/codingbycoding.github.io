// javac TestJDBC.java
// java -classpath .:lib TestJDBC    (in MS-DOS)

import java.sql.DriverManager;
import java.sql.Connection;
import java.sql.SQLException;

import java.sql.Statement;
import java.sql.ResultSet;

public class TestJDBC 
{

    
    public static void main(String[] args)
    {
	String url = new String("jdbc:mysql://localhost:3306/Books");
	String user = "root";
	String password = "root";
	String queryStr = "SELECT * FROM Books";
	
	try
	    {
		Class.forName("com.mysql.jdbc.Driver");
	    }
	catch(ClassNotFoundException e)
	    {
		e.printStackTrace();
	    }



	Connection conn = null;
	Statement state = null;
	ResultSet rs = null;
	
	try
	    {
		 conn = DriverManager.getConnection(url, user, password);
		 state = conn.createStatement();
		 rs = state.executeQuery(queryStr);

		 if(rs.next())
		     {
			 System.out.println(rs.getString(1));
		     }
	    }
	catch(SQLException e)
	    {
		e.printStackTrace();
	    }
	finally
	    {
		if(rs != null)
		    {
			try
			    {
				rs.close();
			    }
			catch(SQLException e)
			    {
				
			    }
		    }

		if(state != null)
		    {
			try
			    {
				state.close();
			    }
			catch(SQLException e)
			    {
						
			    }
		    }

		if(conn != null)
		    {
			try
			    
			    {
				conn.close();
			    }
			catch(SQLException e)
			    {
			    }
		    }





	    }

	
	
    } 
}
