//javac -cp  /home/abc/Documents/apache-log4j-1.2.17/log4j-1.2.17.jar:. testlog4j_1_x.java

//javac -cp  /home/abc/Documents/apache-log4j-1.2.17/log4j-1.2.17.jar;. testlog4j_1_x.java

//java -cp  /home/abc/Documents/apache-log4j-1.2.17/log4j-1.2.17.jar:. testlog4j_1_x

//java -cp  /home/abc/Documents/apache-log4j-1.2.17/log4j-1.2.17.jar;. testlog4j_1_x

import org.apache.log4j.Logger;
import org.apache.log4j.Level;
import org.apache.log4j.BasicConfigurator;
import org.apache.log4j.PropertyConfigurator;


import java.util.Map;
import java.util.HashMap;
    
public class testlog4j_1_x
{
    public static void main(String args[])
    {
	System.out.println("args.length(): " + args.length);

	org.apache.log4j.Logger logger = org.apache.log4j.Logger.getLogger("module");

	BasicConfigurator.configure();

	//PropertyConfigurator.configure("testlog4j_1_x.properties");
	
	logger.setLevel(Level.INFO);
	

	logger.info("info test");
	logger.debug("debug test");

	MyLogger.Instance().info("module1", "VLogger info test");
    }
}


class VLogger
{
    private static VLogger _instance = null;
    private static Map<String, Logger> VLoggers = new HashMap<String, Logger>();    
    
    public static VLogger Instance()
    {
	if(null == _instance)
	    {
		_instance = new VLogger();
	    }

	return _instance;
    }

    private VLogger()
    {
	Map<String, Logger> tempLoggers;
	String[] loggerModules = new String[2];
	loggerModules[0] = "module1";
	loggerModules[1] = "module2";
	
	for(String loggerModule : loggerModules)
	    {
		//tempLoggers.put(loggerModule, Logger.getLogger(loggerModule));
		VLoggers.put(loggerModule, Logger.getLogger(loggerModule));
	    }
	
	// VLoggers.putAll();
    } 


    public static void debug(String moduleName, String message)
    {
	if(VLoggers.get(moduleName).isDebugEnabled())
	    {
		VLoggers.get(moduleName).debug(message);
	    }
    }

    public static void info(String moduleName, String message)
    {
	if(VLoggers.get(moduleName).isInfoEnabled())
	    {
		VLoggers.get(moduleName).info(message);
	    }
    }


    public static void warn(String moduleName, String message)
    {
	
	VLoggers.get(moduleName).warn(message);
	
    }


    public static void error(String moduleName, String message)
    {
	
	VLoggers.get(moduleName).error(message);
	
    }


    public static void fatal(String moduleName, String message)
    {
	VLoggers.get(moduleName).fatal(message);
	
    }

    

}

