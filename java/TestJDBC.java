// javac TestJDBC.java
// java -classpath .:lib TestJDBC    (in MS-DOS)

import java.sql.DriverManager;
import java.sql.Connection;
import java.sql.SQLException;

import java.sql.Statement;
import java.sql.ResultSet;
import java.sql.PreparedStatement;
import java.sql.DatabaseMetaData;


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


		 String pStatStr = "SELECT * FROM Books WHERE Price <> ? ";
		 PreparedStatement pStat = conn.prepareStatement(pStatStr);
		 pStat.setDouble(1, 63.00);
		 ResultSet rsPS = pStat.executeQuery();
		 System.out.println("*************PreparedStatement**********");
		 while(rsPS.next())
		     {
			 System.out.println(rsPS.getString(1));
		     }

		 DatabaseMetaData dbMeta = conn.getMetaData();
		 System.out.println("DB URL: " + dbMeta.getURL());
		 
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
