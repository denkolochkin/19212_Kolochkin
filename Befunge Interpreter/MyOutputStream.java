package ru.nsu.kolochkin.Befunge;

import java.io.OutputStream;
import java.util.List;

public class MyOutputStream extends OutputStream {

	List<Character> buffer;

	public MyOutputStream(List<Character> buffer) { this.buffer = buffer; }

	public List<Character> getBuffer() { return buffer; }
	/**
	 * These methods add symbol (Character
	 * or int) in the buffer.
	 */
	@Override
	public void write(int b) { buffer.add((char) b); }

	public void write(Character c) { buffer.add(c); }
	/**
	 * These methods print symbol
	 * (Character or int).
	 */
	public void print(int c) { System.out.print(c); }

	public void print(Character c) { System.out.print(c); }

}
