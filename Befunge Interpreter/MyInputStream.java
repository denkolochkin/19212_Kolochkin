package ru.nsu.kolochkin.Befunge;

import org.apache.log4j.Logger;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;

public class MyInputStream extends InputStream {

	Logger log = Logger.getLogger(Interpreter.class.getName());

	private List<Character> buffer = new ArrayList<>();

	public List<Character> getBuffer() { return buffer; }
	/**
	 * This method reads symbol
	 * from console and adds it
	 * in the buffer.
	 */
	@Override
	public int read() {
		 try {
			 int a = System.in.read();
			 buffer.add((char) a);
			 log.trace("Read was successful.");
		 } catch (IOException e) {
			 log.error("Read error.", e);
		 	e.printStackTrace();
		 }
		return 0;
	}
}
