// javac TestStream.java
// java TestStream

import java.nio.charset.Charset;
import java.util.Set;
import java.util.Map;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.FileReader;
import java.io.InputStreamReader;

import java.io.FileOutputStream;
import java.io.OutputStreamWriter;

import java.io.PrintWriter;


import java.nio.charset.Charset;
import java.nio.ByteBuffer;
import java.nio.CharBuffer;


import java.util.zip.ZipInputStream;
import java.util.zip.ZipEntry;

public class TestStream
{
    
    public static void main(String[] args)
    {
	System.out.println("TestStream main...");

	System.out.println(System.getProperty("line.separator"));

	System.out.println("name: " + Charset.defaultCharset().name());
	Set<String> charsetAliases = Charset.defaultCharset().aliases();

	System.out.println(charsetAliases.toString());

	// Map<String, Charset> charsetMap = Charset.availableCharsets();
	// for(Map.Entry<String, Charset> entry : charsetMap.entrySet())
	//     {
	// 	System.out.println(entry.toString());
	//     }

	try
	    {
		final int BUFFER_LENGTH = 1024;

		FileOutputStream fos = new FileOutputStream("filename.txt");
		OutputStreamWriter osr = new OutputStreamWriter(fos, "UTF-8");
		String str = new String("Test4Test");
		osr.write(str, 0, str.length());
		osr.flush();

		
		FileInputStream fis = new FileInputStream("filename.txt");
		System.out.println("available: " + fis.available());

		FileReader fr = new FileReader("filename.txt");
		char[] cs = new char[BUFFER_LENGTH];

		
		fr.read(cs);
		System.out.println("cs: " + cs);
		

		int byteTotal = fis.available();
		byte[] bs = new byte[byteTotal];
		fis.read(bs);
		System.out.println("bs: " + bs);

		InputStreamReader isr = new InputStreamReader(fis, "UTF-8");
		System.out.println("getEncoding: " + isr.getEncoding());
		char[] isrcs = new char[BUFFER_LENGTH]; 
		fr.read(isrcs, 0, BUFFER_LENGTH);
		// System.out.println("isrcs: " + isrcs);
		// System.out.print(isrcs);

		Charset chset = Charset.forName("UTF-8");
		ByteBuffer btBuf = ByteBuffer.wrap(bs, 0, bs.length);
		CharBuffer chBuf = chset.decode(btBuf);
		System.out.println("chBuf.toString: " + chBuf.toString());
		
		PrintWriter pw = new PrintWriter(System.out);
		pw.write(isrcs);


		ZipInputStream zipI = new ZipInputStream(new FileInputStream("Test.jar"));
		ZipEntry entry;
		while((entry = zipI.getNextEntry()) != null)
		    {
			System.out.println("entry.getName(): " + entry.getName());
			zipI.closeEntry();
			    
		    }
		zipI.close();
		
	    }
	catch(FileNotFoundException e) 
	    {
		System.out.println(e.toString());
	    }
	catch(IOException e)
	    {
		System.out.println(e.toString());
	    }
	finally
	    {
		// osr.close();
		// fis.close();
	    }


    }
}

